// =======================================================
//
// IMPORTANT NOTE: Do not modify this file
//     (except to uncomment the provided test cases 
//     and add your test cases where specified)
//
// =======================================================


#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "Matrix.h"

#define __EPSILON 0.0000000001 //Need this to compare doubles because representation.

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here
void ExtraCreditTest(); //Write this if you write resize()
Matrix rref(const Matrix& m);

//Function to test a ton of matrices at once.
void BatchTest(double start, double step, unsigned int rows, unsigned int cols,
               unsigned int num);

//Quick function that returns if two doubles are very similar to each other.
bool double_compare(double a, double b);

//Uses Gauss-Jordan elimination to create a Reduced Row Echelon Form matrix.
//Matrix rref(const Matrix& m);

int main(){


	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	//Uncomment this to allocate a lot of 100x100 matrices so leaks will be bigger.
	
	BatchTest(100,0.1,100,100,50);
	std::cout << "Completed all batch tests." << std::endl;
	

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	//Uncomment this if you write the resize() function.
	
	ExtraCreditTest();
	std::cout << "Completed all student extra credit tests." << std::endl;
	
	return 0;
}

////////////////Test functions//////////////////////
//Some basic tests
void SimpleTest(){  //well behaved getrow/read after
	
	//Default constructor
	Matrix m1;
	assert(m1.num_rows() == 0 && m1.num_cols() == 0);

	//Copy constructor
	Matrix m2(3,4,0);
	assert(m2.num_rows() == 3 && m2.num_cols() == 4);
	
	Matrix m2_copy(m2);
	assert(m2_copy.num_rows() == 3 && m2_copy.num_cols() == 4);
	m2_copy.set(1,1,27);
	double d0;
	assert(m2.get(1,1,d0));
	assert(double_compare(d0,0.0));
	assert(m2_copy.get(1,1,d0));
	assert(double_compare(d0,27));

	//Equality and Inequality
	Matrix m3;
	assert(m1 == m3);
	assert(m1 != m2);

	//Printing
	std::cout << "Empty matrix:";
	std::cout << m1 << std::endl;

	std::cout << "Zeroed 3x4 matrix:";
	std::cout << m2 << std::endl;

	std::cout << "One after the other:";
	std::cout << m1 << m2 << std::endl;

	//Set & get
	Matrix m5(4,4,2);
	Matrix m6(4,4,12);
	assert(m6.set(2,1,7));
	assert(m6.set(3,3,11));
	double d1;
	assert(m6.get(2,1,d1));
	assert(d1==7);

	//Addition
	std::cout << "Adding m5 and m6" << std::endl;
	std::cout << m5 << m6 << std::endl;

	Matrix m7;
	m7 = m5;

	Matrix m8(m5);
	assert(m7 == m8);

	assert(m7.add(m6));
	std::cout << "The result" << std::endl;
	std::cout << m7 << std::endl;

	double* r1 = NULL;
	r1 = m7.get_row(2);
	assert(r1[0] == 14 && r1[1] == 9);

	delete [] r1; //Remember we need to clean up dynamic allocations.

	Matrix m9(3,6,0);
	m9.set(0,0,1);
	m9.set(0,1,2);
	m9.set(0,2,1);
	m9.set(0,3,1);
	m9.set(1,0,2);
	m9.set(1,1,3);
	m9.set(1,2,-1);
	m9.set(1,4,1);
	m9.set(2,0,3);
	m9.set(2,1,-2);
	m9.set(2,2,-1);
	m9.set(2,5,1);

	std::cout << "Attempting Gauss-Jordan reduced row echelon form." 
		  << m9 << std::endl;
	Matrix m12 = rref(m9);
	std::cout << m12 << std::endl;
	double comparison_value;
	assert(m12.get(0,3,comparison_value));
	assert(double_compare(comparison_value,0.25));
	assert(m12.get(0,1,comparison_value));
	assert(double_compare(comparison_value,0.0));
	assert(m12.get(1,5,comparison_value));
	assert(double_compare(comparison_value,-3.00/20));
	assert(m9.get(0,3,comparison_value));
	assert(double_compare(comparison_value,1.0));
	assert(m9.get(0,1,comparison_value));
	assert(double_compare(comparison_value,2.0));
	assert(m9.get(1,5,comparison_value));
	assert(double_compare(comparison_value,0.0));

	Matrix m11(3,4,0);
	m11.set(0,0,1);
	m11.set(0,1,2);
	m11.set(0,2,3);
	m11.set(0,3,4);

	m11.set(1,0,5);
	m11.set(1,1,6);
	m11.set(1,2,7);
	m11.set(1,3,8);

	m11.set(2,0,9);
	m11.set(2,1,10);
	m11.set(2,2,11);
	m11.set(2,3,12);

	std::cout << "M11 to be quartered: " << std::endl;
	std::cout << m11 << std::endl;

	Matrix* ma1 = NULL;
	ma1 = m11.quarter();
	assert(ma1 != NULL);

	std::cout << "UL: " << std::endl << ma1[0] << std::endl;
	std::cout << "UR: " << std::endl << ma1[1] << std::endl;
	std::cout << "LL: " << std::endl << ma1[2] << std::endl;
	std::cout << "LR: " << std::endl << ma1[3] << std::endl;

	for(unsigned int i=0; i<4; i++){
		assert((ma1[i].num_rows() == 2) && (ma1[i].num_cols() == 2));
	}

	//Upper Left
	assert(ma1[0].get(0,0,comparison_value));
	assert(double_compare(comparison_value,1));
	assert(ma1[0].get(1,1,comparison_value));
	assert(double_compare(comparison_value,6));

	//Upper Right
	assert(ma1[1].get(0,0,comparison_value));
	assert(double_compare(comparison_value,3));
	assert(ma1[1].get(1,1,comparison_value));
	assert(double_compare(comparison_value,8));

	//Lower Left
	assert(ma1[2].get(0,0,comparison_value));
	assert(double_compare(comparison_value,5));
	assert(ma1[2].get(1,1,comparison_value));
	assert(double_compare(comparison_value,10));

	//Lower Right
	assert(ma1[3].get(0,0,comparison_value));
	assert(double_compare(comparison_value,7));
	assert(ma1[3].get(1,1,comparison_value));
	assert(double_compare(comparison_value,12));

	delete [] ma1;
	
}

