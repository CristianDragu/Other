import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Vector;

public class Prieteni {

	int[][] capacity, flow;
	int size, start, end, eliminari = 0;
	public final static int UNDEFINED = 0;
	final static int NONE = -1;
	
	public static void main(String[] args) throws IOException{
		
		Prieteni prieteni = new Prieteni();
		prieteni.readData();
		prieteni.eliminari = prieteni.maxFlow(prieteni.start, prieteni.end);
		
		BufferedWriter bw = new BufferedWriter(new FileWriter("prieteni.out"));
		
		bw.write(prieteni.eliminari + "");
		System.out.println(prieteni.eliminari);
		bw.close();
	}
	
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
	
	public void readData() throws IOException{
		BufferedReader br = new BufferedReader(new FileReader("prieteni.in"));
		String linie = br.readLine();
		
		String[] slinie = linie.split(" ");
		size = Integer.parseInt(slinie[0]);
		
		initMatrix(size);
		
		for(int i = 0; i < size; i++){
			linie = br.readLine();
			slinie = linie.split(" ");
			for(int j = 0; j < size; j++)
				capacity[i][j] = Integer.parseInt(slinie[j]);
		}
		
		linie = br.readLine();
		slinie = linie.split(" ");
		start = Integer.parseInt(slinie[0]);
		end = Integer.parseInt(slinie[1]);
	}
	
	public void initMatrix(int size){
		capacity = new int[size][size];
		flow = new int[size][size];
		
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++){
				capacity[i][j] = UNDEFINED;
				flow[i][j] = UNDEFINED;
			}
	}
	
}
