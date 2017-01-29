Titlu proiect: Algoritmi de detectare a coliziunilor in spatiul 3D
Materia: SPG
Studenti: Dragu Cristian(343C4), Barbuceanu Malin(342C1)


	Acest proiect a presupus realizarea a 2 algoritmi de detectare a coliziunilor. Pentru exemplificarea functionalitatilor
am pornit de la unul din laboratoarele de grafica si am folosit 2 corpuri, anume un cub si un iepure. Algoritmii implementati
au fost urmatorii:

	- sphere-to-sphere collision detection - in acest caz am determinat centrul fiecarui obiect facand media aritmetica a 
coordonatelor sale pe x, pe y, respectiv pe z. Am aflat apoi diametrul cercului afland distanta maxima intre punctele cele
mai departate de pe cele 3 axe. Avand centrul fiecaruia dintre cele 2 corpuri, am aflat distanta euclidiana dintre cele 2 
puncte si am comparat o cu suma razelor. Astfel, stiind ca in cadrul animatiei obiectele isi modifica doar pozitia pe 
verticala, am verificat daca distanta intre centru cercurilor este mai mica decat suma razelor, caz in care avem coliziune.

	- triangle-to-triangle - collision detection - am folosit algoritmul lui Moller. Acest algoritm presupune verificarea 
fiecarei perechi de triunghiuri care compun o mesha, pereche de forma (t1, t2), unde t1 apartine obiectului 1, iar t2 obiec-
tului 2. Am determinat ecuatiile planurilor in care se gasesc cele 2 triunghiuri. Am calculat apoi proiectiile punctelor 
catre celalalt plan si in functie de pozitiile acestor vectori am verificat care sunt punctele triunghiului aflate pe 
aceeasi parte a planului despartit de linie. Astfel, daca intervalele de pe linia care intersecteaza triunghiurile nu se
intersecteaza, atunci nici triunghiurile nu vor avea coliziune.
	Link Moller: https://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf

	Taste: w, a, s, d, r, f - mutarea camerei in sus, jos, stanga, dreapta, fata, spate
		   q, e - rotirea camerei
		   m - modul de determinare a coliziunii - unul dintre modurile prezentate mai sus