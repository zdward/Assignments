============COMPUTER ARCHITECTURE README============

(1) matrixMultiply.c -- This program multiples two matrices of specified size in C. Command line arguments are:
Number of rows in matrix 1, number of cols in matrix 1, number of rows in matrix 2, number of cols in matrix 2.


(2) matrixMultiply.s -- matrixMultiply.c re-written in MIPS Assembly language. Instead of having command line arguments,
the user inputs n, the number of rows in matrix 1, m, the number of cols in matrix 1/number of rows in matrix2, and k, the
number of cols in matrix 2.


(3) arithmetic_to_mips.c -- This program takes a python-type variable assignment statement involving arithmetic and 
converts it to a series of mips instructions. 
Example output: 

bash$ ./a.out         
Please enter a valid C assignment statement:     
f = g + h - 42;      
The MIPS pseudocode is:      
add $t0,$s1,$s2      
sub $s0,$t0,42     
bash$ ./a.out     
Please enter a valid C assignment statement:      
x = q - 12 + j;        
The MIPS pseudocode is:        
sub $t0,$s1,12    
add $s0,$t0,$s2    
bash$ ./a.out     
Please enter a valid C assignment statement:     
a = x - y + 13 + x - a;     
The MIPS pseudocode is:     
sub $t0,$s1,$s2     
add $t1,$t0,13    
add $t2,$t1,$s1     
sub $s0,$t2,$s0    

(4) cache_simulator.c -- This program written in C simulates how a cache of size 256 will store a series of memory addresses in a provided text document.    The simulator works for a direct-mapped cache, 2-way associative cache and a 4-way associative cache. The simulator also provides you the option of using Belady's algorithm or the Least-Recently-Used algorithm for replacement in the cache.   

Command line arguments: N-way(associativity), Belady/LRU, filename.txt    

Example output:   
bash$ ./a.out 2 LRU ex01.dat   
Cache size: 256    
Cache associativity: 2   
Cache sets: 128   
Cache algorithm: LRU   
1 (miss)   
33 (miss)   
2 (miss)   
34 (miss)   
65 (miss)   
1 (hit)   
66 (miss)  
2 (hit)   
97 (miss)   
65 (hit)   
Cache accesses: 10   
Cache hits: 3     
Cache misses: 7     
Overall hit rate: 0.300000    

  



