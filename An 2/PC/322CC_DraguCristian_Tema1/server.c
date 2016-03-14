#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int parity(char* str, int len){
	int i, j, nrSetBits = 0;
	for (i = 0; i < len; i++)
		for(j = 7; j >= 0; j--)
			if (str[i] & (1<<j))
				nrSetBits++;

	return nrSetBits%2;
}

void sendACK(msg r){
	r.payload[0] = parity("ACK", 3);
	sprintf(r.payload + 1, "%s", "ACK");
	r.len = strlen(r.payload);
	send_message(&r);
}

msg sendNACK(msg r){
	r.payload[0] = parity("NACK", 4);
	sprintf(r.payload + 1, "%s", "NACK");
	r.len = strlen(r.payload);
	send_message(&r);
	recv_message(&r);

	return r;
}

char* codificare(char *str){
	char* res;
	res = (char*)malloc(2 * strlen(str));

	unsigned int k = 0, i;
	unsigned char p1, p2, p4, p8;
	unsigned char d1, d2, d3, d4 , d5, d6, d7, d8;

	for(i = 0; i < strlen(str); i++){

		d1 = (str[i] >> 7) & 1;
		d2 = (str[i] >> 6) & 1;
		d3 = (str[i] >> 5) & 1;
		d4 = (str[i] >> 4) & 1;
		d5 = (str[i] >> 3) & 1;
		d6 = (str[i] >> 2) & 1;
		d7 = (str[i] >> 1) & 1;
		d8 = (str[i] >> 0) & 1;

		p1 = (d1 + d2 + d4 + d5 + d7) % 2;
		p2 = (d1 + d3 + d4 + d6 + d7) % 2;
		p4 = (d2 + d3 + d4 + d8) % 2;
		p8 = (d5 + d6 + d7 + d8) % 2;

		res[k] |= p1 << 3;
		res[k] |= p2 << 2;
		res[k] |= d1 << 1;
		res[k] |= p4 << 0;
		res[k + 1] |= d2 << 7;
		res[k + 1] |= d3 << 6;
		res[k + 1] |= d4 << 5;
		res[k + 1] |= p8 << 4;
		res[k + 1] |= d5 << 3;
		res[k + 1] |= d6 << 2;
		res[k + 1] |= d7 << 1;
		res[k + 1] |= d8 << 0;

		k += 2;
	}

	return res;
}

char* corect(msg r){
	int i, k = 0;
	char* res;
	res = (char*)malloc(r.len);

	for(i = 0; i < r.len; i += 2)
	{

		unsigned char b1, b2;
		unsigned char p0, p1, p2, p3;
		unsigned char d0, d1, d2, d3, d4, d5, d6, d7;

		b1 = r.payload[i];
		b2 = r.payload[i + 1];

		p0 = (((b1 >> 3) & 1) + ((b1 >> 1) & 1) + ((b2 >> 7) & 1) + ((b2 >> 5) & 1) + ((b2 >> 3) & 1) + ((b2 >> 1) & 1)) % 2;
		p1 = (((b1 >> 2) & 1) + ((b1 >> 1) & 1) + ((b2 >> 6) & 1) + ((b2 >> 5) & 1) + ((b2 >> 2) & 1) + ((b2 >> 1) & 1)) % 2;
		p2 = ((b1 & 1) + ((b2 >> 7) & 1) + ((b2 >> 6) & 1) + ((b2 >> 5) & 1) + (b2 & 1)) % 2;
		p3 = (((b2 >> 4) & 1) + ((b2 >> 3) & 1) + ((b2 >> 2) & 1) + ((b2 >> 1) & 1) + (b2 & 1)) % 2;

		if( p0 + p1 + p2 + p3 ){
			if( (p0 + p1 * 2 + p2 * 4 + p3 * 8) < 4){
				unsigned char sum = 4 - (p0 + p1 * 2 + p2 * 4 + p3 * 8);
				b1 ^= 1 << sum;
			}
			else{
				unsigned char sum = 12 - (p0 + p1 * 2 + p2 * 4 + p3 * 8);
				b2 ^= 1 << sum;
			}
		}

		d7 = ( (b2 >> 0) & 1);
		d6 = ( (b2 >> 1) & 1);
		d5 = ( (b2 >> 2) & 1);
		d4 = ( (b2 >> 3) & 1);
		d3 = ( (b2 >> 5) & 1);
		d2 = ( (b2 >> 6) & 1);
		d1 = ( (b2 >> 7) & 1);
		d0 = ( (b1 >> 1) & 1);
		
		res[k] |= d7 << 0;
		res[k] |= d6 << 1;
		res[k] |= d5 << 2;
		res[k] |= d4 << 3;
		res[k] |= d3 << 4;
		res[k] |= d2 << 5;
		res[k] |= d1 << 6;
		res[k] |= d0 << 7;
		
		k++;
	}

	return res;
}

