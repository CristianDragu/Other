import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberInputStream;
import java.util.Collections;
import java.util.Comparator;
import java.util.Vector;

public class AMA {

	class Arc{
		
		int start;
		int end;
		int cost;
		
		public Arc(int start, int end, int cost){
			this.start = start;
			this.end = end;
			this.cost = cost;
		}
	}
	
	int n, m;
	Vector <Vector <Arc>> adiacenta = new Vector <Vector<Arc>>();
	Vector <Arc> muchii = new Vector<Arc>();
	int[] numarArbore = new int[100];
	Vector <Arc> MuchiiAMA = new Vector<Arc>();
	
	public Vector<Integer> bfs(int start){
		Vector <Integer> q = new Vector<Integer>();
		int[] parent = new int[n];
		
		q.add(start);
		parent[start] = 0;
		
		for(Integer i : q){
			for(Arc muchie : adiacenta.get(i)){
				if(!q.contains(muchie.end)){
					q.add(muchie.end);
					parent[muchie.end] = i;
				}
			}
		}
		
		int muchieMax = 9999;
		for(int i = 1; i <= n; i++){
			
		}
		
		return q;
	}
	
	public Vector <Arc> Kruskal(){
		Vector <Arc> MuchiiAMA = new Vector<Arc>();
		
		for(int i = 1; i <= n; i++){
			numarArbore[i] = i;
		}
		
		Collections.sort(muchii, new Comparator<Arc>() {

			@Override
			public int compare(Arc a1, Arc a2) {
				return a1.cost - a2.cost;
			}
		});
		
		for(Arc muchie : muchii){
			if(numarArbore[muchie.start] != numarArbore[muchie.end]){
				MuchiiAMA.add(muchie);
			}
			for(int j = 1; j <= n; j++)
				if(numarArbore[j] == numarArbore[muchie.end] && j != muchie.end)
					numarArbore[j] = numarArbore[muchie.start];
			numarArbore[muchie.end] = numarArbore[muchie.start];
		}
		
		return MuchiiAMA;
	}
	
	public static void main(String[] args) throws IOException{
		
		AMA o = new AMA();
		o.readData();
		o.printData();
		o.MuchiiAMA = o.Kruskal();
		o.printResult();
	}
	
	public void readData() throws IOException {
		int x1, x2, cost;
		BufferedReader br = new BufferedReader(new FileReader("data.in"));
		String linie = br.readLine();
		
		String[] slinie = linie.split(" ");
		n = Integer.parseInt(slinie[0]);
		m = Integer.parseInt(slinie[1]);
		
		for(int i = 0; i <= n; i++)
			adiacenta.add(new Vector<Arc>());
		
		for(int i = 0; i < m; i++){
			
			linie = br.readLine();
			slinie = linie.split(" ");
			
			x1 = Integer.parseInt(slinie[0]);
			x2 = Integer.parseInt(slinie[1]);
			cost = Integer.parseInt(slinie[2]);
			
			adiacenta.get(x1).add(new Arc(x1,x2,cost));
			adiacenta.get(x2).add(new Arc(x2,x1,cost));
			muchii.add(new Arc(x1, x2, cost));
		}
		
		br.close();
	}
	
	public void printData(){
		
		System.out.println("Lista de adiacenta\n");
		for(int i = 1; i <= n; i++){
			System.out.print(i + " : ");
			for(int j = 0; j < adiacenta.get(i).size(); j++)
				 System.out.print(adiacenta.get(i).get(j).end + " " + adiacenta.get(i).get(j).cost + "; ");
			System.out.println();
		}
		
	}
	
	public void printResult(){
		System.out.print("\nMuchii AMA: ");
		for (int i = 0; i < MuchiiAMA.size(); i++)
			System.out.print(MuchiiAMA.get(i).start + " " + MuchiiAMA.get(i).end + "; ");
	}
	
}
