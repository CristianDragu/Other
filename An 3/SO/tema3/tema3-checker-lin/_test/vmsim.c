/*Dragu Cristian*/

#include <stdio.h>
#include <stdlib.h>
#include "vmsim.h"
#include "common.h"
#include "helpers.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

data_set *data = NULL;
int data_length, data_max_length = 1;

/**
 * Functie ce ofera protectie de write unei pagini
 */
void set_prot_write(struct page_table_entry *page, int pos)
{
	int ret;

	ret = mprotect(page->start, p_sz, PROT_READ | PROT_WRITE);
	if (ret == -1)
		return;
	page->dirty = TRUE;
	page->protection = PROTECTION_WRITE;
	page->state = STATE_IN_RAM;
}

/**
 * Functie ce seteaza protectia de read a unei pagini
 */
void set_prot_read(struct page_table_entry *page, int pos)
{
	char *array;
	char *p_ret;
	int ret;

	array = malloc(p_sz);
	memset(array, 0, p_sz);
	if (!array)
		return;

	/*daca e in swap, salvez continutul paginii*/
	if (page->state == STATE_IN_SWAP) {
		ret = mprotect(page->start, p_sz, PROT_READ | PROT_WRITE);
		if (ret == -1)
			return;
		memcpy(array, page->start, p_sz);
	}

	/*daca pagina nu a fost "alocata", atunci o demapez ca sa
		o mapez peste o pagină din RAM
	*/
	if (page->state == STATE_NOT_ALLOC) {
		ret = munmap(page->start, p_sz);
		if (ret == -1)
			return;
	}

	p_ret = mmap(page->start, p_sz,
					PROT_READ | PROT_WRITE,
					MAP_SHARED | MAP_FIXED,
					data[pos].map->ram_handle,
					data[pos].last_frame * p_sz);

	if (p_ret == (char *) -1)
		return;

	/*scriu continutul salvat. Daca era in swap avea date in ea,
		daca nu, e umpluta de zerouri
	*/
	w_set_file_pointer(data[pos].map->ram_handle,
						data[pos].last_frame * p_sz);
	w_write_file(data[pos].map->ram_handle, array, p_sz);

	free(array);

	/*ofer protectie de read*/
	ret = mprotect(page->start, p_sz, PROT_READ);
	if (ret == -1)
		return;

	page->prev_state = page->state;
	page->state = STATE_IN_RAM;
	page->protection = PROTECTION_READ;
	page->frame = &(data[pos].frames[data[pos].last_frame]);
	page->frame->index = data[pos].last_frame;
	page->frame->pte = page;
}

/**
 * Functie pentru aflarea offset-ului din cadrul tabelei de frame-uri
 * Daca last frame ajunge la dimensiunea num_frames, inseamna ca s-a
 * ocupat tot ram-ul si last_frame devine 0 ... eventual se va face
 * o trecere in swap a paginii care are indexul frame-ului la care
 * este mapata egal cu last_frame
 */
void increase_last_frame(int pos)
{
	if (data[pos].last_frame + 1 < data[pos].num_frames)
		data[pos].last_frame++;
	else {
		data[pos].ram_full = TRUE;
		data[pos].last_frame = 0;
	}
}

/**
 * Gaseste indexul paginii care este legata la un frame cu index-ul last_frame
 */
int page_for_swap_index(int pos)
{
	int i;

	for (i = 0; i < data[pos].num_pages; i++)
		if (data[pos].page_table[i].state == STATE_IN_RAM &&
			data[pos].page_table[i].frame->index ==
			data[pos].last_frame)
			return i;

	return -1;
}

/**
 * Functie pentru "mutarea" unei pagini din ram si maparea ei peste
 * o pagina din swap.
 */
void to_swap(int pos, int index_for_swap, struct page_table_entry *page)
{
	char *array1, *array2;
	int ret;
	w_ptr_t p_ret;

	array1 = malloc(p_sz);
	if (array1 == NULL)
		return;
	array2 = malloc(p_sz);
	if (array2 == NULL)
		return;

	memset(array1, 0, p_sz);
	if (!array1)
		return;

	/*salvez ce era scris in pagina*/
	ret = mprotect(page->start, p_sz, PROT_READ | PROT_WRITE);
	if (ret == -1)
		return;
	memcpy(array2, page->start, p_sz);

	/*umplu pagina fizica cu zerouri*/
	w_set_file_pointer(data[pos].map->ram_handle,
						data[pos].last_frame * p_sz);
	w_write_file(data[pos].map->ram_handle, array1, p_sz);

	ret = mprotect(page->start, p_sz, PROT_NONE);
	if (ret == -1)
		return;

	/*demapez pagina*/
	ret = munmap(page->start, p_sz);
	if (ret == -1)
		return;

	p_ret = mmap(page->start, p_sz,
				PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_FIXED,
				data[pos].map->swap_handle,
				index_for_swap * p_sz);
	if (p_ret == (char *) -1)
		return;

	if (page->dirty == TRUE) {
		ret = mprotect(page->start, p_sz, PROT_READ | PROT_WRITE);
		if (ret == -1)
			return;
	}

	/*scriu datele in noua pagina din swap*/
	w_set_file_pointer(data[pos].map->swap_handle, index_for_swap * p_sz);
	w_write_file(data[pos].map->swap_handle, array2, p_sz);

	ret = mprotect(page->start, p_sz, PROT_READ);
	if (ret == -1)
		return;

	page->prev_state = page->state;
	page->state = STATE_IN_SWAP;
	page->protection = PROTECTION_READ;
	page->dirty = TRUE;
	page->frame = NULL;

	free(array1);
	free(array2);
}

