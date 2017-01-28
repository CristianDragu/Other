import java.io.File;
import java.util.Scanner;
import java.util.Vector;

public class DrumulMonezilor {
	
	public static int n;
	public static int m;
	public static int[][] labirint;
	public static Vector<punct> path = new Vector<punct>();

	public static class punct{
		int i,j;
		
		public punct(int i, int j){
			this.i = i;
			this.j = j;
		}
	}
	
	private void readData ( String filename ) {
		Scanner scanner = null;

		try {

			scanner = new Scanner(new File(filename));

			n = scanner.nextInt();
			m = scanner.nextInt();
			
			labirint = new int[n][m];
			
			for (int i = 0; i < n; i++)
				for(int j = 0; j < m; j++)
					labirint[i][j] = scanner.nextInt();
			
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				if (scanner != null) scanner.close();
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
	}
	
	public static void construiesteCost(int[][] cost, int i, int j, int k, int sumatemp){
		cost[0][0] = labirint[0][0];
		
		for (i=0; i<n; i++)
			for (j=0; j<m; j++)
				if (i!=0 || j!=0)
				{
					if (labirint[i][j]!=-1)
					{
						int m1 = -1;
						int m2 = -1;
						if (i>0) m1 = cost[i-1][j];
						if (j>0) m2 = cost[i][j-1];
						cost[i][j] = Math.max(m1,m2) + labirint[i][j];
					}
					else cost[i][j] = -1;
				}
		System.out.println(cost[n-1][m-1]);
		
		//-------------refac drum---------------------
		i=n-1;j=m-1;
		path.add(new punct(i,j));
		while( i != 0 && j != 0){
			if(labirint[i-1][j] > labirint[i][j-1]){
				path.add(new punct(i-1,j));
				i--;
			}
			else{
				path.add(new punct(i,j-1));
				j--;
			}
		}
	}
	
	public static void findPath(){
		int[][] cost = new int[n][m];
		
		for (int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				cost[i][j] = 0;
		
		int i = 0, j = 0;
		try{
			construiesteCost(cost, 0, 0, 0, 0);
			
		} catch(Exception e){
			System.out.print("Exceptie!");
		}
	}
	
	public static void main(String[] args){
		DrumulMonezilor o = new DrumulMonezilor();
		o.readData("date2.txt");
		o.print();
		o.findPath();
		for(punct p: path)
			System.out.println(p.i + " " + p.j);
	}
	
	public static void print(){
		try{
			for (int i = 0; i < n; i++){
				for(int j = 0; j < m; j++)
					System.out.print(labirint[i][j] + " ");
				System.out.println();
			}
		} catch(Exception e){
			
		}
	}
	
}
