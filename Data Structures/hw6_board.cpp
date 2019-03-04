#include "board.h"
#include <vector>
#include <string>
#include <iostream>
typedef unsigned int uint;
Board::Board(){
	r = 0;
	c = 0;
}
Board::Board(uint rows, uint cols){ //sets up the game board
	for(uint i = 0; i < rows; i++){
		std::vector<int> temp;
		grid.push_back(temp);
		for(uint j = 0; j < cols; j++){
			grid[i].push_back(0);
		}
	}
	r = rows;
	c = cols;
	//BELOW HANDLES THE ASCII REPRESENTATION
	std::vector<char> top; //ACTS AS THE TOP AND BOTTOM BORDER
	top.push_back('+');
	for(uint c = 0; c < cols; c++){
		top.push_back('-');
	}
	top.push_back('+');
	ascii.push_back(top);
	for(uint i = 0; i < rows; i++){
		std::vector<char> temp(cols+2,' ');
		temp[0] = '|';
		temp[temp.size()-1]='|';
		ascii.push_back(temp);
	}
	ascii.push_back(top);
}
void Board::initialize(uint rows, uint cols){
	for(uint i = 0; i < rows; i++){
		std::vector<int> temp;
		grid.push_back(temp);
		for(uint j = 0; j < cols; j++){
			grid[i].push_back(0);
		}
	}
	r = rows;
	c = cols;	
	//BELOW HANDLES THE ASCII REPRESENTATION
	std::vector<char> top; //ACTS AS THE TOP AND BOTTOM BORDER
	top.push_back('+');
	for(uint c = 0; c < cols; c++){
		top.push_back('-');
	}
	top.push_back('+');
	ascii.push_back(top);
	for(uint i = 0; i < rows; i++){
		std::vector<char> temp(cols+2,' ');
		temp[0] = '|';
		temp[temp.size()-1]='|';
		ascii.push_back(temp);
	}
	ascii.push_back(top);
}
int Board::getRows(){
	return r;
}
int Board::getCols(){
	return c;
}
bool Board::operator==(const Board& other) const{
	bool equal = true;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			if(grid[i][j]!=other.grid[i][j])
				equal = false;
		}
	}
	return equal;	
}
char Board::getAscii(int row, int col){
	return ascii[row][col];
}
void Board::copy(Board& toCopy){
	if(r==toCopy.getRows() && c==toCopy.getCols()){
		for(int i = 0; i < r; i++){ //COPIES GRID (NUMERICAL REPRESENTATION)
			for(int j = 0; j < c; j++){
				grid[i][j] = toCopy.grid[i][j]; 
			}
		}
	}
	for(int i = 0; i < toCopy.ascii.size(); i++){ //COPIES THE ASCII REPRESENTATION
		for(int j = 0; j < toCopy.ascii[0].size(); j++){
			ascii[i][j] = toCopy.ascii[i][j];
		}
	}
	for(int a = 0; a < toCopy.rowsOccupied.size(); a++){
		rowsOccupied.push_back(toCopy.rowsOccupied[a]);
	}
	for(int b = 0; b < toCopy.colsOccupied.size(); b++){
		colsOccupied.push_back(toCopy.colsOccupied[b]);
	}
	for(int c = 0; c < toCopy.shipsonboard.size(); c++){
		shipsonboard.push_back(toCopy.shipsonboard[c]);
	}
	for(int d = 0; d < toCopy.vertOrHor.size(); d++){
		vertOrHor.push_back(toCopy.vertOrHor[d]);
	}
}
void Board::place_ship(uint x0, uint y0, uint x1, uint y1, Ship& ship){ //REMEMBER TO ADD ASCII REPRESENTATION ADJUSTMENT HERE****
	if(x0==x1){
		for(uint i = y0; i <= y1; i++){
			grid[i][x0]+=1;
		}
		std::string name = ship.getName();
		if(name!="submarine"){
			ascii[y0+1][x0+1]='^'; //changed
			for(int y = y0+1; y<y1; y++){ //changed
				ascii[y+1][x0+1]='X'; //changed
			}
			ascii[y1+1][x0+1]='v'; //changed
			vertOrHor.push_back("vertical");
		}
		else{
			ascii[y0+1][x0+1]='o'; //changed
			vertOrHor.push_back("");
		}
	}
	else if(y0==y1){
		for(uint j = x0; j <= x1; j++){
			grid[y0][j]+=1;
		}
		std::string name = ship.getName();
		if(name!="submarine"){
			ascii[y0+1][x0+1]='<'; //changed
			for(int x = x0+1; x < x1; x++){ //changed
				ascii[y0+1][x+1] = 'X'; //changed
			}
			ascii[y0+1][x1+1]='>'; //changed
			vertOrHor.push_back("horizontal");
		}
		else{
			ascii[y0+1][x0+1]='o'; //changed
			vertOrHor.push_back("");
		}
	}
	colsOccupied.push_back(x0);
	rowsOccupied.push_back(y0);
	shipsonboard.push_back(ship);
}
std::vector<int> Board::rowCounts(){
	std::vector<int> rowsum;
	for(int i = 0; i<r; i++){
		int sum = 0;
		for(int j=0; j<c; j++){
			sum+=grid[i][j];
		}
		rowsum.push_back(sum);
	}
	return rowsum;
}
std::vector<int> Board::colCounts(){
	std::vector<int> colsum;
	for(int i=0; i<c; i++){
		int sum = 0;
		for(int j=0; j<r; j++){
			sum+=grid[j][i];
		}
		colsum.push_back(sum);
	}
	return colsum;
}
bool Board::ship_exists(int x0, int x1, int y0, int y1){
	if(x0>0)
		x0-=1;
	if(y0>0)
		y0-=1;
	if(x1<c-1)
		x1+=1;
	if(y1<r-1)
		y1+=1;
	for(int i = y0; i <= y1; i++){
		for(int j = x0; j <= x1; j++){
			if(grid[i][j]==1)
				return true;
		}
	}
	return false;
}
std::vector<int> Board::getRowsOccupied(){
	return rowsOccupied;
}
std::vector<int> Board::getColsOccupied(){
	return colsOccupied;
}
std::vector<std::string> Board::getVertOrHor(){
	return vertOrHor;
}
std::vector<Ship> Board::getShipsOnBoard(){
	return shipsonboard;
}
bool Board::beyond_bounds(int x, int y){
	return x<0 || y<0 || x>=c || y>=r;
}
void Board::printBoard(){
	std::cout<<"Solution:"<<std::endl;
	for(int a = 0; a < shipsonboard.size(); a++){
		std::cout<<shipsonboard[a].getName() << std::string(12-(shipsonboard[a].getName().size()),' ') << rowsOccupied[a] << " " << colsOccupied[a];
		std::cout<<" " << vertOrHor[a];
		std::cout<<std::endl;
	}
	for(int i = 0; i < ascii.size(); i++){
		for(int j = 0; j < ascii[0].size(); j++){
			std::cout<<ascii[i][j];
		}
		std::cout<<std::endl;
	}
}