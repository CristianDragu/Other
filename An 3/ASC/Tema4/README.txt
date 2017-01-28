Tema 4 ASC

Student: Dragu Cristian
Grupa: 332 CC

In rezolvarea temei am pornit de la solutia laboratorului 10.
Solutia consta in folosirea a 3 vectori (latitudine, longitudine si
population), care sunt trimisi la device (GPU) pentru a verifica 
distanta de la o zona la alta.

Functia init_data => aloca memorie pentru cei 3 vectori si citeste
linie cu linie (folosind fgets) din fisier. Continutul liniei citite
(stocata in buf) este copiat si formatat in vectori.
Variabilele geonameid, asciiname si country_name sunt variabile buffer
care sunt folosite doar la citire, deoarece datele scrise in acestea 
nu ajuta in parcurgerea algoritmului.
Variabila "length" reprezinta lungimea celor 3 vectori enumerati mai 
sus, si anume numarul de zone/orase.

In functia gpu_execut_kernel sunt alocate buffere cu dimensiuni 
corespunzatoare celor 3 vectori. Pentru fiecare vector cu date este
alocat un vector al carui nume contine prefixul "device_".

Folosing clEnqueueWriteBuffer sunt copiate datele din memoria locala
in memoria device-ului GPU.

In fisierul device.cl este implementat kernel-ul kernel_id care 
calculeaza populatia accesibila dintr-o zona.

Pentru fiecare zona, sunt calculate distantele de la aceasta la toate
celelalte zone, iar daca distanta dintre ea si o alta zona este mai mica
decat argumentul kmrange, atunci se adauga populati zonei adiacente la
populatia accesibila corespunzatoare.

*****
Mentionez ca am incercat sa rezolv tema folosind si structuri:

typedef struct coord{
	cl_float latitudine, longitudine;
}coord;

typedef struct data{
	coord position;
	cl_int population;
}data;

Am mers pe idea de folosire a structurilor deoarece implementarea este mai
compacta si intuitiva (nefiind nevoia de utilizare a 3 vectori separati).

NU am reusit sa trimit structura la device si de aceea am decis sa folosesc
prima metoda de mai sus.
