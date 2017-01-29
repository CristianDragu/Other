Tema 1 SPG

Nume student: Dragu Cristian
Grupa: 343 C4

1. Detalii implementare tema

Punctele de control sunt inserate in vectorul control_p care este trimis catre shader.
Punctele de control pot fi sterse sau adaugate doar in modul de CREATE. In modul de EDIT
se pot modifica pozitiile punctelor de control si tipul curbei (Bezier, Hermite, Spline,
Bspline, NURBS).

In geometry shader sunt generate n puncte pe o curba. Pentru fiecare punct, in functie
de tipul curbei dorite, se calculeaza punctul generat de algoritmul specific fiecarei 
curbe.

Pentru implementarea temei am plecat de la scheletul laboratorului 2.

Pentru aflarea tangentelor intr-un punct, la curbele ce au necesitat acest lucru 
(Hermite si Spline), m-am folosit de formula spline-urilor Catmull-Rom:

tangentak = w * (P[k + 1] - P[k - 1]);

2. Detalii rulare tema

Taste:

1 - mareste numarul de puncte generate pe curba
2 - micsoreaza numarul de puncte generate pe curba
3 - mareste numarul de instante
4 - micsoreaza numarul de instante
r - switch intre mod translatie si rotatie
b - curba bezier
s - curba spline
S - curba bspline
n - curba nurbs
h - hermite
q - mod CREATE (se adauga/sterg puncte de control)
w - mod EDIT (se poate face drag punctelor de control)
mouse clic stanga - adauga punct in modul CREATE, iar in modul EDIT muta punctul pe care
pe care se face drag
mouse clic dreapta - sterge toate punctele de control daca modul curent este CREATE.