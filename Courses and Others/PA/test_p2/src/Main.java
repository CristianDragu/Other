import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

	int T;
	int[][][][] a = new int[10][10][10][10];
	int  I1, I2, I3, I4;
	int  F1, F2, F3, F4;
	int minCypher = 9999999;
	boolean gasit = false;
	
	public int modulo(int x){
		if(x < 0)
			return 10 + x;
		if(x > 9)
			return x - 10;
		return x;
	}
	
	public void getMin(int i, int j, int k, int l, int pasi){
		if( i >-1 && i < 10 && j >-1 && j < 10 && k >-1 && k < 10 && l >-1 && l < 10 && pasi < minCypher){
			if(a[i][j][k][l] != -1 && a[i][j][k][l] != 1 && pasi < minCypher){
				a[i][j][k][l] = 1;
				if(i == F1 && j == F2 && k == F3 && l == F4){
					if(pasi < minCypher)
						minCypher = pasi;
					gasit = true;
				}
				else{
					getMin(i + 1, j, k, l, pasi + 1);
					getMin(i, j + 1, k, l, pasi + 1);
					getMin(i, j, k + 1, l, pasi + 1);
					getMin(i, j, k, l + 1, pasi + 1);
					getMin(i - 1, j, k, l, pasi + 1);
					getMin(i, j - 1, k, l, pasi + 1);
					getMin(i, j, k - 1, l, pasi + 1);
					getMin(i, j, k, l - 1, pasi + 1);
				}
			}	
		}
	}
	
	public static void main(String[] args) throws FileNotFoundException{
		
		Main o = new Main();
		o.readData();
		
	}
	
	public void readData() throws FileNotFoundException{
		
		int s, j, k, l, n;
		
		Scanner br = new Scanner(new FileInputStream("cypher.in"));
		int T = br.nextInt();
		PrintWriter pr = new PrintWriter("cypher.out");
		
		for(int i = 0; i < T; i++){
			I1 = br.nextInt();
			I2 = br.nextInt();
			I3 = br.nextInt();
			I4 = br.nextInt();
			F1 = br.nextInt();
			F2 = br.nextInt();
			F3 = br.nextInt();
			F4 = br.nextInt();
			n = br.nextInt();
			for(int d = 0; d < n; d++){
				s = br.nextInt();
				j = br.nextInt();
				k = br.nextInt();
				l = br.nextInt();
				a[s][j][k][l] = -1;
			}
			
			getMin(I1, I2, I3, I4, 0);
			if(gasit == false)
				pr.write("-1" + "\n");
			else
				pr.write(minCypher + "\n");
			
			a = new int[10][10][10][10];
			
			minCypher = 9999999;
			gasit = false;
		}
		
		br.close();
		pr.close();
	}
	
}
