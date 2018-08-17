#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

size_t ** transpose(size_t ** data,size_t ROWS, size_t COLS)
{
int i, j;
size_t **datat = (size_t **)malloc(ROWS * sizeof(size_t *));
for (i=0; i<ROWS; i++)
         datat[i] = (size_t *)malloc(COLS * sizeof(size_t));
printf("ROWS and COLS %d,%d \n", ROWS, COLS);
for(i=0;i<ROWS;i++)
	for(j=0;j<COLS;j++) 
	     datat[i][j] = data[j][i];//{printf("%d, %d,%d \n", j, i, data[j][i]);datat[i][j]= data[j][i];}
return(datat);
}
//--------------------------------------Decode--------------------------------------
size_t ** decode(char* file,size_t *r, size_t *c)
{
FILE *fp;
size_t ROWS, COLS;
int i, j; //iterators  
printf("We are here in the decoding process \n");
fp = fopen(file, "r");
fscanf(fp, "%d,%d", &ROWS, &COLS); //first row in the encoded file is the rows and cols of the new encoded array.
printf("After reading %d %d \n", ROWS, COLS);  
//declare your array of the sixe you read from header of encoded file 
size_t **datat = malloc(ROWS * sizeof(size_t*));
for (i = 0; i < ROWS; i++)
    datat[i] = malloc(COLS * sizeof(size_t));
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
     j=0;
     fscanf(fp,"%d,", &i); //first element in compressed file is the row id
     if (i ==deli) break;
     while(1)
                {
                fscanf(fp,"%d,",&j);
		if(j==deli) {deli_count+=1;break; }
                datat[i][j]=1;
                }
if(feof(fp) ) break;
}
fclose(fp);
*r =ROWS;
*c =COLS;
return(datat);
}
//-------------------------------------Main Function----------------------------
int main(int argc, char **argv)
{
if (argc < 3)
        {
        printf("Incorrect no. of input, enter file to decode  the row id you wish to return 0 is the first row, 1 is the second row, ..etc \n");
        return(1);
        }
int rowid = atoi(argv[2]);
char * infile = argv[1];
FILE *fp; 
int i,j; 
//const int max= 1000000; 
size_t  ROWS;
size_t  COLS;
size_t** datat = decode(infile,&ROWS,&COLS); 
printf("We are done after decoding and R, C are : %d %d \n",ROWS, COLS);
size_t** data = transpose(datat,COLS,ROWS); //swap COLS and ROWS for transpose 
printf("%s", "We are done transposing to original form \n");
printf("row id is %d \n", rowid);
for (i =0; i<ROWS; i++) //we are back to the original size 
	printf("%d %c", data[rowid][i],' '); 
free(data);
free(datat);
return(0);
}

