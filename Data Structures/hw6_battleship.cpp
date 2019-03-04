#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "ship.h"
#include "board.h"
#include "battlegame.h"
typedef unsigned int uint;
int main(int argc, char* argv[]){
	std::ifstream inFile(argv[1]);
	std::string word;
	uint r;
	uint c;
	std::vector<int> spacesFilledRows;
	std::vector<int> spacesFilledCols;
	std::vector<Ship> ship_list;
	Board board;
	bool constraint = false;
	int constraintrow;
	int constraintcol;
	char constraintchar;

	while(inFile>>word){
		if(word=="board"){
			inFile>>word;
			r = std::stoi(word); 
			inFile>>word;
			c = std::stoi(word);
			board.initialize(r,c);
		}
		else if(word=="rows"){
			int i = 1;
			while(i<=r){
				inFile>>word;
				spacesFilledRows.push_back(std::stoi(word)); //this will serve as the row_solution vector for battlegame
				i++;
			}
			
		}
		else if(word=="cols"){
			int i = 1;
			while(i<=c){
				inFile>>word;
				spacesFilledCols.push_back(std::stoi(word)); //this will serve as the col_solution vector for battlegame
				i++;
			}
		}
		else{
			if(word=="submarine"){
				Ship s(1,"submarine");
				ship_list.push_back(s);
			}
			else if(word=="destroyer"){
				Ship s2(2,"destroyer");
				ship_list.push_back(s2);
			}
			else if(word=="cruiser"){
				Ship s3(3,"cruiser");
				ship_list.push_back(s3);
			}
			else if(word=="battleship"){
				Ship s4(4,"battleship");
				ship_list.push_back(s4);
			}
			else if(word=="carrier"){
				Ship s5(5,"carrier");
				ship_list.push_back(s5);
			}
			else if(word=="cargo"){
				Ship s6(6,"cargo");
				ship_list.push_back(s6);
			}
			else if(word=="tanker"){
				Ship s7(7,"tanker");
				ship_list.push_back(s7);
			}
			else if(word=="constraint"){
				constraint = true;
				inFile>>word;
				constraintrow = std::stoi(word);
				inFile>>word;
				constraintcol = std::stoi(word);
				inFile>>word;
				constraintchar = word[0];
				if(constraintchar=='_') //the open water case
					constraintchar=' '; //translated into an empty space on the ascii printout
			}
		}
	}	
	sort(ship_list.rbegin(),ship_list.rend());
	if(argc==2){
		uint index = 0;
		if(!constraint){
			Battlegame b(spacesFilledRows,spacesFilledCols,ship_list);
			b.findSols(board,ship_list,index);
			b.uniqueSols();
			b.showSolution(); //gets only one solution
		}
		else{
			Battlegame b(spacesFilledRows,spacesFilledCols,ship_list,constraintrow,constraintcol,constraintchar);
			b.findSols(board,ship_list,index);
			b.uniqueSols();
			b.showSolution();
		}
	}
		
	else if(argc==3){
		std::string arg(argv[2]);
		if(arg!="find_all_solutions"){
			std::cout<<argv[2]<<std::endl;
			std::cout<<"Usage: ./file.exe text.txt find_all_solutions" <<std::endl;
			std::cout<<"Usage #2: ./file.exe text.txt" <<std::endl;
			return 1;
		}
		uint index = 0;
		if(!constraint){
			Battlegame b(spacesFilledRows,spacesFilledCols,ship_list);
			b.findSols(board,ship_list,index);
			b.uniqueSols();
			b.showSolutions(); //displays all solutions, if more than one
		}
		else{
			Battlegame b(spacesFilledRows,spacesFilledCols,ship_list,constraintrow,constraintcol,constraintchar);
			b.findSols(board,ship_list,index);
			b.uniqueSols();
			b.showSolutions();
		}
	}
	return 0;
}
