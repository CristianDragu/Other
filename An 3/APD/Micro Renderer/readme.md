Tema 1 APD - Micro Renderer si Resize folosind tehnici antialiasing

Student: Dragu Cristian
Grupa: 332 CC

Partea 1. SSAA

Am rezolvat aceasta parte a temei utilizand structura image (aflata in homework.h).
Structura are ca parametrii:

- pType -> descrie tipul imaginii. P5 sau P6
- pixelByte -> cati octeti trebuie sa citesc pentru descrierea fiecarui pixel, in functie de tipul 
imaginii (3 daca imaginea este P6, respectiv 1 daca imaginea este P5)
- width si height -> descriu dimensiunile imaginii
- maxValColor -> valoarea maxima a culorilor
- data -> matrice in ce se retin toti octetii ce descriu poza
- res -> matrice rezultat, ce contine octetii imaginii careia i s-a aplicat algoritmul SSAA.

In metoda readInput, deschid un fisier binar din care citesc caracteristicile pozei si le depun 
intr-un element de tip image. Alocarea matricei de date, respectiv res (reszultat), s-a facut 
dinamic. Citirea octetilor pozei s-a facut cu fread, citind cate o linie intreaga de height ori.

In metoda writeData, am deschis fisierul binar in care am scris caracteristicile noii imagini 
rezultate. Am scris octetii imaginii cu functia fwrite.

Descriere metoda resize:

Am copiat caracteristicile (height, width, pType, pixelByte, maxValColor) in variabila out.
In functie de tipul imaginii (P5 sau P6) si al factorului de redimensionare (resize_factor),
aleg cum sa parcurg matricea cu octetii imaginii (data[][]).
Aloc, in paralel, memorie matricei res din variabila out.
Apoi paralelizez parcurgerea matricei data din variabila in, pentru a calcula octetii rezultati 
prin aplicarea algoritmului conform enuntului (inmultind cu kernel gaussian sau medie aritmetica).
sumr, sumg si sumb sunt variabile de tip int in care se depun sunele pentru ca apoi sa fie puse in 
matricea rezultat.
O instructiune in genul "heightImg -= (heightImg % resize_factor);" este desemnata scalarii 
(calcularii dimensiunilor imaginii, care se impart exact la resize_factor).

Partea 2. Micro renderer

Am utilizat tot o structura images, dar care contine doar latura patratului si matricea data.

Imaginea este creata in metoda render.
Aloc matricea data, si paralelizez parcurgerea matricei de width * width octeti. Folosind 
functia de calcul a distantei al unui punct pana la o dreapta, determin culoarea pixelului.

In metoda writeData scriu in fisierul binar de iesire caracteristicile imaginii folosind fprintf 
si fwrite.

Am testat scalabilitatea solutiei atat pe cluster, cat si pe masina locala.

Masina locala (laptop) are urmatoarele caracteristici:

CPU: Core I7 2.5 GHz, quad-core
RAM: 8 GB

Poza utilizata este de tip P6, cu dimensiuni de 4943 x 2515.

In urma rularii temei pe cluster, s-au obtinut urmatoarele rezultate:

./homework blue-abstract-glass-balls.pnm aux.pnm 2 1 => 0.240159
./homework blue-abstract-glass-balls.pnm aux.pnm 2 2 => 0.126734
./homework blue-abstract-glass-balls.pnm aux.pnm 2 4 => 0.067329
./homework blue-abstract-glass-balls.pnm aux.pnm 2 8 => 0.040369
./homework blue-abstract-glass-balls.pnm aux.pnm 3 1 => 0.108895
./homework blue-abstract-glass-balls.pnm aux.pnm 3 2 => 0.057530
./homework blue-abstract-glass-balls.pnm aux.pnm 3 4 => 0.031431
./homework blue-abstract-glass-balls.pnm aux.pnm 3 8 => 0.018620
./homework blue-abstract-glass-balls.pnm aux.pnm 4 1 => 0.150181
./homework blue-abstract-glass-balls.pnm aux.pnm 4 2 => 0.077210
./homework blue-abstract-glass-balls.pnm aux.pnm 4 4 => 0.039844
./homework blue-abstract-glass-balls.pnm aux.pnm 4 8 => 0.021389
./homework blue-abstract-glass-balls.pnm aux.pnm 8 1 => 0.127175
./homework blue-abstract-glass-balls.pnm aux.pnm 8 2 => 0.064110
./homework blue-abstract-glass-balls.pnm aux.pnm 8 4 => 0.032206
./homework blue-abstract-glass-balls.pnm aux.pnm 8 8 => 0.016363
./homework1 100 100 1 => 0.000571
./homework1 100 100 2 => 0.000338
./homework1 100 100 4 => 0.000220
./homework1 100 100 8 => 0.000198
./homework1 10000 10000 1 => 5.584525
./homework1 10000 10000 2 => 2.804061
./homework1 10000 10000 4 => 1.409416
./homework1 10000 10000 8 => 0.712062