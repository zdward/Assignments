#include <iostream>
#include <fstream>
#include "Matrix.h"

Matrix::Matrix(){ //default constructor, rows and columns set to 0
r = 0; 
c = 0;
}
Matrix::Matrix(const Matrix &m){ //copy constructor
	if(m.num_rows()==0 || m.num_cols()==0){ //dont allocate any heap memory
		r = m.num_rows();
		c = m.num_cols();
	}
	else{
	pointArr = new double*[m.num_rows()];  //points to a double array in the heap, size of rows
	for(unsigned int a = 0; a < m.num_rows(); a++){ 
		pointArr[a] = new double[m.num_cols()]; //each array points to another one, size of columns
	}
	for(unsigned int i = 0; i < m.num_rows(); i++){ //this double loop copies all values of m into this matrix
		for(unsigned int j = 0; j < m.num_cols(); j++){
			double retrieve;
			m.get(i,j,retrieve); //retrieve value from m
			pointArr[i][j] = retrieve; //put that value in this matrix
		}
	}
	r = m.num_rows(); //same number of rows as m
	c = m.num_cols(); //same number of cols as m
	}
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double fill){ //normal constructor
	if(rows==0 || cols==0){ //dont set up pointArr if this is the case
		r = rows;
		c = cols;
	}
	else{
	pointArr = new double*[rows]; //points to a double array in the heap, size of rows
	for(unsigned int i = 0; i < rows; ++i){
		pointArr[i] = new double[cols]; //each array points to another in the heap the size of columns
	}
	for(unsigned int j = 0; j < rows; j++){ 
		for(unsigned int k = 0; k < cols; k++){
			pointArr[j][k] = fill; //filling the 2D dynamic array
		}
	}
	r = rows; //setting the private variable r to rows
	c = cols; //setting the private variable c to cols
	}
}
Matrix::~Matrix(){ //destructor
	clear(); //calls the clear function
}
void Matrix::copy(const Matrix &m){ //extra copy function, used to copy data into another matrix
	if(m.num_rows()==0||m.num_cols()==0){ //dont allocate any memory in heap
		r = m.num_rows();
		c = m.num_cols();
	}
	else{
	pointArr = new double*[m.num_rows()]; //same logic entirely as the copy constructor
	for(unsigned int a = 0; a < m.num_rows(); a++){
		pointArr[a] = new double[m.num_cols()];
	}
	for(unsigned int i = 0; i < m.num_rows(); i++){
		for(unsigned int j = 0; j < m.num_cols(); j++){
			double retrieve;
			m.get(i,j,retrieve);
			pointArr[i][j] = retrieve;
		}
	}
	r = m.num_rows();
	c = m.num_cols();
	}
}
void Matrix::initialize(unsigned int rows, unsigned int cols, double fill){ //so matrices can be initialized later
	if(rows==0||cols==0){ //dont allocate any memory in heap
		r = rows;
		c = cols;
	}
	else{
	pointArr = new double*[rows]; //same logic entirely as the (rows,cols,fill) constructor
	for(unsigned int i = 0; i < rows; ++i){
		pointArr[i] = new double[cols];
	}
	for(unsigned int j = 0; j < rows; j++){
		for(unsigned int k = 0; k < cols; k++){
			pointArr[j][k] = fill;
		}
	}
	r = rows;
	c = cols;
	}
}
unsigned int Matrix::num_rows() const{ //returns number of rows
	return r;
}
unsigned int Matrix::num_cols() const{ //returns number of cols
	return c;
}
bool Matrix::get(unsigned int row, unsigned int col, double &atLoc) const{ //gets a value at a specific location
	if(row < r && col < c){ 
		atLoc = pointArr[row][col]; //set atLoc to the value at the specified location
		return true; 
	}
	else 
		return false; //return false because we are not setting atLoc to something
}
bool Matrix::set(unsigned int row, unsigned int col, double atLoc){ //sets a value at a specific location
	if(row < r && col < c){ //if we are within the bounds of the matrix
		pointArr[row][col] = atLoc; //set the value at the location to whatever was passed in (value of atLoc).
		return true; 
	}
	else 
		return false; //return false because a value was not changed
}
bool Matrix::operator==(const Matrix &other) const{ //equality operator
	bool equals = true; //assume equality
	if(r == other.num_rows() && c == other.num_cols()){ 
		for(unsigned int i = 0; i < r; i++){ //loop through the matrix of concern
			for(unsigned int j = 0; j < c; j++){
				double retrieve;
				other.get(i,j,retrieve);
				if(pointArr[i][j]!=retrieve) //if you detect any differences
					equals = false; //the two matrices are no longer equal, so return false
			}	
		}
	}
	else 
		return false; //return false because they arent the same size
	return equals; //return whatever equals came out to be if the else did not execute
}
Matrix& Matrix::operator=(const Matrix &other){ //the assignment operator
	if (&other != this) { //if the reference location is not the same
		this->clear(); 
		this->copy(other); //copy the other data into this current matrix
	}
	return *this; //dereference this matrix and return it
}
bool Matrix::operator!=(const Matrix &other) const{ //the inequality operator
	bool notEquals = false; //same logic as the assignment operator but flipped
	if(r == other.num_rows() && c == other.num_cols()){
		for(unsigned int i = 0; i < r; i++){
			for(unsigned int j = 0; j < c; j++){
				double retrieve;
				other.get(i,j,retrieve);
				if(pointArr[i][j]!=retrieve)
					notEquals = true;
			}	
		}
	}
	else 
		return true;
	return notEquals;
}
void Matrix::multiply_by_coefficient(double coeff){ //scaling a matrix by some coefficient
	for(unsigned int i = 0; i < r; i++){ 
		for(unsigned int j = 0; j < c; j++){ 
			pointArr[i][j] *= coeff; //multiply each and every value by the coefficient
		}
	}
}
bool Matrix::add(Matrix &B){ //adds together two matrices
	if(r == B.num_rows() && c == B.num_cols()){ 
		for(unsigned int i = 0; i < r; ++i){ 
			for(unsigned int j = 0; j < c; ++j){
				double retrieve; 
				B.get(i,j,retrieve); //retrieve every value from the other matrix B
				pointArr[i][j]+=retrieve; //add that value to the current matrix value at (i,j)
			}
		}
		return true; //if addition was successful, return true
	}
	else
		return false; //otherwise, return false
}
bool Matrix::subtract(Matrix &B){ //subtracts matrix B from matrix A (the current matrix)
	if(r == B.num_rows() && c == B.num_cols()){ //same logic as add
		for(unsigned int i = 0; i < r; ++i){
			for(unsigned int j = 0; j < c; ++j){
				double retrieve;
				B.get(i,j,retrieve);
				pointArr[i][j]-=retrieve;
			}
		}
		return true;
	}
	else
		return false;
}
double* Matrix::get_row(unsigned int numRow){ //returns a double* array rowArr (pick a row to return)
	double* rowArr; //make rowArr point to a new double array in the heap, size of # of columns
	if(numRow>=r){
		rowArr = NULL;
		return rowArr;
	}
	rowArr = new double[c];
	for(unsigned int i = 0; i < c; i++){ //look from 0 to # of cols - 1
		rowArr[i] = pointArr[numRow][i]; //put each row element in rowArr from the matrix
	}
	return rowArr; //returning rowArr when its all set up
}
double* Matrix::get_col(unsigned int numCol){ //returns a double* array colArr (pick a col to return)
	double* colArr;
	if(numCol>=c){
		colArr = NULL;
		return colArr;
	} 
	colArr = new double[r]; //make colArr point to a new double array in the heap, size of # of rows
	unsigned int position = 0; //have an extra variable thats incremented called position (in colArr)
	for(unsigned int i = 0; i < r; i++){ 
		colArr[position] = pointArr[i][numCol]; //a number in the column is assigned to colArr at the current position
		position+=1; //can't forget to increment position
	}
	return colArr; //once colArr is set up, return it
}
void Matrix::swap_row(unsigned int row1, unsigned int row2){ //swaps any two rows in the current matrix
	double temprow[c]; //create a temprow to facilitate the swap (the size of the # of columns)
	for(unsigned int j = 0; j < c; j++){ 
		temprow[j] = pointArr[row1][j]; //filling temprow with row1 elements
	}
	for(unsigned int k = 0; k < c; k++){ 
		pointArr[row1][k] = pointArr[row2][k]; //copying row2 to row1
	}
	for(unsigned int l = 0; l < c; l++){ 
		pointArr[row2][l] = temprow[l]; //copying row1 to row2
	}
}
void Matrix::transpose(){ //the transpose operator
	double tempMatrix[c][r]; //create a FLIPPED temp matrix to facilitate transpose
	int newrows = c; 
	int newcols = r;
	for(unsigned int o = 0; o < c; o++){ 
		double colArray[r]; //create a column array to be filled
		unsigned int position = 0; //position iterator starting at 0
		for(unsigned int b = 0; b < r; b++){ 
			colArray[position] = pointArr[b][o]; //filling up colArray
			position+=1; //incrementing position
		}
		for(unsigned int h = 0; h < position; h++){
			tempMatrix[o][h]=colArray[h]; //filling up the transposed tempMatrix
		}
	}
	clear(); 
	r = newrows; //setting r equal to newrows which was set to c
	c = newcols; //setting r equal to newcols which was set to r
	pointArr = new double*[r]; //resetting up pointArr
	for(unsigned int i = 0; i < r; ++i){ //resetting up pointArr part 2
		pointArr[i] = new double[c];
	}
	for(unsigned int j = 0; j < r; j++){ //filling up each element of pointArr (Transposed)
		for(unsigned int k = 0; k < c; k++){
			pointArr[j][k] = tempMatrix[j][k]; //filling from tempMatrix
		}
	}
}
Matrix* Matrix::quarter(){ //the quarter operator
	Matrix* quarterArr = new Matrix[4]; //Matrix* quarterArr pointing to Matrix array in the heap of size 4 (4 quarters)
	unsigned int rows; //# of rows for each quarter
	unsigned int cols; //# of cols for each quarter
	//next step is to fill each matrix depending on the current matrix dimensions
	if(r%2==0){ 
		rows = r/2; 
		if(c%2==0)
			cols = c/2;
		else  
			cols = (c/2)+1; 
	}
	else{ 
		rows = (r/2)+1;
		if(c%2==0) //same logic as above (the rest is repeated)
			cols = c/2;
		else
			cols = (c/2)+1;
	}
	if(rows == 0 || cols == 0){ //The corner case of an empty matrix
		for(int i = 0; i < 4; i++){
			quarterArr[i].initialize(0,0,0); 
		}
	}
	for(unsigned int i = 0; i < 4; i++){ //looping through quarterArr
		quarterArr[i].initialize(rows,cols,0); //initializes quarter matrices filled with 0's
	}
	for(unsigned int a = 0; a < rows; a++){ //filling up UPPER LEFT matrix
		for(unsigned int b = 0; b < cols; b++){
			double obt; //value obtained from corner
			get(a,b,obt);
			quarterArr[0].set(a,b,obt); //changing each indiv. element in UL matrix
		}
	}
	for(unsigned int v = 0; v < rows; v++){ //filling UPPER RIGHT matrix
		for(unsigned int d = c/2; d < c; d++){
			double obt; //value obtained from corner
			get(v,d,obt);
			quarterArr[1].set(v,d-c/2,obt); //changing each indiv. element in UR matrix
		}
	}
	for(unsigned int e = r/2; e < r; e++){ //filling BOTTOM LEFT matrix
		for(unsigned int f = 0; f < cols; f++){
			double obt; //value obtained from corner
			get(e,f,obt);
			quarterArr[2].set(e-r/2,f,obt); //changing each indiv. element in LL matrix
		}
	}
	for(unsigned int g = r/2; g < r; g++){ //filling BOTTOM RIGHT matrix
		for(unsigned int h = c/2; h < c; h++){
			double obt; //value obtained from corner
			get(g,h,obt);
			quarterArr[3].set(g-r/2,h-c/2,obt); //changing each indiv. element in LR matrix
		}
	}
	return quarterArr; //returning Matrix* quarterArr once all set up
	
}
void Matrix::resize(unsigned int rows, unsigned int cols, double fill){ //EXTRA CREDIT: resize oeprator
	//there are three cases: the matrix could be smaller, the same size, or larger after the resize
	if(r==rows && c==cols){ //same size case
		return; 
	}
	else if((r==rows && c>cols)||(r>rows && c==cols)||(r>rows && c>cols)){ //smaller case
		Matrix m(*this); //make a copy matrix of the current matrix
		this->clear(); //empty the current matrix
		this->initialize(rows,cols,fill); //resize it to the new rows and cols with a fill value
		for(unsigned int i = 0; i < r; i++){ //replace all fill values with previous values
			for(unsigned int j = 0; j < c; j++){
				double retrieve;
				m.get(i,j,retrieve);
				this->set(i,j,retrieve);
			}
		}
	}
	else{ //only other case left is the larger case
		Matrix m2(*this); //make a copy matrix of the current matrix
		this->clear(); 
		this->initialize(rows,cols,fill); //resize it to the new rows and cols with a fill value
		for(unsigned int i = 0; i < m2.num_rows(); i++){ 
			for(unsigned int j = 0; j < m2.num_cols(); j++){
				double retrieve;
				m2.get(i,j,retrieve); //retrieve value from copied matrix m2
				this->set(i,j,retrieve); //restore each value in the new resized matrix
			}
		}
	}
}
void Matrix::clear(){ //clear function
	if(r == 0 || c == 0){ 
		return; 
	}
	for(unsigned int i = 0; i < r; i++){ //loop through the rows
		delete [] pointArr[i]; //delete each row
	}
	delete [] pointArr; //delete all of pointArr
	r = 0; 
	c = 0; 
}
std::ostream& operator<<(std::ostream& out, const Matrix &m){ //The output operator
	out << m.num_rows() << " x " << m.num_cols() << " matrix: " << std::endl; //output "num x num matrix: "
	out << "[ "; //starting brace "[ "
	for(unsigned int i = 0; i < m.num_rows(); ++i){ //loop through the matrix
		for(unsigned int j = 0; j < m.num_cols(); ++j){ 
			double retrieve;
			m.get(i,j,retrieve); //retrieve current value
			out<< retrieve << " "; //output value
		}
		if(!(i+1<m.num_rows())){ //if there are no more iterations left
			out << "]" << std::endl; //add on the end brace
		}
		else{ 
			out << std::endl; //make a new line
			out << "  "; //add a space
		}
	}
	if(m.num_cols()==0 || m.num_rows()==0){ //if there are no rows or cols
		out << " ]"; //output ending brace
	}
	out << std::endl; 
	out << "Done Printing."; 
	return out; 
}