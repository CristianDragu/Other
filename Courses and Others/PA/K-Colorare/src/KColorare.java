import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class KColorare {
	
	int n, m, c;
	int[][] adiacenta = new int[40][40];
	int[][] cost = new int[40][30];
	int[] culoriNoduri = new int[40]; //vector ce va contine culorile 
									  //atribuite nodurilor
	int[] solutie = new int[40]; //vector ce va contine solutia finala
	long costTotal = 1999999999; //costul final
	
	/* Metoda ce valideaza solutia partiala gasita pana la momentul curent
	 * Verifica daca nodurile direct adiacente au aceeasi culoare.
	 */
	public boolean valid(int p) {
		for(int i = 0; i < p; i++)
			if(adiacenta[p][i] == 1 && culoriNoduri[i] == culoriNoduri[p])
				return false;
		return true;
	}
	
	/* Metoda ce introduce in vectorul solutie, o posibila solutie finala.
	 * Daca se va gasi alta cu suma totala mai mica, va fi aceea memorata.
	 */
	public void memorareSol(int p) {
		for(int i = 0; i < n; i++)
			solutie[i] = culoriNoduri[i];
	}
	
	/* Metoda ce calculeaza suma costurilor dintre legaturile nodului p 
	 * cu nodurile adiacente acestuia, in functie de culorile lor.
	 */
	public int sumaCosturi(int p) {
		int sum = 0;
		for(int i = 0; i < p; i++)
			if(adiacenta[p][i] == 1)
				sum += cost[culoriNoduri[p]][culoriNoduri[i]];
		return sum;
	}
	
	// Algoritm Backtracking.
	public void bktKColorare(int costPartial, int p) {
		if(costPartial >= costTotal)
			return;
		if(p == n) {
			memorareSol(p);
			costTotal = costPartial;
		}
		else{
			for(int i = 0; i < c; i++) {
				culoriNoduri[p] = i;
				if(valid(p)) {
					int aux = sumaCosturi(p);
					costPartial += aux;
					bktKColorare(costPartial, p + 1);
					culoriNoduri[p] = -1;
					costPartial -= aux;
				}
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		KColorare o = new KColorare();
		o.readData();
		
		for(int i = 0; i < o.n; i++) {
			o.culoriNoduri[i] = -1;
			o.solutie[i] = -1;
		}
		
		o.bktKColorare(0, 0);
			
		o.writeData();

	}
	
	/* Metoda pentru citirea datelor din fisierul de intrare.
	 * Datele se citesc cu un BufferedReader, linie cu linie.
	 * Linia se sparge la caracterul spatiu si se face 
	 * inregistrarea datelor.
	 */
	public void readData() throws IOException {
		int x1, x2, x3;
		BufferedReader br = new BufferedReader(new FileReader("kcol.in"));
		String linie = br.readLine();
		
		String[] slinie = linie.split(" ");
		n = Integer.parseInt(slinie[0]);
		m = Integer.parseInt(slinie[1]);
		c = Integer.parseInt(slinie[2]);
		
		for(int i = 0 ; i < m; i++) {
			linie = br.readLine();
			slinie = linie.split(" ");
			
			x1 = Integer.parseInt(slinie[0]);
			x2 = Integer.parseInt(slinie[1]);
			
			// adiacenta este matricea de adiacenta a grafului
			adiacenta[x1][x2] = 1;
			adiacenta[x2][x1] = 1;
		}
		
		linie = br.readLine();
		
		int liniiCost = (c * (c-1)) / 2;
		for(int i = 0; i < liniiCost; i++) {
			linie = br.readLine();
			slinie = linie.split(" ");
			
			x1 = Integer.parseInt(slinie[0]);
			x2 = Integer.parseInt(slinie[1]);
			x3 = Integer.parseInt(slinie[2]);
			
			// cost este matricea cu costurile legaturilor dintre
			// culori
			cost[x1][x2] = x3;
			cost[x2][x1] = x3;
		}
		
		br.close();
	}
	
	/* Metoda pentru afisarea datelor. Datele se afiseaza cu
	 * un BufferedReader. Solutia cautata (daca este exista)
	 * se va gasi in vectorul solutie si va fi afisata.
	 */
	public void writeData() throws IOException {
		
		BufferedWriter bw = new BufferedWriter(new FileWriter("kcol.out"));
		
		if(solutie[n-1] == -1) {
			bw.write("-1");
			bw.newLine();
		}
		else{
			bw.write(costTotal + "");
			for(int i = 0; i < n; i++) {
				bw.newLine();
				bw.write(i + " " + solutie[i]);
			}
		}
		
		bw.close();
	}
	
}
