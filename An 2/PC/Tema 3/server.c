#include "helper.h"

void error(char *msg){
  perror(msg);
  exit(1);
}

// Metoda care inchide serverul si toate legaturile lui
void closeServer (int size, int publicSocket){

	int i, len;
	char mesaj[BUFFER_LENGTH];
	strcpy(mesaj, "Serverul se inchide : exit");
	len = strlen(mesaj);
	for(i = 0; i <= size; i++){
			sendMessage(i, mesaj, len);
			close(i);
	}
	close(publicSocket);

	exit(0);
}

// Metoda care face update sau adauga datele unui fisier in vectorul de fisiere
void addFile(Client* clients, int sock, char *buf){

	int i;
	char *p;
	p = strtok(buf, " ");
	for(i = 0; i < clients[sock].nrFiles; i++){
		if(strcmp(p, clients[sock].files[i].name) == 0){
			p = strtok(NULL, " ");
			clients[sock].files[i].size = atol(p);
			return;
		}
	}

	strcpy(clients[sock].files[clients[sock].nrFiles].name, p);
	p = strtok(NULL, " ");
	clients[sock].files[clients[sock].nrFiles].size = atol(p);
	clients[sock].nrFiles++;

}

// Metoda care sterge un fisier din vectorul de fisiere, daca exista.
void deleteFile(Client* clients, int sock, char *buf){

	int i;
	char *p;
	p = strtok(buf, " ");
	for(i = 0; i < clients[sock].nrFiles; i++){
		if(strcmp(clients[sock].files[i].name, p) == 0){
			clients[sock].files[i] = clients[sock].files[clients[sock].nrFiles - 1];
			clients[sock].nrFiles --;
			return;
		}
	}
}

// Returneaza indicele clientului care are numele cautat si care este conectat
int clientConnected(Client* clients, int size, char *name){
	
	if(name[0] == 0)
		return -1;
	
	int i;
	for(i = 0; i <= size; i++)
		if(clients[i].connected && strcmp(clients[i].name, name) == 0)
			return i;

	return -1;
}

// Metoda care construieste mesajul cu toate fisierele share-uite de un client
// Se verifica cu "clientConnected" daca exista un client conectat cu numele
// respectiv, apoi se umple mesajul cu datele fisierelor partajate.
// Metoda getFormattedSize returneaza dimensiunea dorita, ca fisierul sa apara
// cu dimensiune exprimata in KiB, etc.
char* getShare(Client* clients, int fdmax, char* buf){

	int i = clientConnected(clients, fdmax, buf);
	char* mesaj = (char*)calloc(1, 255);
	if(i == -1)
		sprintf(mesaj, "-3 : Client inexistent");
	else{
		sprintf(mesaj, "Fisiere partajate de: %s", clients[i].name);
		Files *listaCurenta = clients[i].files;
		if(listaCurenta == NULL)
			sprintf(mesaj, "%s\nNiciun fisier partajat", mesaj);
		else{
			int j;
			sprintf(mesaj, "%s\n%d", mesaj, clients[i].nrFiles);
			for(j = 0; j < clients[i].nrFiles; j++)
				sprintf(mesaj, "%s\n%s %s", mesaj, listaCurenta[j].name, getFormattedSize(listaCurenta[j].size));
		}
	}
	
	return mesaj;
}

