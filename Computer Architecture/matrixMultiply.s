.data
n: .word 4
m: .word 4
k: .word 4
prompt1: .asciiz "Please enter values for n, k, and m:\n"
prompt2: .asciiz "Please enter values for the first matrix ("
prompt3: .asciiz "Please enter values for the second matrix ("
x: .asciiz "x"
rightparen: .asciiz "):\n"
newline: .asciiz "\n"
leftBrace: .asciiz "["
rightBrace: .asciiz "\t]\n"
tab: .asciiz "\t"
mult_by: .asciiz "multiplied by\n"
equals: .asciiz "equals\n"
.text
main:
#asks for n, m and k
li $v0, 4
la $a0, prompt1
syscall

#Grabs the value of n
li $v0, 5
syscall
sw $v0, n
#move $t0, $v0       #stores n in t0

#grabs the value of m
li $v0, 5
syscall
sw $v0, m
#move $t1, $v0       #stores m in t1

#grabs the value of k
li $v0, 5
syscall
sw $v0, k           #stores k in t2
#Please note that throughout the homework assignment...
#Input n = n, input k = m, input m = k
##########################################
matrixOne:
#print the first part of the prompt
li $v0, 4
la $a0, prompt2
syscall

#print out n
li $v0, 1
lw $a0, n
syscall

#print out an x
li $v0, 4
la $a0, x
syscall

#print out m
li $v0, 1
lw $a0, m
syscall

#print out right paren and the colon, finishing the statement
li $v0, 4
la $a0, rightparen
syscall
##########################################
####################################
allocMemOne:

lw $t0, n          	#t0 = n
lw $t1, m          	#t1 = m
multu $t0, $t1  	#t2 = n*m
mflo $t2
li $t3, 4          #t3 = 4
multu $t2, $t3   #t2 *= 4, giving us the correct number of bytes to alloc
mflo $t2

li $v0, 9            #srbk call (allocate heap memory)
move $a0, $t2        #allocate 4*n*m bytes
syscall

move $s0, $v0        #base address of mat1 array stored in s0
move $t9, $s0        #move through the array using t9
####################################################### t0 is a MEMORY ADDRESS!!! FIX!!!
readMatOne:
multu $t0, $t1       #n*m elements stored in t4
mflo $t4
li $t5, 1   			#main counter i = 1
readInLoop:
li $v0, 5
syscall
sw $v0, 0($t9)
seq $t6, $t5, $t4   #if i = n*m set 1 or 0 to t6
li $t7, 1
beq $t6, $t7, promptTwo
addi $t9, $t9, 4
addi $t5, $t5, 1
j readInLoop
#######################################################
promptTwo:
li $v0, 4
la $a0, prompt3
syscall                       #please enter values for the second matrix (

li $v0, 1                     #print out value of m
lw $a0, m
syscall

li $v0, 4                     #print out the multiplication symbol x
la $a0, x
syscall

li $v0, 1                     #print out k (we are still on the same line, remember)
lw $a0, k
syscall

li $v0, 4                     #print out ):\n
la $a0, rightparen
syscall
########################################################
allocMemTwo:

lw $t0, m         		#t0 = m
lw $t1, k         		#t1 = k
multu $t0, $t1    	#t2 = m*k
mflo $t2
li $t3, 4
multu $t2, $t3		#t2 = 4*m*k bytes
mflo $t2

li $v0, 9				#srbk allocate heap memory call
move $a0, $t2           #so we know to allocate 4*m*k bytes
syscall                 #allocate the memory

move $s1, $v0           #base address of the array pointed at by $s1
move $t9, $s1           #we shall increment t0 to move through the array
##########################################################
readMatTwo:
multu $t0, $t1       #m*k elements stored in t4
mflo $t4
li $t5, 1   			#i = 1
readInLoopTwo:
li $v0, 5
syscall
sw $v0 0($t9)
seq $t6, $t5, $t4       #if(i==m*k) --> $t6
li $t7, 1
beq $t6, $t7, display	#if($t6==1) --> finish
addi $t9, $t9, 4        #arrayPos++
addi $t5, $t5, 1        #i++
j readInLoopTwo

