/**
 * Proiectarea Algoritmilor, 2014
 * Lab 8: Drumuri minime
 *
 * @author  Radu Iacob
 * @email   radu.iacob23@gmail.com
 */

package graph;

public class Node {

    private String _city;
    private int _id;
    private boolean _visited = false;
    private Node parent = null;

    public Node(String city, int id) {
        _city = city;
        _id   = id;
    }

    public Node(int id) {
        _city = "";
        _id = id;
    }

    public Node getParent() {
        return parent;
    }

    public void setParent(Node parent) {
        this.parent = parent;
    }

    public int getId() {
        return _id;
    }

    public boolean isVisited() {
        return _visited;
    }

    public void visit() {
        _visited = true;
    }

    public void reset() {
        _visited = false;
    }

    public void setCity( String city ) {
        _city = city;
    }

    public String getCity() {
        return _city;
    }

    public String toString() {
        String res = "Node : ";
        if( _city.length() != 0 ) res += _city + " , ";
        return res += (_id);
    }

}
