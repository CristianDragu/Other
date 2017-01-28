import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Collections;
import java.util.Comparator;
import java.util.Vector;

public class Expozitie {
	
	class Nod {
		
		int numeNod;
		Vector<Integer> lista = new Vector<Integer>();
		
		public Nod(){
			numeNod = -1;
		}
		
		public Nod(int numeNod) {
			this.numeNod = numeNod;
		}
		
	}
	
	/* Clasa pentru memorarea arcelor in vectorul arce.
	 * Perechea (x, y) => arc de la x la y.
	 */
	class Pair {
		
		int x,y;
		
		public Pair(int x, int y) {
			this.x = x;
			this.y = y;
		}
		
	}
	
	int n;
	Vector<Nod> listaAdiacenta = new Vector<Nod>(); // Vector cu listele de
													// adiacenta a nodurilor
	Vector<Integer> vizitari = new Vector<Integer>();
	Vector<Pair> arce = new Vector<Pair>(); // Vector pentru arce
	
	/* Metoda care numara arcele introduse in vectorul arce si
	 * care ies din nodul poz.
	 */
	public int numarArce(int poz) {
		int m = arce.size(), s = 0;
		for(int i = 0; i < m; i++) {
			if(arce.get(i).x == poz)
				s++;
		}
		return s;
	}
	
	/* Metoda principala care rezolva cerinta problemei.
	 * Se parcurge vectorul de vizitari, care contine pe pozitia i, 
	 * care reprezinta si id-ul (numarul) nodului i, numarul de muchii. 
	 * Se cauta nodul cu minim de muchii pentru a fi procesat.
	 * Se iau toti vecinii directi, din listaAdiacenta, ai acestui nod, 
	 * si in functie de paritatea numarului de muchii se fac doua tipuri 
	 * de operatii:
	 * 1. daca suma numarului de muchii si numarului de arce, introduse in 
	 * vectorul arce pana in acest moment, este para atunci se introduc in 
	 * vectorul de arce noile arce ce incep cu nodul nostru minim si 
	 * fiecare vecin in parte, apoi se fac stergerile legaturilor dintre 
	 * cele 2 noduri din lista de adiacenta. Se decrementeaza si numarul 
	 * de muchii din vizitari, pe pozitiile vecinilor.
	 * 2. daca suma este impara, atunci se fac aceleasi operatii ca la pasul 
	 * anterior pentru primii m - 1 vecini ai nodului, iar al n-lea vecin 
	 * care face ca numarul de muchii sa fie impar va fi introdus in arce 
	 * cu forma inversa (de la y la x).
	 */
	public void creazaArce() {
		
	  int poz, min, m;
	  int[] vecini = new int[n];

	  for(int i = 0; i < n; i++) {
	    poz = -1;
	  	min = 5001;
	  	// Cautam nodul cu minim de muchii
		for(int j = 0; j < n; j++) {
		  if(vizitari.get(j) <= min && vizitari.get(j) != 0) {
			poz = j;
			min = vizitari.get(j);
		  }
		}
		// Facem procesarea nodului, introducand si arcele in vector.
		if(poz == -1)
		  break;
		else
		  if((min + numarArce(poz)) % 2 == 0) {
			m = listaAdiacenta.get(poz).lista.size();
			for(int j = 0; j < m; j++)
		      vecini[j] = listaAdiacenta.get(poz).lista.get(j);
			for(int j = 0; j < m; j++) {
			 arce.add(new Pair(poz, vecini[j]));
			 if(listaAdiacenta.get(vecini[j]).lista.removeElement((Object)poz))
			   vizitari.set(vecini[j], vizitari.get(vecini[j]) - 1);
			 listaAdiacenta.get(poz).lista.removeElement((Object)vecini[j]);
			}
			vizitari.set(poz, 0);
		  }
		  else {
			m = listaAdiacenta.get(poz).lista.size() - 1;
			for(int j = 0; j < m + 1; j++)
			  vecini[j] = listaAdiacenta.get(poz).lista.get(j);
			for(int j = 0; j < m; j++) {
			 arce.add(new Pair(poz, vecini[j]));
			 if(listaAdiacenta.get(vecini[j]).lista.removeElement((Object)poz))
			   vizitari.set(vecini[j], vizitari.get(vecini[j]) - 1);
			 listaAdiacenta.get(poz).lista.removeElement((Object)vecini[j]);
			}
			arce.add(new Pair(vecini[m], poz));
			listaAdiacenta.get(poz).lista.removeElement((Object)vecini[m]);
			listaAdiacenta.get(vecini[m]).lista.removeElement((Object)poz);
			vizitari.set(vecini[m], vizitari.get(vecini[m]) - 1);
			vizitari.set(poz, 0);
		  }
	  }
	}
	
	public static void main(String[] args) throws IOException {
		
		Expozitie o = new Expozitie();
		o.readData();
		
		o.creazaArce();
		
		o.writeData();
	}
	
	/* Metoda care citeste datele din fisier
	 * 
	 */
	public void readData() throws IOException {
		int x1, x2;
		BufferedReader br = new BufferedReader(new FileReader("expozitie.in"));
		String linie = br.readLine();
		
		String[] slinie = linie.split(" ");
		n = Integer.parseInt(slinie[0]);
		
		for(int i = 0 ; i < n; i++) {
			listaAdiacenta.add(new Nod(i));
			vizitari.add(0);
		}
		
		while((linie = br.readLine()) != null) {
			slinie = linie.split(" ");
			
			x1 = Integer.parseInt(slinie[0]);
			x2 = Integer.parseInt(slinie[1]);
			
			
			listaAdiacenta.get(x1).lista.add(x2);
			listaAdiacenta.get(x2).lista.add(x1);
			vizitari.set(x1, vizitari.get(x1) + 1);
			vizitari.set(x2, vizitari.get(x2) + 1);
		}
		
		br.close();
	}
	
	/* Metoda care afiseaza solutia in fisier.
	 * 
	 */
	public void writeData() throws IOException {
		
		BufferedWriter b = new BufferedWriter(new FileWriter("expozitie.out"));
		
		int m = arce.size(), s = 0, last = arce.get(0).x;
		
		Collections.sort(arce, new Comparator<Pair>() {

			@Override
			public int compare(Pair o1, Pair o2) {
				return o1.x - o2.x;
			}
		});
		
		// Verificam daca exista un numar impar de arce care ies 
		// dintr-un nod, iar daca exista cel putin unul, atunci 
		// solutia este Imposibil.
		for(int i = 0; i < m; i++) {
			if(arce.get(i).x == last)
				s++;
			else if(s % 2 != 0) {
				b.write("Imposibil");
				b.newLine();
				b.close();
				return;
			}
			else {
				last = arce.get(i).x;
				s = 1;
			}
		}
		
		for(int i = 0; i < m; i++) {
			b.write(arce.get(i).x + " " + arce.get(i).y);
			b.newLine();
		}
		
		b.close();
	}
	
}
