Tema 2 PA

Nume: Dragu Cristian
Grupa: 322 CC

Problema 1

Solutia problemei se bazeaza pe gasirea tuturor drumurilor de 2 si 3 muchii, din graful initial, apoi
se unesc toate aceste drmuri intr-un nou graf neorientat. Se aplica pe acest graf un algoritm de flux 
maxim. Fluxul maxim va reprezenta solutia problemei.

Date de implementare:

-neighbors = vector de vector ce contine muchiile initiale ale grafului.
-paths = lista cu drumurile de 2 si 3 muchii.
-capacity = matricea noului graf rezultat.

Detalii despre metodele folosite se gasesc in sursa problemei.

Problema 2

Algoritmul folosit pentru rezolvarea cerintei se bazeaza pe gasirea unui termen care sa "aproximeze" 
cat mai exact costul printr-o muchie, folosind costul initial si profitul din destinatia muchiei.
Astfel am folosit un algoritm de tip Divide et Impera, pentru gasirea termenului dorit si un 
algoritm Belman-Ford pentru verificarea existentei ciclurilor de cost infinit in graful nou rezultat 
cu noile costuri. (matricea de adiacenta a grafului nou este cost).

Date de implementare:

- muchii_initiale = lista cu muchiile din graful initial
- muchii = lista cu muchiile din noul graf rezultat la fiecare pas al DEI. Acest vector se 
	reinitializeaza la fiecare apel recursiv al DEI.
- Muchie = clasa pentru reprezentarea unei muchii.

Mentiuni:

- algoritmul Belman-Ford folosit in rezolvarea urmeaza pseudocodul din laborator.
- cautare_binara (metoda DEI) cauta rezultatul intre 0 si costul tutorur muchiilor din graful initial.