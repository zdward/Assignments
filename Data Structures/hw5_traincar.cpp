// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include "traincar.h"
#include <algorithm>
// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

/*
THIS FUNCTION PUSHES BACK A TRAINCAR* ONTO ANOTHER TRAINCAR* (ON THE BACK)
BY CONNECTING THE NEXT AND PREV POINTERS. IF THE TRAINCAR* BEING ADDED TO IS NULL,
SET THE TRAINCAR* EQUAL TO THE ONE THAT IS BEING ADDED.
*/
void PushBack(TrainCar* &pointer, TrainCar* toPush){
	if(pointer==NULL){ 
		pointer = toPush; //make pointer point to the car being added and set next and prev to NULL
		toPush->next = NULL;
		toPush->prev = NULL;
	}
	else{
		TrainCar* temp; //temp pointer 
		for(temp = pointer; temp->next!=NULL; temp=temp->next){ //increments temp until its the last TrainCar*
			continue;
		}
		temp->next = toPush; //sets the end of the pointer's "next" pointer to point to the car being added
		toPush->next = NULL; 
		toPush->prev = temp; //finishing the connection by making toPush's prev connect to the end of pointer(a.k.a temp)
	}
}
void PushFront(TrainCar* &pointer, TrainCar* toPush){ //similar logic as pushback, but for the front
	if(pointer==NULL){ //If the pointer is empty, same logic as in pushback
		pointer = toPush;
		toPush->next = NULL;
		toPush->prev = NULL;
	}
	else{ //connect ToPush from the front
		toPush->next = pointer; //connect toPush's next pointer to the main TrainCar* (a.k.a pointer)
		pointer->prev = toPush; //connect pointer's (the main pointer) prev to toPush, fifnishing the connection
		pointer = pointer->prev; //Finally, reset pointer so it points to the first element again
	}
}
void DeleteAllCars(TrainCar* &pointer){ //recursively deletes all cars
	if (pointer == NULL){ //the base case
        return; //if there is nothing in the pointer, we are done
    }
    else { 
    	DeleteAllCars(pointer->next); //will bring us to the end of the list and then go backwards
        delete pointer; //will start deleting cars from end to beginning
    }

    /*
	THIS FUNCTION GETS THE TOTAL WEIGHT AND COUNT FOR EACH CAR IN A TRAINCAR* "car" PASSED IN. 
	THE IMPLEMENTATION INVOLVES LOOPING THROUGH THE TRAINCAR* CAR AND COUNTING THE OCCURANCES OF EACH CAR 
	WHILE INCREMENTING THE WEIGHT AS WE GO.
    */
}	
void TotalWeightAndCountCars(TrainCar* &car,int &totWeight,int &numEngines,int &numFreight,int &numPass,int &numDine,int &numSleep){ 
	TrainCar* temp = car; //set a temporary pointer to point to the beginning of the TrainCar*
	totWeight = 0;
	numEngines = 0;
	numFreight = 0;
	numPass = 0;
	numDine = 0;
	numSleep = 0;
	if(car->next!=NULL){ //if you have more than one car in the train
		while(temp!=NULL){ //while there is a next car
			totWeight+=temp->getWeight(); //add the weight of the car we are on
			if(temp->isEngine()){ //increment whichever category is appropriate
				numEngines+=1;
			}
			else if(temp->isFreightCar()){
				numFreight+=1;
			}
			else if(temp->isPassengerCar()){
				numPass+=1;
			}
			else if(temp->isDiningCar()){
				numDine+=1;
			}
			else if(temp->isSleepingCar()){
				numSleep+=1;
			}
			temp = temp->next; //increment temp
		} 

	} else if(car==NULL) { //empty train
		return;
	} else { //in the case of a train with only one car
		totWeight = car->getWeight();
		if(car->isEngine())
			numEngines+=1;
		else if(car->isFreightCar())
			numFreight+=1;
		else if(car->isPassengerCar())
			numPass+=1;
		else if(car->isDiningCar())
			numDine+=1;
		else if(car->isSleepingCar())
			numSleep+=1;
	}
}

