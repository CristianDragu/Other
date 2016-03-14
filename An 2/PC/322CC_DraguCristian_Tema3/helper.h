#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>

#define CONNECT_ERROR -1
#define READWRITE_ERROR -2
#define NO_CLIENT -3
#define UNKNOWN_CLIENT -4
#define NO_FILE -5
#define DUPLICATE_SHARED_FILE -6

#define MAX_CLIENTS 20
#define DIM_CLIENT_NAME 40
#define DIM_FILE_NAME 40
#define BUFFER_LENGTH 1024

FILE* logFile;
char log_file_name[100];

typedef struct file{
	long size;
	char name[DIM_FILE_NAME];
} Files;

typedef struct {
	char name[DIM_CLIENT_NAME];
	char adr[100];
	int port;
	int connected;
	Files *files;
	int nrFiles;
	int maxFiles;
} Client;

void print_log_entry(char *msg){
	logFile = fopen(log_file_name, "at");
	fprintf(logFile, "%s\n", msg);
	fclose(logFile);
}

char* returnErrorCode (int error){
	switch (error){
		case -1: return "Eroare la conectare";
		case -2: return "Eroare la citire/scriere pe socket";
		case -3: return "Client inexistent";
		case -4: return "Client necunoscut";
		case -5: return "Fisier inexistent";
		case -6: return "Fisier partajat cu acelasi nume";
		default: return "Alta eroare";
	}

	return NULL;
}

int recvMessage(int socket, char *msg){
	memset(msg, 0, BUFFER_LENGTH);
	return recv(socket, msg, BUFFER_LENGTH, 0);
}

int sendMessage(int socket, char *msg, int length){
	return send(socket, msg, length, 0);
}

char* concatArrays(char *s1, char *s2){
	char *res = (char*)malloc(strlen(s1) + strlen(s2));
	strcpy(res, s1);
	strcat(res, s2);

	return res;
}

int readOpperation(int fd, char *buffer){
	memset(buffer, 0, BUFFER_LENGTH);
	int n = read(fd, buffer, BUFFER_LENGTH);

	return n;
}

void validateCommand(int comanda, char *msg, int error){
	if(comanda){
		printf("%d : %s\n", error, msg);
		exit(error);
	}
}

char* getFormattedSize(long size){
	char* sSize = (char*)malloc(20);
	// [0, 1Kb)
	if( size < 1024 ) 
		sprintf(sSize, "%ldB", size);
	// [1Kb, 1Mb)
	else if( size < 1048576 )
		sprintf(sSize, "%ldKiB", size/1024);
	else if( size < 1073741824 )
		sprintf(sSize, "%ldMiB", size/1048576);
	else
		sprintf(sSize, "%ldGiB", size/1073741824);
	
	return sSize;
}