#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <zlib.h>
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
//-------------------------------------Compress each row-------------------------
void compressf(int** datat, int ROWS, int COLS, char* outfile)
{
int i, j; //iterators 
FILE *fp;
int deli =-1;
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
  fprintf(fp, "%d", i); //write rowid 
  for(j=0;j<ROWS;j++)
     {
	//if( i ==17)  printf("We are in row %d and datat[i][j] =%d \n", j,datat[i][j]);
	if(datat[i][j] !=0) 
	{	    
	fprintf(fp, ",%d",j); //write the columns ids of element of row is 1 only and skip zeros. 
	}
     }
  fprintf(fp, ",%d,",deli );
  }
fclose(fp);
printf("Done Compressing \n");
}
//-------------------------------------Main Function----------------------------
int main(int argc, char **argv)
{
char * infile = argv[1];

if (argc < 2) 
	{
	printf("Incorrect no. of input, check you entered file name \n");
	return(1);
        }
infile =argv[1];
int i,j; 
const int max= 1000000; 
int ROWS =max, COLS =max;

int **data = malloc(ROWS * sizeof(int*));
for (i = 0; i < ROWS; i++)
    data[i] = malloc(COLS * sizeof(int));

FILE* fp;

fp =fopen(infile, "r");

if (fp == NULL)
    { printf ("Error opening file unexist.ent: %s\n",strerror(errno)); 
    exit(1); }
i =0;
while(1) 
{
       ROWS = i;
       j =0; 
       while(1)
	 	{
        	char temp;
		fscanf(fp,"%c",&temp);
		//printf("temp is %c", temp);
                if(temp =='\n') break; 
        	if(temp==' ') continue;
		data[i][j]=(temp -'0');
		j+=1;
		COLS=j;
		}
    if(feof(fp)) break; 
    i+=1;
}
fclose(fp);
printf("After reading file we have ROWS and COLS: ");
printf("%d, %d \n", ROWS, COLS);
int**datat = transpose(data,ROWS, COLS); 
printf("Done transposing \n");
compressf(datat, ROWS, COLS, "compressed.txt");
free(data);
return(0);
}

