import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Vector;

public class p1 {
	
	public static class Nod{
		int x, y;
		
		public Nod(int x, int y){
			this.x = x;
			this.y = y;
		}
	}
	
	public static void lee(int[][] a, int x, int y, int k) {
		a[x][y]=k;
		
		if (a[x-1][y] != -1 && a[x-1][y] != 0)
			if (a[x-1][y] == -2) lee(a, x-1, y, k+1);
	        else if (a[x-1][y] > k+1) lee(a, x-1, y, k+1);
	 
	    if (a[x+1][y] != -1 && a[x+1][y] != 0)
	        if (a[x+1][y] == -2) lee(a, x+1, y, k+1);
	        else if (a[x+1][y] > k+1) lee(a, x+1, y, k+1);
	                
	    if (a[x][y-1] != -1 && a[x][y-1] != 0)
	        if (a[x][y-1] == -2) lee(a, x, y-1, k+1);
	        else if (a[x][y-1] > k+1) lee(a, x, y-1, k+1);
	        
	    if (a[x][y+1] != -1 && a[x][y+1] != 0)
	        if (a[x][y+1] == -2) lee(a, x, y+1, k+1);
	        else if (a[x][y+1] > k+1) lee(a, x, y+1, k+1);
	 
	}
	
	public static void bfs(int[][] labirint, int n, int m, int startx, int starty, int endx, int endy){
		
		Nod nodstart = new Nod(startx, starty);
		Nod nodend = new Nod(endx, endy);
		
		Vector<Nod> q = new Vector<Nod>();
		Vector<Nod> parents = new Vector<Nod>();
		
		q.add(nodstart);
		
		for(int i = 0; i < n * m; i++)
			parents.add(new Nod(0, 0));
		
		Nod node = nodstart;
		
		int[] x = {1, 0, -1, 0};
		int[] y = {0, 1, 0, -1};
		
		while(q.get(0).x != nodend.x && q.get(0).y != nodend.y){
			for(int i = 0; i < 4; i++){
				if(labirint[node.x + x[i]][node.y + y[i]] != 0 && labirint[node.x + x[i]][node.y + y[i]] != -1){
					q.add(new Nod(node.x + x[i], node.y + y[i]));
					parents.set(q.indexOf(q.lastElement()), q.lastElement());
				}
			}
			q.remove(0);
		}
		
		
	}
	
	public static void main(String[] args) throws FileNotFoundException{
		
		int n, m, val;
		
		Scanner s = new Scanner(new File("Puzzle.in"));
		
		n = s.nextInt();
		m = s.nextInt();
		
		int startx = s.nextInt() + 1;
		int starty = s.nextInt() + 1;
		int endx = s.nextInt() + 1;
		int endy = s.nextInt() + 1;

		int[][] labirint = new int[n+2][m+2];
		
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++){
				val = s.nextInt();
				if(val == 1)
					labirint[i][j] = -2;
				else
					labirint[i][j] = val;
			}
		
		bording(labirint, n, m);
		
		lee(labirint, startx, starty, 0);
		
		bfs(labirint, n, m, startx, starty, endx, endy);
		
		print(labirint, n, m);

	}
	
	public static void bording(int[][] labirint, int n, int m){
		
		for(int i = 0; i <= n + 1; i++){
			labirint[i][0] = -1;
			labirint[i][m + 1] = -1;
			labirint[0][i] = -1;
			labirint[n + 1][i] = -1;
		}
			
	}
	
	public static void print(int[][] labirint, int n, int m){
		
		for(int i = 0; i <= n + 1; i ++){
			for(int j = 0; j <= m + 1; j++)
				if(labirint[i][j] == -2)
					System.out.print("1 ");
				else
					System.out.print(labirint[i][j] + " ");
			System.out.println();
		}
		
	}
	
}
