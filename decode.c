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
//-------------------------------Read the first line in the compressed file to get ROWS and COLS------------------------
printf("We will start the decoding process \n");
fp = fopen(file, "r");
fscanf(fp, "%d,%d", &ROWS, &COLS); //first row in the encoded file is the rows and cols of the new encoded array.
printf("Your file has %d ROWS and %d COLS \n", ROWS, COLS);  

//------------------------------Declare your array of the size you read from header of encoded file--------------------------- 
size_t **datat = malloc(ROWS * sizeof(size_t*));
for (i = 0; i < ROWS; i++)
    datat[i] = malloc(COLS * sizeof(size_t));
//-----------------------------Initialize the array with zeros, we can use calloc too-----------------------------------------------
for(i=0;i<ROWS;i++) 
 for(j=0;j<COLS;j++)  
    datat[i][j]=0; 
printf("We are done allocation for decoding \n");
//-----------------------------Loop through the file change the value of the matrix for the columns we read from the file------------------------------------ 
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
//-----------------------------------------Return rows and cols an close your file
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
size_t  ROWS;
size_t  COLS;
size_t** datat = decode(infile,&ROWS,&COLS); 
if ( (rowid >= COLS) || (rowid <0) )  //COLS is the rows of the original matrix  
    {
     printf("You requested a row that exceeds your file size or make sure you use zero index, first row is 0\n");
     exit(EXIT_FAILURE);
    }
printf("We are done decoding and your file now has %d Rows and %d COLS \n",ROWS, COLS);
size_t** data = transpose(datat,COLS,ROWS); //swap COLS and ROWS for transpose 
printf("%s", "We are done transposing to original form \n");
printf("row id is %d \n", rowid);
for (i =0; i<ROWS; i++) //we are back to the original size 
	printf("%d %c", data[rowid][i],' '); 
free(data);
free(datat);
return(0);
}

