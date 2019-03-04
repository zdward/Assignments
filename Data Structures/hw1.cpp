#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cmath>
void flush_left(unsigned int width, char* inputfile, char* outfile); 
void flush_right(unsigned int width, char* inputfile, char* outfile); 
void full_justify(unsigned int width, char* inputfile, char* outfile); 
/* Each of these three functions above operate using similar logic
The first step is organizing a 2D vector where each sub-vector has words for elements
(Each sub-vector can be transformed into a single lined by summing the words together)
The next step is making sense of the 2D vector and printing it out accordingly
*/
int main(int argc, char* argv[]) { 
	if(argc!=5){ //checks correct number of arguments 
		return 1; 
	}
	bool isNumber = true; //boolean that argument 3 is valid
	bool isCommand = true; //boolean that argument 4 is valid
	//std::ofstream inFile(argv[2]); //opening the output file;
	std::string width_arg = argv[3]; //should be an integer width. e.g)  16, 15, etc.
	std::string command = argv[4]; //left_justify, right_justify, or full_justify
	for(unsigned int i = 0; i<width_arg.size(); ++i){
		if(!isdigit(width_arg[i]))
			isNumber = false; //if any character isnt a number, argument 3 is invalid
	}
	if(command!="full_justify" && command!="flush_left" && command!="flush_right"){
		isCommand = false;
	}
	if(!isNumber || !isCommand){ //makes sure the last two arguments are valid
		std::cerr << "Make sure arguments 3 and 4 are valid" << std::endl;
		exit(1);
	}
	unsigned int wid = std::atoi(argv[3]); //the specified width
	if(command=="flush_left")
		flush_left(wid,argv[1],argv[2]);
	else if(command=="flush_right")
		flush_right(wid,argv[1],argv[2]);
	else
		full_justify(wid,argv[1],argv[2]);	
}
void flush_left(unsigned int width, char* inputfile, char* outfile){ //creates left-justified box without top and bottom ascii borders
	std::string word; //
	std::string line = "";
	std::vector<std::vector<std::string> > text; //2D vector where each sub-vector represents a line of text
	std::vector<std::string> words; //will represent a sub_vector of text
	std::ifstream inFile(inputfile);
	std::ofstream oFile; 
	oFile.open(outfile);
	std::vector<std::string> dummy; //Dummy vector which represents a line of text in 'text' 2D vector
	text.push_back(dummy);
	int spaces;
	int lineNum = 0;
	std::string Border(width+4,'-');
	oFile << Border << std::endl;
	while(inFile>>word){ //sets up the 2D vector text
		if((line.size()+word.size())>width){
			if(word.size()>width){ //takes care of the hyphen case in which one word is too large for one line

				int skipForward = width; //value to be incremented so that the hyphenated word can be properly printed
				int NumLinesNeeded = ceil(float(word.size())/float((width-1))); //width-1 accounts for the hyphens that will be added, ceil rounds up
				int num = 1; //iterator to be used
				std::string toAdd = word.substr(0,width-1)+"-"; //first cut-off of the long word
				if(line.size()==0) //adds the first hyphen cut-off to the 2D vector
					text[lineNum].push_back(toAdd); //adding it to the vector
				else{ 
					lineNum+=1;
					std::vector<std::string> q; //dummy vector
					text.push_back(q); //creates new empty space for hyphen cut-off to be added to
					text[lineNum].push_back(toAdd); //adds hyphen cut-off to NEXT line, hence the dummy vector being added before 
				}
				unsigned int charsLeft = word.size() - (width)+1; //keeping track of the characters left in the large word
				while(num<NumLinesNeeded){ 
					lineNum+=1;
					std::vector<std::string> w; 
					text.push_back(w); //adds a new empty line to the vector to be filled in by the next iteration
					num+=1;
					if(charsLeft<width){ //adds final portion of hyphenated word to the 2D vector
						toAdd = word.substr(skipForward-2,charsLeft+2);
						text[lineNum].push_back(toAdd);
						line = toAdd+" ";
					} else { 
						toAdd = word.substr(skipForward-1,width-1);
						charsLeft-=width+1; //decrementing charsLeft accordingly 
						std::string addHyphen = toAdd + "-"; 
						text[lineNum].push_back(addHyphen); //adds hyphenated cut-off to 2D vector
						skipForward+=width; //incrementing forward in the word accordingly, skipping over what was already covered
						if(num==NumLinesNeeded) 
							line = word+" "; //making sure to add that space at the end to avoid wrong output
						}
					}
				} //End of the block which handles hyphens/words that are too large for the specified width
			else{ 
			lineNum+=1; //increment line to access in 'text'
			std::vector<std::string> w;
			text.push_back(w);
			text[lineNum].push_back(word);
			line=word+" ";
			}
		}
		else{
			text[lineNum].push_back(word);
			line+=word+" ";
		}	
	}
	for (int i=0; i <=lineNum; ++i) { //This loop handles actually printing out the 2D vector we set up before.
		words = text[i];
		line = "";
		oFile<<"| ";
		for(unsigned int j = 0; j < words.size(); ++j){ //transforms 1D vector into a line string with one space in between each word
			if(j!=words.size()-1){
				line+=words[j] + " ";
			}
			else{
				line+=words[j];
			}
		}
		if(i==lineNum){ //when we reach the end
			spaces = width-line.size();
			oFile << line << std::string(spaces,' ') << " |" << std::endl;
			break;
		}
		if(words.size()==1){ //The case in which a line only has one word
		spaces = width-line.size();
		oFile<<words[0]<<std::string(spaces,' ') << " |" << std::endl;
		}

		else if(words.size()>1){ //The case in which a line has more than one word
			 spaces = width-line.size();
			oFile << line << std::string(spaces,' ')  << " |" << std::endl;
		}
	}
	oFile << Border << std::endl; //print out the bottom border before we close the file
	oFile.close();
}
void flush_right(unsigned int width, char* inputfile, char* outfile){ //logic for this function is similar to flush_left
	std::string word;
	std::string line = "";
	std::vector<std::vector<std::string> > text; //2D vector where each sub-vector represents a line of text
	std::vector<std::string> words; //will represent a sub_vector of text
	std::ifstream inFile(inputfile);
	std::ofstream oFile;
	oFile.open(outfile);
	std::vector<std::string> dummy; //Dummy vector which represents a line of text in 'text' 2D vector
	text.push_back(dummy);
	int spaces;
	int lineNum = 0;
	std::string Border(width+4,'-');
	oFile << Border << std::endl;
	while(inFile>>word){ //sets up the 2D vector text
		if((line.size()+word.size())>width){
			if(word.size()>width){ //takes care of the hyphen case in which one word is too large for one line
				int skipForward = width;
				int NumLinesNeeded = ceil(float(word.size())/float((width-1))); //width-1 accounts for the hyphens that will be added, ceil rounds up
				int num = 1;
				std::string toAdd = word.substr(0,width-1)+"-"; //first cut-off of the long word
				if(line.size()==0)
					text[lineNum].push_back(toAdd); //adding it to the vector
				else{
					lineNum+=1;
					std::vector<std::string> q; //dummy vector
					text.push_back(q);
					text[lineNum].push_back(toAdd);
				}
				unsigned int charsLeft = word.size() - (width)+1;
				while(num<NumLinesNeeded){
					lineNum+=1;
					std::vector<std::string> w; 
					text.push_back(w); //adds a new empty line to the vector to be filled in by the next iteration
					num+=1;
					if(charsLeft<width){ //when we have reached the end of our hyphenated word...logic similar to that in flush_left
						toAdd = word.substr(skipForward-2,charsLeft+2); 
						text[lineNum].push_back(toAdd);
						line = toAdd+" ";
					} else {
						toAdd = word.substr(skipForward-1,width-1);
						charsLeft-=width+1;
						std::string addHyphen = toAdd + "-";
						text[lineNum].push_back(addHyphen);
						skipForward+=width;
						if(num==NumLinesNeeded)
							line = word+" ";
						}
					}
				}
			else{
			lineNum+=1;
			std::vector<std::string> w;
			text.push_back(w);
			text[lineNum].push_back(word);
			line=word+" ";
			}
		}
		else{
			text[lineNum].push_back(word);
			line+=word+" ";
		}	
	}
	for (int i=0; i <=lineNum; ++i) {
		words = text[i];
		line = "";
		oFile<<"| ";
		for(unsigned int j = 0; j < words.size(); ++j){ //transforms 1D vector into a line string with one space in between each word
			if(j!=words.size()-1)
				line+=words[j] + " ";
			else
				line+=words[j];
		}
		if(i==lineNum){
			spaces = width-line.size();
			oFile << std::string(spaces,' ') << line << " |" << std::endl;
			break;
		}
		if(words.size()==1){ //The case in which a line only has one word
		spaces = width-line.size();
		oFile<< std::string(spaces,' ') << words[0] << " |" << std::endl;
		}

		else if(words.size()>1){ //The case in which a line has more than one word
			 spaces = width-line.size();
			oFile << std::string(spaces,' ') << line << " |" << std::endl;
		}
	}
	oFile << Border << std::endl;
	oFile.close();
}
void full_justify(unsigned int width, char* inputfile, char* outfile){
	std::string word;//word taken in and reset using the input operator >>
	std::vector<std::string> words; //will represent a sub_vector of text
	std::vector<std::vector<std::string> > text; //2D vector where each sub-vector represents a line of text
	std::string line = ""; //line to be constructed by adding together each element of the sub-vectors in text and to be used in calculations(size-related)
	int spaces; //to be calculated, spaced in between each word
	int extra; //extra spaces that need to be assigned to the left most words
	int lineNum=0; 
	std::ifstream inFile(inputfile); //opening the input file
	std::ofstream oFile;
	oFile.open(outfile); //opening the output file
	std::string Border(width+4,'-'); //creating the top and bottom border with the formula length=width+4
	oFile << Border << std::endl; 
	std::vector<std::string> v; //temporary dummy vector that will be used so that we can index 'text'
	text.push_back(v); //makes it so the text vector starts out with at least one sub-vector
	while(inFile>>word){ //sets up the 2D vector text
		if((line.size()+word.size())>width){ 
			if(word.size()>width){ //takes care of the hyphen case in which one word is too large for one line
				int skipForward = width; //value to be incremented so that the hyphenated word can be properly printed
				int NumLinesNeeded = ceil(float(word.size())/float((width-1))); //width-1 accounts for the hyphens that will be added, ceil rounds up
				int num = 1; //iterator to be used 
				std::string toAdd = word.substr(0,width-1)+"-"; //first cut-off of the long word
				if(line.size()==0) //takes care of adding the first hyphenated cut-off to the 2D vector
					text[lineNum].push_back(toAdd); //adding it to the vector
				else{
					lineNum+=1;
					std::vector<std::string> q; //dummy vector
					text.push_back(q);
					text[lineNum].push_back(toAdd); //add the hyphenated cut-off on the NEXT line!! Not current line.
				}
				unsigned int charsLeft = word.size() - (width)+1; //keeping track of the characters left
				while(num<NumLinesNeeded){ //takes care of adding the word which will include one of more hyphens to the 2D text vector
					lineNum+=1;
					std::vector<std::string> w; 
					text.push_back(w); //adds a new empty line to the vector to be filled in by the next iteration
					num+=1;
					if(charsLeft<width){ //takes care of adding to the 2D Vector the final portion of the hyphenated word
						toAdd = word.substr(skipForward-2,charsLeft+2);
						text[lineNum].push_back(toAdd);
						line = toAdd+" ";
					} else { //takes care of every other portion
						toAdd = word.substr(skipForward-1,width-1);
						charsLeft-=width+1; //decrementing charsLeft accordingly
						std::string addHyphen = toAdd + "-"; 
						text[lineNum].push_back(addHyphen);
						skipForward+=width;
						if(num==NumLinesNeeded)
							line = word+" ";
						}
					}
				}
			else{
			lineNum+=1; 
			std::vector<std::string> w;
			text.push_back(w);
			text[lineNum].push_back(word);
			line=word+" ";
			}
		}
		else{
			text[lineNum].push_back(word);
			line+=word+" ";
		}	
	}
	for (int i=0; i <=lineNum; ++i) {
		words = text[i];
		line = "";
		oFile<<"| ";
		for(unsigned int j = 0; j < words.size(); ++j){ //transforms 1D vector into a line string with one space in between each word
			if(j!=words.size()-1)
				line+=words[j] + " ";
			else
				line+=words[j];
		}
		if(i==lineNum){
			spaces = width-line.size();
			oFile << line << std::string(spaces,' ') << " |" << std::endl;
			break;
		}
		if(words.size()==1){ //The case in which a line only has one word
		spaces = width-line.size();
		oFile<<words[0] << std::string(spaces,' ') << " |" << std::endl;
		}
		else if(words.size()>1){ //The case in which a line has more than one word
		spaces = (width-line.size())/(words.size()-1);
		if(float(width-line.size())/float(words.size()-1)==spaces){ //case #1, there are just the right amount of spaces
			for(unsigned int i = 0; i<words.size(); ++i){ //loop through the words vector
				if(words[i]!=words[words.size()-1]) //if youre not on the last word
					oFile<<words[i] + std::string(spaces+1,' '); //print out the word with the right amount of spaces
				else {
					oFile<< words[i] << " |" << std::endl; //print out the last word
					words.clear();
				}
			}
		}
		 else if (float(width-line.size())/float(words.size()-1) > spaces and spaces!=0){ //case #2, there are extra spaces
			extra=(width-line.size())-((words.size()-1)*spaces);
			for(unsigned int i = 0; i<words.size(); ++i){
				if(words[i]!=words[words.size()-1]){
					oFile<<words[i] + std::string(spaces+1,' ');
					if(extra>0){ //takes care of all of the extra spacing. Adds them leftmost until there are no more
						oFile<<std::string(1, ' ');
						extra-=1;
					}
				} else {
					oFile<< words[i] << " |" << std::endl; //print out the last word
					words.clear();
				}
			}
		} 
		 else if (float(width-line.size())/float(words.size()-1) > spaces and spaces==0) { //case #3, there arent enough spaces
			spaces = width-line.size(); //leftover spaces
			for(unsigned int i = 0; i<words.size(); ++i){ //simply add the spaces to the leftmost words
				if(i!=words.size()-1){
					oFile <<words[i] + std::string(1, ' ');
					if(spaces>0){
						oFile <<std::string(1, ' ');
						spaces-=1;
					}
				} else {
					oFile << words[i] << " |" << std::endl; //print out the last word
					words.clear();
				}
			}
		}			
		}		
		}
		oFile << Border << std::endl;
		oFile.close();
}
