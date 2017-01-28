/**
 * Proiectarea Algoritmilor, 2014
 * Lab 8: Drumuri minime
 *
 * @author  Radu Iacob
 * @email   radu.iacob23@gmail.com
 */

package lab8;
import java.util.ArrayList;

import minCost.BellmanFord;
import minCost.Dijkstra;
import minCost.RoyFloyd;
import graph.Graph;
import graph.Node;

public class Main{


    /**
     * Problem configuration
     */
    final public static String startLabel = "Bucuresti";
    final public static String endLabel   = "Paris";

    final public static String dataSet1 = "./date1"; /* graph with positive edges */
    final public static String dataSet2 = "./date2"; /* graph with negative edges, Dijkstra should fail */
    final public static String dataSet3 = "./date3"; /* graph with negative cycle */

    public enum Task{
        ROY_FLOYD,
        DIJKSTRA,
        BELLMAN_FORD
    }

    /* TODO: change dataSet and currentTask */
    public static String dataSet     = dataSet2;
    public static Task   currentTask = Task.DIJKSTRA;

    public static void main(String[] args)
    {
        Graph graph = new Graph(dataSet);
        Node source = graph.getNode(startLabel);
        Node dest   = graph.getNode(endLabel);

        switch (currentTask) {

            case ROY_FLOYD:
            {
                RoyFloyd solver = new RoyFloyd(graph.getNodeCount());
                solver.computeRoyFloyd(graph);
                solver.PrintMinPath(graph, source, dest);
                break;
            }

            case DIJKSTRA:
            {
                Dijkstra solver = new Dijkstra(graph);
                ArrayList<Integer> distance = solver.computeDistance(source);
                printDistance(graph, distance);
                break;
            }

            case BELLMAN_FORD:
            {
                BellmanFord solver = new BellmanFord(graph);
                ArrayList<Integer> distance = solver.computeDistance(source);
                printDistance(graph, distance);
                break;
            }

            default: break;
        }
    }

    static public void printDistance(Graph graph, ArrayList<Integer> distance)
    {
        System.out.println("Result: ");
        int nodeCount = graph.getNodeCount();
        ArrayList<Node> nodes = graph.getNodes();

        for (int i = 0; i < nodeCount; ++i){
            System.out.println(nodes.get(i).getCity() + " , " + distance.get(i));
        }
    }
}
