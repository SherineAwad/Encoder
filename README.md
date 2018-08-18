This program reads a N*M 0 and 1 matrix seperated by space from a file and encodes it. 
To encode, it transpose the matrix, each row becomes a column. Then it compress row by row not the entire matrix and write each compressed row to a new file. 
To decode, it decompress each row and transpose the matrix to its original and returns the row requested by the user. 


Example: 
--------

Lets say we have sample.txt and it contains 6*5 matrix: 

0 1 0 1 0
1 0 0 0 1
0 1 0 1 0
1 0 1 0 1
0 1 0 1 0
1 1 1 0 1


to encode this file, we can run:: 

  
    cc encode.c -o run 

Then we need to run our compiled program and pass the sample.txt and the outputfile of compression::
 

  ./run sample.txt compressed.txt 


What encode will do step by step is: 

It will transpose the matrix so it becomes::
 

0 1 0 1 0 1
1 0 1 0 1 1 
0 0 0 1 0 1
1 0 1 0 1 0
0 1 0 1 0 1


Then, it will compress each row by writing only the row id and the cols id where the value is 1. This is a simplified version of CRS.

So the first row will be compressed as: 

0,1,3,5,-1 and we will add -1 to seperate rows. 

the final encoded file will contain in the first row the size of the transpose matrix in this case 5*6 and each compressed row seperated by -1 and finaly -100. 

So it will be:: 

   5,6
   0,1,3,5,-1,1,0,2,4,-1,2,1,3,5,-1,3,0,2,4,-1,4,1,3,5,-1,-100


To decode, the program will read the first row to get the size of the compressed file and constucts a matrix of this size and initalize it with zero.  
It loops through rows, the first element is the row id, and it fills those cols it reads with 1 in the matrix. 

To decode we run:: 


    cc decode.c -o derun 

then we need to pass the compressed file we have in the encoding step and the row id we need to print:: 


     ./derun compressed.txt  0 


The previous command will return:: 

  0  1  0  1  0

which is the first row in the original matrix in the sample.txt before encoding. 


