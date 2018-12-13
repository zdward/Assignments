#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*CSCI 2500 -- Homework 06 by Zachary Ward
Cache Simulator
*/
/*Used to determine if we've hit every element in the given set*/
int isFilled(int* array, int size){
	int filled = 1;
	int i;
	for(i = 0; i < size; i++){
		if(array[i]!=1) filled = 0;
	}
	return filled;
}
/*Used in LRU_index and beladys_index*/
int determineSize(int* array){
	int size = 0;
	int i;
	for(i = 0; i < 4; i++){
		if(array[i]!=0) size++;
		else break;
	}
	return size;
}
/*Given an array of mem_addresses in a certain set, this function tells you
which index (within this set) to remove/replace with the new memory address*/
int beladys_index(int* mem_addresses,int* input_array, int input_size, int current_index){
	int seenSize = determineSize(mem_addresses); //determine amount of elements we have to look for
	int seen_elements[seenSize];
	int max_index = 0;
	int i;
	for(i = 0; i < seenSize; i++){
		seen_elements[i] = 0;
	}
	i = current_index;
	/*While we haven't seen everything and we havent surpassed our input*/
	while(!isFilled(seen_elements,seenSize) && i < input_size){
		int j;
		for(j = 0; j < 4; j++){
			if(input_array[i]==mem_addresses[j]){
				max_index = j;
				seen_elements[j] = 1; //properly adjust boolean array
			}
		}
		i++;
	}
	/*Return the index within the set to replace*/
	int a;
	/*Last minute adjustment to max_index*/
	for(a = 0; a < seenSize; a++){
		if(seen_elements[a]==0){
			max_index = a;
		}
	}
	return max_index;
}
int LRU_index(int* mem_addresses,int* input_array,int input_size,int current_index){
	int seenSize = determineSize(mem_addresses); //determine amount of elements we have to look for
	int seen_elements[seenSize];
	int least_index = 9999; //set least_index to something very large at first
	int a;
	for(a = 0; a < seenSize; a++){
		seen_elements[a] = 0;
	}
	int i = current_index;	
	/*While we haven't seen everything we are looking for. I.e, if we have {1,129}
	in our set, we dont stop looping back through our inputs until we have seen
	the number 1 once and the number 129 once*/
	while(!isFilled(seen_elements,seenSize)){
		int j;
		for(j = 0; j < 4; j++){ //loop through mem_addresses
			if(input_array[i]==mem_addresses[j]){ //if current input == place in mem_addresses
				least_index = j;
				seen_elements[j] = 1; //properly adjust boolean array
			}
		}
		i--;
	}
	return least_index;
}
/*We use this to determine whether or not the mem_address is in the cache.
Standard O(n) algorithm, may be more expensive than we need, but not to worry
for now.*/
int linear_search(int* cache_array, int mem_address){ 
	int i;
	for(i = 0; i < 1024; i++){
		if(cache_array[i] == mem_address) return 1;
	}
	return 0;
}
void insert(int* cache,int mem_address,int associativity,int* input_array,int input_size,
	int current_index, char* algorithm){
	int cache_sets = 256/associativity;
	int index = mem_address % cache_sets;
	/*Beladys algorithm*/
	if(cache[index]!=0){
		int timesIncremented = 0;
		while(timesIncremented < associativity-1 && cache[index]!=0){
			index+=cache_sets;
			timesIncremented++; 
		}
		if(cache[index]!=0){
			int mem_addresses[4] = {0,0,0,0};
			int index2 = mem_address % cache_sets;
			int i = 0;
			/*Fetch all memory addresses in the current set*/
			while(i < associativity){
				mem_addresses[i] = cache[index2+(i*cache_sets)]; //fetches each memory address
				i++;
			}
			/*Returns the memory address index used furthest into the future.*/
			int set_index = 0;
			if(strcmp(algorithm,"Belady")==0){
				set_index= beladys_index(mem_addresses,input_array,input_size,current_index);
			}
			else if(strcmp(algorithm,"LRU")==0){
				set_index = LRU_index(mem_addresses,input_array,input_size,current_index);
			}	
			int index_to_remove = (mem_address % cache_sets) + (set_index*cache_sets);
			cache[index_to_remove] = mem_address;
		
		}else{
			cache[index] = mem_address;
		}
	}
	else{
		cache[index] = mem_address;
	}

}
int main(int argc, char** argv){
	if(argc!=4){
		perror("Wrong number of command line arguments!");
		return EXIT_FAILURE;
	}
	int* cache = (int*) malloc(1024*sizeof(int)); //Our cache representation
	int associativity = atoi(argv[1]);
	FILE* file = fopen(argv[3],"r"); 
	char numbers[1024]; //We use this to achieve our input array.
	int input_numbers[1024]; //This contains our input, i.e {1,23,65...} etc.
	int i;
	for(i = 0; i < 1024; i++){ //Equivalent to memset (but working instead of not working)
		input_numbers[i] = 0;
	}
	int input_index = 0;
	int memory_accesses = 0;
	int num_hits = 0;
	int num_misses = 0;
	while(fgets(numbers,1024,file)){ //read in each line
		memory_accesses++;
		numbers[strlen(numbers)-1] = 0; //To get rid of the new line character
		input_numbers[input_index] = atoi(numbers);
		input_index++;
	}
	fclose(file);
	/*Below is where we actually handle hit/misses and dealing with the cache*/
	i = 0;
	printf("Cache size: 256\n");
	printf("Cache associativity: %d\n", associativity);
	printf("Cache sets: %d\n", 256/associativity);
	printf("Cache algorithm: %s\n", argv[2]);
	while(input_numbers[i]!=0){
		int hit_or_miss = linear_search(cache,input_numbers[i]); //1 if we have a hit, 0 if we have a miss
		//printCache(cache);
		if (hit_or_miss == 0){
			num_misses++;
			printf("%d (miss)\n", input_numbers[i]);
			insert(cache,input_numbers[i],associativity,input_numbers,memory_accesses,i,argv[2]);
		}
		else{
			printf("%d (hit)\n", input_numbers[i]);
			num_hits++;
		}
		i++;
	}
	printf("Cache accesses: %d\n", memory_accesses);
	printf("Cache hits: %d\n", num_hits);
	printf("Cache misses: %d\n", num_misses);
	float float_hits = num_hits * 1.0; //So we can do float division
	float hit_rate = float_hits/memory_accesses;
	printf("Overall hit rate: %f\n", hit_rate);
	free(cache); //Freeing the dynamic memory we've used
	return 0;
}
