Tema 1 PC

Nume: Dragu Cristian
Grupa: 322CC

Am implementat metode pentru toate subpunctele.

Fiecare metoda are un nume specific (de exemplu, pentru partea de ls, cele 3 metode pentru modurile diferite de testare sunt ls, lsParity, lsHamming; regula se aplica si pentru celelalte subpuncte).

Metodele sendACK si sendNACK au rolul de a trimite mesaje de ack, respectiv nack.

Metoda Parity returneaza paritatea unui sir de caractere.

Cele 2 metode "codificare" si "corect", codifica, respectiv decodifica, un sir de caractere. (am incercat sa urmaresc schema din pdf-ul temei astfel ca citirea codului sa devina mai usoara, pentru codificarea bitilor).

Mentionez ca toate testele se termina cu succes, fara loop-uri infinite, cu exceptia ultimelor doua, unde, in ciuda faptului ca scot pachetele bune din fisier (la cp Hamming), nu le scriu bine in fisierul destinatie, probabil o problema venita de la lungimea sirului returnata de strlen sau fread.
