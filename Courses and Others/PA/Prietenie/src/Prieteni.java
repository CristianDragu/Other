import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Vector;

public class Prieteni {
	
	int size, start, end, eliminari = 0;
	Vector<Vector<Integer>> neighbors = new Vector<Vector<Integer>>();
	Vector<Vector<Integer>> paths = new Vector<Vector<Integer>>();
	int[][] capacity;
	public final static int UNDEFINED = 0;
	final static int NONE = -1;
	
	// Algoritm de bfs pe un graf neorientat. Returneaza un drum de 
	// ameliorare.
	public Vector<Integer> bfs(int source, int sink) {
	    ArrayList<Integer> parent = new ArrayList<Integer>(size);

	    for (int i = 0; i < size; ++i) {
	      parent.add(NONE);
	    }

	    LinkedList<Integer> q = new LinkedList<Integer>();
	    q.add(source);

	    while (parent.get(sink) == NONE && q.size() > 0) {
	      int node = q.get(0);
	      q.remove(0);

	      for (int i = 0; i < size; ++i) {
	        if (capacity[i][node] > 0 && capacity[node][i] > 0 && parent.get(i) == NONE && parent.get(node) != i) {
	          parent.set(i, node);
	          q.add(i);
	        }
	      }
	    }

	    if (parent.get(sink) == NONE) {
	      return new Vector<Integer>(0);
	    }

	    Vector<Integer> path = new Vector<Integer>();
	    for (int node = sink; node != NONE; node = parent.get(node)) {
	      path.add(node);
	    }
	    Collections.reverse(path);
		
	    return path;
	}
	
	// Algoritm de aflare a fluxului maxim intr-un graf, iar rezultatul
	// returnat va reprezenta numarul de prieteni ce trebuiesc eliminati.
	public int maxFlow(int source, int sink) {
	    
	    int maxflow = 0;
	    
	    while (true) {
	      Vector<Integer> new_path = bfs(source, sink);

	      for(int i = 0; i < new_path.size() - 1; i++)
	    	  if(capacity[new_path.get(i)][new_path.get(i + 1)] == 0)
	    		  break;
	      
	      if(new_path.size() == 0){
	    	  break;
	      }
	      else{
	    	  maxflow++;
	    	  for(int i = 0; i < new_path.size() - 1; i++){
	    		  capacity[new_path.get(i)][new_path.get(i + 1)]--;
	    		  capacity[new_path.get(i + 1)][new_path.get(i)]--;
	    	  }
	      }
	    }
	    
	    return maxflow;
	}
	
	// Metoda care introduce un drum in lista de drumuri
	public void addPath(Integer i){
		
		Vector<Integer> aux = new Vector<Integer>();
		aux.add(start);
		aux.add(i);
		aux.add(end);
		paths.add(aux);
		
	}
	
	// Metoda care introduce un drum in lista de drumuri
	public void addPath(Integer i, Integer j){
		
		Vector<Integer> aux = new Vector<Integer>();
		aux.add(start);
		aux.add(i);
		aux.add(j);
		aux.add(end);
		paths.add(aux);
		
	}
	
	// Metoda care adauga la lista de drumuri (paths), drumurile de 
	// 2 muchii.
	public void twoHopsPaths(){
		
		Vector<Integer> sourceNeighbors = neighbors.get(start);
		Vector<Integer> nod1;
		
		for(Integer i : sourceNeighbors){
			nod1 = neighbors.get(i);
			for(Integer j : nod1){
				if(j == end)
					addPath(i);
			}
		}
		
	}
	
	// Metoda care adauga la lista de drumuri (paths), drumurile de 
	// 3 muchii.
	public void threeHopsPaths(){
		
		Vector<Integer> sourceNeighbors = neighbors.get(start);
		Vector<Integer> nod1;
		Vector<Integer> nod2;
		
		for(Integer i : sourceNeighbors){
			nod1 = neighbors.get(i);
			for(Integer j : nod1){
				if(i != j){
					nod2 = neighbors.get(j);
					for(Integer k : nod2){
						if(k == end)
							addPath(i, j);
					}
				}
			}
		}
		
	}
	
	// Metoda care construieste un graf neorientat pe baza
	// drumurilor de 2 si 3 muchii.
	public void buildNewGraph(){
		
		int n = paths.size(), m;
		
		for(int i = 0; i < n; i++){
			m = paths.get(i).size() - 1;
			for(int j = 0; j < m; j++){
				capacity[paths.get(i).get(j)][paths.get(i).get(j + 1)] = 1;
				capacity[paths.get(i).get(j + 1)][paths.get(i).get(j)] = 1;
			}
		}
		
	}
	
	/* Metoda care apeleaza functiile de mai sus pentru a obtine
	 * drumurile de 2 muchii, respectiv de 3, pentru a forma un
	 * nou graf neorientat cu acestea, pe care se fa aplica un
	 * algoritm de flux maxim.
	 */
	public void createNewGraph(){
		
		twoHopsPaths();
		threeHopsPaths();
		buildNewGraph();
		
	}
	
	public static void main(String[] args) throws IOException{
		
		Prieteni prieteni = new Prieteni();
		prieteni.readData();
		
		prieteni.createNewGraph();
		prieteni.eliminari = prieteni.maxFlow(prieteni.start, prieteni.end);
		
		BufferedWriter bw = new BufferedWriter(new FileWriter("prieteni.out"));
		
		bw.write(prieteni.eliminari + "");
		bw.close();
	}

	// Metoda care citeste din fisierul de intrare datele
	public void readData() throws IOException{
		BufferedReader br = new BufferedReader(new FileReader("prieteni.in"));
		String linie = br.readLine();
		int x;
		
		String[] slinie = linie.split(" ");
		size = Integer.parseInt(slinie[0]);
		
		initMatrix(size);
		
		for(int i = 0; i < size; i++)
			neighbors.add(new Vector<Integer>());
		
		for(int i = 0; i < size; i++){
			linie = br.readLine();
			slinie = linie.split(" ");
			for(int j = 0; j < size; j++){
				x = Integer.parseInt(slinie[j]);
				if(x == 1)
					neighbors.get(i).add(j);
			}
		}
		
		linie = br.readLine();
		slinie = linie.split(" ");
		start = Integer.parseInt(slinie[0]);
		end = Integer.parseInt(slinie[1]);
		
		br.close();
	}
	
	//Metoda care initializeaza matricea de capacitate
	public void initMatrix(int size){
		capacity = new int[size][size];
		
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++){
				capacity[i][j] = UNDEFINED;
			}
	}
	
}
