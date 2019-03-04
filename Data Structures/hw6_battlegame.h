#ifndef BATTLEGAME_H_
#define BATTLEGAME_H_
#include "ship.h"
#include "board.h"
#include <vector>
typedef std::vector<std::vector<int> > TwoDimIntVec;
class Battlegame{
	public:
		Battlegame(std::vector<int> row_sol, std::vector<int> col_sol, std::vector<Ship> ships);
		Battlegame(std::vector<int> row_sol, std::vector<int> col_sol, std::vector<Ship> ships, int conrow, int concol, char conchar);
		void uniqueSols(); //Gets rid of repeat solutions
		void findSols(Board& b, std::vector<Ship>& ships, uint index); //OUR RECURSIVE FUNCTION!! YAY!
		TwoDimIntVec find_placements(Ship& s, Board& b1);
		bool can_place_horiz(Ship& s, Board& b1, int x0, int y0);
		bool can_place_vert(Ship& s, Board& b1, int x0, int y0);
		void showSolution();
		void showSolutions();
		void recordInstances(std::vector<Ship> list_ships);

	private:
		std::vector<Board> all_solutions;
		std::vector<Board> unique_solutions;
		std::vector<Ship> ship_list;
		Board b;
		std::vector<int> row_solution;
		std::vector<int> col_solution;
		bool constraint;
		int constraintrow;
		int constraintcol;
		char constraintchar;
};
#endif
