#include "helper.h"

FILE *in;

void error(char *msg){
    perror(msg);
    exit(0);
}

// Metoda care deconecteaza clientul
void closeClient(char *msg, int publicSocket, int serverSocket){
    print_log_entry(msg);
    close(publicSocket);
    close(serverSocket);
    exit(0);
}

// Metoda care adauga un fisier, daca nu exista deja, in lista locala de fisiere
int addFiles(Files *sharedFiles, int nrFiles, char *p){

  int i, sem = 0;
  for(i = 0; i < nrFiles; i++)
    if(strcmp(sharedFiles[i].name, p) == 0)
      sem = 1;

  if(sem == 0){
    strcpy(sharedFiles[nrFiles].name, p);
    nrFiles++;
  }

  return nrFiles;
}

// Metoda care cauta si sterge un fisier din lista locala de fisiere
int checkSharedFile(Files *sharedFiles, int nrFiles, char *p){

  int i;
  for(i = 0; i < nrFiles; i++){
    if(strcmp(sharedFiles[i].name, p) == 0){
      if(i == nrFiles - 1)
        return 1;
      else{
        strcpy(sharedFiles[i].name, sharedFiles[nrFiles - 1].name);
        return 1;
      }
    }
  }

  return 0;
}

int main(int argc, char *argv[]){
  //validateArgs(argc, argv);

  int sockfd, n, fdmax, nr, i, len;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  fd_set read_fds,tmp_fds;

  Client clients[MAX_CLIENTS];
  // sharedFiles = vector cu fisierele partajate ale clientului
  Files *sharedFiles;
  int nrFiles = 0;
  sharedFiles = (Files*)malloc(sizeof(Files) * 1000);

  char buffer[BUFFER_LENGTH];
  // Pregatesc deschiderea folderului care contine fisierele clientului
  char numeFisier[40];
  strcpy(numeFisier, argv[2]);

  // Daca comanda de deschidere a clientului nu este corecta inchid programul
  if (argc < 5) {
    fprintf(stderr,"Usage %s nume_client folder_client port_client server_address server_port\n", argv[0]);
    exit(0);
  }

  // Deschid socketul prin care comunic cu serverul
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");
    
  FD_ZERO(&read_fds);
  FD_ZERO(&tmp_fds);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(atoi(argv[5]));
  inet_aton(argv[4], &serv_addr.sin_addr);
        
  validateCommand( connect(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0, returnErrorCode(CONNECT_ERROR), CONNECT_ERROR ); 
  memset(buffer, 0, BUFFER_LENGTH);
  sprintf(buffer, "%s %s", argv[1], argv[3]);
  send(sockfd, buffer, strlen(buffer), 0);

  FD_SET(0, &read_fds);
  FD_SET(sockfd, &read_fds);
  fdmax = sockfd;

  // Creez fisierul de log al clientului
  strcpy(log_file_name, argv[1]);
  sprintf(log_file_name, "%s.log", log_file_name);
  logFile = fopen( log_file_name, "wt" );
  fclose(logFile);

  while(1){
    tmp_fds = read_fds;
    // Ascult pe multimea socketilor de citire
    validateCommand( select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1, returnErrorCode(READWRITE_ERROR), READWRITE_ERROR );

    for (i = 0; i <= fdmax; i++) {
      if ( FD_ISSET(i, &tmp_fds) ) {
        if (i == sockfd){
          memset(buffer, 0, BUFFER_LENGTH);
          if ((n = recv(i, buffer, sizeof(buffer), 0)) <= 0) {
            // Daca apare o eroare inseamna ca serverul este inchis sau eroare de primire
            if (n == 0) {
              error("Server closed");
            } else {
              error("ERROR in recv");
            }
            close(i); 
            FD_CLR(i, &read_fds); 
          } 
          else {
            // Primesc mesaj de la server cu raspunsurile acestuia
            // Despart buffer in 2 pointeri, p si buffer: buffer va contine prima linie 
            // a mesajului, care este comanda trimisa de client, iar p este raspunsul.
            char *p = buffer;
            while(*p != '\n'){
              p++;
            }
            *p = 0;
            p++;
            printf ("SERVER:\n%s",p);
            print_log_entry(buffer);
            print_log_entry(p);

            // Daca a fost trimisa comanda cu infoclients, construiesc vectorul de clienti
            // in care retin numele, adresa si portul fiecaruia.
            if(strcmp(buffer, "infoclients") == 0){
              int nrClients = 0;
              char *line = strtok(p, "\n");
              while(line != NULL){
                char *cuvant = line;
                char *nume, *adr, *port;
                nume = line;
                while(*cuvant != ' ')
                  cuvant++;
                *cuvant = 0;
                cuvant++;
                adr = cuvant;
                while(*cuvant != ' ')
                  cuvant++;
                *cuvant = 0;
                cuvant++;
                port = cuvant;
                while(*cuvant != '\n' && *cuvant != '\0')
                  cuvant++;
                *cuvant = 0;
                strcpy(clients[nrClients].name, nume);
                strcpy(clients[nrClients].adr, adr);
                clients[nrClients].port = atoi(port);
                nrClients++;
                line = strtok(NULL, "\n");
              }
            }
          }
        }
        else {
          // Citesc de la stdin o comanda si o interpretez
          memset(buffer, 0, BUFFER_LENGTH);
          fgets(buffer, BUFFER_LENGTH - 1, stdin);
          if(strcmp(buffer, "quit\n") == 0){
            // Trimit serverului mesaj ca acest client se inchide.
            n = send(sockfd,buffer,strlen(buffer), 0);
            print_log_entry(buffer);
            print_log_entry("S-a inchis legatura cu serverul\n");
            printf("S-a inchis legatura cu serverul\n");
            close(sockfd);
            return 0;
          }
          else if(strncmp(buffer, "share", 5) == 0){
            // Scot numele fisierului din buffer pentru a verifica existenta acestuia
            char copie[BUFFER_LENGTH];
            char *p;
            strcpy(copie, buffer);
            p = strtok(copie, " ");
            p = strtok(NULL, " ");
            if(p[strlen(p) - 1] == '\n')
              p[strlen(p) - 1] = 0;
            if(buffer[strlen(buffer) - 1] == '\n')
              buffer[strlen(buffer) - 1] = 0;
            sprintf(numeFisier, "%s/%s", numeFisier, p);
            int f;
            struct stat fileStat;
            if((f = open(numeFisier, O_RDONLY)) >= 0){
              nrFiles = addFiles(sharedFiles, nrFiles, p);
              fstat(f, &fileStat);
              sprintf(buffer,"%s %ld\n", buffer, fileStat.st_size);
            }
            else {
              print_log_entry(buffer);
              print_log_entry("-5 : Fisier inexistent");
              printf("-5 : Fisier inexistent\n");
              continue;
            }
            close(f);
            strcpy(numeFisier, argv[2]);
          }
          else if(strncmp(buffer, "unshare", 7) == 0){
            char copie[BUFFER_LENGTH];
            char *p;
            strcpy(copie, buffer);
            p = strtok(copie, " ");
            p = strtok(NULL, " ");
            if(p[strlen(p) - 1] == '\n')
              p[strlen(p) - 1] = 0;
            if(checkSharedFile(sharedFiles, nrFiles, p) == 1){
              nrFiles--;
            }
            else {
              print_log_entry(buffer);
              print_log_entry("-5 : Fisier inexistent");
              printf("-5 : Fisier inexistent\n");
              continue;
            }
          }

          // Trimit mesajul procesat serverului, iar daca nu se trimite afisez mesaj
          n = send(sockfd,buffer,strlen(buffer), 0);
          if (n < 0) {
            print_log_entry("-2 : Eroare la citire/scriere pe socket");
            printf("-2 : Eroare la citire/scriere pe socket\n");
          }
        }
      }
    }
  }

  close(sockfd);

  return 0;
}