display:            #displays [...] multiplied by [...]
li $v0, 4			#we start by printing a new line
la $a0, newline
syscall

move $t0, $s0 #so we can loop through array1
move $t1, $s1 #so we can loop through array2


################################################# PRINTING OUT THE FIRST MATRIX
li $t9, 1 #rowcounter = 1
li $t2, 1 #colcounter = 1

rowloop:

li $v0, 4
la $a0, leftBrace
syscall

columnloop:
lw $t3, 0($t0) #store number at current index in t3
li $v0, 1 #this block prints out number
move $a0, $t3
syscall

lw $t5, m  #store number of columns in t5
seq $t4, $t5, $t2 #compare number of columns to counter
li $t6, 1
beq $t4, $t6, rightbr #if we have hit the last column, print out a \t]

li $v0, 4 #otherwise, simply print a tab
la $a0, tab
syscall

addi $t2, $t2, 1 #Increment the counter
addi $t0, $t0, 4 #Move ahead 4 bytes to the next integer
j columnloop #loop

rightbr:
li $v0, 4
la $a0, rightBrace
syscall

#comparing row counter to number of rows
lw $t7, n #number of rows stored in t7
seq $t4, $t7, $t9 #compared boolean value stored in t4 (0 or 1)
li $t6, 1
beq $t4, $t6, multipliedBy #if the row counter == # of rows, we are done, move on to next part
addi $t9, $t9, 1 #otherwise increment the row counter by 1
li $t2, 1 #reset colcounter to 1
addi $t0, $t0, 4 #move to the next number
j rowloop #jump to begining of the row loop


################################################# DONE PRINTING OUT THE FIRST MATRIX
multipliedBy:
li $v0, 4 			#print "multiplied by" with a new line
la $a0, mult_by
syscall
################################################## PRINT OUT SECOND MATRIX
li $t9, 1 #rowcounter = 1
li $t2, 1 #colcounter = 1

rowloop2:

li $v0, 4
la $a0, leftBrace
syscall

columnloop2:
lw $t3, 0($t1) #store number at current index in t3
li $v0, 1 #this block prints out number
move $a0, $t3
syscall

lw $t5, k  #store number of columns in t5
seq $t4, $t5, $t2 #compare number of columns to counter
li $t6, 1
beq $t4, $t6, rightbr2 #if we have hit the last column, print out a \t]

li $v0, 4 #otherwise, simply print a tab
la $a0, tab
syscall

addi $t2, $t2, 1 #Increment the counter
addi $t1, $t1, 4 #Move ahead 4 bytes to the next integer
j columnloop2 #loop

rightbr2:
li $v0, 4
la $a0, rightBrace
syscall

#comparing row counter to number of rows
lw $t7, m #number of rows stored in t7
seq $t4, $t7, $t9 #compared boolean value stored in t4 (0 or 1)
li $t6, 1
beq $t4, $t6, multiply #if the row counter == # of rows, we are done, move on to next part
addi $t9, $t9, 1 #otherwise increment the row counter by 1
li $t2, 1 #reset colcounter to 1
addi $t1, $t1, 4 #move to the next number
j rowloop2 #jump to begining of the row loop
################################################ DONE PRINTING OUT SECOND MATRIX
multiply: #note that the matrix will be n x k --> store this in s2
move $t0, $s0 #reset t0
move $t1, $s1 #reset t1
li $v0, 9 #allocate heap memory for resultant matrix
lw $t2, n #will have n rows
lw $t3, k  #will have k columns
multu $t2, $t3  #multiply these
mflo $t8
li $t3, 4 #4 bytes per element
multu $t8, $t3 #multiply by 4 bytes per element
mflo $t8
move $a0, $t8 #move number of bytes to allocate into a0
syscall #allocate the memory

move $s2, $v0
move $s7, $s2 #make s7 point to the beginning of s2...we are running out of registers here :/

