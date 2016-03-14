Tema 2 EGC

Nume: Dragu Cristian
Grupa: 332 CC

Explicare variabile(cele mai importante) folosite:

- obiecte = vector cu elemente de tip Mesh. Se stocheaza in el toate elementele platformelor
- cola1, cola2, TREX = elemente Mesh ce reprezinta bonusuri, respectiv inamici

Am folosit ca schelet pentru tema, codul din laboratorul 5.

Am modificat clasa Mesh astfel incat sa aiba in componenta sa o structura "punct" ce ma ajuta 
sa retin coordonatele coltului stanga-spate-jos, respectiv dreapta-fata-sus.

Deplasarea se face conform cerintei problemei, utilizand tastele a, d si spacebar. Camera 
se roteste cu sagetile stanga si dreapta. Animatiile sunt conform cerintei.
Tasta de reset este 'c'.

Explicare algoritm din metoda notifyEndFrame:

Daca jocul nu s-a terminat, verific daca s-a dat o comanda de rotire a camerei. Daca da, 
atunci rotesc camera treptat cu un factor fix(0.1). Daca nu se roteste camera, atunci 
verific coliziunea cu fiecare element din platforme si cu inamicii si bonusurile din joc. 
Metoda hasCollision verifica coliziunea bilei ("personajul principal") cu diferitele 
elemente. De asemenea verific si daca cumva bila se afla pe un obiect (booleanul peobiect), 
desi prezinta coliziune cu acesta. Daca un obiect are coliziune cu bila, dar bila se afla 
pe obiect, atunci se poate deplasa.
Variabila jump si booleanul sepoatesari sunt motorul sariturii. Daca bila se afla pe un 
corp, atunci se poate executa o saritura. Cand tasta Spacebar este apasata variabila jump 
se incarca cu o valoare fixa, care apoi este scazuta treptat odata cu translatarea in sus 
a bilei, pana cand devine 0. Bila este in libera cadere atat timp cat peobiect == false, 
adica se afla in aer.