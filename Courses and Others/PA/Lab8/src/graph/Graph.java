/**
 * Proiectarea Algoritmilor, 2014
 * Lab 8: Drumuri minime
 *
 * @author  Radu Iacob
 * @email   radu.iacob23@gmail.com
 */

package graph;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

import graph.Node;

/**
 * Graph is retained using adjacency lists
 * eg.: for each node you store a list of edges
 *      (edge: pair with the identity of the neighbour and the cost)
 */
public class Graph {

    public static final int MAX_VALUE = 99999;
    ArrayList< Node > Nodes = new ArrayList<Node>();
    ArrayList< ArrayList< Pair< Node, Integer > > > Edges =
            new ArrayList< ArrayList< Pair< Node, Integer > > >();

    public Graph() {}

    public Graph(String inputFile) {
        initFromFile(inputFile);
    }

    /**
     * @return a list with every node in the graph
     */
    public ArrayList< Node > getNodes() {
        return Nodes;
    }

    /**
     * @return a list with every neighbour of a given node
     * and the associated distance
     */
    public ArrayList< Pair< Node, Integer > > getEdges(Node node) {
        return Edges.get( node.getId() );
    }

    public int getNodeCount() {
        return Nodes.size();
    }

    public String toString() {

        StringBuilder ans = new StringBuilder("Print Graph:\n");

        for (Node node : Nodes) {

            ans.append( "OutEdges for " + node.toString() + " -> ");
            for (Pair<Node,Integer> edge : getEdges(node)) {
                 ans.append( edge.getFirst().getCity() );
                 ans.append( "( " + edge.getSecond() + " ) |" );
            }

            ans.append("\n");
        }

        ans.append("\n");
        return ans.toString();
    }

    /**
     * Reseteaza flag-ul de visit pentru toate nodurile
     */
    public void reset()
    {
        for( Node node : Nodes ){
            node.reset();
        }
    }

    public void initFromFile(String inputFile) {

        clearGraph();
        Scanner scanner;
        try {
            scanner = new Scanner(new File(inputFile));
            readData(scanner);
            scanner.close();
        } catch (FileNotFoundException e) {
            throw new RuntimeException("Check file path.(invalid scanner object)");
        }
    }

    /**
     * Function to parse a custom graph file for the lab
     *
     * Input Format:
     * N = number of nodes
     * N lines with the city names
     * M = number of edges
     * M lines with Node_i Node_j   costBetweenNodeiNodej -- list of edges
     * @param filename
     */
    private void readData (Scanner scanner) {

        int _nodes = scanner.nextInt();
        for (int i = 0; i < _nodes; ++i) {

            String city = scanner.next();
            Node new_node = new Node(city, i);
            insertNode(new_node);
        }

        int edges = scanner.nextInt();
        int node1, node2, cost;

        for (int i = 0; i < edges; ++i) {
            node1 = scanner.nextInt();
            node2 = scanner.nextInt();
            cost  = scanner.nextInt();
            insertEdge( Nodes.get(node1), Nodes.get(node2), cost );
        }
    }

    public void insertNode(Node node) {
        Nodes.add(node) ;
        Edges.add(new ArrayList< Pair< Node, Integer > >());
        registerNode( node );
    }

    public void insertEdge(Node node1, Node node2, Integer cost)  {
        Edges.get( node1.getId() ).add( new Pair< Node, Integer >( node2, cost ) );
    }

    public void clearGraph() {
        Nodes.clear();
        Edges.clear();
        nodeDict.clear();
    }

    private HashMap< String, Node > nodeDict = new HashMap<String,Node>();

    public Node getNode(String city) {
        return nodeDict.get(city);
    }

    private void registerNode( Node node ) {
        nodeDict.put(node.getCity(), node);
    }
}
