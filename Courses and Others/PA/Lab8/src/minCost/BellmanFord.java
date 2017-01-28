/**
 * Proiectarea Algoritmilor, 2014
 * Lab 8: Drumuri minime
 *
 * @author  Radu Iacob
 * @email   radu.iacob23@gmail.com
 */

package minCost;

import graph.Graph;
import graph.Node;
import graph.Pair;

import java.util.ArrayList;

public class BellmanFord extends MinCost {

    public BellmanFord(Graph graph) {
        super(graph);
    }

    /**
     * Given a graph with either positive or negative cost edges,
     * compute the distance from a source node to every other node
     * using the classic BellmanFord implementation. [3p]
     *
     * Expected Complexity: O( V * E )
     * where V - num vertices in graph
     *       E - num edges in graph
     *
     * @param source
     * @return
     */
    public ArrayList<Integer> computeDistance(Node source) {

        int nodeCount = graph.getNodeCount();
        ArrayList<Node> nodes = graph.getNodes();
        ArrayList< Pair< Node, Integer > > vecini = graph.getEdges(source);

        distance.set(source.getId(), 0);
        
        for(int i = 0; i < vecini.size(); i++){
        	distance.set(vecini.get(i).getFirst().getId(), vecini.get(i).getSecond());
        }
        
        System.out.println(distance);
        
        for(int i = 0; i < nodeCount - 2; i++){
        	for(Node nod : nodes){
        		for(int j = 0; j < graph.getEdges(nod).size(); j++){
        			if(distance.get(graph.getEdges(nod).get(j).getFirst().getId()) > distance.get(nod.getId()) + graph.getEdges(nod).get(j).getSecond()){
        				distance.set(graph.getEdges(nod).get(j).getFirst().getId(), distance.get(nod.getId()) + graph.getEdges(nod).get(j).getSecond());
        			}
        		}
        	}
        }
        
        checkNegativeCycle();

        return distance;
    }

    /**
     * TODO: Check if there exists a negative cycle and
     * print such a cycle if it exists. [1p]
     */

    public void checkNegativeCycle() {
    	for(Node nod : graph.getNodes()){
    		for(int j = 0; j < graph.getEdges(nod).size(); j++){
    			if(distance.get(graph.getEdges(nod).get(j).getFirst().getId()) > distance.get(nod.getId()) + graph.getEdges(nod).get(j).getSecond()){
    				System.out.println("EXISTA CICLURI NEGATIVE!!");
    			}
    		}
    	}
    }

}
