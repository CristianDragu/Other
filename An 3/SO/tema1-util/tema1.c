#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash.c"
#include "functii.h"
#include "utils.h"

int main(int argc, char *argv[])
{
	bucket *q, *end, *nou, **hash_table, **aux_table;
	int hash_length, nr_bucket, i, j;
	bool exista;
	char line[20001];
	char *p, *cuvant;
	char *linee = NULL;
	int k = 0;

	for (i = 0; i < strlen(argv[1]); i++)
		DIE(!(argv[1][i] >= 48 && argv[1][i] <= 57), "Param gresit!");
	hash_length = atoi(argv[1]);
	DIE(hash_length <= 0, "Param gresit!");

	hash_table = (bucket **)malloc(hash_length * sizeof(bucket *));

	for (i = 0; i < hash_length; i++) {
		hash_table[i] = (bucket *)malloc(sizeof(bucket));
		hash_table[i]->next = NULL;
	}
	if (argc == 2) {
		while (fgets(line, 20001, stdin)) {
			if (!isalnum(line[strlen(line) - 1]))
				line[strlen(line) - 1] = '\0';
			if (strlen(line) <= 3)
				continue;
			p = strtok(line, " ");
			if (strcmp(p, "add") == 0) {
				p = strtok(NULL, " ");
				DIE(p == NULL, "Param gresit!");
				insert(hash_table, hash_length, p);
			} else if (strcmp(p, "remove") == 0) {
				p = strtok(NULL, " ");
				DIE(p == NULL, "Param gresit!");
				remove_elem(hash_table, hash_length, p);
			} else if (strcmp(p, "find") == 0) {
				p = strtok(NULL, " ");
				DIE(p == NULL, "Param gresit!");
				find(hash_table, hash_length, p);
			} else if (strcmp(p, "clear") == 0) {
				clear(hash_table, hash_length);
			} else if (strcmp(p, "print_bucket") == 0) {
				p = strtok(NULL, " ");
				print_bucket(hash_table, hash_length, p);
			} else if (strcmp(p, "print") == 0) {
				p = strtok(NULL, " ");
				print_hash(hash_table, hash_length, p);
			} else if (strcmp(p, "resize") == 0) {
				p = strtok(NULL, " ");
				DIE(p == NULL, "Param gresit!");
				hash_table = resize(hash_table, &hash_length, p);
			}
		}
	} else if (argc > 2) {
		for (j = 0; j < argc - 2; j++) {
			input = fopen(argv[j + 2], "r");
			DIE(input == NULL, "Param gresit!");
			while (fgets(line, 20001, input)) {
				if (!isalnum(line[strlen(line) - 1]))
					line[strlen(line) - 1] = '\0';
				if (strlen(line) <= 3)
					continue;
				p = strtok(line, " ");
				if (strcmp(p, "add") == 0) {
					p = strtok(NULL, " ");
					DIE(p == NULL, "Param gresit!");
					insert(hash_table, hash_length, p);
				} else if (strcmp(p, "remove") == 0) {
					p = strtok(NULL, " ");
					DIE(p == NULL, "Param gresit!");
					remove_elem(hash_table, hash_length, p);
				} else if (strcmp(p, "find") == 0) {
					p = strtok(NULL, " ");
					DIE(p == NULL, "Param gresit!");
					find(hash_table, hash_length, p);
				} else if (strcmp(p, "clear") == 0) {
					clear(hash_table, hash_length);
				} else if (strcmp(p, "print_bucket") == 0) {
					p = strtok(NULL, " ");
					print_bucket(hash_table, hash_length, p);
				} else if (strcmp(p, "print") == 0) {
					p = strtok(NULL, " ");
					print_hash(hash_table, hash_length, p);
				} else if (strcmp(p, "resize") == 0) {
					p = strtok(NULL, " ");
					DIE(p == NULL, "Param gresit!");
					hash_table = resize(hash_table, &hash_length, p);
				}
			}
			fclose(input);
		}
	}

	clear(hash_table, hash_length);
	for (i = 0; i < hash_length; i++)
		free(hash_table[i]);
	free(hash_table);

	return 0;
}
