#include <vector>
#include <iostream>
#include "battlegame.h"
typedef unsigned int uint;
typedef std::vector<std::vector<int> > TwoDimIntVec;

Battlegame::Battlegame(std::vector<int> row_sol, std::vector<int> col_sol, std::vector<Ship> ships){
row_solution = row_sol;
col_solution = col_sol;
ship_list = ships;
b.initialize(row_sol.size(),col_sol.size());
constraint = false;
}
Battlegame::Battlegame(std::vector<int> row_sol, std::vector<int> col_sol, std::vector<Ship> ships, int conrow, int concol, char conchar){
row_solution = row_sol;
col_solution = col_sol;
ship_list = ships;
b.initialize(row_sol.size(),col_sol.size());
constraint = true;
constraintrow = conrow;
constraintcol = concol;
constraintchar = conchar;
}
bool Battlegame::can_place_horiz(Ship& s, Board& b1, int x0, int y0){
	int x1 = x0 + s.getLength() - 1;
	std::vector<int> column_buffer;
	int row_buffer;
	std::vector<int> rowcounts = b1.rowCounts();
	std::vector<int> colcounts = b1.colCounts();
	if(x1>b1.getCols()-1)
		return false;
	row_buffer = row_solution[y0]-rowcounts[y0];
	if(row_buffer<s.getLength())
		return false;
	for(int i = x0; i <= x1; i++){
		column_buffer.push_back(col_solution[i]-colcounts[i]);
	}
	for(uint i = 0; i < column_buffer.size(); i++){
		if(column_buffer[i]<1)
			return false;
	}
	if(b1.ship_exists(x0,x1,y0,y0)) //error is here. Apparently a ship exists?
		return false;

	return true;
}
bool Battlegame::can_place_vert(Ship& s, Board& b1, int x0, int y0){
	int y1 = y0 + s.getLength()-1;
	std::vector<int> row_buffer;
	int col_buffer;
	std::vector<int> rowcounts = b1.rowCounts();
	std::vector<int> colcounts = b1.colCounts();
	if(y1>b1.getRows()-1)
		return false;
	col_buffer = col_solution[x0] - colcounts[x0];
	if(col_buffer < s.getLength())
		return false;
	for(int i = y0; i <= y1; i++){
		row_buffer.push_back(row_solution[i]-rowcounts[i]);
	}
	for(uint i = 0; i < row_buffer.size(); i++){
		if(row_buffer[i]<1)
			return false;
	}
	if(b1.ship_exists(x0,x0,y0,y1))
		return false;

	return true;
}

TwoDimIntVec Battlegame::find_placements(Ship& s, Board& b1){ //PROBLEM IS WITH DUPLICATE PLACEMENTS 
	TwoDimIntVec placements;
	for(int x0 = 0; x0 < b1.getCols(); x0++){
		for(int y0 = 0; y0 < b1.getRows(); y0++){
			if(can_place_horiz(s, b1, x0, y0)){ //this never evaluates to true
				std::vector<int> placement;
				placement.push_back(x0);
				placement.push_back(y0);
				placement.push_back(x0+s.getLength()-1);
				placement.push_back(y0);
				bool alreadyAdded = false;
				for(int i = 0; i < placements.size(); i++){
					if(placements[i]==placement)
						alreadyAdded = true;
				}
				if(!alreadyAdded)	
					placements.push_back(placement);
			}
			if(can_place_vert(s,b1,x0,y0)){ //neither does this
				std::vector<int> placement;
				placement.push_back(x0);
				placement.push_back(y0);
				placement.push_back(x0);
				placement.push_back(y0+s.getLength()-1);
				bool alreadyAdded = false;
				for(int i = 0; i < placements.size(); i++){
					if(placements[i]==placement)
						alreadyAdded = true;
				}
				if(!alreadyAdded)
					placements.push_back(placement);
			}
		}
	}
	return placements;
}
void Battlegame::findSols(Board& b, std::vector<Ship>& ships, uint index){ 
	if(index>=ships.size()){ //our base case: we placed all ships
		if(!constraint){
			all_solutions.push_back(b);
			return;
		}
		else{
			if(b.getAscii(constraintrow+1,constraintcol+1)==constraintchar){
				all_solutions.push_back(b);
				return;
			}
			else
				return;
		}
	}
	//find our placement options
	Ship current_ship = ships[index];
	TwoDimIntVec possible_placements = find_placements(current_ship,b);
	int remainingShips = 0;
	uint pseudoIndex = index;
	//NEWLY ADDED STUFF
	while(ships[pseudoIndex].getName()==current_ship.getName()){
		if(pseudoIndex+1<ships.size()){
			pseudoIndex+=1;
			if(ships[pseudoIndex].getName()==current_ship.getName())
				remainingShips+=1;
		}
		else
			break;
	}
	//END OF NEWLY ADDED STUFF
	//recurse for each placement option
	for(uint i = 0; i < possible_placements.size(); i++){
		Board new_board(b.getRows(),b.getCols());
		new_board.copy(b);
		std::vector<int> placement = possible_placements[i];
		int x0 = placement[0];
		int y0 = placement[1];
		int x1 = placement[2];
		int y1 = placement[3];
		new_board.place_ship(x0,y0,x1,y1,current_ship);
		findSols(new_board,ships,index+1); //our recursive call
	}
	
}
void Battlegame::uniqueSols(){
	unique_solutions.push_back(all_solutions[0]);
	for(uint i = 0; i < all_solutions.size(); i++){
		bool alreadyAdded = false;
		for(uint j = 0; j < unique_solutions.size(); j++){
			if(all_solutions[i]==unique_solutions[j])
				alreadyAdded=true;
		}
		if(!alreadyAdded)
			unique_solutions.push_back(all_solutions[i]);
	}
}
void Battlegame::showSolution(){
	unique_solutions[0].printBoard();
}
void Battlegame::showSolutions(){
	for(uint i = 0; i < unique_solutions.size(); i++){
		unique_solutions[i].printBoard();
		std::cout<<std::endl;
	}
	if(unique_solutions.size()==0)
		std::cout<<"No solutions" <<std::endl;
}