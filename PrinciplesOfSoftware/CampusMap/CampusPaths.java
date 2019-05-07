package CampusMap;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

import GraphADT.Digraph;
import GraphADT.Edge;
import GraphADT.Node;
import Marvel.MarvelParser;
import Marvel2.Path;

public class CampusPaths {
	
	
	/* Converts any id to a string. If input is not an id
	 * return same thing
	 * 
	 * @param inter_or_building, either an id or a name
	 * @requires inter_or_building is valid, that is, it can be translated
	 * to an id in our Digraph
	 * @returns a string name corresponding to the input if the input
	 * is an id. If the input was some a name, the same thing is returned.
	 */
	public String translate(String inter_or_building) {
		Model m = new Model();
		
		//if you didn't put in a digit to begin with, return that
		if(!m.isDigit(inter_or_building))
			return inter_or_building;
		
		//if your input is a digit
		else {
			
			//if it has a name
			if(m.name_from_id(inter_or_building) != "")
				return m.name_from_id(inter_or_building);
			
			//if it doesn't
			else {
				return "Intersection " + inter_or_building;
			}
		}
	}
	
	/*
	 * @param nameOrId, either a name or id
	 * @returns a boolean whether or not the input represents an
	 * intersection in our graph
	 */
	public boolean isIntersection(String nameOrId) {
		boolean isIntersection = false;
		
		Model m = new Model();
		m.createNewGraph("data/RPI_map_data_Nodes.csv","data/RPI_map_data_Edges.csv");
		
		//if we are dealing with a number
		if(m.isDigit(nameOrId)) {
			Digraph<String,Double> dg = m.retrieve_graph();
			if(dg.findNode(nameOrId) != null && m.name_from_id(nameOrId).equals("")) {
				isIntersection = true;
			}
		}
		//otherwise...we are dealing with some name, we don't need to check this
		return isIntersection;
	}
	
	/*
	 * @param nameOrId, a name or id (series of digits in a string)
	 * @returns a boolean whether or not our input represents a valid location
	 * in our digraph, whether this location is an intersection or a building
	 */
	public boolean isValidPlace(String nameOrId) {
		boolean isValidPlace = false;
		
		Model m = new Model();
		m.createNewGraph("data/RPI_map_data_Nodes.csv","data/RPI_map_data_Edges.csv");
		Digraph<String,Double> dg = m.retrieve_graph();
		
		//if we are dealing with a number
		if(m.isDigit(nameOrId)) {
			if(dg.findNode(nameOrId) != null)
				isValidPlace = true;
		}
		
		//if we are dealing with a building name
		else {
			String id = m.id_from_name(nameOrId);
			
			//if there is a corresponding ID
			if(id != null) {
				isValidPlace = true;
			}
		}
		return isValidPlace;
	}
	
	

	/* listOptions functions. Lists all options available to user.
	 * 
	 * @effects prints a list of options from which the user can choose
	 */
	public void listOptions() {
		System.out.println("-----------OPTIONS-----------");
		System.out.println("b: lists all buildings in the form (name,id), alphabetized by name");
		System.out.println("r: prompts user for id or name of TWO buildings and prints directions for the shortest route");
		System.out.println("q: quits the program");
		System.out.println("m: prints a menu of all commands (this menu)");
		System.out.println();
	}
	
	/*
	 *  @effects prints a list of buildings ordered lexicographically
	 *  by name. Buildings are printed in the form (name,id), without the
	 *  parenthesis.
	 */
	public void listBuildings() {
		//what we are returning
		String ret = "";
		
		Model m = new Model();
		
		//build the graph
		m.createNewGraph("data/RPI_map_data_Nodes.csv","data/RPI_map_data_Edges.csv");
		
		Digraph<String,Double> retrieved = m.retrieve_graph();
		
		//create a treeset to sort the buildings
		TreeSet<String> sorted = new TreeSet<String>();
		
		for(Node<String,Double> place: retrieved.getNodes()) {
			
			//getting the id 
			String building_id = place.getValue();
			String building_name;
			
			//convert to a name, either "" or the name of a building
			building_name = m.name_from_id(building_id);
			
			if(building_name.equals(""))
				continue;
			
			else
				sorted.add(building_name);
		}
		
		for(String name: sorted) {
			System.out.println(name + "," + m.id_from_name(name));
		}
		
	
	}
	
