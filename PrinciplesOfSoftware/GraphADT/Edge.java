package GraphADT;


public class Edge<T,K> {
	//Representation Invariant: An Edge cannot have a null edge_label, start Node or end Node. 
	//-----------------------------------------------------------------------------------------------
	// Abstraction Function:
	//
	// AF (Edge) = (edge_label,start,end)
	//     edge_label = a String stored by the Edge, acting as a label
	//	   start = the parent Node of the Edge, the Node which it exits from
	//     end = the child Node of the Edge, the Node which it leads to
	//
	//
	private T edge_label;
	private Node<K,T> start;
	private Node<K,T> end;

	
	/**
	 * @requires obj != null, no member of the internal representation of obj is null.
	 * @params obj, an Edge to copy
     * @effects Constructs a new Edge with the same internal representation values as obj.
	 */
	public Edge(Edge<T,K> obj) {
		this.edge_label =  obj.getLabel();
		this.start = obj.getStart();
		this.end = obj.getEnd();
		checkRep();
	}
	/**
	 * @requires label!=null, parent!=null, child!=null
	 * @params label, a String stored by this Edge,and child, a Node to lead to.
     * @effects Constructs a new Edge with a label which originates from some parent Node
     * and leads to some child Node.
     * 
	 */
	public Edge(T label, Node<K,T> parent, Node<K,T> child) {
		this.edge_label = label;
		this.start = parent;
		this.end = child;
		checkRep();
	}
	/** equals() overload for edge, so no duplicates in HashSet of edges in each node
	 * @param an Object o, which is hopefully an Edge
	 * @returns a boolean whether or not this Edge is equal to the input object. We note that two Edges
	 * are equal if they have the same edge_label, start node and end node.
	 */
	@Override
	public boolean equals (Object o) {
		if(!(o instanceof Edge<?,?>))
			return false;
		else {
			Edge<?,?> obj = ((Edge<?,?>)o);
			return (this.edge_label == obj.edge_label) && 
					(this.start==obj.start) && (this.end==obj.end);
		}
	}
	/**
     * getLabel function. Retrieves the Edge's label.
     * 
     * @returns The label of this Edge.
     * 
     */
	public T getLabel() {
		return this.edge_label;
	}
	/**
     * getStart function. Retrieves the starting point of the Edge, or, in other
     * words, the Node in which the Edge exits from.
     * 
     * @returns the Node in which this Edge exits from.
     * 
     */
	public Node<K,T> getStart() {
		return this.start;
	}
	/**
     * getEnd function. Retrieves the Node in which this Edge points to.
     * 
     * @returns the Node in which this Edge enters, or leads to.
     * 
     */
	public Node<K,T> getEnd() {
		return this.end;
	}
	
	/*
	 * setWeight function. Changes weight of the edge.
	 * 
	 * @modifies edge_label by setting it equal to new_weights value
	 */
	public void setWeight(T new_weight) {
		edge_label = new_weight;
	}
	/**
     * Checks that the representation invariant holds (if any). 
     * 
     * @throws RuntimeException if the representation invariant is violated
     */
	private void checkRep() throws RuntimeException {
		if(this.edge_label == null || this.start == null || this.end == null)
			throw new RuntimeException("Cannot have a null edge_label, start, or end node.");
	}
}