/**
 * Functie ce muta o pagina din swap in ram
 */
void from_swap(int pos, int index_for_swap,
						struct page_table_entry *page)
{
	char *array1, *array2;
	int ret;
	w_ptr_t p_ret;

	array1 = malloc(p_sz);
	if (array1 == NULL)
		return;
	array2 = malloc(p_sz);
	if (array2 == NULL)
		return;

	memset(array1, 0, p_sz);
	if (!array1)
		return;

	/*salvez ce era scris in pagina*/
	ret = mprotect(page->start, p_sz, PROT_READ | PROT_WRITE);
	if (ret == -1)
		return;
	memcpy(array2, page->start, p_sz);

	w_set_file_pointer(data[pos].map->swap_handle,
						index_for_swap * p_sz);
	w_write_file(data[pos].map->swap_handle, array1, p_sz);

	ret = mprotect(page->start, p_sz, PROT_NONE);
	if (ret == -1)
		return;

	/*demapez pagina*/
	ret = munmap(page->start, p_sz);
	if (ret == -1)
		return;

	/*remapez pagina peste o pagina din ram*/
	p_ret = mmap(page->start, p_sz,
				PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_FIXED,
				data[pos].map->ram_handle,
				data[pos].last_frame * p_sz);
	if (p_ret == (char *) -1)
		return;

	/*scriu in pagina datele salvate anterior si setez protectia de read*/
	w_set_file_pointer(data[pos].map->ram_handle,
						data[pos].last_frame * p_sz);
	w_write_file(data[pos].map->ram_handle, array2, p_sz);

	ret = mprotect(page->start, p_sz, PROT_READ);
	if (ret == -1)
		return;

	page->prev_state = page->state;
	page->state = STATE_IN_RAM;
	page->protection = PROTECTION_READ;
	page->dirty = FALSE;
	page->frame = &(data[pos].frames[data[pos].last_frame]);
	page->frame->index = data[pos].last_frame;
	page->frame->pte = page;
}

/**
 * Handler pentru exceptii.
 */
void sig_handler(int signum, siginfo_t *siginfo, void *aux)
{
	w_exception_handler_t prev_handler;

	/*Salvez adresa unde a aparut un fault.*/
	char *addr_page_fault = (char *)siginfo->si_addr;

	if (!w_get_previous_exception_handler(&prev_handler))
		return;

	if (signum != SIGSEGV) {
		prev_handler(signum, siginfo, aux);
		return;
	}

	int i, index_page_fault = -1, pos, index_for_swap;
	struct page_table_entry *page;

	/*Iterez prin vectorul data si caut pagina la care apare fault-ul*/
	for (i = 0; i < data_length; i++) {
		char *start = data[i].page_table[0].start;
		char *end = data[i].page_table[data[i].num_pages - 1].start
					+ p_sz;
		if (addr_page_fault - start >= 0 && end - addr_page_fault > 0) {
			index_page_fault = (addr_page_fault - start) / p_sz;
			pos = i;
			break;
		}
	}

	/*salvez pagina care a provocat fault-ul*/
	page = &(data[pos].page_table[index_page_fault]);

	switch (page->state) {
	/*daca pagina nu a fost "alocata", atunci trebuie sa o
		remapez cu protectie de read
	*/
	case STATE_NOT_ALLOC:
		if (data[pos].ram_full != TRUE) {
			set_prot_read(page, pos);
			increase_last_frame(pos);
		} else {
			/*daca au fost folosite toate frame-urile,
				trec o pagina in swap si o pun pe cea cu fault
				in locul ei
			*/
			index_for_swap = page_for_swap_index(pos);
			to_swap(pos, index_for_swap,
				&(data[pos].page_table[index_for_swap]));
			set_prot_read(page, pos);
			increase_last_frame(pos);
			return;
		}
		break;
	case STATE_IN_RAM:
		if (page->protection == PROTECTION_READ) {
			set_prot_write(page, pos);
			return;
		}
		if (page->protection == PROTECTION_NONE) {
			set_prot_read(page, pos);
			return;
		}
		return;
	case STATE_IN_SWAP:
		/*Pagina e in swap si trebuie sa o trec in ram*/
		index_for_swap = page_for_swap_index(pos);
		to_swap(pos, index_for_swap,
				&(data[pos].page_table[index_for_swap]));
		from_swap(pos, index_for_swap, page);
		increase_last_frame(pos);
		return;
	}
}

