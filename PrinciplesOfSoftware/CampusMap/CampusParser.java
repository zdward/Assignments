package CampusMap;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class CampusParser {
	/** @param: filename The path to the "CSV" file that contains the buildings and intersections
	 * in the graph.                                                                                                
    @param: places The Set that stores all locations, building or intersection, in our graph to be built
    @param: ids_to_places a hashmap allowing us to convert an id to a place. This is useful later on
    @effects: populates places and ids_to_places so we can use them to build our graph
    @throws: IOException if file cannot be read of file not a CSV file    
    @throws NumberFormatException if the function fails to convert a string to a number (its not a number). 
    In this case, there is something wrong with the input file.                                                                                 
    */
	public static void readPlaces(String filename, Set<Place> places, HashMap<String,Place> ids_to_places) throws NumberFormatException, IOException {
		
		BufferedReader reader = new BufferedReader(new FileReader(filename));
        String line = null;
        
        //loop through each line
        while ((line = reader.readLine()) != null) {
        	
        	//split the line into 4 arguments
        	String arguments[] = line.split(",");
        	
        	//grab (name,id,x,y)
        	String name = arguments[0];
        	String id = arguments[1];
        	int x_coord = Integer.parseInt(arguments[2]);
        	int y_coord = Integer.parseInt(arguments[3]);
        	
        	//set_up new node to add
        	Place to_add = new Place(name,id,x_coord,y_coord);
        	ids_to_places.put(id, new Place(name,id,x_coord,y_coord));
        	
        	places.add(to_add);
       }
        reader.close();
	}
	
	/** @param: filename The path to the "CSV" file that contains buildings in the format (b1,b2)
	 * telling us a path leads from b1 to b2 and b2 to b1                                                                           
    @param: connections The Set of ArrayLists (which each contain only two elements, b1 and b2) 
    which is going to be populated.
    @effects: populated connections with the appropriate edges to be added to our graph
    @throws: IOException if file cannot be read of file not a CSV file    
    @throws NumberFormatException if the function fails to convert a string to a number (its not a number). 
    In this case, there is something wrong with the input file.                                                                                 
    */
	public static void readConnections(String filename, Set<ArrayList<String>> connections) throws NumberFormatException, IOException{
		BufferedReader reader = new BufferedReader(new FileReader(filename));
        String line = null;
        
        //loop through each line
        while ((line = reader.readLine()) != null) {
        	
        	//split the line into 4 arguments
        	String arguments[] = line.split(",");
        	ArrayList<String> id_pair = new ArrayList<String>();
        	
        	//grab (id1,id2) pair
        	id_pair.add(arguments[0]);
        	id_pair.add(arguments[1]);
        	
        	//add (id1,id2) to set of connections
        	connections.add(id_pair);
       }
        reader.close();
	}
}
