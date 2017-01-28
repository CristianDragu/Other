/**
 * Proiectarea Algoritmilor, 2014
 * Lab 8: Drumuri minime
 *
 * @author  Radu Iacob
 * @email   radu.iacob23@gmail.com
 */

package minCost;

import graph.Graph;

import java.util.ArrayList;

public class MinCost {

    protected ArrayList<Integer> distance;
    protected Graph graph;

    public MinCost( Graph graph ){

        this.graph = graph;

        int nodeCount = graph.getNodeCount();
        distance = new ArrayList<Integer>(nodeCount);
        for( int i = 0; i < nodeCount; ++i ){
            distance.add(Graph.MAX_VALUE);
        }
    }

    protected void resetDistance()
    {
        for( int i = 0; i < distance.size(); ++i ){
            distance.set(i, Graph.MAX_VALUE );
        }
    }

}
