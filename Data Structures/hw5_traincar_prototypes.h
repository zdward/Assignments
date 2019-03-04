// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//
#ifndef _TRAINCAR_PROTOTYPES_H_
#define _TRAINCAR_PROTOTYPES_H_
#include "traincar.h"
#include <vector>
void PushBack(TrainCar* &pointer, TrainCar* toPush); //responsible for adding on to a TrainCar*'s end using next and prev
void DeleteAllCars(TrainCar* &pointer);  //deletes all cars in a TrainCar* recursively
float CalculateSpeed(TrainCar* &car); //Calculates the speed of a TrainCar* on a 2% incline
std::vector<TrainCar*> ShipFreight(TrainCar* &allEngines, TrainCar* &allFreight, int minspeed, int maxcars); //constructing shipping trains with the engines and freight passed. 
void TotalWeightAndCountCars(TrainCar* &car,int &totWeight,int &numEngines,int &numFreight,int &numPass,int &numDine,int &numSleep); //achieves total weight of a TrainCar* and specific car count
float AverageDistanceToDiningCar(TrainCar* train); //Achieves average distance from a passenger car to a dining car
int ClosestEngineToSleeperCar(TrainCar* train); //finds the smallest distance from an engine to a sleeper car
void Separate(TrainCar* &train1, TrainCar* &train2, TrainCar* &train3); //Separates one train into two separate trains of similar speed
void RemoveEngineT2(TrainCar* &toRemove, TrainCar* &extractor); //helper function for separate, removes an engine from Train2
void RemoveCarT2(TrainCar* &toRemove, TrainCar* &extractor); //helper function for separate, removes a non-engine car from Train2
void PushFront(TrainCar* &pointer, TrainCar* toPush); //Pushes a TrainCar* to the front of another TrainCar* by connecting next and prev links
void RemoveEngineT3(TrainCar* &toRemove, TrainCar* &extractor); //helper function for separate, removes engine from Train3
void RemoveCarT3(TrainCar* &toRemove, TrainCar* &extractor); //helper function for separate, removes engine from Train3
void RemoveEngineShip(TrainCar* &toRemove, TrainCar* &extractor); //removes engines for shipFreight function
void RemoveCarShip(TrainCar* &toRemove, TrainCar* &extractor); //removes cars for shipFreight function
#endif

