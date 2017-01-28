import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collections;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Vector;

class Paznic{
	
	int x = 0;
	int y = 0;
	
	public Paznic(int x, int y){
		this.x = x;
		this.y = y;
	}
	
}

class Cell{
	
	int x = 0;
	int y = 0;
	
	public Cell(int x, int y){
		this.x = x;
		this.y = y;
	}
	
}

public class Comori {

	/*public static void lee(int[][] a, int x, int y, int k) {
		a[x][y]=k;
	    
		if (a[x-1][y] != -2 && a[x-1][y] != -1)
			if (a[x-1][y] == 0) lee(a, x-1, y, k+1);
	        else if (a[x-1][y] > k+1) lee(a, x-1, y, k+1);
	 
	    if (a[x+1][y] != -2 && a[x+1][y] != -1)
	        if (a[x+1][y] == 0) lee(a, x+1, y, k+1);
	        else if (a[x+1][y] > k+1) lee(a, x+1, y, k+1);
	                
	    if (a[x][y-1] != -2 && a[x][y-1] != -1)
	        if (a[x][y-1] == 0) lee(a, x, y-1, k+1);
	        else if (a[x][y-1] > k+1) lee(a, x, y-1, k+1);
	        
	    if (a[x][y+1] != -2 && a[x][y+1] != -1)
	        if (a[x][y+1] == 0) lee(a, x, y+1, k+1);
	        else if (a[x][y+1] > k+1) lee(a, x, y+1, k+1);
	 
	}*/
	
	public static boolean contains(Vector<Paznic> paznici, int x, int y){
		for(Paznic paznic : paznici)
			if(paznic.x == x && paznic.y == y)
				return true;
		
		return false;
	}
	
	public static void bfs(int[][] labirint, Vector<Paznic> paznici, int n){
		LinkedList<Cell> queue = new LinkedList<Cell>();
		
		for(Paznic paznic : paznici)
			queue.add(new Cell(paznic.x, paznic.y));
		
		while(!queue.isEmpty()){
			Cell c = queue.poll();
			
			if(labirint[c.x + 1][c.y] != -2 && labirint[c.x + 1][c.y] != -1 && !contains(paznici, c.x + 1, c.y)){
				if(labirint[c.x + 1][c.y] == 0){
					queue.add(new Cell(c.x + 1, c.y));
					labirint[c.x + 1][c.y] = labirint[c.x][c.y] + 1;
				}
			}
			
			if(labirint[c.x - 1][c.y] != -2 && labirint[c.x - 1][c.y] != -1 && !contains(paznici, c.x - 1, c.y)){
				if(labirint[c.x - 1][c.y] == 0){
					queue.add(new Cell(c.x - 1, c.y));
					labirint[c.x - 1][c.y] = labirint[c.x][c.y] + 1;
				}
			}
			
			if(labirint[c.x][c.y + 1] != -2 && labirint[c.x][c.y + 1] != -1 && !contains(paznici, c.x, c.y + 1)){
				if(labirint[c.x][c.y + 1] == 0){
					queue.add(new Cell(c.x, c.y + 1));
					labirint[c.x][c.y + 1] = labirint[c.x][c.y] + 1;
				}
			}
			
			if(labirint[c.x][c.y - 1] != -2 && labirint[c.x][c.y - 1] != -1 && !contains(paznici, c.x, c.y - 1)){
				if(labirint[c.x][c.y - 1] == 0){
					queue.add(new Cell(c.x, c.y - 1));
					labirint[c.x][c.y - 1] = labirint[c.x][c.y] + 1;
				}
			}
		}
	}
	
	public static void main(String[] args) throws IOException{
		int n, m;
		
		Scanner s = new Scanner(new File("data.txt"));
		
		n=s.nextInt();
		m=s.nextInt();
		
		int[][] labirint = new int[n+2][m+2];
		Vector<Paznic> paznici = new Vector<Paznic>();
		
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++){
				labirint[i][j] = s.nextInt();
				if(labirint[i][j] == -2){
					paznici.add(new Paznic(i, j));
					labirint[i][j] = 0;
				}
			}
		
		bording(labirint, n, m);
		
		bfs(labirint, paznici, n);
		
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
		
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++)
				if(labirint[i][j] == -1)
					System.out.print("#" + " ");
				else
					System.out.print(labirint[i][j] + " ");
			System.out.println();
		}
		
	}
	
}
