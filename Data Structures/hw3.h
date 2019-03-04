#ifndef MATRIX_H_
#define MATRIX_H_
#include <fstream>

class Matrix{
	public:
		//CONSTRUCTORS
		Matrix(); //constructor
		Matrix(const Matrix &m); //copy constructor
		Matrix(unsigned int rows, unsigned int cols, double fill); //normal constructor
		~Matrix(); //destructor
		//MEMBER FUNCTIONS
		void initialize(unsigned int rows, unsigned int cols, double fill); //so the quarter function works
		unsigned int num_rows() const; //returns number of rows
		unsigned int num_cols() const; //returns number of columns
		bool operator==(const Matrix &other) const; //equality operator
		bool operator!=(const Matrix &other) const; //inequality operator
		Matrix& operator=(const Matrix &other); //assignment operator
		void clear(); //clear function
		void copy(const Matrix &m); //copy function (extra)
		bool get(unsigned int row, unsigned int col, double &atLoc) const; //accesses a specific value
		bool set(unsigned int row, unsigned int col, double atLoc); //changes a specific value
		void multiply_by_coefficient(double coeff); //scales the matrix 
		void swap_row(unsigned int row1, unsigned int row2); //swap any two rows
		void transpose(); //transpose operator
		bool add(Matrix &B); //add this matrix with any other matrix
		bool subtract(Matrix &B); //subtract matrix B from this one
		double* get_row(unsigned int numRow); //returns a row
		double* get_col(unsigned int numCol); //returns a col
		Matrix* quarter(); //quarter operator
		void resize(unsigned int rows, unsigned int cols, double fill); //extra credit: resizes the matrix

	private:
		//REPRESENTATION
		double** pointArr; //dynamic 2D array
		unsigned int r; //rows
		unsigned int c; //columns
};

std::ostream& operator<<(std::ostream& out, const Matrix &m);

#endif
