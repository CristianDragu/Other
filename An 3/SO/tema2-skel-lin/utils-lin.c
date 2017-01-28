/**
 * Operating Systems 2013 - Assignment 2
 *
 */

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <unistd.h>

#include "utils.h"

#define READ		0
#define WRITE		1

/**
 * Internal change-directory command.
 */

static bool shell_cd(word_t *dir)
{
	if (dir != NULL && dir->string != NULL) {
		if (chdir(dir->string) == 0)
			return true;
		fprintf(stderr, "No such file or directory\n");
		return false;
	} else
		return chdir(getenv("HOME"));
}

/**
 * Internal exit/quit command.
 */
static int shell_exit(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * Concatenate parts of the word to obtain the command
 */
static char *get_word(word_t *s)
{
	int string_length = 0;
	int substring_length = 0;

	char *string = NULL;
	char *substring = NULL;

	while (s != NULL) {
		substring = strdup(s->string);

		if (substring == NULL)
			return NULL;

		if (s->expand == true) {
			char *aux = substring;

			substring = getenv(substring);

			/* prevents strlen from failing */
			if (substring == NULL)
				substring = "";

			free(aux);
		}

		substring_length = strlen(substring);

		string = realloc(string, string_length + substring_length + 1);
		if (string == NULL) {
			if (s->expand == false)
				free(substring);
			return NULL;
		}

		memset(string + string_length, 0, substring_length + 1);

		strcat(string, substring);
		string_length += substring_length;

		if (s->expand == false)
			free(substring);

		s = s->next_part;
	}

	return string;
}

/**
 * Concatenate command arguments in a NULL terminated list in order to pass
 * them directly to execv.
 */
static char **get_argv(simple_command_t *command, int *size)
{
	char **argv;
	word_t *param;

	int argc = 0;

	argv = calloc(argc + 1, sizeof(char *));
	assert(argv != NULL);

	argv[argc] = get_word(command->verb);
	assert(argv[argc] != NULL);

	argc++;

	param = command->params;
	while (param != NULL) {
		argv = realloc(argv, (argc + 1) * sizeof(char *));
		assert(argv != NULL);

		argv[argc] = get_word(param);
		assert(argv[argc] != NULL);

		param = param->next_word;
		argc++;
	}

	argv = realloc(argv, (argc + 1) * sizeof(char *));
	assert(argv != NULL);

	argv[argc] = NULL;
	*size = argc;

	return argv;
}

/**
* Deschide fisierele din redirectari, apoi duplica descriptorul de
* fiser in stdin, stdou sau sterr, dupa caz.
*/
void open_files(simple_command_t *s)
{
	int fi, fo, fe;
	char *file, *file2;

	/*
	Daca comanda citita primeste, prin redirectare, input dintr-un fisier,
	se incearca deschiderea fisierelui si copierea file desriptorului
	*/
	if (s->in != NULL) {
		file = get_word(s->in);
		fi = open(file, O_RDONLY);
		if (fi == -1) {
			perror("Open file error");
			exit(1);
		}
		dup2(fi, STDIN_FILENO);
	}
	/*
	Se procedeaza la fel daca comanda are redirectat outputul catre
	un fiser.
	*/
	if (s->err != NULL && s->out != NULL) {
		file = get_word(s->out);
		file2 = get_word(s->err);
		if (strcmp(file2, file) == 0) {
			if (s->io_flags > 0)
				fo = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fo = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fo == -1) {
				perror("Open file error");
				exit(1);
			}
			dup2(fo, STDERR_FILENO);
			dup2(fo, STDOUT_FILENO);
			return;
		}
	}
	if (s->out != NULL) {
		file = get_word(s->out);
		if (s->io_flags > 0)
			fo = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fo = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fo == -1) {
			perror("Open file error");
			exit(1);
		}
		dup2(fo, STDOUT_FILENO);
	}
	if (s->err != NULL) {
		file = get_word(s->err);
		if (s->io_flags > 0)
			fe = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fe = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fe == -1) {
			perror("Open file error");
			exit(1);
		}
		dup2(fe, STDERR_FILENO);
	}
}