lw $t2, m
li $t3, 1
beq $t2, $t3, separateSenario #separate case if colmat1=rowmat2=1
############################################################################
li $t2, 1 #row counter MAT 1
li $t3, 1 #col counter MAT 1
li $t8, 1 #row counter MAT 2
li $t9, 1 #col counter MAT 2
li $t6, 0 #temp register which will be used for each resultant element
outershell:
lw $t4, 0($t0) #starts off as first number in first row of Mat1

lw $t5, 0($t1) #starts off as first number in first col of Mat2

innerloop:
multu $t5, $t4 #multiply the two numbers, store temporarily in s3
mflo $s3
addu $t6, $t6, $s3
lw $t7, m #load number of columns of MAT1 into register t7
beq $t7, $t3, check2 #if MAT1 current col == number of cols in MAT1
#if this is not the case...
addi $t0, $t0, 4 #jump to next element in mat1
#for matrix 2, to get to the next element, we need to shift
li $s4, 1 #counter for num times we move forward in mat2
shiftloop:
addi $t1, $t1, 4 #move forward to next element
lw $s5, k
beq $s4, $s5, stopshifting  #if(num times moved == num cols in MAT2), stop shifting.
#otherwise...
addi $s4, $s4, 1 #increment the number of times we moved
j shiftloop #restart the loop

stopshifting:
addi $t3, $t3, 1 #increment the column counter in MAT 1
addi $t8, $t8, 1 #increment the row counter in MAT 2
j outershell

check2:
sw $t6, 0($s7) #store result in element of result
lw $t7, k #load number of COLUMNS for mat 2 in t7
beq $t7, $t9, changerows #if current column in matrix 2 == number of columns in matrix 2
#otherwise..
beginrow: #loop back to the beginning of the row (using the col counter)
lw $t7, m #load the amount of columns from matrix 1 into t7
addi $t7, $t7, -1 #we want to shift back col-1 times
li $t6, 0 #number of times we shift back
restartrow:
addi $t0, $t0, -4 #shift back in mat1
addi $t6, $t6, 1 #increment the amount of times we shifted back
beq $t6, $t7, stoprestartingrow
j restartrow

stoprestartingrow:
j preshiftloop2 #moves to the next element in MAT2
#reset col counter in MAT1, row counter should still be what it was
#

#jumpback:
#addi $t0, $t0, 4 #advance t0 to next element
preshiftloop2:
addi $s7, $s7, 4  #move forward one element in the result matrix
li $s4, 0 #counter for num times we move backwards in mat2
lw $s5, k
addi $s5, $s5, -1 #col-1 == value stored in $s5
shiftloop2: #shift BACK col-1 times.
#if we are not done shifting
addi $t1, $t1, -4 #move BACK one element
addi $s4, $s4, 1 #increment number of times we moved back
beq $s4, $s5, dontjump #before, it jumped to stopshiftingback. Remember.
j shiftloop2

dontjump:
addi $t8, $t8, -1 #decrement row counter in MAT2, because you've ascended one row
li $s6, 1 #load in 1 for s6
beq $t8, $s6, stopshiftingback #if your current row in mat2 == 1, you're GOOD :D
#otherwise...
li $s4, 0
lw $s5, k
ascendrow:
addi $t1, $t1, -4 #move back one element
addi $s4, $s4, 1 #increment number of times we moved back
beq $s4, $s5, dontjump #if you've ascended a row, stop
j ascendrow #otherwise keep on looping



li $t3, 1 #reset COL counter in MAT1 to 1
addi $t2, $t2, 1 #INCREMENT row counter in MAT1
li $t8, 1 #reset ROW counter in MAT2 to 1
addi $t9, $t9, 1 #INCREMENET col counter in MAT2
nextcondition:
lw $t7, k #load in number of columns in mat 2 to t7
beq $t9, $t7, printresultantMat #if the number of columns in MAT 2 == column counter for MAT 2
#We still have to store our result in t6 in s7
j restartrow

