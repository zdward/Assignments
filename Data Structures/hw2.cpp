#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Scoresheet.h"
#include <cstring>
void SortLines(char* inputfile, std::vector<std::vector<std::string> > &toSort);
bool sortCol(const std::vector<std::string> &v1, const std::vector<std::string> &v2);
int main(int argc, char* argv[]){
	if(argc!=4)
		return 1;
	std::vector<std::vector<std::string> > sortedLines; //holds name info and score info
	SortLines(argv[1],sortedLines); //constructs and sorts sortedLines alphabetically
	Scoresheet scores(sortedLines,argv[2]);
	if(strcmp(argv[3],"standard")==0)
		scores.display(true); //standard = true --> display standard
	else if(strcmp(argv[3],"custom")==0)
		scores.display(false); //standard = false --> display custom
	else{
		std::cerr<<"Not a valid argument" << std::endl;
		exit(1);
	}
}
bool sortCol(const std::vector<std::string> &v1, const std::vector<std::string> &v2){ //helper function for sorting each vector in the 2D vector
	if(v1[1] < v2[1]) //returns true if the last name is alphabetically first
		return true;
	else if(v1[1]==v2[1]){ //if the last names are the same
		if(v1[0] < v2[0]) //returns true if the first name is alphabetically first
			return true;
		else //otherwise returns false
			return false;
	}
	else //otherwise returns false
		return false;
}
void SortLines(char* inputfile, std::vector<std::vector<std::string> > &toSort){ //creates and sorts 2D Vector alphabetically
	std::ifstream inFile(inputfile); //opening the input file
	std::string line; //line to be constantly reset
	std::vector<std::string> words_in_line; //looks like {"George", "Smith", "9", "1", "10", "8", "2", "10"...} and will be constantly reset
	while(getline(inFile,line)){ //constructs the 2D vector
		std::string toAdd = "";
		for(unsigned int i = 0; i < line.size(); ++i){ //expected result: vector --> {"George", "Smith", "9", "1", "10", "8", "2", "10"...} per sub-vector
			if(line[i]!=' '){
				toAdd+=line[i];
				if(i==line.size()-1)
					words_in_line.push_back(toAdd);
			}
				
			else{
				words_in_line.push_back(toAdd); 
				toAdd="";
			}
		}
		toSort.push_back(words_in_line); //adding the 1D temp vector to the 2D vector
		words_in_line.clear(); //resetting words_in_line
	}
	sort(toSort.begin(), toSort.end(), sortCol); //once the 2D vector toSort is constructed, sort it using the helper function I implemented
}