/**
* Functia verifica daca comanda este o variabila de mediu
* (Variabila=valoare). Returneaza 1 daca e, 0 altfel.
*/
int is_env_var(simple_command_t *s)
{
	word_t *word = s->verb;

	if (word == NULL)
		return 0;
	if (word->string == NULL)
		return 0;
	if (word->next_part == NULL)
		return 0;
	else
		word = word->next_part;
	if (strcmp(word->string, "=") != 0)
		return 0;
	if (word->next_part == NULL)
		return 0;
	else
		word = word->next_part;
	if (word->string == NULL)
		return 0;

	return 1;
}

/**
* Functia verifica daca comanda defineste o variabila de mediu.
* Daca da, atunci este salvata.
*/
int environment_var(simple_command_t *s)
{
	/*
	Verificam daca comanda are caracteristicile unei variabile de mediu:
	"Variabila=valoare"
	*/
	if (is_env_var(s)) {
		char *left_val = strdup(s->verb->string);
		char *right_val = strdup(s->verb->next_part->next_part->string);

		setenv(left_val, right_val, 1);
		free(left_val);
		free(right_val);

		return 1;
	}
	return 0;
}

/**
 * Parse a simple command (internal, environment variable assignment,
 * external command).
 */
static int parse_simple(simple_command_t *s, int level, command_t *father)
{
	char *verb = get_word(s->verb);

	/*
	* Verific mai intai daca comanda este una interna (quit, exit, cd, true,
	* false).
	*/
	if (strcmp(verb, "true") == 0) {
		return 0;
	} else if (strcmp(verb, "false") == 0) {
		return -1;
	} else if (strcmp(verb, "quit") == 0 || strcmp(verb, "exit") == 0) {
		shell_exit();
	} else if (strcmp(verb, "cd") == 0) {
		char *file;

		if (s->in != NULL) {
			file = get_word(s->in);
			int fi = open(file, O_RDONLY, 0644);

			if (fi == -1) {
				perror("Open file error");
				exit(1);
			}
			dup2(fi, 0);
		}
		/**
		* Tratez cazul in care primesc comanda: cd dir > fisier,
		* cand dir nu exista si comanda da eroare, dar se creeaza
		* fisierul fisier.
		*/
		if (s->out != NULL) {
			file = get_word(s->out);
			int fo = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);

			if (fo == -1) {
				perror("Open file error");
				exit(1);
			}
		}
		if (s->err != NULL) {
			file = get_word(s->err);
			int fe = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);

			if (fe == -1) {
				perror("Open file error");
				exit(1);
			}
		}
		if (shell_cd(s->params) == false)
			return -1;
	} else {

		/*
		* Verific daca s este o comanda ce defineste o variabila de mediu.
		* Daca da, o salvez si returnez 0, iar daca nu, continui executia
		* functiei, din moment ce e posibil sa fie o comanda.
		*/
		if (environment_var(s))
			return 0;

		/*Execut comanda intr-un child process*/
		int status, ret;
		pid_t pid = fork();

		if (pid < 0) {
			perror("Fork error");
			exit(1);
		}
		/*Copil*/
		if (pid == 0) {
			open_files(s);
			int size;
			char **argv = get_argv(s, &size);

			if (execvp(argv[0], argv) == -1) {
				char *unknown_cmd_msg;
				unknown_cmd_msg = calloc(100, 1);
				sprintf(unknown_cmd_msg, "Execution failed for '%s'", argv[0]);
				fprintf(stderr, "%s\n", unknown_cmd_msg);
				free(unknown_cmd_msg);
				exit(1);
				return -1;
			}
		/*Parinte*/
		} else {
			ret = waitpid(pid, &status, 0);
			if (ret == -1)
				perror("Waitpid error");
			if (WIFEXITED(status))
				return WEXITSTATUS(status);
		}
	}

	return 0;
}

/**
 * Process two commands in parallel, by creating two children.
 */
