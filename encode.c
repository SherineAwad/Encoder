#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <zlib.h>
#include "data.h"
//-------------------------Encode Transpose----------
int** transpose(int **data, int ROWS, int COLS )
{
int temp = ROWS;
//ROWS =COLS;
//COLS = temp;
int i, j;
printf("We will start transposing with passed ROWS $ COLS %d %d\n", ROWS, COLS);
int **datat = (int **)malloc(COLS * sizeof(int *));
for (i=0; i<COLS; i++)
        datat[i] = (int *)malloc(ROWS * sizeof(int));
//--------------TRANSPOSE
for(i=0;i<COLS;i++)
   for(j=0;j<ROWS;j++)
          datat[i][j] = data[j][i];

return(datat);
}
//-------------------------------------------------------------------------------
/*int ** read_file(char* infile, int *rows, int *cols)
{
FILE * fp;
char * line = NULL;
size_t len = 0;
ssize_t read;
const char *sep = " ";
int i = 0;
int j = 0;
char *token = NULL;
const int max= 1000000;
int ROWS =max, COLS =max;
int **data = malloc(ROWS * sizeof(int*));
for (i = 0; i < ROWS; i++)
    data[i] = malloc(COLS * sizeof(int));

fp = fopen(infile, "r");
if (fp == NULL)
  {
    printf("Error opening");
    exit(EXIT_FAILURE);
  }
int myrow =0; 
while ((read=getline(&line, &len, fp)) != -1)
  {
     j =0; 
     token = line;
     token = strtok(line, sep);
     printf("len is %d \n", sizeof(line));
     printf("Line is %s \n", line);
     while(token != NULL)
     {
       //printf("token is %s \n", token);
       //printf("printing atoi %d , row is %d , cols is %d \n", atoi(line), myrow,j);
       data[myrow][j] = atoi(token);
       token=strtok(NULL,sep);
       j+=1;
     }
  // printf("j is %d \n", j);
   myrow +=1; 
  }
ROWS =myrow;
COLS = j-1;
*rows = ROWS;
*cols = COLS;
printf("Rows is %d and COLS is %d \n", ROWS, COLS);
for(i=0;i<ROWS;i++) 
{
   for(j=0;j<COLS;j++) 
       {printf("%d,", data[i][j]);}
   printf("$");
}

return data;
}i */
//-------------------------------------Compress each row-------------------------
void compressf(int** datat, int ROWS, int COLS, char* outfile)
{
int i, j; //iterators 
FILE *fp;
//int deli =-1;
int  deli =-1;
fp = fopen(outfile, "w+t");
if ( fp == NULL )
{
    printf( "Could not output file for compression\n" );
    exit(1);
} 
fprintf(fp,"%d,%d\n", COLS, ROWS); // write size of our transposed matrix in header of encoded file 
printf("Here in Compress %d %d", ROWS, COLS);
for(i=0;i<COLS; i++)  
  {
  fprintf(fp, "%d,", i); //write rowid 
  for(j=0;j<ROWS;j++)
     {
	if(datat[i][j] !=0) 
	{	    
	fprintf(fp, "%d,",j); //write the columns ids of element of row is 1 only and skip zeros. 
	}
     }
  fprintf(fp, "%d,",deli );
  }
fprintf(fp, "%d", -100);
fclose(fp);
printf("Done Compressing \n");
}
//-------------------------------------Main Function----------------------------
int main(int argc, char **argv)
{
char * infile = argv[1];
FILE* fp;
if (argc < 2) 
	{
	printf("Incorrect no. of input, check you entered file name \n");
	return(1);
        }
infile =argv[1];
int i,j; 
int ROWS ,COLS;
int **data = malloc(ROWS * sizeof(int*));
for (i = 0; i < ROWS; i++)
    data[i] = malloc(COLS * sizeof(int));
data =read_file(infile,&ROWS,&COLS);
printf("After reading file we have ROWS and COLS: ");
printf("%d, %d \n", ROWS, COLS);
int**datat = transpose(data,ROWS, COLS); 
printf("Done transposing \n");
compressf(datat, ROWS, COLS, "compressed.txt");
free(data);
return(0);
}