//Write your own test cases here
void StudentTest(){
	Matrix m1(0,1,3); //testing a corner case: only one 0 in rows
	std::cout<<m1<<std::endl;
	Matrix m2(2,3,1); //even rows and odd columns quarter testing
	m2.set(0,1,2);
	m2.set(0,2,3);
	m2.set(1,0,4);
	m2.set(1,1,5);
	m2.set(1,2,6);
	std::cout<<m2<<std::endl;
	Matrix* arr = m2.quarter();
	std::cout<<"QUARTER FOR MATRIX m2: " << std::endl;
	for(int i = 0; i < 4; i++){
		std::cout<<arr[i]<<std::endl;
	}
	delete [] arr;
	
	Matrix m3(1,4,2); 
	m3.set(0,0,1); 
	m3.set(0,2,3);
	m3.set(0,3,4);
	std::cout<<m3<<std::endl;
	Matrix* arr2 = m3.quarter(); 
	std::cout<<"QUARTER FOR MATRIX m3: " << std::endl; //testing quarter with only one row
	for(int i = 0; i < 4; i++){
		std::cout<<arr2[i]<<std::endl;
	}
	delete [] arr2;

	double* a = m2.get_row(0);
	std::cout<<"ELEMENTS IN ROW 0 OF m2: " << std::endl;
	for(int i = 0; i < 3; i++){
		std::cout<<a[i]<<std::endl;
	}
	delete [] a;
	m2.multiply_by_coefficient(3.14);
	std::cout<<"m2 Multiplied by 3.14: " << std::endl;
	std::cout<<m2<<std::endl;
	std::cout<<"m2 TRANSPOSED: " << std::endl;
	m2.transpose();
	std::cout<<m2<<std::endl;
	Matrix onebyone(1,1,2);
	Matrix* arr3 = onebyone.quarter();
	std::cout<<"ONE BY ONE MATRIX: " << std::endl;
	std::cout<<onebyone<<std::endl;
	std::cout<<"QUARTER FOR ONEBYONE MATRIX: " << std::endl;
	for(unsigned int i = 0; i < 4; i++){
		std::cout<<arr3[i]<<std::endl;
	}
	delete [] arr3;
	Matrix m4(10,10,0); //100 element matrix
	for(unsigned int i = 0; i < m4.num_rows(); i++){
		for(unsigned int j = 0; j < m4.num_cols(); j++){
			m4.set(i,j,i+j);
		}
	}
	std::cout<<"MATRIX m4: " << std::endl;
	std::cout<<m4<<std::endl;
	double* col = m4.get_col(2); //third column
	std::cout<<"ALL ELEMENTS IN COLUMN 3 of Matrix M4: " << std::endl;
	for(unsigned int i = 0; i < m4.num_rows(); i++){
		std::cout<<col[i] << " ";
	}
	std::cout<<std::endl;
	m4.transpose(); //SHOULD BE THE SAME!!
	std::cout<<"TRANSPOSED m4: " << std::endl;
	std::cout<<m4<<std::endl;
	delete [] col;
	
	std::cout<<"QUARTER ON AN EMPTY MATRIX [ ]: " << std::endl;
	Matrix zero(0,0,0); //checking the corner case of quarter on an empty matrix
	
	Matrix *arr7 = zero.quarter();
	for(int i = 0; i < 4; i++){
		std::cout<<arr7[i]<<std::endl;
	}
	delete [] arr7;
	//Finally, copying an empty matrix just to test if this works
	Matrix toBeCopied(0,0,0);
	Matrix theCopy(toBeCopied);
	std::cout<<"This is a copy of an empty matrix: " << std::endl;
	std::cout<<theCopy<<std::endl;
	
}

