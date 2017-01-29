Tema 1 IOC

Nume student: Dragu Cristian
Grupa: 343 C4

1. Prezentare implementare

Pentru rezolvarea temei am vrut sa imi construiesc propriul API care sa imi dea datele dorite, 
cum ar fi temperatura camerei, starea ferestrelor si a becurilor.
Am implementat o aplicatie RESTful folosind Java si Spring. Pentru implementarea aplicatiei am 
pornit de la tutorialul https://spring.io/guides/gs/rest-service/ care te invata cum sa 
creezi o aplicatie in Java si Spring si a rula aplicatia folosind Maven. Aplicatia facuta de 
mine are posibilitatea de a oferi mai multe informatii decat parametrii enumerati mai sus, dar 
in rezolvarea cerintei m-am limitat doar la acestia.

Pe langa acest API, m-am folosit si de call-uri de ajax catre OpenWeatherMap pentru a face rost 
de date despre vremea in zona casei, si call-uri catre Google Maps pentru a afisa o harta 
centrata pe coordonatele casei.

Dupa cum am spus si mai sus, aplicatia preia date despre vreme si daca se indica o vreme putin 
prielnica aerisirii casei, se face un call POST catre API si se inchid ferestrele.

In Rooms Manager, sunt prezentate starile parametrilor pentru fiecare camera din casa si se 
pot modifica acesti parametrii prin metode POST.

In House Preview este o schema de prezentare a casei inteligente. Treceti cu cursorul peste poza
:).


2. Rulare tema

In arhiva radacinii sunt 2 directoare: Web si API.

Directorul API contine aplicatia ce imi da datele legate de camerele casei. Pentru crearea unui 
server care sa aiba API-ul activ trebuie sa:
- aveti Maven pe PC (nu am testat rularea API-ului fara)
- deschideti un command prompt (pe Windows) in directorul API.
- daca nu aveti setata variabila globala JAVA_HOME care sa indice catre directorul cu jdk-ul 
instalat, setati-o folosind: set JAVA_HOME=[Locatie JDK] (exemplu in cazul PC-ului meu: 
set JAVA_HOME=C:\Program Files\Java\jdk1.8.0_111)
- rulati comanda: mvnw.cmd clean package
- si apoi comanda: java -jar target/gs-rest-service-0.1.0.jar
- "serverul" cu API-ul ar trebui sa functioneze in acest moment

***Foarte Important*** In continuare pentre deschiderea paginii html este nevoie sa aveti instalat 
un addon in browser care sa permita trimiterea de request-uri catre un API din propriul PC. 
Aceasta problema apare doar pentru ca sunt limitat de browser, acest tip de apeluri catre propria 
masina fiind interzise de browser. Instalati un addon care sa permita trecerea request-urilor 
catre propria masina. (de exemplu, eu folosesc in Chrome addon-ul CORS).

Daca toate sunt bune si frumoase, intrati in directorul Web din radacina arhivei si incarcati 
index.html.

Enjoy!