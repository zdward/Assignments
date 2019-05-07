package Marvel2;
import GraphADT.Digraph;
import GraphADT.Node;
import Marvel.MarvelParser;
import GraphADT.Edge;
import java.util.*;
import java.io.*;

public class MarvelPaths2{
	private static Digraph<String,Double> dg;
	
	
	/**
	 * Default constructor.
	 * 
     * @effects Constructs a new MarvelPaths2 object, initializing the internal graph to empty
	 */
	public MarvelPaths2() {
		dg = new Digraph<String,Double>();
	}
	
	/**
	 * Returns the graph for testing
	 * 
	 * @returns g, our internal Digraph for testing purposes
	 */
	public Digraph<String,Double> retrieve_graph() {
		return dg;
	}
	
	/**
	 * createNewGraph function. This function takes in a filename, parses it, and
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
					dg.addNode(charIt.next());
				}
				
				//add all edges to the graph
				for (Map.Entry<String,Set<String>> entry : charsInBooks.entrySet())  
				{
					String book_name = entry.getKey();
					ArrayList<String> common_characters = new ArrayList<String>(entry.getValue());
					for(int i = 0; i < common_characters.size(); i++) {
						for(int j = i; j < common_characters.size(); j++) {
							boolean hasEdgeAlready = false;
							if(i!=j) {
								Node<String,Double> node_i = dg.findNode(common_characters.get(i));
								Node<String,Double> node_j = dg.findNode(common_characters.get(j));
								for(Edge<Double,String> e: node_i.getEdges()) {
									if(e.getEnd().equals(node_j)) {
										hasEdgeAlready = true;
										e.setWeight(e.getLabel()+1);
										//adjust weight of edge between nodes i and j
										
										Edge<Double,String> e_reverse = node_j.findEdge(node_i);
										e_reverse.setWeight(e_reverse.getLabel()+1);
									}
								}
								if(!hasEdgeAlready) {
									dg.addEdge(common_characters.get(i),common_characters.get(j), 1.0);
								}
							}
						}
					}
				}
				for(Node<String,Double> current_n: dg.getNodes()) {
					for(Edge<Double,String> current_ed: current_n.getEdges()) {
						current_ed.setWeight(1.0/current_ed.getLabel());
					}
				}
		}
		

	
	/**
	 * findPath function. This function returns a string containing the least cost path 
	 * from some source character to another input character. The cost between two characters
	 * is the multiplicative inverse of the amount of books they are in together.
	 * 
	 * @param a String node1 which represents the name of a character and a String node2 which
	 * represents the name of another character.
	 * @returns a String containing the least cost path from g.findNode(node1) to
	 * g.findNode(node2). If node1 and node2 are different and invalid characters, then 
	 * the String returned will contain two lines, one which says "unknown character " + node1
	 * and one which says "unknown character " + node2. If only one of these characters are unknown, only
	 * one of the previous lines are printed. If node1 and node2 are valid and the same, "path from " + node1
	 * + " to " + node2 + ":\n" is returned. Lastly, if there exists no path going from g.findNode(node1) to
	 * g.findNode(node2), then "path from " + node1 + " to " + node2 + ":\nno path found\n" is 
	 * returned.
	 */
	public static Path findPath(String CHAR1, String CHAR2, Digraph<String,Double> to_merge) {
		dg = new Digraph<String,Double>();
		dg = to_merge;
		//finished path
		Path finished = new Path();
		
		//the priority queue in Dijkstra's algorithm
		PriorityQueue<Path> active = new PriorityQueue<Path>();
		
		Path start = new Path();
		
		start.addFirstNode(dg.findNode(CHAR1));
		
		//add start to active
		active.add(start);
		
		
		while(active.size() != 0) {
//			System.out.println("============QUEUE OF NODES:==========");
//			for(Path p: active) {
//				p.print_path();
//			}
//			System.out.println("============DONE WITH QUEUE==========");
			//declare minPath
			Path minPath = active.poll();
			//declare minDest
			Node<String,Double> minDest = new Node<String,Double>(null);
			
			minDest = minPath.getNodes().get(minPath.getNodes().size()-1);
			
			//case when minDest = dest
			if(minDest.equals(dg.findNode(CHAR2))) {
				return minPath;
			}
			
			//if minDest is in finished
			if(finished.getNodes().contains(minDest)) {
				continue;
			}
			
			//for each edge e = <minDest, child>
			for(Edge<Double,String> e: minDest.getEdges()) {
				
				//if child is not in finished
				if(!(finished.getNodes().contains(e.getEnd()))) {					
					Path newPath = new Path(minPath);
					

					
					//newPath = minPath + e
					newPath.extend_path(e.getEnd(),e);
					
					
					//add newPath to active
					active.add(newPath);
				}
			}
			
			//if(minPath.getEdges().size() > 0)
				//add minDest to finished
			if(finished.getNodes().size()==0)
				finished.addFirstNode(minDest);
			
			else
				finished.extend_path(minDest, minPath.getEdges().get(minPath.getEdges().size()-1));
		} 
		//case of no path
		return new Path();
	}
}