w_boolean_t vmsim_init(void)
{
	if (!w_set_exception_handler(sig_handler))
		return FALSE;
	return TRUE;
}

w_boolean_t vmsim_cleanup(void)
{
	w_exception_handler_t previous_handler;

	if (!w_get_previous_exception_handler(&previous_handler))
		return FALSE;

	if (!w_set_exception_handler(previous_handler))
		return FALSE;

	return TRUE;
}

/**
 * Functie pentru maparea paginilor si salvarea datelor necesare
 * procesarii ulterioare (tabele de pagini, num_pages, etc.)
 */
w_boolean_t vm_alloc(w_size_t num_pages, w_size_t num_frames,
				      vm_map_t *map)
{
	if (num_frames > num_pages || num_frames <= 0 || num_pages <= 0)
		return FALSE;

	w_handle_t ram_handle, swap_handle;
	int ret, i;
	char ram_name[] = "RAMXXXXXX", swap_name[] = "SWAPXXXXXX";
	w_ptr_t start;

	ram_handle = mkostemp(ram_name, O_CREAT | O_RDWR);
	if (ram_handle == -1)
		return FALSE;

	swap_handle = mkostemp(swap_name, O_CREAT | O_RDWR);
	if (swap_handle == -1)
		return FALSE;

	ret = ftruncate(ram_handle, num_frames * p_sz);
	if (ret != 0) {
		close(ram_handle);
		close(swap_handle);
		return FALSE;
	}
	ret = ftruncate(swap_handle, num_pages * p_sz);
	if (ret != 0) {
		close(ram_handle);
		close(swap_handle);
		return FALSE;
	}

	start = mmap(NULL, num_pages * p_sz,
						PROT_NONE,
						MAP_SHARED | MAP_ANONYMOUS,
						-1,
						0);

	if (start == (char *) -1) {
		close(ram_handle);
		close(swap_handle);
		return FALSE;
	}

	map->start = start;
	map->ram_handle = ram_handle;
	map->swap_handle = swap_handle;

	/*verific dimensiunea maxima a vectorului data. Daca e prea mica
		atunci realoc cu dimensiune dubla
	*/

	if (data_length + 1 <= data_max_length) {
		data = realloc(data, 2 * data_max_length * sizeof(data_set));
		data_max_length *= 2;
	}

	/*creez tabela de pagini*/

	struct page_table_entry *page_table;

	page_table = malloc(num_pages * sizeof(struct page_table_entry));
	if (page_table == NULL)
		return FALSE;

	for (i = 0; i < num_pages; i++) {
		struct page_table_entry page;

		page.state = STATE_NOT_ALLOC;
		page.prev_state = STATE_NOT_ALLOC;
		page.dirty = FALSE;
		page.protection = PROT_NONE;
		page.start = (char *)start + p_sz * i;
		page.frame = NULL;
		page_table[i] = page;
	}

	/*salvez toate datele necesare (tabela de pagini, tabela de frames,
		map si altele) in coada vectorului, apoi incrementez dimensiunea
		acestuia
	*/

	data[data_length].num_pages = num_pages;
	data[data_length].num_frames = num_frames;
	data[data_length].map = map;
	data[data_length].page_table = page_table;
	data[data_length].ram_full = FALSE;
	data[data_length].last_frame = 0;

	struct frame *frames;

	frames = malloc(num_frames * sizeof(struct frame));
	if (frames == NULL)
		return FALSE;

	for (i = 0; i < num_frames; i++) {
		struct frame frame;

		frame.index = i;
		frame.pte = NULL;
		frames[i] = frame;
	}

	data[data_length].frames = frames;

	data_length++;

	return TRUE;
}

/**
 * Functia verifica aparitia adresei de start in fiecare prima
 * pagina din tabela de pagini a fiecarui element din structura
 * data_set. Daca este gasita, se face o mutare la stanga a tuturor
 * elementelor.
 */
w_boolean_t vm_free(w_ptr_t start)
{
	if (start <= 0)
		return FALSE;

	int i, j, ret;

	for (i = 0; i < data_length; i++) {
		if (data[i].page_table[0].start == start) {
			ret = close(data[i].map->ram_handle);
			if (ret == -1)
				return FALSE;
			ret = close(data[i].map->swap_handle);
			if (ret == -1)
				return FALSE;
			ret = munmap(start, data[i].num_pages * p_sz);
			if (ret == -1)
				return FALSE;
			for (j = i; j < data_length - 1; j++) {
				data[i].map = data[i + 1].map;
				data[i].num_pages = data[i + 1].num_pages;
				data[i].num_frames = data[i + 1].num_frames;
				data[i].page_table = data[i + 1].page_table;
				data[i].frames = data[i + 1].frames;
			}
			data_length--;
			break;
		}
	}

	return TRUE;
}
