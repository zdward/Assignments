#include <stdio.h>
#include <stdlib.h>
/*
Matrix Multiplication CS2500 - Hw01
by Zachary Ward
*/
int numberOfDigits(int a){ //function for getting # of digits
  int count = 0;
  while(a != 0)
  //Cut off last digit until you can't anymore
    {
        a /= 10;
        ++count;
    }
    return count; //returning the count of interest
}
int LargestDigitsPerCol(int** Matrix, int rows, int col){
  /*This function returns the number with the most amount of
  digits in a specified column*/
  int row;
  int maxNum;
  maxNum = 0;
  for(row = 0; row < rows; row++){ //looping through all rows of a column
    if(numberOfDigits(Matrix[row][col])>maxNum) //comparison to max
      maxNum = numberOfDigits(Matrix[row][col]); //resetting of max
  }
  return maxNum; //returning the # with max digits
}
void printFormattedMatrix(int** Matrix, int rows, int cols, int arr[]){ //Handles all spacing and formatting
  int col, row, spaces;
  for(row = 0; row < rows; row++){ //DOUBLE FOR LOOP GOING THROUGH THE MATRIX
    for(col = 0; col < cols; col++){
      if(col==0 && col!=cols-1){ //When we only want to print a [
        printf("[");
        spaces = 0;
        while(spaces<arr[col]-numberOfDigits(Matrix[row][col])){ //print required number of spaces
          printf(" ");
          spaces++;
        }
        printf("%d",Matrix[row][col]); //print our matrix value at some location (row,col)
      }
      else if(col==0 && col==cols-1){ //If we only have one column
        printf("[");
        spaces = 0;
        while(spaces<arr[col]-numberOfDigits(Matrix[row][col])){ //printing required number of spaces
          printf(" ");
          spaces++;
        }
        if(row!=rows-1) //If not on the last row
          printf("%d]\n",Matrix[row][col]); //handling correct formatting
        else //If we are on the last row
          printf("%d]",Matrix[row][col]); //handling correct formatting
      }
      else if(col!=0 && col!=cols-1){ //Some column in between first and last
        spaces = 0;
        while(spaces<arr[col]-numberOfDigits(Matrix[row][col])+1){ //print correct number of spaces
          printf(" ");
          spaces++;
        }
        printf("%d",Matrix[row][col]); //print correct Matrix value
      }
      else if(col==cols-1){ //If we are on the last column
        spaces = 0;
        while(spaces<arr[col]-numberOfDigits(Matrix[row][col])+1){ //print correct number of spaces
          printf(" ");
          spaces++;
        }
        if(row!=rows-1) //not on the last row
          printf("%d]\n",Matrix[row][col]); //handling correct formatting
        else //on last row
          printf("%d]",Matrix[row][col]); //handling correct formatting (NO new line character)
      }
    }
  }
}
int main(int argc, char** argv){
  int** MAT1; //First matrix
  int** MAT2; //Second matrix
  int** RESULT; //Result matrix
  int i,j,k,row1,col1,row2,col2; //loop variables
  if(argc!=5){ //CHECKING FOR CORRECT # of ARGS.
    fprintf(stderr,"ERROR: Invalid inputs!\n"); //error message
		return EXIT_FAILURE;
  }//converting our command line arguments to integers
  row1 = atoi(argv[1]);
  col1 = atoi(argv[2]);
  row2 = atoi(argv[3]);
  col2 = atoi(argv[4]);
  if(col1!=row2){
    fprintf(stderr,"ERROR: Invalid inputs!\n"); //error message
  	return(0);
  }
  //BEGINNING MEMORY (M)ALLOCATION..get it
  MAT1 = (int**)malloc(row1*sizeof(int*)); //MAT1 MEM ALLOCATION
  for(i = 0; i < row1; i++){ //looping through rows of MAT1
    MAT1[i] = (int*)malloc(col1*sizeof(int));
  }
  MAT2 = (int**)malloc(row2*sizeof(int*)); //MAT2 MEM ALLOCATION
  for(i = 0; i < row2; i++){
    MAT2[i] = (int*)malloc(col2*sizeof(int));
  }
  RESULT = (int**)malloc(row1*sizeof(int*)); //RESULT MEM ALLOCATION
  for(i = 0; i < row1; i++){
    RESULT[i] = (int*)malloc(col2*sizeof(int));
  }
  //DONE ALLOCATING THE NECESSARY MEMORY.

  // REQUEST MAT1 VALUES
  printf("Please enter the values for the first matrix (%dx%d):\n",row1,col1);
  for(i=0; i< row1; i++)
  {
  	for(j=0; j< col1; j++)
  	{
  		scanf("%d", &MAT1[i][j]);
  	}
  }
  //REQUEST MAT2 VALUES
  printf("Please enter the values for the second matrix (%dx%d):\n",row2,col2);
  for(i=0; i< row2; i++)
  {
  	for(j=0; j< col2; j++)
  	{
  		scanf("%d", &MAT2[i][j]);
  	}
  }
  printf("\n");
  int LargestDigitsMat1[col1]; //Array to store number with most digits in EACH column
  //array the size of the amount of columns in the FIRST matrix.
  int col;
  for(col = 0; col < col1; col++){ //populate LargestDigitsMat1
    LargestDigitsMat1[col] = LargestDigitsPerCol(MAT1,row1,col); //using my helper function
  }
  printFormattedMatrix(MAT1,row1,col1, LargestDigitsMat1); //Now we can print our first matrix
  printf("\nmultiplied by\n");
  int LargestDigitsMat2[col2]; //Same array but for the second matrix
  for(col = 0; col < col2; col++){ //populate LargestDigitsMat2
    LargestDigitsMat2[col] = LargestDigitsPerCol(MAT2, row2, col);
  }
  printFormattedMatrix(MAT2, row2, col2, LargestDigitsMat2); //now we can correctly print our second matrix
  printf("\nequals\n");
  //CALCULATION BEGINS...
  for(i=0; i < row1; i++)
  {
  	for(j=0; j < col2; j++)
  	{
  		RESULT[i][j] = 0;
   		for(k=0; k<col1; k++)
  		  RESULT[i][j] = RESULT[i][j] + MAT1[i][k] * MAT2[k][j]; //Performing the multiplication
  	}
  }
  int LargestDigitsResult[col2];
  //Same concept as LargestDigitsMat1 but with the resultant matrix
  for(col = 0; col < col2; col++){ //populating the array
    LargestDigitsResult[col] = LargestDigitsPerCol(RESULT, row1, col);
  }
  printFormattedMatrix(RESULT,row1,col2,LargestDigitsResult); //now we can properly print out our result
  //Freeing the dynamically-allocated arrays, and then we are done!
  free(MAT1);
  free(MAT2);
  free(RESULT);
  return EXIT_SUCCESS;
}
