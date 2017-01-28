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

public class RoyFloyd {

    Integer cost[][];
    Node    detour[][];
    
    public static final int INF = Graph.MAX_VALUE;

    public RoyFloyd (int nodeCount)
    {
        cost   = new Integer[ nodeCount ][ nodeCount ];
        detour = new Node[ nodeCount ][ nodeCount ];
    }

    /**
     * Given a graph with either positive or negative cost edges, </br>
     * compute the minimum path cost between every node as well </br>
     * as the 'next-hop' node for every such node. [3p] </br>
     *
     * Expected complexity: O( V^3 ) </br>
     * where V - num vertices in graph </br>
     *
     * Input:
     * Graph graph  -- Directed graph </br>
     *
     * Result:
     * Matrix for cost   </br>
     * - cost[i][j] - minimum cost for a path from node i to node j </br>
     * Matrix for detour </br>
     * - detour[i][j] - the "next" node on the path from node i to node j </br>
     *
     *
     * Hint (useful API): </br>
     * graph.getEdges(node) </br>
     *
     * Debugging:
     * dumpCostMatrix(); </br>
     *
     * Don't forget to initialize the cost and detour matrixes!
     * @param graph
     */
    public void computeRoyFloyd (Graph graph) {

        resetCostMatrix();
        resetDetourMatrix();

        ArrayList<Node> nodes = graph.getNodes();
        int nodeCount = graph.getNodeCount();
        
        for(int i = 0; i < nodeCount; i++)
        		cost[i][i] = 0;
        
        for(int i = 0; i < nodeCount; i++){
        	ArrayList< Pair< Node, Integer > > vecini = graph.getEdges(nodes.get(i));
        	for(int j = 0; j < vecini.size(); j++){
        		cost[nodes.get(i).getId()][vecini.get(j).getFirst().getId()] = vecini.get(j).getSecond();
        	}
        }
        
        for(int k = 0; k < nodeCount; k++)
        	for(int i = 0; i < nodeCount; i++)
        		for(int j = 0; j < nodeCount; j++)
        			if(cost[i][j] > cost[i][k] + cost[k][j]){
        				cost[i][j] = cost[i][k] + cost[k][j];
        				nodes.get(k).setParent( new Node(nodes.get(i).getCity(), nodes.get(i).getId()) );
        				nodes.get(j).setParent( new Node(nodes.get(k).getCity(), nodes.get(k).getId()) );
        			}
        
        for(int i = 0; i < nodeCount; i++){
    		for(int j = 0; j < nodeCount; j++)
    			System.out.print(cost[i][j] + " ");
    		System.out.println();
    	}
    }

    /**
     * Print the path with minimum cost between two given
     * nodes, based on the detour matrix computed previously [1p]
     *
     * @param node1
     * @param node2
     */

    public void PrintMinPath (Graph graph, Node node1, Node node2) {

    	ArrayList<Node> nodes = graph.getNodes();
    	
        System.out.print("Best route between ");
        System.out.println( node1.getCity() + " and " + node2.getCity() );

        graph.reset();
        node1.visit();

        // Hint:
        // You may use getNextNode() to retrieve the "next" node
        // on the path from node1 to node2.
        
        System.out.println("Total cost: " + cost[node1.getId()][node2.getId()]);
        
        System.out.print("Calea este : ");
        
        do{
        	node2 = new Node( nodes.get(node2.getId()).getParent().getCity(), nodes.get(node2.getId()).getParent().getId());
        	System.out.print(node2.getId() + " ");
        }while(node2.getId() != node1.getId());
    }

    /**
     *
     * @param node1
     * @param node2
     * @return
     */

    private Node getNextNode (Graph graph, Node node1, Node node2) {

        int id1 = node1.getId();
        int id2 = node2.getId();

        if (id1 == id2) {
            throw new RuntimeException("Path from node " + node1.getCity() + " to itself requested");
        }

        Node pivot = detour[id1][id2];
        if (pivot == null) {
            throw new RuntimeException("No path connects " + node1.getCity() + " to " + node2.getCity() );
        }

        if (pivot.isVisited()) {
            throw new RuntimeException("Cycle Detected");
        }
        pivot.visit();

        return pivot;
    }

    public void dumpCostMatrix()
    {
        for (int i = 0; i < cost.length; ++i) {
            for(int j = 0; j < cost[i].length; ++j) {
                System.out.print( cost[i][j] + " ");
            }
            System.out.print("\n");
        }

        System.out.println("\n");
    }

    public void resetCostMatrix()
    {
        for (int i = 0; i < cost.length; ++i) {
            for (int j = 0; j < cost[i].length; ++j) {
                cost[i][j] = INF;
            }
        }
    }

    public void resetDetourMatrix()
    {
        for (int i = 0; i < detour.length; ++i) {
            for (int j = 0; j < detour[i].length; ++j) {
                detour[i][j] = null;
            }
        }
    }

}