void ls(msg r){
	int file_count = 0, i;
	struct dirent * entry;
	DIR * dirp;
	dirp = opendir(r.payload + 3);
	while ((entry = readdir(dirp)) != NULL) {
	    file_count++;
	}
	closedir(dirp);
	dirp = opendir(r.payload + 3);

	sprintf(r.payload, "%d", file_count);
	r.len = strlen(r.payload);
	send_message(&r);
	recv_message(&r);

	for(i = 0; i < file_count; i++){
		entry = readdir(dirp);
		sprintf(r.payload, "%s", entry->d_name);
		r.len = strlen(r.payload) + 1;
		send_message(&r);
		recv_message(&r);
	}
	closedir(dirp);
}

void lsParity(char *comanda){
	msg t, r;
	int file_count = 0, i;
	struct dirent * entry;
	DIR * dirp;
	dirp = opendir(comanda + 3);
	while ((entry = readdir(dirp)) != NULL) {
	    file_count++;
	}
	closedir(dirp);
	dirp = opendir(comanda + 3);

	char *aux;
	aux = (char*)malloc(10);
	sprintf(aux, "%d", file_count);
	sprintf(r.payload, "%d", parity(aux, strlen(aux)));
	sprintf(r.payload + 1, "%d", file_count);
	r.len = strlen(r.payload);

	do{
		send_message(&r);
		recv_message(&t);
	}while(t.len == 5);

	for(i = 0; i < file_count; i++){
		entry = readdir(dirp);
		sprintf(r.payload, "%d", parity(entry->d_name, strlen(entry->d_name)));
		sprintf(r.payload + 1, "%s", entry->d_name);
		r.len = strlen(r.payload) + 1;
		do{
			send_message(&r);
			recv_message(&t);
		}while(t.len == 5);
	}
}

void lsHamming(char *comanda){
	msg r;
	int file_count = 0, i;
	struct dirent * entry;
	DIR * dirp;
	dirp = opendir(comanda + 3);
	while ((entry = readdir(dirp)) != NULL) {
	    file_count++;
	}
	closedir(dirp);
	dirp = opendir(comanda + 3);
	
	char *aux;
	aux = (char*)malloc(1400);
	sprintf(aux, "%d", file_count);
	memset(r.payload, 0, 1400);
	memcpy(r.payload, codificare(aux), 2 * strlen(aux));
	sprintf(r.payload, "%s", codificare(aux));
	r.len = 2 * strlen(aux) + 1;
	send_message(&r);
	recv_message(&r);

	for(i = 0; i < file_count; i++){
		entry = readdir(dirp);
		memset(r.payload, 0, 1400);
		memcpy(r.payload, codificare(entry->d_name), 2 * strlen(entry->d_name));
		r.len = 2 * strlen(entry->d_name) + 1;
		send_message(&r);
		recv_message(&r);
	}
}

void cp(msg r){
	FILE* fop = fopen(r.payload + 3, "r");
	fseek(fop, 0, SEEK_END);
	int size = ftell(fop);
	fseek(fop, 0, SEEK_SET);

	sprintf(r.payload, "%d", size);
	r.len = strlen(r.payload);
	send_message(&r);
	recv_message(&r);

	char *message;
	message = (char*)malloc(1400 * sizeof(char));
	int dimRead;

	while((dimRead = fread(message , 1, 1400, fop)) != 0){
		memcpy(r.payload, message, dimRead);
		r.len = dimRead;
		send_message(&r);
		recv_message(&r);
	}
	fclose(fop);
}

void cpParity(char* comanda){
	msg t, r;
	FILE* fop = fopen(comanda + 3, "r");
	fseek(fop, 0, SEEK_END);
	int size = ftell(fop);
	fseek(fop, 0, SEEK_SET);

	char *aux;
	aux = (char*)malloc(10);
	sprintf(aux, "%d", size);
	sprintf(r.payload, "%d", parity(aux, strlen(aux)));
	sprintf(r.payload + 1, "%d", size);
	r.len = strlen(r.payload);
	do{
		send_message(&r);
		recv_message(&t);
	}while(t.len == 5);

	int dimRead;

	while((dimRead = fread(r.payload + 1, 1, 1399, fop)) != 0){
		r.len = dimRead + 1;
		r.payload[0] = parity(r.payload + 1, r.len - 1);
		do{
			send_message(&r);
			recv_message(&t);
		}while(t.len == 5);
	}
	fclose(fop);
}

void cpHamming(char* comanda){
	msg r;
	FILE* fop = fopen(comanda + 3, "r");
	fseek(fop, 0, SEEK_END);
	int size = ftell(fop);
	fseek(fop, 0, SEEK_SET);
	
	char *aux;
	aux = (char*)malloc(1400);
	sprintf(aux, "%d", size);
	memset(r.payload, 0, 1400);
	memcpy(r.payload, codificare(aux), 2 * strlen(aux));
	r.len = 2 * strlen(aux) + 1;
	send_message(&r);
	recv_message(&r);

	char *message;
	message = (char*)malloc(700 * sizeof(char));

	while(fread(message, 1, 700, fop) && size > 0){
		size -= 700;
		memset(r.payload, 0, 1400);
		sprintf(aux, "%s", message);
		memcpy(r.payload, codificare(aux), 2 * strlen(aux));
		r.len = 2 * strlen(aux);
		send_message(&r);
		recv_message(&r);
	}
}

