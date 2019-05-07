package CampusMap;

public class Place {
private String name;
private String id;
private double x;
private double y;
//Abstraction Function: Name represents the a Place's building name, if it has one (name != ""). 
//Every place has an id, a string of digits, and x and y coordinates, representing the Place<name,id,x,y>'s 
// location.
//--------------------------------------------------------------------------------
//Representation Invariant: (name,id != null) && (x, y >= 0) && (for char c in id, 
// c is a digit)
	

	/**
	 * Place constructor
	 * @param name, representing the location name. It is "" if our place represents an intersection
	 * @param id, A string holding a series of digits, representing the id of our location
	 * @param x, representing the x coordinate of our location in the campus map
	 * @param y, representing the y coordinate of our location in the campus map
	 * @effects Constructs a new Place object, initializing this.name,this.id,this.x
	 * and this.y
	 */
	
	public Place(String name, String id, double x, double y) {
		this.name = name;
		this.id = id;
		this.x = x;
		this.y = y;
		checkRep();
	}
	
	
	/**distance function. Returns the euclidean distance from one location to another.
	 * 
	 * @param other, a place to calculate the distance to from this place instance
	 * @returns a double representing the distance between this place instance and other
	 */
	public double distance(Place other) {
		double squared_differences = Math.pow(this.x-other.x(),2) + Math.pow(this.y-other.y(),2);
		return Math.sqrt(squared_differences);
	}
	
	/**name function. Returns the name of our current place instance
	 * 
	 * @return this.name
	 */
	public String name() {
		return name;
	}
	
	/**id function. Returns the id of our current place instance
	 * 
	 * @return this.id
	 */
	public String id() {
		return id;
	}
	
	/**x function. Returns the x coordinate of our current place instance
	 * 
	 * @return this.x
	 */
	public double x() {
		return x;
	}
	
	/**y function. Returns the y coordinate of our current place instance
	 * 
	 * @return this.y
	 */
	public double y() {
		return y;
	}
	
	/**
     * Checks that the representation invariant holds (if any). 
     * 
     * @throws RuntimeException if the representation invariant is violated
     */
	private void checkRep() throws RuntimeException{
		if(name == null || id == null) {
			throw new RuntimeException("Can't have name == null or id == null");
		}
		if(x < 0 || y < 0)
			throw new RuntimeException("must have x > 0 and y > 0");
		 char[] charArray = id.toCharArray();
		    for(char c:charArray)
		    {
		        if (!Character.isDigit(c))
		            throw new RuntimeException("id must be a series of digits");
		    }
	}
}