int main(int argc, char *argv[]) {

	struct sockaddr_in serv_addr, cli_addr;
  int sockfd, newsockfd, clilen;
  char buffer[BUFFER_LENGTH], mesaj[BUFFER_LENGTH];
  int n, i, k;

  Client clients[MAX_CLIENTS];

  fd_set read_fds;	//multimea de citire folosita in select()
  fd_set tmp_fds;	//multime folosita temporar 
     
  int fdmax;		//valoare maxima file descriptor din multimea read_fds

  if (argc < 2) {
    fprintf(stderr,"Usage : %s port\n", argv[0]);
    exit(1);
  }

  // Golim multimea de descriptori de citire (read_fds) si multimea tmp_fds 
  FD_ZERO(&read_fds);
  FD_ZERO(&tmp_fds);
     
  // sockfd = socketul public pe care se conecteaza toti clientii 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  validateCommand( sockfd < 0, "Eroare la crearea socketului", 3 );

  // Setez portul serverului ca cel primit ca parametru.
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;	// foloseste adresa IP a masinii
  serv_addr.sin_port = htons(atoi(argv[1]));

  validateCommand( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) < 0, "Eroare la bindarea socketului public.", 3 );
  validateCommand( listen(sockfd, MAX_CLIENTS) < 0, "Eroare la setarea socketului public pe ascultare.", 3 );

  //adaugam noul file descriptor (socketul pe care se asculta conexiuni) in multimea read_fds
  FD_SET(0, &read_fds);
  FD_SET(STDIN_FILENO, &read_fds);
  FD_SET(sockfd, &read_fds);
  fdmax = sockfd;

  // Forever loop :)
	while (1) {

		// Fac o copie a socketilor de citire originali 
		tmp_fds = read_fds;

		// Ascult pe multimea socketilor de citire
		validateCommand( select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1, returnErrorCode(READWRITE_ERROR), READWRITE_ERROR );
	
		for(i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {
				// a venit ceva pe socketul inactiv(cel cu listen) = o noua conexiune actiunea serverului: accept()
				if (i == sockfd) {
					clilen = sizeof(cli_addr);
					if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) == -1) {
						error("ERROR in accept");
					}
					else {
						//adaug noul socket intors de accept() la multimea descriptorilor de citire
						FD_SET(newsockfd, &read_fds);
						if (newsockfd > fdmax) { 
							fdmax = newsockfd;
						}
						// Initializez un nou client in vectorul de clienti.
						clients[newsockfd].connected = 1;
						clients[newsockfd].nrFiles = 0;
						strcpy(clients[newsockfd].adr, inet_ntoa(cli_addr.sin_addr));
						if(n = recv(newsockfd, buffer, BUFFER_LENGTH, 0) > 0){
							char *p;
							p = strtok(buffer, " ");
							strcpy(clients[newsockfd].name, p);
							p = strtok(NULL, " ");
							clients[newsockfd].port = atoi(p);
							clients[newsockfd].maxFiles = 10;
							clients[newsockfd].nrFiles = 0;
							clients[newsockfd].files = (Files*)malloc(10 * sizeof(Files));
						}
						else{
							// Daca se pierde conexiunea cu clientul => il deconectez
							printf("S-a pierdut conexiunea cu clientul!\n");
							clients[newsockfd].connected = 0;
						}
					}
					printf("Noua conexiune de la %s cu adresa %s, port %d, socket_client %d\n", clients[newsockfd].name, clients[newsockfd].adr, clients[newsockfd].port, newsockfd);
				}
				// Am primit date pe unul din socketii cu care vorbesc cu clientii
				else {
					memset(buffer, 0, BUFFER_LENGTH);
					if ((n = recv(i, buffer, sizeof(buffer), 0)) <= 0) {
						// Daca un client se deconecteaza => il resetez in vector
						if (n == 0) {
							printf("Conexiunea cu socket-ul %d intrerupta.\n", i);
							clients[i].connected = 0;
						} 
						// Verific daca se inchide serverul (daca am primit mesaj de quit pe server)
						else {
							fgets(buffer, BUFFER_LENGTH, stdin);
							if(strcmp(buffer, "quit\n") == 0){
								printf("Se inchide serverul.\n");
								closeServer(fdmax, sockfd);
							}
						}
						close(i); 
						FD_CLR(i, &read_fds); // scoatem din multimea de citire socketul pe care 
					}
					// Aici primesc comanda de la client
					else {
						buffer[n - 1] = 0;
						printf("Am primit comanda: %s\n", buffer);
				    	
				    // Analizez comanda primita in functie de tipul comenzii
				    	
				    if(strcmp(buffer, "infoclients") == 0){
				  	int j;
				  	memset(buffer, 0, BUFFER_LENGTH);
				  	strcpy(buffer, "infoclients\n");
				  	for(j = 0; j <= fdmax; j++){
				   		if(clients[j].connected == 0)
								continue;
				    		sprintf(buffer, "%s%s %s %d\n", buffer, clients[j].name, clients[j].adr, clients[j].port);
				    	}
				    	send(i, buffer, strlen(buffer), 0);
				    }
				    else if(strncmp(buffer, "share", 5) == 0){
				    	// Realoc vectorul de fisiere pentru un anumit client, daca este necesar
				    	if(clients[i].nrFiles == clients[i].maxFiles){
				    		clients[i].maxFiles = 2 * clients[i].maxFiles;
				    		clients[i].files = realloc(clients[i].files, clients[i].maxFiles * sizeof(Files));
				    	}
				    	char aux[BUFFER_LENGTH];
				    	strcpy(aux, buffer);
				    	addFile(clients, i, buffer + 6);
				    	memset(buffer, 0, BUFFER_LENGTH);
				    	sprintf(buffer, "%s\nSuccess\n", aux);
				    	send(i, buffer, strlen(buffer), 0);
				    }
				    else if(strncmp(buffer, "unshare", 7) == 0){
				    	char aux[BUFFER_LENGTH];
				    	strcpy(aux, buffer);
				    	deleteFile(clients, i, buffer + 8);
				    	memset(buffer, 0, BUFFER_LENGTH);
				    	sprintf(buffer, "%s\nSuccess\n", aux);
				    	send(i, buffer, strlen(buffer), 0);
				    }
				    else if(strncmp(buffer, "getshare", 8) == 0){
				    	sprintf(buffer, "%s\n%s\n", buffer, getShare(clients, fdmax, buffer + 9));
				    	send(i, buffer, strlen(buffer), 0);
				    }
					}
				} 
			}
		}

  }

  close(sockfd);

  return 0; 
}
