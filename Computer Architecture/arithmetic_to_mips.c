#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*HW02 By Zachary Ward
-- MIPS Pseudocode generator*/

int isInteger(char c){ //Tells us whether a certain character is an int
  if(isdigit(c))
    return 1;
  else
    return 0;
}
/*This function stores the letters in the input in an array.
The index of each element corresponds to the register number.*/
void storeLetters(char* toTranslate, char* savedArray){
  int savedArrayIndex = 0;
  int i = 0;
  while(toTranslate[i]!=';'){
    if(isalpha(toTranslate[i])){
      int j;
      int found = 0;
      for(j = 0; j < 50; j++){ //arbitrary endpoint.
        if(toTranslate[i]==savedArray[j])
          found = 1;
      }
      if(!found){
        savedArray[savedArrayIndex] = toTranslate[i];
        savedArrayIndex++;
      }
    }
    i++;
  }
}
/*This will help us determine what register number we output,
as the register number is just our index. Thats how i have
this array set up.*/
int getIndexInSavedArray(char element, char* savedArray){
  int i;
  int index;
  for(i = 0; i < 50; i++){
    if(savedArray[i]==element)
      index = i;
  }
  return index;
}
/*Checks if C statement is syntactically correct.*/
int hasSemicolon(char* toTranslate){
  int i;
  int hasSemi = 0;
  for(i = 0; i < 100; i++){
    if(toTranslate[i]==';')
      hasSemi = 1;
  }
  return hasSemi;
}
/*
For the functions below, the index is AT the + or - operator.
We know there is either a letter or number to the left AND right
of the operator logically. These functions check whether or not we
encounter numbers.
*/
int isNumberToLeft(char* toTranslate, int index){ //treated as bool function
  index-=2; //move to the next set of characters, leftward
  if(!isdigit(toTranslate[index]))
    return 0;
  else
    return 1;
}
int isNumberToRight(char* toTranslate, int index){ //treated as bool function
  index+=2; //move to the next set of characters, rightward
  if(!isdigit(toTranslate[index]))
    return 0;
  else
    return 1;
}
/*These two functions allow us to know how long the number
we are about to deal with is. This is very nice to know.*/
int getLengthLeft(char* toTranslate, int index){
  index-=2;
  int count = 0;
  while(index!=0){ //this should tell us the size of our number
    if(isdigit(toTranslate[index]))
      count++;
    else
      break;
    index--;
  }
  if(index==0 && isdigit(toTranslate[index]))
    count++;
  return count;
}
int getLengthRight(char* toTranslate, int index){
  index+=2;
  int count = 0;
  while(isdigit(toTranslate[index])){
    count++;
    index++;
  }
  return count;
}
/*
For the two functions below, we acquire the number
of interest and return it.
*/
int acquireLeft(char* toTranslate, int index, int size){
  int numToReturn;
  index-=2;
  char num[size+1];
  num[size]='\0';
  while(size!=0){ //stores the number in the char array called num
    num[size-1] = toTranslate[index];
    size--;
    index--;
  }
  sscanf(num,"%d",&numToReturn);
  return numToReturn;
}
int acquireRight(char* toTranslate, int index, int size){
  int numToReturn;
  index+=2;
  char num[size+1];
  num[size]='\0';
  int i = 0;
  while(i<size){
    num[i] = toTranslate[index];
    i++;
    index++;
  }
  sscanf(num,"%d",&numToReturn);
  return numToReturn;
}
/*This function parses a string and informs us
how many +'s and - signs we have.  This is helpful
because the number of MIPS lines we have == number of operations.'*/
int numOperations(char *stated){
  int ops = 0;
  int i = 0;
  while(stated[i]!='\0'){ //while we havent hit the end of the string
    if(stated[i]=='+' || stated[i]=='-'){ //if its an operation
      ops++; //increment operation count
      i++; //increment iteration variable
    }
    else
      i++;
  }
  return ops; //return our count of operations
}

