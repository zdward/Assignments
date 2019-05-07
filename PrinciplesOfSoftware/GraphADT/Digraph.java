package GraphADT;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.TreeSet;

public class Digraph<T,K> {
	//Representation Invariant: No Nodes in a Digraph share the same value (i.e. there can be
	//only one Node named 'A'). Between two particular Nodes, similarly, no Edges between the Nodes
	//can share the same label. Throughout the entire Digraph, however, there may be two or more edges
	//with the same label. Lastly, we always have it that the 'start' Nodes of an Edge
	//correspond with the data in the ArrayList of outgoing edges in each existing Node.
	//-----------------------------------------------------------------------------------------------
	// Abstraction Function: Hashtable<String,Node> nodes represents our Digraph where each String key
	// is the name of a Node in the graph and each value is the actual Node. We node that each Node has
	// a corresponding HashSet of edges internally.
	private Hashtable<T,Node<T,K>> nodes;
	
	/**
	 * Default constructor.
	 * 
     * @effects Constructs a new Digraph with no nodes and no edges
	 */
	public Digraph() {
		nodes = new Hashtable<T,Node<T,K>>();
		checkRep();
	}
	
	/**
	 * addNode function. Adds a Node storing a String nodeData to the Digraph.
	 * 
	 * @param a type T nodeData to store
	 * @throws an RuntimeException if nodeData == null
	 * @modifies Digraph.nodes, since an entry <nodeData, new Node(nodeData)> is added
	 */
	public void addNode(T nodeData) {
		if(nodeData == null) {
			throw new RuntimeException("Enter a valid value for nodeData");
		}
		else {
			Node<T,K> toAdd = new Node<T,K>(nodeData);
			nodes.put(nodeData,toAdd); //add a node to our list of nodes
		}
		//checkRep();
	}
	
	/**
	 * findNode function. Returns the desired Node object (that you are searching for).
	 * 
	 * @param a type T nodeData which a Node has stored. The Node which contains this string
	 * as a value is the Node which you are searching for.
	 * @returns null if there is no node which contains nodeData in the Digraph, otherwise, 
	 * the Node containing nodeData in the Digraph is returned
	 */
	public Node<T,K> findNode(T nodeData) {
		if(nodeData == null || nodes.get(nodeData) == null)
			return null;
		else
			return nodes.get(nodeData);
	}
	/**
	 * addEdge function. Adds an Edge exiting from the Node with the value of parentNode and
	 * leading to the Node with the value of childNode. This Edge will store a String, acting as 
	 * it's label, called edgeLabel.
	 * 
	 * @param a type T parentNode, contained by a Node to start an Edge from. Following a type T
	 * childNode, contained by a Node to lead the Edge to. Finally, a type T edgeLabel, contained by
	 * the edge upon creation.
	 * @modifies Digraph.nodes: Adds on to the list of outgoing edges in some Nodes in the ArrayList
	 * of Digraph.nodes.
	 */
	public void addEdge(T parentNode, T childNode, K edgeLabel) {
		Node<T,K> parent = findNode(parentNode);
		Node<T,K> child = findNode(childNode);
		parent.addEdge(edgeLabel, child);
		if(!child.equals(parent))
			child.addEdge(edgeLabel, parent);
	//	checkRep();
	}
	/**
	 * getNodes function. Gets a list of Nodes currently in this Digraph instance, each Node having
	 * an ArrayList of exiting edges.
	 * 
	 * @returns a list of Nodes in the Digraph, each Node with a corresponding list of Edges
	 * which exit from it.
	 */
	public TreeSet<Node<T,K>> getNodes(){
		TreeSet<Node<T,K>> ret = new TreeSet<Node<T,K>>(new NodeComparator());
		ArrayList<Node<T,K>> to_read = new ArrayList<Node<T,K>>(nodes.values());
		for (Node<T,K> n: to_read) {
			ret.add(n);
		}
		return ret;
	}
	
	/**
     * Checks that the representation invariant holds (if any). 
     * 
     * @throws RuntimeException if the representation invariant is violated
     */
	private void checkRep() throws RuntimeException{
		//First, we check if any two nodes share the same value in linear time
		Hashtable<Node<T,K>,Integer> occurrences = new Hashtable<Node<T,K>,Integer>();
		TreeSet<Node<T,K>> ret = getNodes();
		Iterator<Node<T,K>> it = ret.iterator();
		while(it.hasNext()) {
			Node<T,K> e = it.next();
			Integer null_or_not = occurrences.put(e,1);
			if(null_or_not != null) {
				throw new RuntimeException("You can't have duplicate nodes!");
			}
		}
		//Next, we check if there are any edges with the same label between each possible Node pair
		//loop through each node
		it = ret.iterator(); //reuse our previous iterator to save some memory
		while(it.hasNext()) { //loop through each node
			Hashtable<K,HashSet<Node<T,K>>> edgeEnds = new Hashtable<K,HashSet<Node<T,K>>>();
			Node<T,K> current_node = it.next();
			//acquire all edges going out from current node
			HashSet<Edge<K,T>> outgoing_edges = current_node.getEdges();
			HashSet<K> outgoing_edges_strings = new HashSet<K>();
			Iterator<Edge<K,T>> edgeIter = outgoing_edges.iterator();
			//loop through edges and populate outgoing_edges_strings
			while(edgeIter.hasNext()) {
				Edge<K,T> currentEdge = edgeIter.next();
				outgoing_edges_strings.add(currentEdge.getLabel());
			}
			edgeIter = outgoing_edges.iterator();
			Iterator<K> labelIter = outgoing_edges_strings.iterator();
			while(labelIter.hasNext() && edgeIter.hasNext()) {
				K currentLabel = labelIter.next();
				Edge<K,T> currentEdge = edgeIter.next();
				if(edgeEnds.contains(currentLabel)) {
					if(edgeEnds.get(currentLabel).contains(currentEdge.getEnd())) {
						throw new RuntimeException("You can't have multiple edges between two Nodes with the same name.");
					}
				}
				else {
					//add to the occurrences (edgeEnds) hash table
					HashSet<Node<T,K>> children = new HashSet<Node<T,K>>();
					children.add(currentEdge.getEnd());
					edgeEnds.put(currentLabel,children);
				}
			}	
		}
		/*Finally, we check to see if each edge's start and end correspond with each Node's internal
		ArrayList<Edge> data. To do this, we just have to check whether each edge's start Node is the node
		it is actually going out from.*/
		it = ret.iterator();
		while(it.hasNext()) {
			Node<T,K> current = it.next();
			Iterator<Edge<K,T>> edgeIt = current.getEdges().iterator(); 
			while(edgeIt.hasNext()) {
				Edge<K,T> e = edgeIt.next(); //current edge
				if(!(e.getStart().getValue().equals(current.getValue()))) {
					throw new RuntimeException("Edge information doesn't match the ArrayList<Edge> stored in nodes.");
				}
			}
		}
	}
}
