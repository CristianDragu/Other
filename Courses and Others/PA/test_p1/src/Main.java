import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
	
	int n;
	int[] v = new int[100001];
	
	public int secvMax(){
		
		int maxsum = 0, sumbefore = 0, sumafter = 0, j;
		
		for(int i = 0; i < n; i++){
			if(v[i] == 1)
				++sumbefore;
			else{
				j = i + 1;
				sumafter = 0;
				while(j < n && v[j] == 1){
					++sumafter;
					j++;
				}
				if(sumafter + sumbefore + 1 > maxsum)
					maxsum = sumafter + sumbefore + 1;
				sumbefore = 0;
			}
		}
		
		return maxsum;
		
	}
	
	public static void main(String[] args) throws FileNotFoundException{
			
		Main o = new Main();
		o.readData();
		int a = 3;
		System.out.println((int)(a * 2.25));
		PrintWriter pr = new PrintWriter("secv1.out");
		pr.write(o.secvMax() + "\n");
		pr.close();
		
	}
	
	public void readData() throws FileNotFoundException{
		
		Scanner br = new Scanner(new FileInputStream("secv1.in"));
		n = br.nextInt();
		for(int i = 0; i < n; i++){
			v[i] = br.nextInt();
		}
			
		br.close();
		
	}
	
}
