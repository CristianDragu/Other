/******************************************************************************/
/* Tema 2 Protocoale de Comunicatie (Aprilie 2015)                            */
/******************************************************************************/

#include "sim.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api.h"
#include "utils.h"

int versioning = 1;

typedef struct{

  int version;
	int vecini[100][100];
  int *tabela_rutare;

} nod;

typedef struct{

  int r1, r2, type, cost, moment;

} eveniment;

typedef struct{

  int src, dst, moment, tag;
  char payload[1000];

} mesaj;

int n, timp, nrevenimente, nrmessages;
mesaj *mesaje;
eveniment *evenimente;
nod *routere;

FILE *events;
FILE *messagesfile;

nod init_router(nod router){
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      router.vecini[i][j] = 32000;

  return router;
}

void init_sim(int argc, char **argv) {
  
  FILE *topologie;

  topologie = fopen(argv[1], "r");
  messagesfile = fopen(argv[2], "r");
  events = fopen(argv[3], "r");

  fscanf(topologie, "%d", &n);

  routere = new nod[n];
  for(int i = 0; i < n; i++){
    routere[i].tabela_rutare = new int[n];
    routere[i] = init_router(routere[i]);
  }


  int start, end, cost;
  char* message;

  while(!feof(topologie)){
  	fscanf(topologie, "%d%d%d", &start, &cost, &end);

  	routere[start].vecini[start][end] = cost;
    //routere[start].vecini[end][start] = cost;
  }

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(i != j && routere[i].vecini[i][j] != 32000){
        message = new char[100];
        sprintf(message, "%d %d %d %d", j, routere[i].vecini[i][j], i, versioning);
        //printf("%s\n", message);
        endpoint[i].send_msg(&endpoint[j], message, strlen(message), NULL);
      }

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      routere[i].vecini[j][j] = 0;

  fscanf(events, "%d", &timp);
  fscanf(events, "%d", &nrevenimente);
  evenimente = new eveniment[nrevenimente];

  for(int i = 0; i < nrevenimente; i++)
    fscanf(events, "%d%d%d%d%d", &(evenimente[i]).r1, &(evenimente[i]).r2, &(evenimente[i]).type, &(evenimente[i]).cost, &(evenimente[i]).moment);
  //process_messages();

  fscanf(messagesfile, "%d", &nrmessages);
  mesaje = new mesaj[nrmessages];

  for(int i = 0; i < n; i++){
    fscanf(messagesfile, "%d%d%d%d", &(mesaje[i]).src, &(mesaje[i]).dst, &(mesaje[i]).moment, &(mesaje[i]).tag);
    fgets(mesaje[i].payload, 1000, messagesfile);
  }

}

void clean_sim() {
  
  for(int i = 0; i < n; i++){
    printf("Nodul %d are vecinii: ", i);
    for(int  j = 0; j < n; j++)
      if(routere[i].vecini[i][j] != 32000)
        printf("%d ", j);
    printf("\n");
  }

  printf("\n");

  printf("Routerul 1 are urmatoarea tabela:\n");
  for(int k = 0; k < n; k++){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++)
      if(routere[k].vecini[i][j] != 32000)
        printf("%d ", routere[k].vecini[i][j]);
      else
        printf("0 ");
    printf("\n");
  }
  printf("\n");
}

    int i,j,k,ok=1;

    for (i=0;i<n;i++)
      for (j=0;j<n;j++)
          for (k=1;k<n;k++)
            if (routere[k-1].vecini[i][j]!=routere[k].vecini[i][j]) ok=0;

  if (ok==1) printf("DA\n");
  else printf("NU\n");

}

int ind = 0;

void trigger_events() {

  while(ind < nrevenimente){
    if(get_time() < evenimente[ind].moment)
      break;
    else if(get_time() == evenimente[ind].moment){
      versioning++;
      if(evenimente[ind].type == 1){
        char* message;
        message = new char[100];
        sprintf(message, "%d 32000 %d %d", evenimente[ind].r2, evenimente[ind].r1, versioning);
        for(int i = 0; i < n; i++)
          if(routere[evenimente[ind].r1].vecini[evenimente[ind].r1][i] != 32000 && evenimente[ind].r1 != i)
            endpoint[evenimente[ind].r1].send_msg(&endpoint[i], message, strlen(message), NULL);
        
        routere[evenimente[ind].r1].vecini[evenimente[ind].r1][evenimente[ind].r2] = 32000;
        routere[evenimente[ind].r1].vecini[evenimente[ind].r2][evenimente[ind].r1] = 32000;
      }
      else if(evenimente[ind].type == 0){
        char* message;
        message = new char[100];
        sprintf(message, "%d %d %d %d", evenimente[ind].r2, evenimente[ind].cost, evenimente[ind].r1, versioning);
        routere[evenimente[ind].r1].vecini[evenimente[ind].r1][evenimente[ind].r2] = evenimente[ind].cost;
        routere[evenimente[ind].r1].vecini[evenimente[ind].r2][evenimente[ind].r1] = evenimente[ind].cost;
        for(int i = 0; i < n; i++)
          if(routere[evenimente[ind].r1].vecini[evenimente[ind].r1][i] != 32000 && evenimente[ind].r1 != i)
            endpoint[evenimente[ind].r1].send_msg(&endpoint[i], message, strlen(message), NULL);
      }
    }

    ind++;
  }

  printf("Se face update la events\n");

}

