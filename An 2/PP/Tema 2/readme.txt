Tema 2 PP - Kalah

Student: Dragu Cristian
Grupa: 322 CC

In rezolvarea temei, am implementat toate metodele din Boards.hs, respectiv AISimple.hs. Astfel, nu am 
rezolvat si partea de Mini-max.

Metode principale (mai mari):

1. Adauga pietre

    Metoda care muta pietrele in casute.
    houses = vectorul meu cu casutele ce trebuiesc parcurse cand se muta pietrele.
    val = valoarea initiala de pietre care au fost luate din casuta aleasa pentru mutare
    start = pozitia de inceput a vectorului
    ind = indice pentru pozitia actuala in vector

    Mentiuni:
    Exemplu tabla de joc:
        0 1 0 0 0 0
    0                 0
       19 1 1 1 1 1
            |
    
    Daca poz este situat pe casuta marcata cu linie, atunci vectorul meu houses va 
    fi de forma: 1 1 1 0 0 0 0 1 0 19 1 1 (pleaca de la pozitia de start si merge 
    circular pe tabla de joc).

    Metoda parcurge vectorul in mod recursiv, punand pietrele in casute.
    Pietrele sunt puse in casute doar intr-o parcurgere a vectorului, folosind formula: 
    valoareDinCasa + [valPietreActualeRamase / 14] + 1

    Baza mea are formula: 7 - start.

2. Move

 Metoda move care se foloseste de metodele de mai sus pentru a realiza o mutare
 Am folosit variabile cu nume sugestive pentru a se intelege mai usor ideea de 
 rezolvare.
 In cazul in care este la mutare oponentul, ROTESC tabla de joc pentru a putea
 folosi functiile de mai sus.
 Jucatorul care urmeaza sa execute urmatoarea mutare este dat de formulele:
   ((7 - h) + val) `mod` 13 == 7, in cazul in care muta oponentul acum
   (h + val) `mod` 13 == 7, daca You muta in momentul actual.

Mai multe detalii legate de implementare se gasesc in fisierele sursa!