float CalculateSpeed(TrainCar* &car){ //CALCULATES THE SPEED OF A TRAINCAR* ON A 2% INCLINE
	TrainCar* temp = car; //creation of a temporary pointer, pointing to the beginning of car
	int totWeight=0;
	int num_engines=0;
	while(temp->next!=NULL){ //while there is a next car
		totWeight+=temp->getWeight(); //incrementing weight
		if(temp->isEngine()) //keep track of all engines
			num_engines+=1;
		temp=temp->next;
	}
	totWeight+=temp->getWeight(); //increment weight one last time
	if(temp->isEngine()) //still keeping in mind the case that the last car could be an engine
		num_engines+=1;
	int horsepower = 3000*num_engines;
	return float((horsepower*550*1.8))/(0.02*5280*totWeight); //formula for speed, simplified to prevent an integer overflow
}
void RemoveCarShip(TrainCar* &toRemove, TrainCar* &extractor){ //Helper function, removes car closest to average weight in allFreight in ShipFreight function
	extractor = toRemove; //sets up extractor to equal the main TrainCar*
	TrainCar* temp; //set up a TrainCar* we will use to iterate
	bool found = false; 
	float closestDifference;
	float difference;
	int n = 0;
	int total =0;
	int preferredWeight; //the main variable we are looking for
	for(temp = toRemove; temp->next!=NULL; temp = temp->next){
		n+=1;
		total+=temp->getWeight();
	}
	float avgWeight = float(total)/n; //calculate average weight
	closestDifference = fabs(toRemove->getWeight()-avgWeight); //used to store closest difference
	preferredWeight = toRemove->getWeight();
	for(temp = toRemove; temp->next!=NULL; temp = temp->next){
		difference = fabs(temp->getWeight()-avgWeight);
		if(difference<closestDifference){
			closestDifference = difference; //finds the actual smallest deviation from average weight
			preferredWeight = temp->getWeight(); //determines preferredWeight based on smallest deviation
		}
	}

	temp = toRemove; //resets temp to be at the beginning of toRemove
	while(!found){ //finds and extracts car with preferredWeight
		if(temp->prev!=NULL){ 
			if(temp->getWeight()==preferredWeight){ 
				extractor = temp; //sets up extractor
				found = true;
				temp = temp->prev;
				if(temp->next->next!=NULL){
					temp->next=temp->next->next; //Step 1 in removing node from middle of list
					temp=temp->next;
					temp->prev=temp->prev->prev; //step 2 in removing node from middle of list
					temp=temp->prev;
					extractor->prev = NULL; //extractor is now disconnected after these two statements
					extractor->next = NULL; //now disconnected 
				}
				else{ //if we are at the end
					temp->next = NULL; 
					extractor->prev = NULL; //cutting off extractor
				}
			}
			else{
				if(temp->next!=NULL)
					temp = temp->next; //incrementing along toRemove
				else
					break;
			}
		}
		else{ //for when we are at the beginning of toRemove
			if(temp->getWeight()==preferredWeight){ 
				extractor = temp; //similar logic to above when we found our preferred car
				found = true;
				if(temp->next!=NULL){ //we are only concerned with disconnecting the leftmost node in this case however
					toRemove = toRemove->next; //moving next up one
					temp = toRemove;
					temp->prev = NULL;  //cutting off connection
				}
				else
					toRemove = NULL;
				extractor->next = NULL; //severing all connection with extractor
			}
			else{
				if(temp->next!=NULL)
					temp = temp->next;
				else
					break;
			}	
		}	
	}
}
void RemoveEngineShip(TrainCar* &toRemove, TrainCar* &extractor){ //helper for shipFreight, removes engines
	extractor = toRemove; //sets up the extraction variable to the beginning of toRemove
	if(toRemove->next!=NULL){  
		toRemove = toRemove->next; //move toRemove forward
		toRemove->prev = NULL; //get rid of prev connection
		extractor->next = NULL; //get rid of next connection
	}
	else{ //if there is no next node
		extractor->prev = NULL; //cut off extractors prev
		extractor->next = NULL; //cut off extractors next
		toRemove = NULL; //toRemove is now empty
	}
}
std::vector<TrainCar*> ShipFreight(TrainCar* &allEngines, TrainCar* &allFreight, int minspeed, int maxcars){ //MAJOR ALGORITHM #1: SHIPFREIGHT
	std::vector<TrainCar*> toBeReturned; //initializing the vector we will return
	TrainCar* extract; //initializing the extraction variable we will re-use 
	while(allEngines!=NULL){ //while you still have engines..
		if(allFreight==NULL) //When you've used up your freight, end the loop. We're done.
			break; 
		int totWeight = 0; 
		int numCars = 0;
		int enginesAdded = 0;
		float speed;
		TrainCar* toAdd = NULL; //variable which we will constantly reset, fill, and push back to toBeReturned
		RemoveEngineShip(allEngines,extract); //add your first engine
		PushBack(toAdd,extract);
		totWeight+=150;
		numCars+=1; //increment enginesAdded, numcars, and totWeight accordingly..
		enginesAdded+=1;
		while(allFreight!=NULL && maxcars-numCars!=0){ //While you still have freight and spaces to fill in toAdd

			RemoveCarShip(allFreight,extract); //remove a freight car which is closest to allFreight average weight
			speed = float((enginesAdded*3000*550*1.8))/(0.02*5280*(totWeight+extract->getWeight())); //update speed
			if(speed>minspeed){ //only if adding a car will not take you below min speed
				PushBack(toAdd,extract); //add the car
				numCars+=1; //increment numCars and totWeight accordingly
				totWeight+=extract->getWeight();
				speed = float((enginesAdded*3000*550*1.8))/(0.02*5280*(totWeight)); //reset speed
			}	
			else{ //if adding a car will take you below min speed
				if(allEngines==NULL){
					PushBack(allFreight,extract); //put the freight car back, you're not using it.
					break;
				}
				else{ 
					PushBack(allFreight,extract); //put the freight car back, same reason.
					if(maxcars-numCars>(4)){ //if you have 4 (arbitrary number) spaces or less spaces, don't bother adding another engine
						RemoveEngineShip(allEngines,extract);
						PushFront(toAdd,extract);
						enginesAdded+=1;
						numCars+=1;
						totWeight+=150;
					}
					else
						break;
				}
			}
		}
		toBeReturned.push_back(toAdd); //push back toAdd before you reset it
	}
	return toBeReturned; //return the vector, finally.
}
float AverageDistanceToDiningCar(TrainCar* train){ //Calculates average distance from a passenger car to a dining car
	TrainCar* temp = train; //sets a temporary variable to loop through train, looking for passenger cars
	TrainCar* temp2; //will be used to check if there are dining cars on either side of a passenger car
	int distCovered = 0; //will be incremented when temp2 moves left or right
	int numPass = 0; //num of passenger cars in the train
	int total = 0; //total distance
	float avg; //average Distance variable
	bool isDiningLeftSide = false; //is set to true when a dining car is found on the left side of a passenger car
	bool isDiningRightSide = false; //is set to true but for right side
	int candidateDistance1; //candidate distances will be compared, which ever one is smaller will be added to total
	int candidateDistance2;
	int PassengerCount = 0; //amount of passenger cars in the train
	int DiningCount = 0; //amount of dining cars in the train
	for(temp2 = train; temp2->next!=NULL; temp2=temp2->next){
		if(temp2->isPassengerCar())
			PassengerCount+=1;
		else if(temp2->isDiningCar())
			DiningCount+=1;
	}
	if(temp2->isPassengerCar()) //accounting for the last car
		PassengerCount+=1;
	else if(temp2->isDiningCar()) //accounting for the last car
		DiningCount+=1; 
	if(PassengerCount==0)
		return -1; //no passengers, so infinite distance 
	if(DiningCount==0)
		return -1; //no dining cars, so infinite distance
	while(temp->next!=NULL){
		if(temp->isPassengerCar()){ 
			temp2 = temp; //start from the passenger car
			numPass+=1; //increment # of passenger cars because we've found one
			isDiningLeftSide = false; //reset the bool variables
			isDiningRightSide = false;
			while(temp2->prev!=NULL){ //if you can keep going backwards
				if(temp2->isDiningCar()){
					isDiningLeftSide = true; //set this variable to true once you've hit a dining car
					candidateDistance1 = distCovered; //setting up candidateDistance1
					break; //we are done looping at this point
				}
				else if(temp2->isEngine() || temp2->isFreightCar()){ //when you've hit an engine or freightcar, just stop
					break;
				}
				else{
					temp2 = temp2->prev; //in all other cases just keep going backwards
					distCovered+=1; //dont forget to increment your distance whenever you go backwards
				}
			}
			if(temp2->isDiningCar()){ //makes sure if the first car is a dining car, that it is accounted for
				candidateDistance1 = distCovered;
				isDiningLeftSide = true;
			}
			temp2 = temp; //now we reset temp2 and repeat the process but going forwards instead of backwards
			distCovered = 0; //of course, reset distCovered
			while(temp2->next!=NULL){ 
				if(temp2->isDiningCar()){ //if youve found a dining car in FRONT of the passenger car represented by temp
					isDiningRightSide = true;
					candidateDistance2 = distCovered; //set up your candidateDistance2 and stop the loop
					break;
				}
				else if(temp2->isEngine() || temp2->isFreightCar()){ //if youve hit an engine of freightcar, stop
					break;
				}
				else{
					temp2 = temp2->next; //progress forward and increment distance
					distCovered+=1;
				}
			}
			if(temp2->isDiningCar()){ //makes sure if the last car is a dining car, that it is accounted for
				candidateDistance2 = distCovered;
				isDiningRightSide = true;
			}
			if(isDiningLeftSide && isDiningRightSide){ //If you have a dining car on both sides of the passenger car
				if(candidateDistance1 < candidateDistance2){ //compare which distance is smaller
					total+=candidateDistance1; //add the smaller distance to the total
				}
				else if(candidateDistance1 > candidateDistance2){ 
					total+=candidateDistance2; //add the smaller distance to total
				}
				else if(candidateDistance1 == candidateDistance2){ //same value, add either one to total
					total+=candidateDistance1; //arbitrarily chose candidateDistance1, but candidateDistance2 would also work
				}
			}
			else if(isDiningLeftSide && (!isDiningRightSide)){ //if you only have a dining car on the left side
				total+=candidateDistance1; //add the only candidateDistance that exists, candidateDistance1
			}
			else if((!isDiningLeftSide) && isDiningRightSide){ //same logic as above
				total+=candidateDistance2;
			}
			else if(!isDiningLeftSide && !isDiningRightSide){ //if you couldn't find any dining cars
				return -1; //"infinite" distance case
			}
			temp = temp->next; //progress temp forward, finally
			distCovered=0; //reset distance covered 
		}
		else{ //If you havent hit a passenger car
			temp = temp->next; //simply go forward, still looking for a passenger car
		}
	}
	isDiningLeftSide = false; 
	isDiningRightSide = false;
	if(temp->isPassengerCar()){ //accounting for a passenger car at the end
		temp2 = temp;
		numPass+=1;
		while(temp2->prev!=NULL){ //Since you are at the end, you only need to check for dining cars on the left side/behind
				if(temp2->isDiningCar()){ 
					isDiningLeftSide = true; 
					total+=distCovered;
					break;
				}
				else if(temp2->isEngine()){
					return -1; //If you are on the last passenger car at the END, and you hit an engine first, you are isolated.
					//this means you have an "infinite" distance case here
				}
				else{
					temp2 = temp2->prev; 
					distCovered+=1;
				}
		}
	}
avg = float(total)/numPass; //calculate average as a float
	return avg; //return it
}

