#include <stdbool.h>

struct bucket {
	char *word;
	struct bucket *next;
};
typedef struct bucket bucket;

FILE *file, *input;

void insert(bucket **hash_table, int hash_length, char *p)
{
	bucket *nou, *end, *q;
	bool exista = false;
	int nr_bucket;

	nr_bucket = hash(p, hash_length);
	q = hash_table[nr_bucket];
	q = q->next;
	end = hash_table[nr_bucket];
	while (q != NULL) {
		if (strcmp(p, q->word) == 0) {
			exista = true;
			break;
		}
		end = q;
		q = q->next;
	}
	if (exista == false) {
		nou = (bucket *)malloc(sizeof(bucket));
		nou->word = strdup(p);
		nou->next = NULL;
		end->next = nou;
	}
}

void remove_elem(bucket **hash_table, int hash_length, char *p)
{
	bucket *end, *q, *r;
	int nr_bucket;

	nr_bucket = hash(p, hash_length);
	q = hash_table[nr_bucket];
	q = q->next;
	end = hash_table[nr_bucket];
	while (q != NULL) {
		if (strcmp(p, q->word) == 0) {
			r = end->next;
			end->next = end->next->next;
			r->next = NULL;
			free(r->word);
			free(r);
			break;
		}
		end = q;
		q = q->next;
	}
}

void find(bucket **hash_table, int hash_length, char *p)
{
	bucket *q, *end;
	bool exista = false;
	int nr_bucket;

	nr_bucket = hash(p, hash_length);
	q = hash_table[nr_bucket];
	q = q->next;
	end = hash_table[nr_bucket];
	while (q != NULL) {
		if (strcmp(p, q->word) == 0) {
			exista = true;
			break;
		}
		end = q;
		q = q->next;
	}
	p = strtok(NULL, " ");
	if (p == NULL) {
		if (exista == false)
			printf("False\n");
		else
			printf("True\n");
	} else {
		file = fopen(p, "a");
		if (exista == false)
			fprintf(file, "False\n");
		else
			fprintf(file, "True\n");
		fclose(file);
	}
}

void clear(bucket **hash_table, int hash_length)
{
	bucket *q, *end;
	int i;

	for (i = 0; i < hash_length; i++) {
		q = hash_table[i]->next;
		end = hash_table[i];
		if (q != NULL && q->next != NULL) {
			end->next = NULL;
			end = q;
			q = q->next;
			while (q != NULL) {
				free(end->word);
				free(end);
				end = q;
				q = q->next;
			}
			if (end != NULL) {
				free(end->word);
				free(end);
			}
		} else if (q != NULL && q->next == NULL) {
			end->next = NULL;
			free(q->word);
			free(q);
		}
	}
}

void print_bucket(bucket **hash_table, int hash_length, char *p)
{
	bucket *q;
	int nr_bucket;

	nr_bucket = atoi(p);
	if (nr_bucket >= hash_length)
		return;
	q = hash_table[nr_bucket];
	q = q->next;
	p = strtok(NULL, " ");
	if (p == NULL) {
		while (q != NULL) {
			printf("%s ", q->word);
			q = q->next;
		}
		printf("\n");
	} else {
		file = fopen(p, "a");
		while (q != NULL) {
			fprintf(file, "%s ", q->word);
			q = q->next;
		}
		fprintf(file, "\n");
		fclose(file);
	}
}

void print_hash(bucket **hash_table, int hash_length, char *p)
{
	bucket *q;
	int i;

	if (p == NULL) {
		for (i = 0; i < hash_length; i++) {
			q = hash_table[i];
			q = q->next;
			while (q != NULL) {
				printf("%s ", q->word);
				q = q->next;
			}
			if (hash_table[i]->next != NULL)
				printf("\n");
		}
	} else {
		file = fopen(p, "a");
		for (i = 0; i < hash_length; i++) {
			q = hash_table[i];
			q = q->next;
			while (q != NULL) {
				fprintf(file, "%s ", q->word);
				q = q->next;
			}
			if (hash_table[i]->next != NULL)
				fprintf(file, "\n");
		}
		fclose(file);
	}
}

bucket **resize(bucket **hash_table, int *hash_length, char *p)
{
	bucket **aux_table, *q;
	int i;

	if (strcmp(p, "halve") == 0 && *hash_length / 2 >= 1) {
		aux_table = (bucket **)malloc((*hash_length / 2)
					* sizeof(bucket *));
		for (i = 0; i < *hash_length / 2; i++) {
			aux_table[i] = (bucket *)malloc(sizeof(bucket));
			aux_table[i]->next = NULL;
		}
		for (i = 0; i < *hash_length; i++) {
			q = hash_table[i];
			q = q->next;
			while (q != NULL) {
				insert(aux_table, *hash_length / 2, q->word);
				q = q->next;
			}
		}
		clear(hash_table, *hash_length);
		for (i = 0; i < *hash_length; i++)
			free(hash_table[i]);
		free(hash_table);
		*hash_length = *hash_length / 2;
		return aux_table;
	} else if (strcmp(p, "double") == 0) {
		aux_table = (bucket **)malloc((*hash_length * 2)
					* sizeof(bucket *));
		for (i = 0; i < *hash_length * 2; i++) {
			aux_table[i] = (bucket *)malloc(sizeof(bucket));
			aux_table[i]->next = NULL;
		}
		for (i = 0; i < *hash_length; i++) {
			q = hash_table[i];
			q = q->next;
			while (q != NULL) {
				insert(aux_table, *hash_length * 2, q->word);
				q = q->next;
			}
		}
		clear(hash_table, *hash_length);
		for (i = 0; i < *hash_length; i++)
			free(hash_table[i]);
		free(hash_table);
		*hash_length = *hash_length * 2;
		return aux_table;
	}

	return hash_table;
}
