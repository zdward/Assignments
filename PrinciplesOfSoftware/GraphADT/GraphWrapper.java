package hw4;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;


public class GraphWrapper{
	Digraph<String,String> g;
	
	
	/**
	 * Default constructor.
	 * 
     * @effects Constructs a new GraphWrapper with no nodes and no edges
	 */
	public GraphWrapper() {
		g = new Digraph<String,String>();
	}
	
	/**
	 * addNode function. Adds a node labeled as nodeData to the Digraph g.
	 * 
	 * @param a String nodeData to store
	 * @modifies Digraph.nodes by adding a Node storing a String nodeData with
	 * no Edges exiting this Node
	 */
	public void addNode(String nodeData) {
		g.addNode(nodeData);
	}
	/**
	 * addEdge function. Adds an edge <parentNode,childNode> labeled as 
	 * edgeLabel to the Digraph.
	 * 
	 * @param Strings parentNode, childNode, and edgeLabel: parentNode represents 
	 * the Node in which the Edge exits, childNode represents the Node in which the 
	 * Edge enters, and edgeLabel represents the label, or weight, of the Edge.
	 * @modifies Digraph.nodes by adding a Node storing a String nodeData with
	 * no Edges exiting this Node
	 */
	public void addEdge(String parentNode, String childNode, String edgeLabel) {
		g.addEdge(parentNode, childNode, edgeLabel);
	}
	
	/**
	 * listNodes function. Returns an iterator<String> which returns the 
	 * nodes in alphabetical order.
	 * 
	 * @returns an iterator which returns the nodes in lexicographical (alphabetical) order. 
	 * If there are no Nodes in the given Digraph, then an Iterator<String> referring to a single "" 
	 * element in an ArrayList of size 1 is returned.
	 */
	public Iterator<String> listNodes(){
		//already alphabetized
		TreeSet<Node<String,String>> nodes = new TreeSet<Node<String,String>>(g.getNodes());
		ArrayList<String> node_strings = new ArrayList<String>();
		ArrayList<String> no_nodes = new ArrayList<String>();
		if(nodes.size() == 0)
			return no_nodes.iterator();
		Iterator<Node<String,String>> nodeIt = nodes.iterator();
		
		//populate node_strings
		while(nodeIt.hasNext()){
			node_strings.add(nodeIt.next().getValue());
		}
		
		return node_strings.iterator();
	}
	/**
	 * listChildren function. Returns an iterator which returns the list of childNode(edgeLabel) 
	 * in lexicographical (alphabetical) order by node name and 
	 * secondarily by edge label
	 * 
	 * @returns null if parentNode has no children or the parentNode does not exist, 
	 * otherwise, an Iterator<String> which returns the list of childNode(edgeLabel) in 
	 * alphabetical order by name and secondarily by edge label
	 */
	public Iterator<String> listChildren(String parentNode){
		//base our final answer off of this list ^^
		TreeSet<String> childrenStrings = new TreeSet<String>(); 
		//find the parent node
		Node<String,String> origin = g.findNode(parentNode);
		//if no parent node or EMPTY GRAPH
		if(origin == null || origin.getEdges().size()==0) {
			Iterator<String> it = childrenStrings.iterator();
			return it;
		}
		
		//so that all edges are sorted already
		TreeSet<Edge<String,String>> outgoing_edges = new TreeSet<Edge<String,String>>(new EdgeComparator());
		Iterator<Edge<String,String>> edgeIt = origin.getEdges().iterator();
		
		//populate outgoing_edges TreeSet
		while(edgeIt.hasNext()) {
			Edge<String,String> e = edgeIt.next();
			outgoing_edges.add(e);
		}
		
		edgeIt = outgoing_edges.iterator();
		
		//loop through each edge
		while(edgeIt.hasNext()) {
			Edge<String,String> currentE = edgeIt.next();
			String toAdd = currentE.getEnd().getValue(); //grab a child's value/string/name
			toAdd+="(" + currentE.getLabel()+ ")";
			childrenStrings.add(toAdd);
		}
		Iterator<String> ret = childrenStrings.iterator();
		return ret;
	}
}

//for homework 6, we don't really use this, so...
//I commented out the original code and put in placeholder
//code for now
class NodeComparator implements Comparator<Node<?,?>>{

	@Override
	public int compare(Node<?,?> arg0, Node<?,?> arg1) {
		String s1 = (String)arg0.getValue();
		String s2 = (String)arg1.getValue();
		return s1.compareTo(s2);
	}
	
	
}

class EdgeComparator implements Comparator<Edge<String,String>>{

	@Override
	public int compare(Edge<String,String> o1, Edge<String,String> o2) {
		String s1 = o1.getLabel();
		String s2 = o2.getLabel();
		if(s1.compareTo(s2) == 0) {
			return -1;
		}
		else {
			return s1.compareTo(s2);
		}
	}
	
}
