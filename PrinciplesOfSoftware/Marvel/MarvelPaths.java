package Marvel;
import GraphADT.Digraph;
import GraphADT.Node;
import GraphADT.Edge;
import java.util.*;
import java.io.*;

public class MarvelPaths{
	private Digraph<String,String> g;
	
	
	/**
	 * Default constructor.
	 * 
     * @effects Constructs a new MarvelPaths object, initializing the internal graph to empty
	 */
	public MarvelPaths() {
		g = new Digraph<String,String>();
	}
	
	/**
	 * Returns the graph for testing
	 * 
	 * @returns g, our internal Digraph for testing purposes
	 */
	public Digraph<String,String> retrieve_graph() {
		return this.g;
	}
	
	/**
	 * createNewGraph function. This function takes in a filename, parses it, and constructs
	 * builds up our internal Digraph g to represent the data.
	 * 
	 * @param a String filename to read
	 * @modifies (Digraph) g: Adds on new nodes and edges to our internal Digraph so it corresponds
	 * with the data in our input file
	 */
	public void createNewGraph(String filename) {
		//create our Map and Set
		Map<String, Set<String>> charsInBooks = new HashMap<String, Set<String>>();
		Set<String> chars = new HashSet<String>();
		
		//populate Map and Set
		try {
			MarvelParser.readData(filename, charsInBooks, chars);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//so we can loop through chars
		Iterator<String> charIt = chars.iterator();
		
		//add all nodes to the graph
		while(charIt.hasNext()) {
			g.addNode(charIt.next());
		}
		
		//add all edges to the graph
		for (Map.Entry<String,Set<String>> entry : charsInBooks.entrySet())  
		{
			String book_name = entry.getKey();
			ArrayList<String> common_characters = new ArrayList<String>(entry.getValue());
			for(int i = 0; i < common_characters.size(); i++) {
				for(int j = i; j < common_characters.size(); j++) {
					if(i!=j) {
						g.addEdge(common_characters.get(i),common_characters.get(j), book_name);
					//	g.addEdge(common_characters.get(j),common_characters.get(i), book_name);
					}
				}
			}
		}
	}
	
	/**
	 * findPath function. This function returns a string containing the lexicographically shortest path 
	 * from some source character to another input character.
	 * 
	 * @param a String node1 which represents the name of a character and a String node2 which
	 * represents the name of another character.
	 * @returns a String containing the lexicographically shortest path from g.findNode(node1) to
	 * g.findNode(node2). If node1 and node2 are different and invalid characters, then 
	 * the String returned will contain two lines, one which says "unknown character " + node1
	 * and one which says "unknown character " + node2. If only one of these characters are unknown, only
	 * one of the previous lines are printed. If node1 and node2 are valid and the same, "path from " + node1
	 * + " to " + node2 + ":\n" is returned. Lastly, if there exists no path going from g.findNode(node1) to
	 * g.findNode(node2), then "path from " + node1 + " to " + node2 + ":\nno path found\n" is 
	 * returned.
	 */
	public String findPath(String node1, String node2) {
		String ret = "";
		
		//null cases
		if(g.findNode(node1) == null || g.findNode(node2) == null) {
			if(g.findNode(node1) == null)
				ret += "unknown character " + node1 + "\n";
			if(g.findNode(node2) == null && (!node1.equals(node2)))
				ret += "unknown character " + node2 + "\n";
			return ret;
		}
		
		//the case in which start == end
		if(node1.equals(node2)) {
			ret = "path from " + node1 + " to " + node2 + ":\n";
			return ret;
		}
		
		//Map M in the pseudocode
		HashMap<Node<String,String>, List<Edge<String,String>>> nodes_to_paths = new HashMap<Node<String,String>,List<Edge<String,String>>>();
		
		//we create a queue
		LinkedList<Node<String,String>> queue = new LinkedList<Node<String,String>>();
		
		//add start to queue and empty list to map
		queue.add(g.findNode(node1));
		List<Edge<String,String>> empty = new ArrayList<Edge<String,String>>();
		nodes_to_paths.put(g.findNode(node1),empty);
		
		while(queue.size() != 0) {
			
			//Dequeue a vertex from the queue, n
			Node<String,String> n = queue.poll();
			
			if(n.getValue().equals(node2)){
				ret += "path from " + node1 + " to " + node2 + ":\n";
				List<Edge<String,String>> path = nodes_to_paths.get(n);
				for(Edge<String,String> s: path) {
					ret += s.getStart().getValue() + " to "+ s.getEnd().getValue() + " via " + s.getLabel() + "\n";
				}
			}
			
			//sort edges in increasing order of their endNodes (children of source)
			//if children of source are equal, then sort by comparing edge values
			TreeSet<Edge<String,String>> currentEdges = new TreeSet<Edge<String,String>>(new EdgeComparator2());
			for(Edge<String,String> e: n.getEdges()) {
				currentEdges.add(e);
			}
			
			//for each (sorted) edge
			for(Edge<String,String> e: currentEdges) {
				if(!nodes_to_paths.containsKey(e.getEnd())){
					//Let p be what node1 maps onto in M
					List<Edge<String,String>> path_to_n = new ArrayList<Edge<String,String>>(nodes_to_paths.get(n));
					
					//Let p' be p with e appended
					List<Edge<String,String>> path_to_n_prime = new ArrayList<Edge<String,String>>(path_to_n);
					path_to_n_prime.add(e);
					
					//add m --> p' to M
					nodes_to_paths.put(e.getEnd(),path_to_n_prime);
					
					//add m to queue
					queue.add(e.getEnd());
				}
			}
		}
		//the case of no path
		if(ret.equals("")) {
			return "path from " + node1 + " to " + node2 + ":\nno path found\n";
		}
		return ret;
	}	
}

//so we can sort our edges properly, allowing this specific BFS procedure to work
class EdgeComparator2 implements Comparator<Edge<String,String>>{

	@Override
	public int compare(Edge<String,String> o1, Edge<String,String> o2) {
		String s1 = o1.getEnd().getValue();
		String s2 = o2.getEnd().getValue();
		if(s1.compareTo(s2) == 0) {
			return o1.getLabel().compareTo(o2.getLabel());
		}
		else {
			return s1.compareTo(s2);
		}
	}
	
}