void translate(char* toTranslate, char* s_Array){
  int numLines = numOperations(toTranslate); //Tells us how many MIPS lines we need
  int i = 0; //iteration variable
  int bool_Printed_Once = 0;
  int t_Used = 0; //Number of $t registers used
  //int s_Used = 1; //Number of $s registers used
  while(toTranslate[i]!=';'){
    if(toTranslate[i]=='+' && numLines > 1){ //case 1
        if(!bool_Printed_Once){ //if you havent used any temps yet
          if(isNumberToLeft(toTranslate,i)){
            int numLength = getLengthLeft(toTranslate,i);
            int num = acquireLeft(toTranslate, i,numLength);
            int index = i+2;
            int importantNumber = getIndexInSavedArray(toTranslate[index], s_Array); //importantNumber = $s reg number.
            printf("add $t%d,%d,$s%d\n", t_Used, num, importantNumber);
            numLines--;
            t_Used++;
          }
          else if(isNumberToRight(toTranslate,i)){
            int numLength = getLengthRight(toTranslate,i);
            int num = acquireRight(toTranslate,i,numLength);
            int index = i-2;
            int importantNumber = getIndexInSavedArray(toTranslate[index], s_Array); //importantNumber = $s reg number.
            printf("add $t%d,$s%d,%d\n", t_Used, importantNumber, num);
            numLines--;
            t_Used++;
          }
          else{
            int index1 = i-2;
            int index2 = i+2;
            int importantNumber1 = getIndexInSavedArray(toTranslate[index1],s_Array); //importantNumber = $s reg number.
            int importantNumber2 = getIndexInSavedArray(toTranslate[index2],s_Array);
            printf("add $t%d,$s%d,$s%d\n", t_Used, importantNumber1, importantNumber2);
            t_Used++;
            numLines--;
          }
        }
        else{ //if you HAVE used a temp before, numbertoLeft is not a case here.
          if(isNumberToRight(toTranslate,i)){ //if a number is present (to the left is not a test case here)
            int numLength = getLengthRight(toTranslate,i);
            int num = acquireRight(toTranslate,i,numLength);
            printf("add $t%d,$t%d,%d\n", t_Used, t_Used-1, num);
            t_Used++;
            numLines--;
          }
          else{ //no number
            int index = i+2;
            int importantNumber = getIndexInSavedArray(toTranslate[index],s_Array); //importantNumber = $s reg number.
            printf("add $t%d,$t%d,$s%d\n", t_Used, t_Used-1, importantNumber);
            t_Used++;
            numLines--;
          }
        }
        bool_Printed_Once = 1;
      }
    else if(toTranslate[i]=='+' && numLines == 1){ //case 2
      if(t_Used > 0) {   //if its your last line, but other lines have preceded
        if(isNumberToRight(toTranslate,i)){
          int numLength = getLengthRight(toTranslate,i);
          int num = acquireRight(toTranslate,i,numLength);
          printf("add $s0,$t%d,%d\n", t_Used-1, num);
          numLines--;
        }
        else{
          int index = i+2;
          int importantNumber = getIndexInSavedArray(toTranslate[index],s_Array); //importantNumber = $s reg number.
          printf("add $s0,$t%d,$s%d\n", t_Used-1, importantNumber);
          numLines--;
        }
      }
      else if(t_Used==0){ //if its your last and only line
        if(isNumberToLeft(toTranslate,i)){
          int numLength = getLengthLeft(toTranslate,i);
          int num = acquireLeft(toTranslate, i,numLength);
          int index = i+2;
          int importantNumber = getIndexInSavedArray(toTranslate[index],s_Array); //importantNumber = $s reg number.
          printf("add $s0,%d,$s%d\n",num,importantNumber);
          numLines--;
        }
        else if(isNumberToRight(toTranslate,i)){
          int numLength = getLengthRight(toTranslate,i);
          int num = acquireRight(toTranslate,i,numLength);
          int index = i-2;
          int importantNumber = getIndexInSavedArray(toTranslate[index],s_Array); //importantNumber = $s reg number.
          printf("add $s0,$s%d,%d\n",importantNumber,num);
          numLines--;
        }
        else{
          int index1 = i-2;
          int index2 = i+2;
          int importantNumber1 = getIndexInSavedArray(toTranslate[index1],s_Array); //importantNumber = $s reg number.
          int importantNumber2 = getIndexInSavedArray(toTranslate[index2],s_Array); //importantNumber = $s reg number.
          printf("add $s0,$s%d,$s%d\n", importantNumber1, importantNumber2);
          numLines--;
        }
      }
    }
    if(toTranslate[i]=='-' && numLines > 1){ //case 3
      if(!bool_Printed_Once){ //if you havent used any temps yet
        if(isNumberToLeft(toTranslate,i)){ //if there is a number to the left of our '-'
          int numLength = getLengthLeft(toTranslate,i); //get the length of the number to pass in
          int num = acquireLeft(toTranslate, i,numLength); // acquire number
          int index = i+2;
          int importantNumber = getIndexInSavedArray(toTranslate[index],s_Array);
          printf("sub $t%d,%d,$s%d\n", t_Used, num, importantNumber);
          numLines--;
          t_Used++;
        }
        else if(isNumberToRight(toTranslate,i)){
          int numLength = getLengthRight(toTranslate,i);
          int num = acquireRight(toTranslate,i,numLength);
          int index = i-2;
          int importantNumber = getIndexInSavedArray(toTranslate[index],s_Array);
          printf("sub $t%d,$s%d,%d\n", t_Used, importantNumber, num);
          numLines--;
          t_Used++;
        }
        else{
          int index1 = i-2;
          int index2 = i+2;
          int importantNumber1 = getIndexInSavedArray(toTranslate[index1],s_Array);
          int importantNumber2 = getIndexInSavedArray(toTranslate[index2],s_Array);
          printf("sub $t%d,$s%d,$s%d\n", t_Used, importantNumber1, importantNumber2);
          t_Used++;
          numLines--;
        }

      }
      else{ //if you HAVE used a temp before
        if(isNumberToRight(toTranslate,i)){
          int numLength = getLengthRight(toTranslate,i);
          int num = acquireRight(toTranslate,i,numLength);
          printf("sub $t%d,$t%d,%d\n", t_Used, t_Used-1, num);
          numLines--;
          t_Used++;
        }
        else{
          int index = i+2;
          int importantNumber = getIndexInSavedArray(toTranslate[index],s_Array);
          printf("sub $t%d,$t%d,$s%d\n", t_Used, t_Used-1, importantNumber);
          t_Used++;
          numLines--;
        }
      }
      bool_Printed_Once = 1;
    }
    else if(toTranslate[i]=='-' && numLines==1){ //case 4
      if(t_Used > 0){ //if its your last line, but other lines have preceded
        if(isNumberToRight(toTranslate,i)){
          int numLength = getLengthRight(toTranslate,i);
          int num = acquireRight(toTranslate,i,numLength);
          printf("sub $s0,$t%d,%d\n", t_Used-1, num);
          numLines--;
        }
        else{
          int index=i+2;
          int importantNumber = getIndexInSavedArray(toTranslate[index],s_Array);
          printf("sub $s0,$t%d,$s%d\n", t_Used-1, importantNumber);
          numLines--;
        }
      }
      else if(t_Used == 0){ //if its your last and only line
        if(isNumberToLeft(toTranslate,i)){
          int numLength = getLengthLeft(toTranslate,i);
          int num = acquireLeft(toTranslate, i,numLength);
          int index=i+2;
          int importantNumber = getIndexInSavedArray(toTranslate[index],s_Array);
          printf("sub $s0,%d,$s%d\n",num,importantNumber);
          numLines--;
        }
        else if(isNumberToRight(toTranslate,i)){
          int numLength = getLengthRight(toTranslate,i);
          int num = acquireRight(toTranslate,i,numLength);
          int index=i-2;
          int importantNumber = getIndexInSavedArray(toTranslate[index],s_Array);
          printf("sub $s0,$s%d,%d\n",importantNumber,num);
          numLines--;
        }
        else{
          int index1=i-2;
          int index2=i+2;
          int importantNumber1 = getIndexInSavedArray(toTranslate[index1],s_Array);
          int importantNumber2 = getIndexInSavedArray(toTranslate[index2],s_Array);
          printf("sub $s0,$s%d,$s%d\n", importantNumber1, importantNumber2);
          numLines--;
        }
      }
    }
    i++;
  }
}

int main(){
  char* statement; //to hold our C statement input
  char* savedArray; //The array above is intended to hold all LETTERS read in. Index+1 corresponds to register number.
  statement = (char*)malloc(256); //allocating some random size
  printf("Please enter a valid C assignment statement:\n");
  fgets(statement,256,stdin);
  if(hasSemicolon(statement)){
    printf("The MIPS pseudocode is:\n");
    savedArray = (char*)malloc(256);
    storeLetters(statement,savedArray);
    translate(statement, savedArray);
  }
  else
    perror("This is not a valid C statement!\n");
  free(statement);
  free(savedArray);
  return EXIT_SUCCESS;
}
