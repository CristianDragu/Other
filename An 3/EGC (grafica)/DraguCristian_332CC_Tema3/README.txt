Tema 3 EGC

Nume: Dragu Cristian
Grupa: 332 CC

Am implementat tema utilizand laboratorul 7.

Main.cpp:

Am scris clasa Unda ce ma ajuta sa retin caracteristicile unei unde in fiecare obiect de tip Unda.
Vectorul cu obiecte de tip Unda este trimis catre shader vertex (fiecare element in parte).

Shader_gouraud_vertex.glsl:

Am importat toate caracteristicile undelor intr-un vector de tipul Unda (o structura scrisa in shader ce reprezinta echivalentul 
clasei din main cu acelasi nume). 
Pentru fiecare unda, calculez inaltimea in punctul curent, dar si in cele 4 puncte alaturate, utilizand formula sinusoidala. Apoi 
urmand metoda prezentata in enuntul temei, am calculat lumina in punctul curent.

Am implementat 3 unde, dar tema va fi prezentata la laborator utilizand doar 2 unde (una circulara si una directionala) pentru 
claritate si simplitudine. 
Daca se doreste rularea temei cu cele 3 unde, sau in orice format dorit, modificati for-ul din shader vertex. (e singurul for :) ).