Nume Echipa: 
	Still Loading

Studenti: 	
	Dragu Cristian - capitan
	Margarit Vicentiu
	Constantinescu Daniel-Andrei
	Dragan Daniela
			

ETAPA 1

->Alegerea Regiunilor:

	Avem 3 ArrayListuri: Unul cu SuperRegiuni fara bonus, unul fara wastelanduri si unul cu wastelanduri. Le sortez pe fiecare in 
felul urmator: cel fara bonus crescator dupa dimensinue si crescator dupa numarul de wastelanduri(exista si SuperReginui fara bonus dar cu 
wastelanduri), cel fara wastelanduri crescator dupa dimensiune si descrescator dupa bonus, iar cel cu wastelanduri crescator dupa numarul 
de wastelanduri si descrescator dupa bonus. Aleg mai intai regiuni din ArrayList-ul fara wastelanduri, apoi daca asta e gol aleg din cel 
cu wastelanduri, iar in final aleg din cel fara bonus.

->Plasament:

	Metoda hasEnemyNear verifica daca o regiune are un inamic in apropiere (player sau neutru).

	Metoda computeArmiesDifferences creeaza un vector cu diferentele de armate intre o regiune detinuta de mine si maximul de unitati 
dintr-o regiune inamica vecina cu aceasta (player sau neutra). Apoi sorteaza vectorul crescator. (unde diferenta este negativa, 
inseamna ca in acea regiune trebuiesc plasate armate pentru a consolida apararea). Cu cat diferenta este un numar mai mic, cu atat 
inseamna ca trebuie consolidata mai puternic acea regiune.

	Metoda getPlaceArmiesMoves este bazata pe modul greedy. Calculeaza suma dezavantajelor (diferentelor negative de unitati din vectorul 
obtinut din computeArmiesDifferences) si pe baza aceste sume creeaza un factor de calitate (armiesFactor). Cu acest factor de calitate 
se vor distribui armatele cu conditia ca numarul de armate initiale inmultit cu factorul sa fie mai mic ca numarul de unitati ramase 
pentru distribuire. Dupa ce s-au completat diferenta de armate, daca mai raman unitati nedistribuite, atunci ele vor fi puse in 
regiunea din varful vectorului (regiunea cu deficitul cel mai mare).

->Transfer:

	Metoda deployOnFrontier, completeaza vectorul cu transferurile ce urmeaza a fi facute. Metoda implementeaza un algoritm BFS care cauta 
drumul cel mai scurt de la regiunile din interiorul zonei detinute (compactul de regiuni detinute de mine) catre cea mai apropiata 
regiune de pe frontiera. In momentul gasirii unei regiuni de pe frontiera, metoda makePath parcurge drumul recursiv inapoi pentru a 
vedea care este regiunea unde trebuie mutata armata din regiunea mea initiala.

->Atac:

	Iau 4 ArrayListuri, unul cu regiuni neutre din aceeasi SuperRegiune, unul cu regiuni inamice din aceeasi SuperRegiune, unul cu regiuni neutre din alte SuperRegiuni si unul cu regiuni inamice din alte SuperRegiuni. Daca am armata suficienta(sa depasesc acel 70% ca sa fiu sigur ca va merge atacul) fac attackTransferMove daca nu astept inca o runda.



ETAPA 2

->Alegerea Regiunilor:

	La fel ca la etapa 1.

->Plasament:

	Am introdus intr-un ArrayList toate SuperRegiunile ce le vad pe harta iar din astea le-am selectionat numai pe cele din SuperRegiuni ce nu sunt detinute total de mine si pe cele ce au un bonus. Daca nu au bonus atunci le iau numai daca vad un inamic in aceea SuperRegiune. Sortez crescator aceste SuperReginui in functie de numarul de reginui ce mai trebuiesc cucerite(adica pe primul loc se va afla SuperRegiunea cu doar o regiune necucerita iar pe ultimul loc SuperRegiunea cu 0 teritorii cucerite). Iau pe rand fiecare SuperRegiune si caut prima regiune ce are inamici prin preajma. Cand o gaseste cauta numarul de inamici din jur si pune in regiune numarul de inamici * 1.5 - armata din regiune + 1. Dupa asta da break si trece la urmatoarea SuperRegiune. Daca au mai ramas soldati si nu exista SuperRegiuni goale(adica nu detin nimic in ele) repet pasul. Daca exista SuperRegiuni necucerite iau prima SuperRegiune, iau pe rand toate regiunile si caut prin vecinii ei, o regiune detinuta de mine si pun in vecin(adica regiunea mea) restul de armata.

->Transfer:

	La fel ca la etapa 1.

->Atac:

	La fel ca la etapa 1.