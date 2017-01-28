import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.ArrayList;

public class Negustor {
	
	int n, m;
	double mij_prec = 0.0, costTotalMuchii = 0.0;
	int[] profit;
	ArrayList<Muchie> muchii = new ArrayList<Muchie>();
	ArrayList<Muchie> muchii_initiale = new ArrayList<Muchie>();
	double[][] cost;
	
	class Muchie{
		int x, y;
		double cost;
		
		public Muchie(int x, int y, double cost){
			this.x = x;
			this.y = y;
			this.cost = cost;
		}
	}
	
	// Algoritm care verifica existenta unui ciclu negativ in graf.
	public boolean belman_ford(int source){
		
		double[] distances = new double[n];
		
		for(int i = 0; i < n; i++)
			if(cost[source][i] != 0)
				distances[i] = cost[source][i];
			else
				distances[i] = 32000;
		
		distances[source] = 0;
		
		for(int i = 1; i <= n - 2; i++){
			for(int j = 0; j < muchii.size(); j++){
				Muchie m = muchii.get(j);
				if(distances[m.y] > distances[m.x] + m.cost)
					distances[m.y] = distances[m.x] + m.cost;
			}
		}
		
		for(int j = 0; j < muchii.size(); j++){
			Muchie m = muchii.get(j);
			if(distances[m.y] > distances[m.x] + m.cost)
				return true;
		}
		
		return false;
	}
	
	/* Un algoritm DEI pentru gasirea unui numar care sa aproximeze costul, 
	 * in functie de profit, de la un nod la altul.
	 * Se aplica un algoritm Belman-Ford pentru a se verifica daca exista 
	 * cicluri de cost negativ in graf (se aplica pe matricea cost).
	 */
	public void cautare_binara(double lower, double upper) throws IOException{
		
		muchii.clear();
		double mij = (lower + upper) / 2;
		
		if(Math.abs(mij - mij_prec) < 0.0000001){
			writeData(mij);
		}
		else{
			mij_prec = mij;
			for(int j = 0; j < muchii_initiale.size(); j++){
				Muchie m = muchii_initiale.get(j);
				cost[m.x][m.y] = mij * m.cost - profit[m.y];
				muchii.add(new Muchie(m.x, m.y, mij * m.cost - profit[m.y]));
			}
			if(belman_ford(0) == true)
				cautare_binara(mij, upper);
			else
				cautare_binara(lower, mij);
		}
	}
	
	public static void main(String[] args) throws IOException{
		Negustor negustor = new Negustor();
		negustor.readData();
		negustor.cautare_binara(0, negustor.costTotalMuchii);
	}
	
	// Metoda pentru citirea datelor
	public void readData() throws IOException{
		
		BufferedReader br = new BufferedReader(new FileReader("negustori.in"));
		String linie = br.readLine();
		
		String[] slinie = linie.split(" ");
		n = Integer.parseInt(slinie[0]);
		m = Integer.parseInt(slinie[1]);
		
		profit = new int[n];
		cost = new double[n][n];
		
		linie = br.readLine();
		slinie = linie.split(" ");
		for(int i = 0; i < n; i++){
			profit[i] = Integer.parseInt(slinie[i]);
		}
		
		for(int i = 0; i < m; i++){
			linie = br.readLine();
			slinie = linie.split(" ");
			
			muchii_initiale.add(new Muchie(Integer.parseInt(slinie[0]), Integer.parseInt(slinie[1]), Integer.parseInt(slinie[2])));
			costTotalMuchii += Integer.parseInt(slinie[2]);
		}
		
		br.close();
	}
	
	// Metoda pentru afisarea rezultatului
	public void writeData(double mij) throws IOException{
		String pattern = "#0.000000";
		DecimalFormat decimalFormat = new DecimalFormat(pattern);
		String format = decimalFormat.format(mij);
		
		BufferedWriter bw = new BufferedWriter(new FileWriter("negustori.out"));
		
		bw.write(format);
		bw.close();
	}
	
}