	/*This is our angle function. We input an angle, and assuming we start out facing north, this
	 * function returns the corresponding direction we are heading in.
	 * 
	 * @param theta, an angle to translate into a direction (assuming we start facing north)
	 * @requires theta >= 0
	 * @returns a direction corresponding to our input angle theta.
	 */
	public String getDirection(Double theta) {
		String direction = "";
		
		//[-22.5,22.5) should be NORTH 
		if((337.5 <= theta && theta <= 360.0) || (0 <= theta && theta < 22.5))
			direction = "North";
		
		//[22.5,67.5) should be NORTHEAST
		if(22.5 <= theta && theta < 67.5)
			direction = "NorthEast";
		
		//[67.5,112.5) should be EAST
		if(67.5 <= theta && theta < 112.5)
			direction = "East";
		
		//[112.5,157.5) should be SOUTHEAST
		if(112.5 <= theta && theta < 157.5)
			direction = "SouthEast";
		
		//[157.5,202.5) should be SOUTH
		if(157.5 <= theta && theta < 202.5)
			direction = "South";
		
		//[202.5,247.5) should be SOUTHWEST
		if(202.5 <= theta && theta < 247.5)
			direction = "SouthWest";
		
		//[247.5,292.5) should be WEST
		if(247.5 <= theta && theta < 292.5)
			direction = "West";
		
		//[292.5,337.5) should be NORTHWEST
		if(292.5 <= theta && theta < 337.5)
			direction = "NorthWest";
		
		return direction;
	}
	
	
	/* 
	 * @param start, a building name or id to start from
	 * @param end, a building name or id to travel to
	 * @returns a string containing the shortest path from start to end. If one
	 * of the input buildings are not valid, then we return "Unknown building: name". If both are 
	 * unknown and not the same, we print this message twice. We return a similar message for inputs
	 * that represent intersections. In this case, we return "Unknown building: [id]", printed once or twice,
	 * depending on whether or not the input consists of two different intersections or not. If there exists no
	 * path from start to end, we say so, returning, "There is no path from " + start + " to " + end + ".". Lastly,
	 * when a path does exist, the string we return also contains the cost of said path.
	 */
	public String findPath(String start, String end) {
		double cost = 0.0;
		boolean start_is_place = false;
		boolean end_is_place = false;
		
		String startID = "";
		String endID = "";
		String ret = "";
		
		Model m = new Model();
		m.createNewGraph("data/RPI_map_data_Nodes.csv", "data/RPI_map_data_Edges.csv");
		Digraph<String,Double> internal_graph = m.retrieve_graph();
		
		
		//One is intersection, one isnt
		if(isIntersection(start) && !isIntersection(end)) {
			
			//is the remaining place valid?
			if(isValidPlace(end)) {
				ret += "Unknown building: [" + start+"]";
				
			}
			
			//the remaining place is not valid
			else {
				ret += "Unknown building: [" + start + "]\n";
				if(!m.isDigit(end))
					ret += "Unknown building: " + end;
				else
					ret += "Unknown building: [" + end + "]";
			}
			return ret;
		}
		
		//One is intersection, one isnt
		else if(!isIntersection(start) && isIntersection(end)) {
			
			if(isValidPlace(start)) {
				ret += "Unknown building: [" + end+"]";
			}
			
			else {
				if(!m.isDigit(start))
					ret += "Unknown building: " + start + "\n";
				else
					ret += "Unknown building: [" + start + "]\n";
				ret += "Unknown building: [" + end+"]";
			}
			return ret;
		}
		
		//Both are not intersections
		else if(!isIntersection(start) && !isIntersection(end)) {
		
			//end is invalid
			if(isValidPlace(start) && !isValidPlace(end)) {
				if(m.isDigit(end)) 
					ret += "Unknown building: [" + end + "]";
				else
					ret += "Unknown building: " + end;
				return ret;
			}
			//start is invalid
			else if(!isValidPlace(start) && isValidPlace(end)) {
				if(m.isDigit(start)) 
					ret += "Unknown building: [" + start + "]";
				else
					ret += "Unknown building: " + start;
				return ret;
			}
			//both are invalid
			else if(!isValidPlace(start) && !isValidPlace(end)) {
				
				if(m.isDigit(start) && !m.isDigit(end)) {
					ret += "Unknown building: [" + start + "]\n";
					ret += "Unknown building: " + end ;
				}
				
				if(!m.isDigit(start) && m.isDigit(end)) {
					ret += "Unknown building: " + start + "\n";
					ret += "Unknown building: [" + end + "]";
				}
				
				if(m.isDigit(start) && m.isDigit(end)) {
					if(!start.equals(end)) {
						ret += "Unknown building: [" + start + "]\n";
						ret += "Unknown building: [" + end + "]";
					}
					else {
						ret += "Unknown building: [" + end + "]";
					}
				}
				
				if(!m.isDigit(start) && !m.isDigit(end)) {
					if(!start.equals(end)) {
						ret += "Unknown building: " + start + "\n";
						ret += "Unknown building: " + end;
					}
					else
						ret += "Unknown building: " + end;
				}
				
				return ret;
			}
			
		}
		
		//Both are intersections
		else if(isIntersection(start) && isIntersection(end)) {
			if(!start.equals(end)) {
				ret += "Unknown building: [" + start + "]\n";
				ret += "Unknown building: [" + end + "]";	
			}
			else {
				ret += "Unknown building: [" + end + "]";	
			}
			return ret;
		}
		
		
			
		//then our input is an id, at this point we know its a valid place, so convert
		if(m.isDigit(start)) {
			ret += "Path from " + m.name_from_id(start) + " to ";
		}
		
		//then you know for certain that your input is a building
		else if(!m.isDigit(start)) {
			ret += "Path from " + start + " to ";
		}
		
		//then our input is an id, at this point we know its a valid place, so convert
		if(m.isDigit(end)) {
			ret += m.name_from_id(end) + ":\n";
		}
		
		//if its just a place, then add it in the string
		else if(!m.isDigit(end)) {
			ret += end + ":\n";
		}
		//build the graph
		m.createNewGraph("data/RPI_map_data_Nodes.csv","data/RPI_map_data_Edges.csv");
		
		
		//otherwise...
		Path shortest_path = new Path();
		//if start is a number and has a building name, convert it
		if(m.isDigit(start)) {
			start = m.name_from_id(start);
		}
		if(m.isDigit(end)) {
			end = m.name_from_id(end);
		}
		//run Dijkstra's algorithm
		shortest_path = m.findPath(start, end);
		
		//grab the nodes and edges from the path
		ArrayList<Node<String,Double>> shortest_nodes = shortest_path.getNodes();
		ArrayList<Edge<Double,String>> shortest_edges = shortest_path.getEdges();
		
		//for each node in shortest_nodes
		for(int i = 0; i < shortest_nodes.size(); i++) {
			if(i < shortest_nodes.size()-1) {
				Node<String,Double> current = shortest_nodes.get(i);
				Node<String,Double> ahead = shortest_nodes.get(i+1);
				
				//get the angle between the two nodes
				double bearing = m.angle(current.getValue(), ahead.getValue());
				
				//get the direction, a function of the angle
				String direction = getDirection(bearing);
				
				
				if(isIntersection(ahead.getValue())) {
					ret += "\tWalk " + direction + " to (Intersection " + ahead.getValue() + ")\n";
				}
				
				else {
					ret += "\tWalk " + direction + " to (" + m.name_from_id(ahead.getValue()) + ")\n";
				}
				//adjust cost
				cost += shortest_edges.get(i).getLabel();
				
			}
		}
		
		start = translate(start);
		end = translate(end);
		
		if(!start.equals(end)){
			if(cost < 0.00001) {
				ret = "";
				ret += ("There is no path from " + start + " to " + end + ".");
			}
			else {
				ret += "Total distance: " + String.format("%.3f", cost) + " pixel units.";
			}
		}
		
		else
			ret += "Total distance: " + String.format("%.3f", cost) + " pixel units.";
		
		
		
		return ret;
	}
	
	/*
	 * @param String[] args, representing any command line arguments.
	 * @effects simulates the user experience, reads inputs, and acts accordingly. 
	 */
	public static void main(String[] args) {
		CampusPaths p = new CampusPaths();
		Scanner input = new Scanner(System.in);
		while(true) {
			String user_input = input.nextLine();
			
			//if b is inputted, then we list buildings
			if(user_input.equals("b")) {
				
				p.listBuildings();
				
			}
			//we find the shortest path in this case
			else if(user_input.equals("r")) {
				System.out.print("First building id/name, followed by Enter: ");
				String name_or_id1 = input.nextLine();
				System.out.print("Second building id/name, followed by Enter: ");
				String name_or_id2 = input.nextLine();
				System.out.println(p.findPath(name_or_id1, name_or_id2));
				
			}
			//this is when we quit
			else if (user_input.equals("q")) {
				break;
			}
			//we list the menu options if m is inputted
			else if(user_input.equals("m")) {
				p.listOptions();
			}
			
			//if anything else is inputted, we tell the user that this option is unknown
			else {
				System.out.println("Unknown option");
				continue;
			}
		}
		//always close your scanners
		input.close();
	}
	
}
