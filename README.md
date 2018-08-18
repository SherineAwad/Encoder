This program reads a N*M 0 and 1 matrix seperated by space from a file and encodes it. 
To encode, it transpose the matrix, each row becomes a column. Then it compress row by row not the entire matrix and write each compressed row to a new file. 
To decode, it decompress each row and transpose the matrix to its original and returns the row requested by the user. 


Example: 
--------

Lets say we have sample.txt and it contains 6*5 matrix: 


0 1 0 1 1

1 0 1 0 1

0 0 0 1 1

1 0 1 0 1

0 1 0 1 1

1 1 1 0 1


to encode this file, we can run:: 

  
    cc encode.c -o run 

Then we need to run our compiled program and pass the sample.txt and the outputfile of compression::
 

    ./run sample.txt compressed.txt 


What encode will do step by step is: 

It will transpose the matrix so it becomes::
 

    0 1 0 1 0 1

    1 0 0 0 1 1 

    0 1 0 1 0 1

    1 0 1 0 1 0 

    1 1 1 1 1 1


Then, it will compress each row by writing only the row id and the cols id where the value is 1. This is a simplified version of CRS.

So the first row will be compressed as: 

0,1,3,5,-1 and we will add -1 to seperate rows. 

the final encoded file will contain in the first row the size of the transpose matrix in this case 5*6 and each compressed row seperated by -1 and finaly -100. 

So it will be::


     5,6
     0,1,3,5,-1,1,0,4,5,-1,2,1,3,5,-1,3,0,2,4,-1,4,0,1,2,3,4,5,-1,-100


To decode, the program will read the first row to get the size of the compressed file and constucts a matrix of this size and initalize it with zero.  
It loops through rows, the first element is the row id, and it fills those cols it reads with 1 in the matrix. 

To decode we run::


    cc decode.c -o derun
 

then we need to pass the compressed file we have in the encoding step and the row id we need to print::


     ./derun compressed.txt  0 


The previous command will return::



    0  1  0  1  0  1

which was the first col in the original matrix in the sample.txt before encoding. 


and:: 

 
     ./derun compressed.txt 4 


will return:: 


    1  1  1  1  1  1


Which is the last column in the original matrix. 


A run on a bigger sample 
------------------------

Lets creat rand.dat::
  
     (for i in `seq 1 1000`; do (for j in `seq 1 10000`; do echo $((RANDOM % 2 * RANDOM % 2)); done ) | paste -sd ' ' -; done ) > rand.dat

Checking the size of rand.dat::

      ls -lah rand.dat 


rand.dat is 19M:: 


	-rw-r--r--  1 sherine  staff    19M Aug 18 17:38 rand.dat



Lets encode and record time 'simplified time':: 


    time ./run rand.dat compressed.dat  


The output is as follows:: 


	We are reading your file 
	Your file has 1000 ROWS and 10000 COLS 
	We will start transposing your 1000 ROWS and 10000 COLS file 
	Done transposing 
	We are compressing your 1000 rows and 10000 cols file 
	Done Compressing 


Took less than a minute:: 
 

	real	0m2.601s
	user	0m1.287s
	sys	0m1.236s 


Lets check size of compressed.dat:: 


      ls -lah compressed.dat 


compressed.dat is 9.3M, approximately 48% of rand.dat size:: 



	-rw-r--r--  1 sherine  staff   9.3M Aug 18 17:38 compressed.txt

Lets decode and record simiplified time::


    time ./derun compressed.dat 1 >out


Again less than a minute:: 


        real	0m0.364s
	user	0m0.305s
	sys	0m0.041s




Resources
----------


1. http://netlib.org/linalg/html_templates/node91.html 
2. https://stackoverflow.com/questions/18942719/reading-from-a-text-file-and-storing-in-a-2d-array
3. https://www.youtube.com/watch?v=Lhef_jxzqCg&t=0s&index=13&list=LLZ8i9y_OkuRkKyoUx1wI1nw&ab_channel=Udacity
4. https://stackoverflow.com/questions/4242499/preferring-malloc-over-calloc 
