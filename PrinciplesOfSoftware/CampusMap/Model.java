package CampusMap;

import java.lang.Math;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

import GraphADT.Digraph;
import GraphADT.Node;
import Marvel2.MarvelPaths2;
import Marvel2.Path;

public class Model {
	//each node is an ID, each edge has a double weight
private Digraph<String,Double> dg;
private HashMap<String,String> name_to_id;
private HashMap<String,String> id_to_name;
private HashMap<String,ArrayList<Double>> id_to_coords;


/**
 * Default constructor.
 * 
 * @effects Constructs a new Model object, initializing the internal graph to empty and
 * name_to_id, id_to_name, and id_to_coords as empty hashmaps
 */
	public Model() {
		
		//initialize instance variables
		dg = new Digraph<String,Double>();
		name_to_id = new HashMap<String,String>();
		id_to_name = new HashMap<String,String>();
		id_to_coords = new HashMap<String,ArrayList<Double>>();
	}
	
	
	/**
	 * Returns the internal Digraph so we can use Digraph functions in 
	 * CampusPaths
	 * 
	 * @returns g, our internal Digraph 
	 */
	public Digraph<String,Double> retrieve_graph(){
		return dg;
	}
	
	/**
	 * createNewGraph function. This function takes in a nodes_file and edges_file, 
	 * parses them, and builds our internal Digraph corresponding to the data in these files.
	 * 
	 * @param nodes_file, containing all nodes in the Digraph
	 * @param edges_file, containing all edges in the Digraph
	 * @modifies (Digraph) this.dg: Adds on new nodes and edges to our internal Digraph so it corresponds
	 * with the data in our input file
	 */
	public void createNewGraph(String nodes_file, String edges_file) {
		
		//initialize places and connections
		Set<Place> places = new HashSet<Place>();
		HashMap<String,Place> ids_to_places = new HashMap<String,Place>();
		Set<ArrayList<String>> connections = new HashSet<ArrayList<String>>();
		
		//populate Map and Set
		try {
			CampusParser.readPlaces(nodes_file, places,ids_to_places);
			CampusParser.readConnections(edges_file, connections);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		//add all nodes
		for(Place p: places) {
			
			//add the id of the place
			dg.addNode(p.id());
			
			//add to converter hashmaps
			id_to_name.put(p.id(),p.name());
			name_to_id.put(p.name(),p.id());
			
			//set up coords list [x,y]
			ArrayList<Double> coords = new ArrayList<Double>();
			coords.add(p.x());
			coords.add(p.y());
			
			//add id --> [x,y] entry
			id_to_coords.put(p.id(),coords);
		}
		
		//for each edge (id1,id2)
		for(ArrayList<String> pair: connections) {
			//grab start and end places <start,end>, O(1) computation
			Place start = ids_to_places.get(pair.get(0));
			Place end = ids_to_places.get(pair.get(1));
			
			//grab euclidean distance from place1 to place2
			double distance = start.distance(end);
			
			//grabbing start and end Nodes, O(1) computation
			Node<String,Double> startNode = dg.findNode(start.id());
			Node<String,Double> endNode = dg.findNode(end.id());
			
			//add Edge from place1 to place2 and vice versa
			startNode.addEdge(distance, endNode);
			endNode.addEdge(distance, startNode);
		}
	}
	
	
	/*isDigit function to determine whether or not a certain String represents
	 * a series of digits. This function is used as a helper function.
	 * 
	 * @param str, we check whether or not this string is a series of digits
	 * @returns a boolean representing whether or not str is a series of digits
	 */
	public boolean isDigit(String str)
	{
	    char[] charArray = str.toCharArray();
	    for(char c:charArray)
	    {
	        if (!Character.isDigit(c))
	            return false;
	    }
	    return true;
	}
		
	
	/* findPath function. This function mostly relies on findPath in MarvelPaths2. 
	 * We pass in p1,p2 and our internal graph dg to findPath in MarvelPaths2
	 * 
	 * @param p1, a string representing either an id or a building name
	 * @param p2, a string representing either an id or a building name
	 * @requires p1 and p2 are valid ids or building names (actually in the graph)
	 * @returns a Path object, found by using Dijkstra's algorithm in MarvelPaths2.
	 */
	public Path findPath(String p1, String p2) {
		//if p1 is a name
		String id1 = "";
		String id2 = "";
		if(!isDigit(p1))
			//convert to its corresponding ID
			id1 = name_to_id.get(p1);
		else
			id1 = p1;
		
		//if p2 is a name
		if(!isDigit(p2))
			//convert to its corresponding ID
			id2 = name_to_id.get(p2);
		else
			id2 = p2;

		return MarvelPaths2.findPath(id1, id2, dg);
	}
	
	/* angle function. Takes in two strings, either being ids or building names,
	 * and calculates the angle between 
	 * 
	 * @param p1, a string representing either an id or name of a building 
	 * @param p2, a string representing either an id or name of a building
	 * @requires p1 and p2 are valid ids or building names (actually in the graph)
	 * @returns a double angle representing the bearing between the two locations 
	 * represented by p1 and p2
	 */
	public double angle(String p1, String p2) {
		ArrayList<Double> coords1 = new ArrayList<Double>();
		ArrayList<Double> coords2 = new ArrayList<Double>();
		double x1,y1,x2,y2;
		//if p1 is a name
		if(name_to_id.containsKey(p1))
			//convert to its corresponding ID
			p1 = name_to_id.get(p1);
				
		//if p2 is a name
		if(name_to_id.containsKey(p2))
			//convert to its corresponding ID
			p2 = name_to_id.get(p2);
		
		//setup coords1 and coords2
		coords1 = id_to_coords.get(p1);
		coords2 = id_to_coords.get(p2);
		
		//set up (x1,y1) and (x2,y2)
		x1 = coords1.get(0);
		y1 = coords1.get(1);
		x2 = coords2.get(0);
		y2 = coords2.get(1);
		
		double angle = Math.atan2((y2-y1),(x2-x1))*(180/Math.PI) + 90;
		
		//so we always have a positive angle bearing
		if(angle < 0)
			return angle + 360;
		else
			return angle;
	}
	
	/*
	 * @param id, an id of some building/place or intersection
	 * @returns a name corresponding to the input id. null is returned
	 * if there is no corresponding name
	 */
	public String name_from_id(String id) {
		return id_to_name.get(id);
	}
	
	/*
	 * @param name, a name of some building
	 * @returns an id corresponding to the input name. null is returned
	 * if there is no corresponding id
	 */
	public String id_from_name(String name) {
		return name_to_id.get(name);
	}
	
	
}
