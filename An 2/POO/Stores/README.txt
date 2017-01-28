Tema POO

Nume: Dragu Cristian
Grupa: 322 CC
Grad de dificultate: 8
Timp alocat: intre 20 si 25 ore

Descriere mod de implementare:

Toate clasele au fost implementate conform cerintei, cu exceptia unor variabile.
Modelul de implementare Factory Pattern se faseste in clasa MagazinFactory.
In clasa Gestiune se gaseste si modelul Singleton Pattern.
Variabilele adaugate in plus, fata de cerinta temei, cu scopul de a imi face creearea temei
mai usoara sunt: in clasa Magazin am adaugat o variabila de tip String in care se retine tipul
magazinului (cu valorile "Minimarket" / "MediumMarket" / "HyperMarket") si initializata in 
constructorul fiecarei clase care mosteneste clasa Magazin; in Gestiune am adaugat un vector
tari pentru a imi fi mai comod sa utilizez tarile.
De altfel am adaugat o metoda calculScutiriTaxeTara in fiecare clasa care mosteneste Magazin,
care imi genereaza rezultatul dorit, pentru o tara, in functie de rezultatul returnat de metoda 
calculScutiriTaxe.

In clasa Gestiune, cele 3 metode, ProduseRead, TaxeRead, FacturiRead, citesc fisierele de intrare,
si construiesc datele necesare generarii fisierului out. Metoda PrintOut genereaza fisierul out,
conform cerintei.
Am folosit DecimalFormat pentru afisarea rezultatelor de calcul cu 4 zecimale.

Fisierul Interfata contine toate clasele si metodele folosite in creearea unei interfete grafice
adecvate.

! Mentionez ca am implementat bonusul de logare !

Fereastra de logare  este implementata in metoda logWindow.
Fereastra de index, de start, cu butoanele catre celelalte ferestre.
Fereastra de incarcare a fisierelor este implementata in metoda filesWindow.
Fereastra de administrare a produselor, in metoda administrationWindow.
Fereastra de statistici in statisticsWindow.

Am incercat sa dau nume metodelor si variabilelor astfel incat sa se inteleaga mai usor la ce sunt 
folosite si cu ce ajuta.