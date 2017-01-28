Flex Parser

// Dragu Cristian 332CC

Am ales ca testele mele sa urmeze modelul dat ca exemplu in enuntul temei. Astfel testele au definitiile de functii 
la inceputul programului, iar functiile cu tot cu continut sunt scrise sub main. Numele functiilor din definitii, le 
adaug intr-un vector.

Identific functiile ce sunt urmate de corpul lor (exemplu: void func1(..argumente..){ ). Afisez numele functiei ce 
tocmai am identificat-o si initializez variabila care numara apelurile de functii (nrFunc).

Apelul unei functii este de tipul func1(); (; la final) ce il distinge de if, for si while, care ar da eroare daca 
se pune ; dupa ele.
Daca intalnesc o functie ce a fost definita la inceputul programului, atunci o afisez si incrementez variabila nrFunc.

Citirea input-ului se face din fisiere de intrare folosind yyin.

Am folosit aceasta solutie deoarece parcurg o singura data input-ul.

MULT mai multe detalii legate de implementare se gasesc in comentariile din fisierul sursa TemaC.l.