//Write this if you write resize()
void ExtraCreditTest(){
Matrix m1(3,3,2); //setting up matrix 1, 3 rows, 3 cols
m1.set(0,0,1);
m1.set(0,1,2);
m1.set(0,2,3);
m1.set(1,0,4);
m1.set(1,1,5);
m1.set(1,2,6);
m1.set(2,0,7);
m1.set(2,1,8);
m1.set(2,2,9);
std::cout<<"M1 PRINTING BELOW"<<std::endl;
std::cout<<m1<<std::endl;
m1.resize(4,4,0); //making the matrix bigger, fill value is 0
std::cout<<"MAKING m1 A LITTLE BIGGER..." << std::endl;
std::cout<<m1<<std::endl;
m1.resize(3,3,0); //returning back to normal
std::cout<<"BACK TO NORMAL..." << std::endl;
std::cout<<m1<<std::endl;
m1.resize(1,2,0);
std::cout<<"SHRINKING TO 1 ROW AND 2 COLS..." << std::endl;
std::cout<<m1<<std::endl;

Matrix m2(0,0,0); //corner case of 0x0 matrix
std::cout<<"EMPTY MATRIX M2: " << std::endl;
std::cout<<m2<<std::endl;
std::cout<<"EXPANDING TO 2 ROWS AND 1 COL, FILL VAL OF 3"<<std::endl;
m2.resize(2,1,3);
std::cout<<m2<<std::endl;
std::cout<<"EXPANDING FURTHER TO 4 ROWS AND 3 COLS, FILL VAL OF 9"<<std::endl;
m2.resize(4,3,9);
std::cout<<m2<<std::endl;
std::cout<<"SHRINKING BACK TO 0 x 0" << std::endl;
m2.resize(0,0,0);
std::cout<<m2<<std::endl;

}


////////////////Utility functions//////////////////////

/*  Function that quickly populates a rows x cols matrix with values from     
 *  start in increments of step. Does this num_times times.
 */
void BatchTest(double start, double step, unsigned int rows, unsigned int cols,
               unsigned int num){
	
	Matrix* m_arr = new Matrix[num];
	for(unsigned int i=0; i<num; i++){
		m_arr[i] = Matrix(rows,cols,0.0);
		unsigned int curr_elem = 0;
		for(unsigned int j=0; j<rows; j++){
			for(unsigned int k=0; k<rows; k++){
				m_arr[i].set(j,k,start+(step*curr_elem));
				curr_elem++;
			}
		}
	}
	delete [] m_arr;
	
}

//Quick function that returns if two doubles are very similar to each other.
bool double_compare(double a, double b){
	
	return (fabs(a-b) < __EPSILON);
	
}

/*  Uses Gauss-Jordan elimination to create a Reduced Row Echelon Form matrix.
 *  These are some good and some bad variable names.
 *  See how much harder it makes it to follow the code?
 *  The lack of comments doesn't help either.
 */

Matrix rref(const Matrix& m){
	
	Matrix ret(m);
	unsigned int curr_col = 0;
	double dummy;
	for(unsigned int i=0; i<ret.num_rows(); i++){
		bool col_all_zeros = true;
		//while(col_all_zeros && col_all_zeros < ret.num_cols()){
		while(col_all_zeros && curr_col < ret.num_cols()){
			for(unsigned int scan_i = 0; scan_i < ret.num_rows(); scan_i++){
				ret.get(scan_i,curr_col,dummy);
				if (!double_compare(dummy,0.0)){
					col_all_zeros = false;
					break;
				}
			}
			if(col_all_zeros){
				curr_col += 1;
			}
		}
		if(curr_col>=ret.num_cols()){
			return ret;
		}

		ret.get(i,curr_col,dummy);
		if(double_compare(dummy,0.0)){
			//Swap with a nonzero row
			for(unsigned int scan_i = i+1; scan_i < ret.num_rows(); scan_i++){
				ret.get(scan_i,curr_col,dummy);
				if(!double_compare(dummy,0.0)){
					ret.swap_row(scan_i,i);
					break;
				}
			}
		}

		//Now we know ret i,curr_col is non-zero so we can use it as a pivot.
		double pivot;
		ret.get(i,curr_col,pivot);
		for(unsigned int j=0; j<ret.num_cols(); j++){
			ret.get(i,j,dummy);
			ret.set(i,j,dummy/pivot);
		}

		for(unsigned int row_i = 0; row_i < ret.num_rows(); row_i++){
			if (row_i == i){
				continue;
			}
			double row_leading_coeff;
			ret.get(row_i,curr_col,row_leading_coeff);
			for(unsigned int col_j = 0; col_j < ret.num_cols(); col_j++){
				double lhs_dummy,rhs_dummy;
				ret.get(row_i,col_j,lhs_dummy);
				ret.get(i,col_j,rhs_dummy);
				ret.set(row_i,col_j,lhs_dummy - (row_leading_coeff*rhs_dummy));
			}
		}
		curr_col +=1 ;
	}
	return ret;
	
}