static bool do_in_parallel(command_t *cmd1, command_t *cmd2, int level, command_t *father)
{
	pid_t pid;
	int ret, result, status;

	pid = fork();

	if (pid < 0) {
		perror("Fork error");
		exit(1);
	}
	/*Copil*/
	if (pid == 0) {
		parse_command(cmd1, level + 1, father);
		exit(EXIT_SUCCESS);
	/*Parinte*/
	} else {
		result = parse_command(cmd2, level + 1, father);
		ret = waitpid(pid, &status, 0);
		if (ret == -1) {
			perror("Waitpid error");
			exit(1);
		}
		if (WIFEXITED(status))
			return WEXITSTATUS(status);
	}

	return result;
}

/**
 * Run commands by creating an anonymous pipe (cmd1 | cmd2)
 */
static bool do_on_pipe(command_t *cmd1, command_t *cmd2, int level, command_t *father)
{
	int fd[2];
	int ret, result, status;
	pid_t pid;

	/*Creez pipe*/
	ret = pipe(fd);
	if (ret == -1) {
		perror("Could not open pipe");
		exit(1);
	}

	pid = fork();
	if (pid < 0) {
		perror("Fork error");
		exit(1);
	}
	/*
	* Copil
	* Inchid file descriptorul pentru read al copilului,
	* deoarece el executa comanda a carei output este trimis
	* ca input celei de-a doua comenzi.
	*/
	if (pid == 0) {
		close(fd[0]);
		ret = dup2(fd[1], STDOUT_FILENO);
		if (ret == -1) {
			perror("Pipe failed");
			exit(1);
		}
		close(fd[1]);

		parse_command(cmd1, level + 1, father);
		exit(EXIT_SUCCESS);
	/*
	* Parinte
	* Inchid fd[1]. Comunic prin fd[0].
	*/
	} else {

		close(fd[1]);
		ret = dup2(fd[0], STDIN_FILENO);
		if (ret == -1) {
			perror("Pipe failed");
			exit(1);
		}
		close(fd[0]);

		result = parse_command(cmd2, level + 1, father);

		ret = waitpid(pid, &status, 0);
		if (ret == -1) {
			perror("Waitpid error");
			exit(1);
		}

		if (WIFEXITED(status))
			return WEXITSTATUS(status);

	}

	return result;
}

/**
 * Parse and execute a command.
 */

int parse_command(command_t *c, int level, command_t *father)
{
	if (c->op == OP_NONE)
		return parse_simple(c->scmd, level, father);

	switch (c->op) {
	case OP_SEQUENTIAL:
		parse_command(c->cmd1, level + 1, c);
		return parse_command(c->cmd2, level + 1, c);

	case OP_PARALLEL:
		return do_in_parallel(c->cmd1, c->cmd2, level + 1, c);

	case OP_CONDITIONAL_NZERO:
		if (parse_command(c->cmd1, level + 1, c) != 0)
			return parse_command(c->cmd2, level + 1, c);
		return 0;

	case OP_CONDITIONAL_ZERO:
		if (parse_command(c->cmd1, level + 1, c) == 0)
			return parse_command(c->cmd2, level + 1, c);
		return -1;

	case OP_PIPE:
		return do_on_pipe(c->cmd1, c->cmd2, level + 1, c);

	default:
		assert(false);
	}

	return 0;
}

/**
 * Readline from mini-shell.
 */
char *read_line()
{
	char *instr;
	char *chunk;
	char *ret;

	int instr_length;
	int chunk_length;

	int endline = 0;

	instr = NULL;
	instr_length = 0;

	chunk = calloc(CHUNK_SIZE, sizeof(char));
	if (chunk == NULL) {
		fprintf(stderr, ERR_ALLOCATION);
		return instr;
	}

	while (!endline) {
		ret = fgets(chunk, CHUNK_SIZE, stdin);
		if (ret == NULL)
			break;

		chunk_length = strlen(chunk);
		if (chunk[chunk_length - 1] == '\n') {
			chunk[chunk_length - 1] = 0;
			endline = 1;
		}

		instr = realloc(instr, instr_length + CHUNK_SIZE + 1);
		if (instr == NULL)
			break;

		memset(instr + instr_length, 0, CHUNK_SIZE);
		strcat(instr, chunk);
		instr_length += chunk_length;
	}

	free(chunk);

	return instr;
}

