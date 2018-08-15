#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int ** transpose(int ** data, int ROWS, int COLS)
{
int i, j;
int **datat = (int **)malloc(ROWS * sizeof(int *));
for (i=0; i<ROWS; i++)
         datat[i] = (int *)malloc(COLS * sizeof(int));
printf("ROWS and COLS %d,%d \n", ROWS, COLS);
for(i=0;i<ROWS;i++)
	for(j=0;j<COLS;j++) 
	     datat[i][j] = data[j][i];//{printf("%d, %d,%d \n", j, i, data[j][i]);datat[i][j]= data[j][i];}

//----print 
/*printf("Here we print from new transpose \n");
for(i =0;i<ROWS; i++)
{
for(j=0;j<COLS;j++)
        printf("%d",datat[i][j]);
printf("\n");
}*/
return(datat);
}
//--------------------------------------Decode--------------------------------------
int ** decode(char* file,int *r, int *c)
{
FILE *fp;
int ROWS, COLS;
int i, j; //iterators  
printf("We are here in the decoding process \n");
fp = fopen(file, "r");
fscanf(fp, "%d,%d", &ROWS, &COLS); //first row in the encoded file is the rows and cols of the new encoded array.
printf("after reading %d %d \n", ROWS, COLS);  
//declare your array of the sixe you read from header of encoded file 
int **datat = malloc(ROWS * sizeof(int*));
for (i = 0; i < ROWS; i++)
    datat[i] = malloc(COLS * sizeof(int));
//initialize the array with zeros 
for(i=0;i<ROWS;i++) 
 for(j=0;j<COLS;j++)  
    datat[i][j]=0; 
printf("We are done allocation in decode \n");
//loop through the file change the value of the matrix for the columns we read from the file 
i =0; 
j =0;
int deli = -1;  
int deli_count =0;
while(1)
{
     if(deli_count >=ROWS) break;
     //printf("Deli count is %d  \n", deli_count);
     j=0;
     //printf("We are in the outer loop  \n");
     fscanf(fp,"%d,", &i); //first element in compressed file is the row id
     if (i ==deli) break;
     while(1)
                {
		//printf("We are in inner loop \n");
                fscanf(fp,"%d,",&j);
		//printf("i is and j is %d %d \n",i,j);
		if(j==deli) {deli_count+=1;break; }
                datat[i][j]=1;
                }
if(feof(fp) ) break;
}
fclose(fp);
printf("We are here printing datat from inside decode \n"); 
for(i =0;i<ROWS;i++)
	{
        for(j =0;j<COLS;j++) 
		printf("%d,", datat[i][j]);
	printf("--\n");
        }
*r =ROWS;
*c =COLS;
return(datat);
}
//-------------------------------------Main Function----------------------------
int main(int argc, char **argv)
{
if (argc < 2)
        {
        printf("Incorrect no. of input, check you entered the row id you wish to return 0 is the first row, 1 is the second row, ..etc \n");
        return(1);
        }
int rowid = atoi(argv[1]);
char * infile = argv[2];
FILE *fp; 
int i,j; 
const int max= 1000000; 
int  ROWS =max;
int  COLS =max;
int **data = malloc(max * sizeof(int*));
for (i = 0; i <max; i++)
    data[i] = malloc(max * sizeof(int));
printf("ROWS and COLS %d %d \n", ROWS, COLS);
fp = fopen(infile, "r+t");
int** newd1 = decode("compressed.txt",&ROWS,&COLS); 
printf("We are done after decoding and R, C are : %d %d \n",ROWS, COLS);
int** newd2 = transpose(newd1,COLS,ROWS); //swap COLS and ROWS for transpose 
printf("%s", "We are done transposing to original form \n");
printf("row id is %d \n", rowid);
//rowid = rowid -1; // we start with zero  
for (i =0; i<ROWS; i++) //we are back to the original size 
	printf("%d %c", newd2[rowid][i],' '); 
//printf("%s", '\n');
/*for(i=0;i<COLS;i++) 
  {
   for(j=0;j<ROWS;j++)
        printf("%d %c", newd2[i][j], ' ');
   printf("%c",'\n');
  }
printf("%s", "Done printing what we need \n"); 
*/
//fclose(fp);
//free(newd1);
//free(newd2);
return(0);
}

