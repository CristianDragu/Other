Tema 2 PC

Student: Dragu Cristian
Grupa: 322 CC

Implementarea algoritmului are la baza 3 structuri de date principale: nod(router), eveniment, mesaj. 
Voi retine in 3 vectori de tipul fiecarei strucuri, datele din cele 3 fisiere de intrare. Apoi, voi
face modificari in legatura cu tabela de rutare si topologie, retinand fiecare schimbare in nodurile 
din vectorul routere (de tip nod). Mesajele din fisierul messages.in vor fi depuse in vectorul 
mesaje, iar evenimentele ce trebuiesc tratate au fost puse in vectorul evenimente.

Metoda init_sim face initializarile structurilor (vectori, matrici, etc), face citirile corespunzatoare, 
pune in tabelele de topologie ale fiecarui nod costurile catre vecinii directi ( matricea de topologie 
a fiecarui nod este numita vecini ).

Metoda trigger_events se uita la primul eveniment din vectorul de evenimente si vede daca s-a ajuns la 
timpul corespunzator. Daca s-a ajuns la timpul respectiv, atunci proceseaza primul mesaj, il trimite 
catre vecinii directi ai nodului, si apoi trece la urmatorul mesaj. Se repepta actiunea pana se ajunge 
la finalul vectorului.

In metoda process_messages se verifica pentru fiecare router daca s-au primit mesaje, iar daca s-au 
primit, se vor face modificarile corespunzatoare in topologie, si se vor trimite mesaje cu schimbarile 
facute vecinilor directi. De altfel, se verifica tot pentru fiecare router daca s-au primit mesaje 
rutabile, si le trimite mai departe pana ajung la destinatie, si se initializeaza trimiterea de 
mesaje rutabile daca s-a ajuns la timpul corespunzator.

Pentru updatarea tabelelor de rutare am folosit un algoritm Dijkstra, si am scos la sfarsit nodul dorit 
pentru a fi introdus in tabela de rutare a fiecarui nod.