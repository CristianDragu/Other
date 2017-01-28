/**
 * Proiectarea Algoritmilor, 2013
 * Lab 7: Aplicatii DFS
 * 
 * @author 	Radu Iacob
 * @email	radu.iacob23@gmail.com
 */

package graph;

import java.util.HashMap;

public class Node {

	String _name;
	int _id;
	
	/**
		Generic property field
	*/
	HashMap< Property, Integer > _prop;
	
	public Node( String name, int id )
	{
		_name = name;
		_id   = id;
		reset();
	}
	
	public Node( int id )
	{
		_name = "";
		_id = id;
		
		_prop = new HashMap< Property, Integer >();
		reset();
	}
	
	public boolean visited()
	{
		return !(discoveryTime == UNSET);
	}
	
	public void reset()
	{
		discoveryTime = lowlink = ctcIndex = UNSET;
		inStack = false;
		_prop.put( Property.CTC, UNSET);
	}
	
	public String getName()
	{
		return _name;
	}
	
	public int getId()
	{
		return _id;
	}
	
	public int getProperty( Property p )
	{
		return _prop.get(p);
	}
	
	public void setProperty( Property p, int value )
	{
		_prop.put( p, value);
	}

	public String toString()
	{
		String res = "Node : ";
		
		if( _name.length() != 0 ) res += _name + " , ";
		res += (_id);
		
		return res;
	}
	
	/*
		DF traversal
	*/

	/**
	 *  Timpul de initializare in parcurgerea DF
	 */
	public int discoveryTime;		

	/*
		Componente tare conexe
	*/
	
	/**
	 *  cel mai mic index al unui nod accesibil din nodul curent 
	 */
	public int lowlink;

	/**
	 *  nodul se afla in stack 
	 */
	public boolean inStack;

	/**
	 *  bonus - indexul componentei tare conexe
	 */
	public int ctcIndex;
	
	/**
	 *  bonus
	 */
	public int sum;
	
	public enum Property{
		CTC
	}

	public final static int UNSET = -1;
}
