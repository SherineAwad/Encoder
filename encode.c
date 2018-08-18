#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdint.h>
//-------------------------Encode Transpose----------
size_t** transpose(size_t **data, size_t ROWS, size_t COLS )
{
size_t temp = ROWS;
int i, j;
printf("We will start transposing your %d ROWS and %d COLS file \n", ROWS, COLS);
size_t **datat = (size_t **)malloc(COLS * sizeof(size_t*));
for (i=0; i<COLS; i++)
        datat[i] = (size_t*)malloc(ROWS * sizeof(size_t));
//--------------TRANSPOSE
for(i=0;i<COLS;i++)
   for(j=0;j<ROWS;j++)
          datat[i][j] = data[j][i];

return(datat);
}
//-------------------------------------------------------------------------------
size_t ** read_file(char* infile, size_t *rows, size_t *cols)
{
FILE * fp;
char * line = NULL;
size_t len = 0;
ssize_t read;
const char *sep = " ";
int i = 0;
int j = 0;
char *token = NULL;
const long max =1000000;
//const long max = 10E9; // or max =SIZE_MAX;  we will need 1 GB RAM, we can ask for this as a requirement, simplifying for my own machine.
size_t ROWS = max;
size_t COLS = max;
size_t**data = malloc(ROWS * sizeof(size_t*));
for (i = 0; i < ROWS; i++)
    data[i] = malloc(COLS * sizeof(size_t));

fp = fopen(infile, "r");
if (fp == NULL)
      {
          printf("Error opening");
          exit(EXIT_FAILURE);
      }
int myrow =0;
j =-1;
printf("We are reading your file \n");
while ((read=getline(&line, &len, fp)) != -1)
  {
   j =-1;
   token = strtok(line, sep);
   while( (token != NULL) ) 
   	{
   	j+=1;
   	data[myrow][j] = atoi(token);
   	token=strtok(NULL,sep);
   	}
   myrow +=1;
 }
ROWS =myrow;
COLS = j+1;
*rows = ROWS;
*cols = COLS;
return data;
}
//-------------------------------------Compress each row-------------------------
void compressf(size_t** datat, size_t ROWS, size_t COLS, char* outfile)
{
int i, j; //iterators 
FILE *fp;
int  deli =-1;
fp = fopen(outfile, "w+t");
if ( fp == NULL )
{
    printf( "Could not output file for compression\n" );
    exit(1);
} 
fprintf(fp,"%d,%d\n", COLS, ROWS); // write size of our transposed matrix in header of encoded file 
printf("We are compressing your %d rows and %d cols file \n", ROWS, COLS);
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
char * outfile = argv[2];
FILE* fp;
if (argc < 3) 
	{
	printf("Incorrect no. of input, check you entered input file name to compress and output file name \n");
	return(1);
        }
infile =argv[1];
size_t i,j; 
size_t ROWS ,COLS;
ROWS = 0; 
COLS = 0;
size_t **data =read_file(infile,&ROWS,&COLS);
printf("Your file has %d ROWS and %d COLS \n", ROWS, COLS);
size_t**datat = transpose(data,ROWS, COLS); 
printf("Done transposing \n");
compressf(datat, ROWS, COLS, outfile);
free(data);
free(datat);
return(0);
}
