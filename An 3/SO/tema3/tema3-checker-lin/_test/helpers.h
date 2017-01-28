enum page_state {
	STATE_IN_RAM,
	STATE_IN_SWAP,
	STATE_NOT_ALLOC
};

struct frame;

/* handle pages (virtual pages) */
struct page_table_entry {
	enum page_state state;
	enum page_state prev_state;
	w_boolean_t dirty;
	w_prot_t protection;
	w_ptr_t start;
	struct frame *frame;	/* NULL in case page is not mapped */
};

/* handle frames (physical pages) */
struct frame {
	w_size_t index;
	/* "backlink" to page_table_entry; NULL in case of free frame */
	struct page_table_entry *pte;
};

struct data_set{
	vm_map_t *map;
	int num_pages;
	int num_frames;
	struct page_table_entry *page_table;
	struct frame *frames;
	w_boolean_t ram_full;
	int last_frame;
};
typedef struct data_set data_set;