void sn(msg r){
	char *fopName;
	fopName = (char*)malloc(1400 * sizeof(char));
	strcpy(fopName, "new_");
	strcat(fopName, r.payload + 3);
	FILE *fop = fopen(fopName, "w");
				
	recv_message(&r);
	send_message(&r);

	int dimRead, i;

	if(atoi(r.payload) % 1400 != 0)
		dimRead = atoi(r.payload) / 1400 + 1;
	else
		dimRead = atoi(r.payload) / 1400;

	for(i = 0; i < dimRead; i++){
		recv_message(&r);
		send_message(&r);

		fwrite(r.payload, 1, r.len, fop);
	}
	fclose(fop);
}

void snParity(char *comanda){
	msg t, r;
	char *fopName;
	fopName = (char*)malloc(1399 * sizeof(char));
	strcpy(fopName, "new_");
	strcat(fopName, comanda + 3);
	FILE *fop = fopen(fopName, "w");
	
	recv_message(&r);

	while(parity(r.payload + 1, r.len - 1) != r.payload[0]){
		r = sendNACK(r);
	}
	sendACK(t);

	int dimRead, i;

	if(atoi(r.payload + 1) % 1399 != 0)
		dimRead = atoi(r.payload + 1) / 1399 + 1;
	else
		dimRead = atoi(r.payload + 1) / 1399;

	for(i = 0; i < dimRead; i++){
		recv_message(&r);
		while(parity(r.payload + 1, r.len - 1) != r.payload[0]){
			r = sendNACK(r);
		}
		sendACK(t);
		fwrite(r.payload + 1, 1, r.len - 1, fop);
	}
	fclose(fop);
}

void snHamming(char *comanda){
	msg r;
	char *fopName;
	fopName = (char*)malloc(1400 * sizeof(char));
	strcpy(fopName, "new_");
	strcat(fopName, comanda + 3);
	FILE *fop = fopen(fopName, "w");
	
	memset(r.payload, 0, 1400);

	recv_message(&r);

	send_message(&r);

	int dimRead, i;

	if(atoi(corect(r)) % 1400 != 0)
		dimRead = atoi(corect(r)) / 1400 + 1;
	else
		dimRead = atoi(corect(r)) / 1400;

	char *aux;
	aux = (char*)malloc(1400);
	for(i = 0; i < dimRead; i++){
		memset(r.payload, 0, 1400);
		recv_message(&r);
		aux = corect(r);
		send_message(&r);

		fwrite(aux, 1, strlen(aux), fop);
	}
}

int main(int argc, char* argv[])
{
	msg r;
	
	printf("[RECEIVER] Starting.\n");
	init(HOST, PORT);
	
	if(argc == 1){
		while(1) {
			recv_message(&r);

			send_message(&r);
			if(strstr(r.payload, "cd") != NULL){
				chdir(r.payload + 3);

			}
			else if(strstr(r.payload, "ls") != NULL){
				ls(r);
			}
			else if(strstr(r.payload, "cp") != NULL){
				cp(r);
			}
			else if(strstr(r.payload, "sn") != NULL){
				sn(r);
			}
			else if(strstr(r.payload, "exit"))
				return 0;

		}
	}
	if(strcmp(argv[1], "parity") == 0){
		while(1){
			recv_message(&r);
			
			while(parity(r.payload + 1, r.len - 1) != r.payload[0]){
				r = sendNACK(r);
			}

			char *comanda;
			comanda = (char*)malloc(r.len);
			strcpy(comanda, r.payload + 1);

			sendACK(r);

			if(strstr(comanda, "cd") != NULL){
				chdir(comanda + 3);
			}
			else if(strstr(comanda, "ls") != NULL){
				lsParity(comanda);
			}
			else if(strstr(comanda, "cp") != NULL){
				cpParity(comanda);
			}
			else if(strstr(comanda, "sn") != NULL){
				snParity(comanda);
			}
			else if(strstr(comanda, "exit") != NULL){
				return 0;
			}
		}
	}
	if(strcmp(argv[1], "hamming") == 0){
		while(1){

			memset(r.payload, 0, 1400);

			recv_message(&r);

			char *comanda;
			comanda = (char*)malloc(1400);

			comanda = corect(r);

			send_message(&r);

			if(strstr(comanda, "cd") != NULL){
				chdir(comanda + 3);
			}
			else if(strstr(comanda, "ls") != NULL){
				lsHamming(comanda);
			}
			else if(strstr(comanda, "cp") != NULL){
				cpHamming(comanda);
			}
			else if(strstr(comanda, "sn") != NULL){
				snHamming(comanda);
			}
			else if(strstr(comanda, "exit") != NULL){
				return 0;
			}
		}
	}

	printf("[RECEIVER] Finished receiving..\n");
	return 0;
}
