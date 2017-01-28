import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Collections;
import java.util.Scanner;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Patrat {

	//Metoda pentru afisarea sumei cautare
	public static void printSum(long s){
		try{
			File file = new File("patrat.out");
			file.createNewFile();
			FileWriter writer = new FileWriter(file);
			BufferedWriter bw = new BufferedWriter(writer);
			
			bw.write(s + "");
		    bw.close();
		} catch(Exception e){
			
		}
		
	}
	
	//Metoda pentru calcularea numarului de sume mai mici ca suma
	//medie (mijSum)
	public static Long getNrSums(Vector<Long> v, int n, long mijSum){
		
		int j = n - 1, i = 0;
		long nrSums = 0;
		
		while(i <= j){
			
			if(v.get(i) + v.get(j) > mijSum)
				j--;
			else{
				nrSums += 2 * (j - i) + 1;
				i++;
			}
			
		}
		
		return nrSums;
		
	}
	
	//aplicam un algoritm Divide et Impera, pentru gasirea sumei
	public static void findSum(Vector<Long> v, int n, long k, long lowerSum, long upperSum){
		if(lowerSum == upperSum){
			printSum(lowerSum);
			return;
		}
		else{
			
			//calculam suma medie si in functie de totalul
			//sumelor mai mici decat suma medie, mergem
			//in standa sau in dreapta sumei cu algoritmul
			long mijSum = (lowerSum + upperSum) / 2;
			long nrSums = getNrSums(v, n, mijSum);
		
			if(nrSums < k){
				lowerSum = mijSum;
				findSum(v, n, k, lowerSum + 1, upperSum);
			}
			else{
				upperSum = mijSum;
				findSum(v, n, k, lowerSum, upperSum);
			}
		}
	}
	
	//dupa ce se face citirea din fisier, sortam vectorul
	//cu numere, pentru a aplica divide et impera pe el
	public static void main(String[] args) throws NumberFormatException, IOException{

		try{
			
			int n;
			long k;
			
			BufferedReader br = new BufferedReader(new FileReader("patrat.in"));
			String linie = br.readLine();
			
			String[] slinie = linie.split(" ");
			n=Integer.parseInt(slinie[0]);
			k=Long.parseLong(slinie[1]);
			
			Vector<Long> v = new Vector<Long>();
			
			while ((linie = br.readLine()) != null) {
			    v.add(Long.parseLong(linie));
			  }
			
			Collections.sort(v);
			if(k == 1)
				printSum(2 * v.firstElement());
			else
				findSum(v, n, k, 2 * v.firstElement(), 2 * v.lastElement());
			
		}catch (FileNotFoundException ex) {

        }
		
	}
	
}
