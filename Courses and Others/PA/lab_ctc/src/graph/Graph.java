/**
 * Proiectarea Algoritmilor, 2013
 * Lab 7: Aplicatii DFS
 * 
 * @author 	Radu Iacob
 * @email	radu.iacob23@gmail.com
 */

package graph;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;
import graph.Node;

public class Graph {

	public enum GraphType {
		DIRECTED,
		UNDIRECTED
	};

	public GraphType _type;

	ArrayList< Node > Nodes;
	ArrayList< ArrayList< Node > > Edges;
	
	public int time;
	
	/**
		Componente tari conexe
	*/
	
	public Stack< Node > stack;
	public ArrayList< ArrayList< Node > > ctc;
	
	/**
		Componente biconexe
	*/
	
	public Stack< Pair< Node, Node > > edgeStack; 
	public ArrayList< Node > articulationPoints;
	public ArrayList< Pair<Node,Node> > muchiiCritice; // bridge
	
	
	public Graph( GraphType type )
	{
		Nodes = new ArrayList<Node>();
		Edges = new ArrayList< ArrayList<Node> >();
	
		stack = new Stack< Node >();
		ctc   = new ArrayList< ArrayList< Node > >();
		
		edgeStack = new Stack< Pair<Node,Node> >();
		
		articulationPoints = new ArrayList< Node >();
		muchiiCritice  	  = new ArrayList< Pair<Node,Node> >();
		
		_type = type;
	}
	
	public int nodeCount()
	{
		return Nodes.size();
	}
	
	public void insertEdge( Node node1, Node node2 )
	{
		Edges.get( node1.getId() ).add( node2 );
	}

	public void insertNode( Node node )
	{
		Nodes.add( node );
		Edges.add( new ArrayList< Node >() );
	}
	
	public ArrayList< Node > getNodes()
	{
		return Nodes;
	}

	public ArrayList< Node > getEdges( Node node )
	{
		return Edges.get( node.getId() );
	}
	
	public void reset()
	{
		for( Node n : Nodes )
			n.reset();
		
		stack.clear();
		ctc.clear();
		
		articulationPoints.clear();
		muchiiCritice.clear();
		
		time = 0;
	}
	
	public void printCTC()
	{
		System.out.println("Strongly Connected Componenets:"); 
		for( ArrayList< Node > c_ctc : ctc ){
			System.out.println( c_ctc );		
		}
		
		System.out.println("\n");
	}
	
	/**
	 * Function to read all the tests
	 * 
	 * Input Format:
	 * N M
	 * Nodei Nodej				   -- list of edges
	 * ...
	 * where
	 * N = Number of Nodes
	 * M = Number of Edges
	 * @param filename
	 */
	
	public void readData( Scanner scanner ){

		if( scanner == null ) return;
		
		int nodes = scanner.nextInt();
		int edges = scanner.nextInt();
		
		for( int i = 0; i < nodes; ++i )
		{
			Node new_node = new Node(i);
			insertNode( new_node );
		}
		
		for( int i = 0; i < edges; ++i )
		{
			int node1 = scanner.nextInt();
			int node2 = scanner.nextInt();
			insertEdge( Nodes.get( node1 ), Nodes.get( node2 ) );
			
			if( _type == Graph.GraphType.UNDIRECTED ){
				insertEdge( Nodes.get(node2), Nodes.get(node1) );
			}
		}
		
	}
	
	public String toString()
	{
		String ans = "Graph:\n";
		for( Node n : Nodes )
		{
			ans += n.toString() + " : ";
			ans += Edges.get(n.getId()).toString(); 
			ans += "\n";
		}
		ans += "\n";
		return ans;
	}
}
