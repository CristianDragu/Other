Tema 1 EGC

Nume student: Dragu Cristian
Grupa: 332 CC

Am implementat tema utilizand scheletul de cod din laboratorul 3.

Fiecare raza este generata in pozitia (0,0) a primului cerc trigonometric, apoi este rotita conform ughiului de rotatie calculat.
Pentru scalare, translatare si rotire, am folosit metodele prezentate in cadrul laboratorului.
Cele n raze (ex: 20 in cazul implementarii mele) sunt obiecte de tip mesh si stocate in vectorul raze[].
Obiectele (obstacolele) din cadrul scenei sunt stocate in vectorul, de tip mesh, obiecte[].
Coordonatele obiectelor (punctul stanga jos, respectiv punctul din dreapta sus) sunt stocate in vectorul de perechi deptunghiuri[].
Toate obiectele (obstacolele) scenei sunt dreptunghiuri. Doar sursa este un cerc, iar oglinda un triunghi, conform cerintei temei.
Fiecare obstacol isi schimba culoarea la o noua rulare a programului. De asemenea, la fiecare apasare a unei taste "w" sau "s", scena 
se reseteaza la forma initiala, iar unghiul razei initiale se modifica.
Scena este fixa, fiind folosite valori date de mine pentru obstacole, cadru, etc.
Sursa, fiind un cerc, am creat-o cu ajutorul metodei myLoadCircle_as_Mesh.

La fiecare pas, se verifica daca varful razei curente, obtinut prin proiectia razei pe cele 2 axe de coordonate, se alfa in scena.
- In cazul in care varful paraseste scena, inseamna ca a atins un perete exterior, iar raza trebuie reflectata. Se creeaza o noua raza, 
se initializeaza lungimea ei, matricea de transformare corespunzatoare, coordonatele varfului, si se roteste conform unghiului de 
reflexie.
- In cazul in care raza are contact cu un obstacol, se verifica daca a atins o latura orizontala sau una verticala si se refac pasii de 
la cazul anterior. Daca raza atinge o latura orizontala, atunci unghiul de reflexie este calculat cu formula 2*pi - alfa, unde alfa este 
unghiul razei incidente fata de axa Ox. Daca atinge o latura verticala, unghiul de reflexie, fata de Ox, este dat de pi - alfa.
- Altfel, daca raza nu a atins un obstacol sau un perete al scenei, raza se scaleaza, iar varful razei este recalculat.