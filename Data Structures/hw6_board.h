#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <string>
#include "ship.h"
typedef unsigned int uint;
class Board{
	public:
		Board();
		Board(uint rows, uint cols);
		void initialize(uint rows, uint cols);
		int getRows();
		int getCols();
		void printBoard();
		std::vector<int> getRowsOccupied();
		std::vector<int> getColsOccupied();
		std::vector<std::string> getVertOrHor();
		std::vector<Ship> getShipsOnBoard();
		char getAscii(int row, int col);
		void copy(Board& toCopy);
		bool operator==(const Board& other) const;
		void place_ship(uint x0, uint y0, uint x1, uint y1, Ship& ship);
		std::vector<int> rowCounts();
		std::vector<int> colCounts();
		bool ship_exists(int x0, int x1, int y0, int y1);
		bool beyond_bounds(int x, int y);
	private:
		std::vector<std::vector<int> > grid; 
		int r; //number of rows
		int c; //number of cols
		std::vector<Ship> shipsonboard; 
		std::vector<int> rowsOccupied;
		std::vector<int> colsOccupied;
		std::vector<std::string> vertOrHor;
		std::vector<std::vector<char> > ascii;
};
#endif