changerows:
lw $t7, n
beq $t2, $t7, nextcondition #if the number of rows in MAT 1 == row counter
addi $t0, $t0, 4 #advance to the next row (this is really just going ahead one element)
addi $t2, $t2, 1 #increment row counter for MAT 1
li $t3, 1 #reset col counter for MAT 1
#loop back to the first element of matrix 2
lw $t7, m #load num of rows of MAT2 into t7
lw $s5, k #load num of cols of MAT2 into s5
multu $t7, $s5 #we need to shift back exactly t6 times - 1
mflo $t6
addi $t6, $t6, -1 #done
li $s5, 0 #we have shifted 0 times to start
restartMatTwo:
addi $t1, $t1, -4 #shift back once
addi $s5, $s5, 1 #increment times we have shifted back
beq $s5, $t6, doneRestarting
#otherwise
j restartMatTwo
doneRestarting:
li $t8, 1 #reset row counter for mat 2
li $t9, 1 #reset col counter for mat 2
li $t6, 0 #reset $t6
addi $s7, $s7, 4 #remember to advance the resultant matrix
j outershell

stopshiftingback: #we have shifted to our desired element in MAT2
li $t6, 0 #reset t6
addi $t9, $t9, 1 #incremement col count for matrix 2
li $t3, 1 #reset col counter for matrix 1
li $t8, 1 #reset row counter for matrix 2, we've already been doing this but just in case
j outershell




separateSenario:
li $t2, 1 #row counter MAT1
li $t3, 1 #col counter MAT2

finalbossloop: #loop for this crazy test case
lw $t4 0($t0)
lw $t5 0($t1)
multu $t4, $t5
mflo $t6
sw $t6 0($s7) #store element
addi $s7, $s7, 4 #move forward in result MAT
lw $t8, k #load in number of cols for MAT2
beq $t3, $t8, descendrow #if current col in mat2 == last col in MAT2, nextrow
#otherwise...
addi $t1, $t1, 4 #move forward in MAT2
addi $t3, $t3, 1 #increment col counter
j finalbossloop

descendrow:
lw $t9, n
beq $t9, $t2, printresultantMat #we are done
#otherwise...
addi $t0, $t0, 4 #move down row
addi $t2, $t2, 1 #increment row counter
move $t1, $s1 #reset MAT 2
li $t3, 1 #reset col counter
j finalbossloop #loop


printresultantMat:
li $v0, 4
la $a0, equals
syscall
move $s7, $s2 #resets resultant array (s7 points at beginning)


######################### PRINT OUT THE RESULTANT MATRIX
li $t9, 1 #rowcounter = 1
li $t2, 1 #colcounter = 1

rowloop3:

li $v0, 4
la $a0, leftBrace
syscall
columnloop3:
lw $t3, 0($s7) #store number at current index in s7

li $v0, 1 #this block prints out number
move $a0, $t3
syscall

lw $t5, k  #store number of columns in t5
seq $t4, $t5, $t2 #compare number of columns to counter
li $t6, 1
beq $t4, $t6, rightbr3 #if we have hit the last column, print out a \t]

li $v0, 4 #otherwise, simply print a tab
la $a0, tab
syscall

addi $t2, $t2, 1 #Increment the counter
addi $s7, $s7, 4 #Move ahead 4 bytes to the next integer
j columnloop3 #loop

rightbr3:
li $v0, 4
la $a0, rightBrace
syscall

#comparing row counter to number of rows
lw $t7, n #number of rows stored in t7
seq $t4, $t7, $t9 #compared boolean value stored in t4 (0 or 1)
li $t6, 1
beq $t4, $t6, endprogram #if the row counter == # of rows, we are done, move on to next part
addi $t9, $t9, 1 #otherwise increment the row counter by 1
li $t2, 1 #reset colcounter to 1
addi $s7, $s7, 4 #move to the next number
j rowloop3 #jump to begining of the row loop
#########################

endprogram:
jr $ra
