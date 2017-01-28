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
import java.util.Comparator;
import java.util.PriorityQueue;

public class Dijkstra extends MinCost{

    public Dijkstra (Graph graph) {
        super(graph);
    }

    private class NodeComparator implements Comparator<Node>
    {
        /**
         * Compares nodes using the current estimation of the distance from
         * the source node.
         */
        @Override
        public int compare(Node arg0, Node arg1) {
            int dist1 = distance.get( arg0.getId() );
            int dist2 = distance.get( arg1.getId() );
            return dist1 > dist2 ? 1 : -1;
        }
    }

    /**
     * Given a graph, with positive cost edges, compute the distance </br>
     * from a source node to every other node using the Dijkstra algorithm. [3p] </br>
     *
     * Expected Complexity: O( (V+E) * lgV ) ~ O( E * lgV ) </br>
     * where </br>
     * V - num vertices in graph </br>
     * E - num edges in graph </br>
     *
     * @param source
     * @return
     */
    public ArrayList<Integer> computeDistance (Node source) {

        resetDistance();
        ArrayList<Node> nodes = graph.getNodes();
        ArrayList< Pair< Node, Integer > > vecini = graph.getEdges(source);
        int nodeCount = graph.getNodeCount();
        PriorityQueue<Node> pq = new PriorityQueue<Node>(nodeCount, new NodeComparator());
        
        System.out.println(graph.getEdges(source));
        System.out.println(graph.getEdges(graph.getEdges(source).get(1).getFirst()));
        
        distance.set(source.getId(), 0);
        for(int i = 0; i < vecini.size(); i++){
        	distance.set(vecini.get(i).getFirst().getId(), vecini.get(i).getSecond());
        	pq.add(vecini.get(i).getFirst());
        }
        
        System.out.println(distance);

        source.visit();
        
        while(!pq.isEmpty()){
        	Node u = pq.poll();
        	u.visit();
        	for(int i = 0; i < graph.getEdges(u).size(); i++){
        		if(!graph.getEdges(u).get(i).getFirst().isVisited() 
        				&& distance.get(graph.getEdges(u).get(i).getFirst().getId()) > 
        				distance.get(u.getId()) + graph.getEdges(u).get(i).getSecond() ){
        			distance.set(graph.getEdges(u).get(i).getFirst().getId(), distance.get(u.getId()) + graph.getEdges(u).get(i).getSecond());
        			pq.add(graph.getEdges(u).get(i).getFirst());
        		}
        	}
        }

        System.out.println(distance);
        
        return distance;
    }

}