int ClosestEngineToSleeperCar(TrainCar* train){ //Finds smallest distance from a sleeper car to an engine
	TrainCar* temp; //initializing our temp variables
	TrainCar* temp2;
	std::vector<int> distances;
	for(temp = train; temp!=NULL; temp=temp->next){ //we use temp to loop through train
		int distCovered = 0; //initializing and resetting distCovered
		if(temp->isSleepingCar()){ 
			for(temp2 = temp; temp2!=NULL; temp2=temp2->prev){ //use temp2 to go backwards from the pos. of temp
				if(temp2->isEngine()){ //when youve hit an engine
					distances.push_back(distCovered); //push back distance to the engine 
				}
				distCovered+=1; //always increment distCovered as you go along
			}
			distCovered = 0; //resetting distCovered
			for(temp2 = temp; temp2!=NULL; temp2=temp2->next){ //use temp2 to go forwards from the pos. of temp
				if(temp2->isEngine()){ //same logic as above
					distances.push_back(distCovered);
				}
				distCovered+=1;
			}
		}
	}
	int min = distances[0]; //Use a minimum-finding algorithm to find the smallest value in the distances vector
	for(unsigned int i = 0; i < distances.size(); i++){
		if(distances[i]<min)
			min = distances[i];
	}
	return min; //return the smallest value passed in distances
} 
/*
THE FOLLOWING FOUR HELPER FUNCTIONS, RemoveEngineT2, RemoveEngineT3,
RemoveCarT2, AND RemoveCarT3 ARE USED IN MY SEPARATE FUNCTION. 
FOR ALL HELPER FUNCTIONS RELATING TO TRAIN2, THEY LOOP THROUGH
TRAIN2 BACKWARDS AND FIND THE CLOSEST ENGINE OR CAR FROM THE END
AND EXTRACT IT. FOR ALL HELPER FUNCTIONS RELATING TO TRAIN3, THEY LOOP
THROUGH TRAIN3 REGULARLY AND FIND THE CLOSEST ENGINE OR CAR FROM
THE BEGINNING AND EXTRACT IT.
*/
void RemoveEngineT2(TrainCar* &toRemove, TrainCar* &extractor){ 
bool found = false; //set to true once we've found an engine
TrainCar* temp; //This will be what we use to iterate through and go BACKWARDS after
for(temp = toRemove; temp->next!=NULL; temp=temp->next){
	continue;
} 
while(!found){ //WHILE YOU HAVENT FOUND AN ENGINE
	if(temp->next!=NULL){
		if(temp->isEngine()){
			extractor = temp;
			found = true; //YOUVE FOUND AN ENGINE!
			temp = temp->next;
			if(temp->prev->prev!=NULL){ //this statement takes care of removing extractor from the middle
				temp->prev = temp->prev->prev;
				temp = temp -> prev;
				temp->next = temp->next->next;
				temp = temp->next;
				extractor->next = NULL;
				extractor->prev = NULL;
			}
			else{ //this statement takes care of removing extractor if its at the beginning
				toRemove = toRemove->next;
				toRemove->prev = NULL;
				temp->prev = NULL;
				extractor->next = NULL;
			}
		}
		else{ //When you havent hit an engine, go backwards if you can
			if(temp->prev!=NULL)
				temp = temp->prev;
			else
				break;
		}
	}
	else{ //When you're at the end
		if(temp->isEngine()){
			extractor = temp;
			found = true; //youve found an engine
			if(temp->prev!=NULL){ //cuts off extractor from the end
				temp = temp->prev;
				temp->next = NULL;
			}
			extractor->prev = NULL; //cutting off extractors connection
		}
		else{ //if you havent found an engine
			if(temp->prev!=NULL) //continue to go backwards if you can
				temp = temp->prev;
			else
				break;
			
		}
	}
}
}
/*
RemoveEngineT3 has the EXACT same logic as RemoveEngineT2, but FLIPPED.
Instead, we iterate forwards and cut connections in the opposite way that we did
in RemoveEngineT2.
*/
void RemoveEngineT3(TrainCar* &toRemove, TrainCar* &extractor){ //used to help cut links in Separate
	bool found = false; //set to true once we've found an engine
	extractor = toRemove; //This is what we will pull out
	TrainCar* temp = toRemove; //This will be what we use to iterate through
	while(!found){
		if(temp->prev!=NULL){
			if(temp->isEngine()){
				extractor = temp;
				found = true;
				temp = temp->prev;
				if(temp->next->next!=NULL){ //removes extractor from the middle
					temp->next=temp->next->next;
					temp=temp->next;
					temp->prev=temp->prev->prev;
					temp=temp->prev;
					extractor->prev = NULL;
					extractor->next = NULL;
				}
				else{ //removes extractor from the end
					temp->next = NULL;
					extractor->prev = NULL;
				}
			}
			else{ //if you havent found an engine, go forward if you can
				if(temp->next!=NULL)
					temp = temp->next;
				else
					break;
			}
		}
		else{ //if you are at the beginning (temp->prev==NULL)
			if(temp->isEngine()){
				extractor = temp;
				found = true;
				if(temp->next!=NULL){ //cuts off extractor from the beginning
					toRemove = toRemove->next;
					temp = toRemove;
					temp->prev = NULL;
				}
				else
					toRemove = NULL;
				extractor->next = NULL; //finalizes the cut
			}
			else{ //if you havent found an engine
				if(temp->next!=NULL) //go forward if you can
					temp = temp->next;
				else
					break;
			}
		}
	}
}
/*
THIS FUNCTION HAS THE SAME LOGIC AS RemoveEngineT2, BUT INSTEAD,
WE ARE LOOKING FOR A CAR THAT IS NOT AN ENGINE, HENCE THE MAIN
CHANGE IS IN LINE 552 and 579, WHERE WE USE THE ! OPERATOR
*/
void RemoveCarT2(TrainCar* &toRemove, TrainCar* &extractor){
	bool found = false;
	TrainCar* temp;
	for(temp = toRemove; temp->next!=NULL; temp = temp->next){
		continue;
	}
	while(!found){
		if(temp->next!=NULL){
			if(!(temp->isEngine())){
				extractor = temp;
				found = true;
				temp = temp->next;
				if(temp->prev->prev!=NULL){
					temp->prev = temp->prev->prev;
					temp = temp->prev;
					temp->next = temp->next->next;
					temp = temp->next;
					extractor->next = NULL;
					extractor->prev = NULL;
				}
				else{
					toRemove = toRemove->next;
					toRemove->prev = NULL;
					temp->prev = NULL;
					extractor->next = NULL;
				}
			}
			else{
				if(temp->prev!=NULL)
					temp = temp->prev;
				else
					break;
			}
		}
		else{
			if(!(temp->isEngine())){
				extractor = temp;
				found = true;
				if(temp->prev!=NULL){
					temp = temp->prev;
					temp->next = NULL;
				}
				extractor->prev = NULL;
			}
			else{
				if(temp->prev!=NULL)
					temp = temp->prev;
				else
					break;
			}
		}
	}
}
/*
THIS FUNCTION IS ALSO VERY SIMILAR TO RemoveEngineT3, AND THE MAIN CHANGE
IS THE INCLUSION OF THE ! OPERATOR WHEN CHECKING FOR AN ENGINE. JUST ABOUT
EVERYTHING ELSE IS THE SAME
*/
void RemoveCarT3(TrainCar* &toRemove, TrainCar* &extractor){ //used to help cut links in Separate
	bool found = false;
	extractor = toRemove; //This is what we will pull out
	TrainCar* temp = toRemove; //This will be what we use to iterate through
	while(!found){
		if(temp->prev!=NULL){
			if(!(temp->isEngine())){
				extractor = temp;
				found = true;
				temp = temp->prev;
				if(temp->next->next!=NULL){
					temp->next=temp->next->next;
					temp=temp->next;
					temp->prev=temp->prev->prev;
					temp=temp->prev;
					extractor->prev = NULL;
					extractor->next = NULL;
				}
				else{
					temp->next = NULL;
					extractor->prev = NULL;
				}
			}
			else{
				if(temp->next!=NULL)
					temp = temp->next;
				else
					break;
			}
		}
		else{
			if(!(temp->isEngine())){
				extractor = temp;
				found = true;
				if(temp->next!=NULL){
					toRemove = toRemove->next;
					temp = toRemove;
					temp->prev = NULL;
				}
				else
					toRemove = NULL;
				extractor->next = NULL;
			}
			else{
				if(temp->next!=NULL)
					temp = temp->next;
				else
					break;
			}
		}
	}
}

