package Marvel2;
import GraphADT.Node;
import GraphADT.Edge;
import java.util.*;


public class Path implements Comparable<Path>{
private ArrayList<Node<String,Double>> nodes;
private ArrayList<Edge<Double,String>> edges;
private double weight;
//Abstraction Function: Each node in nodes represents a character along a Path
//and each edge, weighted, connects a pair of nodes, forming the Path with a total
//weight.
//--------------------------------------------------------------------------------
//Representation Invariant: (nodes!=null) && (edges != null) && (weight >=0) && 
// ((edges.size() == nodes.size()-1) || (edges.size() = nodes.size() ==0) )
	

/**
 * Default constructor.
 * 
 * @effects Constructs a new Path object, initializing an empty list of nodes and edges and 
 * initializing weight to 0.0
 */
	public Path() {
		nodes = new ArrayList<Node<String,Double>>();
		edges = new ArrayList<Edge<Double,String>>();
		weight = 0.0;
	//	checkRep();
	}
	/**
	 * Copy constructor.
	 * 
     * @effects Constructs a new Path object which is a copy of an existing one 
	 */
	public Path(Path copy) {
		nodes = new ArrayList<Node<String,Double>>();
		edges = new ArrayList<Edge<Double,String>>();
		
		for(int i = 0; i < copy.getEdges().size(); i++) {
			edges.add(copy.getEdges().get(i));
		}
		for(int j = 0; j < copy.getNodes().size(); j++) {
			nodes.add(copy.getNodes().get(j));
		}

		
		weight = copy.getWeight();
		
	//	checkRep();
	}
	
	/**
	 * addFirstNode function. Adds the source of a Path (nothing else in Path)
	 * 
	 * @param a Node<String,Double> to add to nodes
	 * @modifies this.nodes, since a Node<String,Double> n1 could be added
	 */
	public void addFirstNode(Node<String,Double> n1) {
		if(nodes.size()!=0)
			return;
		else
			nodes.add(n1);
	//	checkRep();
	}
	
	
	/**
	 * extend_path function. Adds an Edge and a Node connecting to the end of the Edge to 
	 * our Path. Increments weight accordingly
	 * 
	 * @param a Node<String,Double> to add to nodes (of this Path)
	 * @param an Edge<Double,String> to add to edges (of this Path)
	 * @modifies this.nodes, since a Node<String,Double>  could be added
	 * @modifies this.edges, since an Edge<Double,String> could be added
	 * @modifies this.weight, as it is incremented by the edge's weight.
	 */
	public void extend_path(Node<String,Double> node, Edge<Double,String> edge) {
		if(edges.size() != nodes.size()-1) {
		//	checkRep();
			return;
		}
		else {
		nodes.add(node);
		edges.add(edge);
		weight+= edge.getLabel();
	//	checkRep();
		}
	}
	
	/**getWeight function. Retrieves this Path's total cost.
	 * 
	 * @returns this.weight
	 */
		
	public double getWeight() {
		return weight;
	}
	
	/**getNodes function. Retrieves a list of Nodes in the Path (in order).
	 * 
	 * @returns this.nodes
	 */
	public ArrayList<Node<String,Double>> getNodes(){
		return nodes;
	}
	
	/**getEdges function. Retrieves a list of edges in the Path (in order).
	 * 
	 * @returns this.edges
	 */
	public ArrayList<Edge<Double,String>> getEdges(){
		return edges;
	}
	
	
	/** compareTo function for Paths.
	 * 
	 * @param a Path arg0 to compare this Path's weight with.
	 * @returns an integer based on how Paths should be organized/ordered (based on weight)
	 */

	@Override
	public int compareTo(Path arg0) {
		Path p2 = (Path)arg0;
		return Double.compare(weight, p2.getWeight());
	}
	

	/**
     * Checks that the representation invariant holds (if any). 
     * 
     * @throws RuntimeException if the representation invariant is violated
     */
	private void checkRep() throws RuntimeException{
		if(nodes==null)
			throw new RuntimeException("nodes can't be null");
		if(edges==null)
			throw new RuntimeException("edges can't be null");
		if(weight < 0.0)
			throw new RuntimeException("Must have weight >= 0");
		if(edges.size() != nodes.size()-1 || (edges.size() == 0 && nodes.size() == 0))
			throw new RuntimeException("Must have edges.size() == nodes.size()-1");
	}
	
}
