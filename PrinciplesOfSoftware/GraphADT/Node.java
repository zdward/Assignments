package hw4;
import java.util.HashSet;
import java.util.Iterator;

public class Node<T,K> {
	//Representation Invariant: A Node must have a String value such that value != null. Second,
	// In Node.edges, each edge, e, has an e.getStart() value of this Node instance.
	//-----------------------------------------------------------------------------------------------
	// Abstraction Function:
    //
    // AF (Node) = <Edge> , value
    //     <Edge> = { Node.edges[i] | 0 <= i < Node.edges.size () } 
	//	   value = a String value to be stored
    //     
    //
    // i.e. Node object consists of an ArrayList of outgoing edges and stores a type T value
    //
	private T value;
	private HashSet<Edge<K,T>> edges;
	
	
	/**
	 * @param name, the String stored by this Node.
	 * @requires name != null
     * @effects Constructs a new Node which stores a type T name and has
     * no outgoing edges.
	 */
	public Node(T name) {
		this.value = name;
		edges = new HashSet<Edge<K,T>>();
		//checkRep();
	}
	/**equals() override
	 * @param o, an object which is (hopefully) a Node
	 * @returns a boolean whether or not the object o is equal to this Node
	 */
	public boolean equals (Object o) {
		if(!(o instanceof Node<?,?>)) {
			return false;
		}
		else {
			Node<?,?> obj = (Node<?,?>)o;
			return this.value == obj.value;
		}
	}
	/**
     * getValue function. Returns the String stored in the Node, also referred to
     * as its value
     * 
     * @returns The type T stored in this Node instance
     * 
     */
	public T getValue() {
		return this.value;
	}
	/**
     * getEdges function. Returns an ArrayList of edges exiting from this 
     * node.
     * 
     * @returns an ArrayList of Edges exiting this Node instance
     * 
     */
	public HashSet<Edge<K,T>> getEdges(){
		return this.edges;
	}         
	/**
     * addEdge function. Adds an Edge to the list of Edges exiting this
     * Node instance
	 * @param a value K and a Node childNode
     * @requires value!=null and childNode != null.
     * @modifies this.edges: Adds an Edge to this.edges labeled with a String value, leading
     *  to a Node childNode.
     * 
     */
	
	public void addEdge(K value, Node<T,K> childNode) {
		//HashSets take care of duplicates already
		Edge<K,T> e = new Edge<K,T>(value,this,childNode);
		this.edges.add(e);
		//checkRep();
	}
	
	/**
     * findEdge function. Returns an outgoing edge with a specific destination node.
	 * @param a destination Node<T,K> 
     * @returns An Edge<K,T> which takes this node to the destination node
     * 
     */
	public Edge<K,T> findEdge(Node<T,K> destination){
		for(Edge<K,T> edge: edges) {
			if(edge.getEnd().equals(destination))
				return edge;
		}
		return null;
	}
	/**
     * Checks that the representation invariant holds (if any). 
     * 
     * @throws RuntimeException if the representation invariant is violated
     */
	@SuppressWarnings("unused")
	private void checkRep() throws RuntimeException{
		if(value==null)
			throw new RuntimeException("A node value cannot be null.");
		Iterator<Edge<K,T>> it = edges.iterator();
		while(it.hasNext()) {
			Edge<K,T> e= it.next();
			if(!(e.getStart().getValue().equals(this.value))) {
				throw new RuntimeException("All Edges in Nodes.edges must have this Node as it's parent Node.");
			}
		}
	}
}