int indmes = 0;

void process_messages() {
  
  char *msg, *p, *message;
  msg = new char[1000];
  message = new char[1000];

  int start, end, cost, msg_size, versiune, src, dst, tag;
  bool valid;

  for(int i = 0; i < n; i++){
    while((msg_size = endpoint[i].recv_protocol_message(msg)) > -1){
        p = strtok(msg, " ");
        start = atoi(p);
        p = strtok(NULL, " ");
        cost = atoi(p);
        p = strtok(NULL, " ");
        end = atoi(p);
        versiune = atoi(strtok(NULL, " "));

        if(routere[i].version <= versiune){
          if(cost == 32000 && (routere[i].vecini[start][end] != 32000 || routere[i].vecini[end][start] != 32000)) {
            routere[i].version = versiune;
            for(int j = 0; j < n; j++)
              if(routere[i].vecini[i][j] != 32000){
                sprintf(message, "%d %d %d %d", start, cost, end, versiune);
                endpoint[i].send_msg(&endpoint[j], message, strlen(message), NULL);
              }
              routere[i].vecini[start][end] = cost;
              routere[i].vecini[end][start] = cost;
              //printf("A intrat pe ramura de 32000 %d\n", i);
          }
          else if((routere[i].vecini[start][end] != cost || routere[i].vecini[end][start] != cost) && cost != 32000){
            routere[i].vecini[start][end] = cost;
            routere[i].vecini[end][start] = cost;
            routere[i].version = versiune;
            for(int j = 0; j < n; j++)
              if(routere[i].vecini[i][j] != 32000){
                sprintf(message, "%d %d %d %d", start, cost, end, versiune);
                //printf("%d %d %s\n", i, j, message);
                endpoint[i].send_msg(&endpoint[j], message, strlen(message), NULL);
              }
              //printf("A intrat pe ramura de umplere cu vecini\n");
          }
        }
    }
    
    while((valid = endpoint[i].recv_message(&src, &dst, &tag, msg))){
      if(i != dst){
        endpoint[i].route_message(&endpoint[routere[i].tabela_rutare[dst]], dst, tag, msg, NULL);
      }
    }

  }

  while(indmes < nrmessages){

    if(get_time() < mesaje[indmes].moment)
      break;
    else if(get_time() == mesaje[indmes].moment){
      //printf("Acesta este mesajul %s", mes)
      endpoint[mesaje[indmes].src].route_message(&endpoint[routere[mesaje[indmes].src].tabela_rutare[mesaje[indmes].dst]], mesaje[indmes].dst, mesaje[indmes].tag, mesaje[indmes].payload, NULL);
    }

    indmes ++;
  }

  //printf("Se face update la legaturi\n");
}

void Dijkstra(int sursa){

  int i, min, k, ok, vizitat[n], path[n], parent[n];

  for (i = 0; i < n; i++) {
      path[i] = routere[sursa].vecini[sursa][i];
      parent[i] = sursa;
      vizitat[i] = 0;
  }

  parent[sursa] = -1;
  vizitat[sursa] = 1;
  ok = 1;

  while (ok) {
    min = 32000;
    for (i = 0; i < n; i++)
        if (path[i] && !vizitat[i] && min > path[i]) {
          min = path[i];
          k = i;
        }
    if (min != 32000) {
      vizitat[k] = 1;
      for (i = 0; i < n; i++)
        if (!vizitat[i] && path[i] > path[k] + routere[sursa].vecini[k][i]) {
          path[i] = path[k] + routere[sursa].vecini[k][i];
          parent[i] = k;
        }
    }
    else ok = 0;
  }

  int x;
  for (i = 0; i < n; i++) {
    x = i;
    while (x != sursa && parent[parent[x]] != -1) {
      x = parent[x];
    }
    routere[sursa].tabela_rutare[i] = x;
    //printf("am stabilit pt routerul %d rutarea pt %d\n", sursa, i);
  }

}

void update_routing_table() {

  for(int i = 0; i < n; i++)
    Dijkstra(i);

}