/* The final function in this homework, Separate. My approach was rather complicated, 
but here is the breakdown: I started by splitting train1 in half. If theres an even
number of cars, the split is even, if the number of cars are odd, then there is one
more car in train1. After the split, I even out the engines in both trains as much
as i can by removing engines from the train that has more and either pushingFront or 
pushingBack on the other train, whichever uses less "shifts", minimizing cost. Finally, 
I move around cars while minimizing shifts until the speeds of train2 and train3 
are as close to each other as possible. */

void Separate(TrainCar* &train1, TrainCar* &train2, TrainCar* &train3){
	train2 = NULL;
	train3 = NULL;
	int totWeight,numEngines,numFreight,numPass,numDine,numSleep; //initialized so we can use TotalWeightAndCountCars for convenience
	TrainCar* extract; //used to extract from train1 into train2 and train3
	int carsTaken = 1;
	TotalWeightAndCountCars(train1,totWeight,numEngines,numFreight,numPass,numDine,numSleep); 
	int totalCars = numEngines+numFreight+numPass+numDine+numSleep;
	//The first step is to get train1 split up into two "even" trains, train2 and train3
	if(totalCars%2==0){ //IF YOU HAVE AN EVEN NUMBER OF TOTAL CARS
		while(carsTaken <= totalCars/2){ //PushBack cars onto train2 until the halfway point
			extract = train1; 
			train1=train1->next; //move train1 forward
			train1->prev=NULL;  //cut connection with prev
			extract->next = NULL; //cut connection with next
			PushBack(train2,extract);
			carsTaken+=1;
		}
		while(totalCars+1-carsTaken!=0){ //PushBack the rest of the trains onto train3
			extract = train1;
			if(train1->next!=NULL){ //move train1 forward if you can
				train1=train1->next; 
				train1->prev=NULL; //cut connection
			}
			else //if you cant move train1 forward
				train1=NULL; //then it is now NULL
			extract->next=NULL;
			extract->prev=NULL;
			PushBack(train3,extract);  
			carsTaken+=1;
		}
	}
	else{ //IF YOU HAVE AN ODD NUMBER OF TOTAL CARS
		while(carsTaken <= (totalCars/2)+1){ //Make it so train2 has one more car than train3
			extract = train1; 
			train1=train1->next;
			train1->prev=NULL;
			extract->next = NULL;
			PushBack(train2,extract);
			carsTaken+=1;
		}
		while(totalCars+1-carsTaken!=0){ //Other than the uneven nature, same logic as above
			extract = train1;
			if(train1->next!=NULL){
				train1=train1->next;
				train1->prev=NULL;
			}
			else
				train1=NULL;
			extract->next=NULL;
			extract->prev=NULL;
			PushBack(train3,extract);
			carsTaken+=1;
		}
	} /*After this brace, we are now done with splitting up the trains, whether they are even or odd.
		Now, we jut need to be concerned with whether we have an even or an odd amount of engines. If
		the number is even, we need to make sure both trains have equal engines in them from the split.
		If one of them has more, then one or more of the engines has to connect to the other train until equality is reached.
		If the number of engines is odd, we need to make sure one train has only one more engine than the other. */

	if(numEngines%2==0){ //EVEN ENGINES CASE
		TrainCar* extraction; //extraction variable to be used in the helper functions
		int weight1,weight2,train2Engines,train3Engines,nFreight,nPass,nDine,nSleep; //so we can use TotalWeightAndCountCars
		TotalWeightAndCountCars(train2,weight1,train2Engines,nFreight,nPass,nDine,nSleep); //only thing that matters really is train2Engines count and weight1
		TotalWeightAndCountCars(train3,weight2,train3Engines,nFreight,nPass,nDine,nSleep); //only thing that matters really is train3Engines count and weight2
		if(train2Engines==train3Engines) //If the engines are equal across trains
			return; //The trains are perfectly split and should have matching speeds.
		else if(train2Engines!=train3Engines){ 
			if(train2Engines>train3Engines){ //if train2 has more engines
				while(train2Engines!=train3Engines){ //take engines away and add to train3 while this is the case
					RemoveEngineT2(train2,extraction); 
					PushFront(train3,extraction);
					train2Engines-=1;
					weight1-=150; //account for weights and number of engines
					weight2+=150;
					train3Engines+=1;
				}
				float speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1)); //declaration of speed variables
				float speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
				if(speed_train2==speed_train3) //If speeds are equal, we are done
					return;
				else if(speed_train2>speed_train3){ //if Train2 is faster
					while(speed_train2>speed_train3){ //Take away cars and push them back while this is the case
						float new_speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1+50)); //new hypothetical speeds
						float new_speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2-50));
						if(new_speed_train2<new_speed_train3) //if the new speeds compare differently
							break; //you are done
				   	    RemoveCarT3(train3,extraction); //otherwise continue with the pushback
				   	    PushBack(train2,extraction);
				   	    weight1+=50; //account for weight change
				   	    weight2-=50; 
				   	    speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1)); //reset speeds
				   	    speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
					}
				}
				else if(speed_train2<speed_train3){ //if Train3 is faster
					while(speed_train2<speed_train3){  //same exact logic
						float new_speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1-50));
						float new_speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2+50));
						if(new_speed_train2>new_speed_train3)
							break;
						RemoveCarT2(train2,extraction);
						PushFront(train3,extraction);
						weight2+=50;
						weight1-=50;
						speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
				   	    speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
					}
				}
			}
			else if(train2Engines<train3Engines){ //The case where train3 has more engines
				while(train2Engines!=train3Engines){ //even out the engines
					RemoveEngineT3(train3,extraction);
					PushBack(train2,extraction);
					weight2-=150;
					weight1+=150;
					train2Engines+=1;
					train3Engines-=1;
				}
				float speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1)); //calculate speed variables
				float speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
				if(speed_train2==speed_train3) //when speeds are equal, you are done
					return;
				else if(speed_train2>speed_train3){ //if train2 is faster
					while(speed_train2>speed_train3){ //add cars to train2 while this is the case (from train3)
						float new_speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1+50)); //but first, calculate hypothetical speeds
						float new_speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2-50));
						if(new_speed_train2<new_speed_train3) //if hypothetical speeds compare differently
							break; //you are done
				   	    RemoveCarT3(train3,extraction); //otherwise, continue with the pushback
				   	    PushBack(train2,extraction);
				   	    weight1+=50; //account for weights
				   	    weight2-=50;
				   	    speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1)); //set speeds
				   	    speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
					}
				}
				else if(speed_train2<speed_train3){ //if train3 is faster
					while(speed_train2<speed_train3){ //add cars to train3 while this is the case (from train2), same logic as above
						float new_speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1-50));
						float new_speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2+50));
						if(new_speed_train2>new_speed_train3)
							break;
						RemoveCarT2(train2,extraction);
						PushFront(train3,extraction);
						weight2+=50;
						weight1-=50;
						speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
				   	    speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
					}
				}
			}
		}
	}
	else if(numEngines%2!=0){ //UNEVEN ENGINES CASE
		TrainCar* extraction; //extraction variable for our helper functions
		int weight1,weight2,train2Engines,train3Engines,nFreight,nPass,nDine,nSleep; //so we can use TotalWeightAndCountCars
		TotalWeightAndCountCars(train2,weight1,train2Engines,nFreight,nPass,nDine,nSleep); //only thing that matters really is train2Engines count and weight1
		TotalWeightAndCountCars(train3,weight2,train3Engines,nFreight,nPass,nDine,nSleep); //only thing that matters really is train3Engines count and weight2

		if(train2Engines==train3Engines+1){ //We are looking for train2 to have one more engine than train3
			float speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
			float speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
			if(speed_train2==speed_train3){ //If this is the case somehow...
				return; //You are done
			}
			else if(speed_train2>speed_train3){ //PushBack cars from train3 to train2 until the next care would yield speed2<speed3
				while(speed_train2>speed_train3){
					float new_speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1+50));
					float new_speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2-50));
					if(new_speed_train2<new_speed_train3)
						break;
					RemoveCarT3(train3,extraction);
					PushBack(train2,extraction);
					weight1+=50;
					weight2-=50;
					speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
					speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
				}
			}
			else if(speed_train2<speed_train3){
				while(speed_train2<speed_train3){
					float new_speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1-50));
					float new_speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2+50));
					if(new_speed_train2>new_speed_train3)
						break;
					RemoveCarT2(train2,extraction);
					PushFront(train3,extraction);
					weight2+=50;
					weight1-=50;
					speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
					speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
				}
			}
		}
		else if(train2Engines>train3Engines+1){ //if train2 has too many engines
			while(train2Engines!=train3Engines+1){ //give engines away to train3 until train2Engines=train3Engines+1
				RemoveEngineT2(train2,extraction);
				PushFront(train3,extraction);
				weight1-=150; //account for weight
				weight2+=150;
				train2Engines-=1; //account for # of engines
				train3Engines+=1;
			}
			/*ASIDE FROM THE DIFFERENCE IN WHEN WE DECIDE TO STOP MOVING AROUND ENGINES, THE LOGIC IS MAINLY THE SAME
			FOR WHEN TO STOP MOVING AROUND CARS FROM ONE TRAIN TO ANOTHER. WE CALCULATE THE HYPOTHETICAL SPEED
			IF WE WERE TO ADD ANOTHER CAR FOR BOTH TRAINS, AND IF THE SPEEDS COMPARE DIFFERENTLY,
			WE ARE DONE MOVING AROUND CARS AND SEPARATION IS COMPLETE. */

			float speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
			float speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
			if(speed_train2==speed_train3){ //If this is the case somehow...
				return; //You are done
			}
			else if(speed_train2>speed_train3){ //if train2 is faster
				while(speed_train2>speed_train3){ //Give cars to train2 until new_speed2<new_speed3
					float new_speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1+50));
					float new_speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2-50));
					if(new_speed_train2<new_speed_train3)
						break;
					RemoveCarT3(train3,extraction);
					PushBack(train2,extraction);
					weight1+=50;
					weight2-=50;
					speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
					speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
				}
			}
			else if(speed_train2<speed_train3){
				while(speed_train2<speed_train3){
					float new_speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1-50));
					float new_speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2+50));
					if(new_speed_train2>new_speed_train3)
						break;
					RemoveCarT2(train2,extraction);
					PushFront(train3,extraction);
					weight2+=50;
					weight1-=50;
					speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
					speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
				}
			}
		}
		else if(train2Engines<train3Engines+1){ //The final case: train3 has way too many engines
			while(train2Engines!=train3Engines+1){ //Until train2 has only one more engines
				RemoveEngineT3(train3,extraction); //Remove an engine from train3 and give it to train2
				PushBack(train2,extraction);
				weight1+=150; //account for weight and # engines
				weight2-=150;
				train2Engines+=1;
				train3Engines-=1;
			}
			/*
			THE REST OF THE CODE IN THIS FUNCTION IS SIMPLY THE SAME LOGIC FROM BEFORE REPEATED
			(WITH MOVING AROUND CARS UNTIL SPEEDS COMPARE DIFFERENTLY).
			*/
			float speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
			float speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
			if(speed_train2==speed_train3){ //If this is the case somehow...
				return; //You are done
			}
			else if(speed_train2>speed_train3){
				while(speed_train2>speed_train3){
					float new_speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1+50));
					float new_speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2-50));
					if(new_speed_train2<new_speed_train3)
						break;
					RemoveCarT3(train3,extraction);
					PushBack(train2,extraction);
					weight1+=50;
					weight2-=50;
					speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
					speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
				}
			}
			else if(speed_train2<speed_train3){
				while(speed_train2<speed_train3){
					float new_speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1-50));
					float new_speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2+50));
					if(new_speed_train2>new_speed_train3)
						break;
					RemoveCarT2(train2,extraction);
					PushFront(train3,extraction);
					weight2+=50;
					weight1-=50;
					speed_train2 = float((3000*train2Engines*550*1.8))/(0.02*5280*(weight1));
					speed_train3 = float((3000*train3Engines*550*1.8))/(0.02*5280*(weight2));
				}
			}
		}
	}	
}
