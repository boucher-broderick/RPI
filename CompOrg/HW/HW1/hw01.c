/* 
Assignment 1: NxM Matrix Multiplication 
CSCI-2500 Fall 2021
Brody Boucher

The goal of this program is to create matrices from output and then be able to
print them out as well as multiply them together. The whole time that this is happening 
the program should be constanlty checking for potential errors in the input or
the multiplication.
*/

/******************************************************************************/
/* Usual suspects to include  */
/******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

/******************************************************************************/
/* Function Calls */
/******************************************************************************/

typedef struct{
  double** data;
  int rows;
  int cols;
} matrix; 

int mm_alloc(matrix* mat);
int mm_free (matrix* mat);
int mm_print(matrix* mat);
int mm_read (char* filename, matrix* mat);
matrix* mm_matrix_mult(matrix* mat1, matrix* mat2);


int mm_alloc(matrix* mat)
{
  /*
  Notes:
  Allocate an array of pointers to a double
  Then, allocate an row/array of doubles and assign each double pointer that row
  Make sure you're allocating using mat->data in the matrix struct
  You can use calloc for allocation and zeroing out all the bytes
  - otherwise, you'd want to manually set all arrays to 0 (good practice)
  If your malloc/calloc returns null, the allocation failed
  */

  mat->data = (double **)malloc(sizeof(double *)*mat->rows);   /// creates first array
  for(int i=0; i< mat->rows; i++){
    mat->data[i] = malloc(sizeof(double)*mat->cols);    // creates second array
  }

  return 0;
}

int mm_free(matrix* mat)
{
  /*
  Notes:
  Reverse the allocation process, but you'll be calling free() instead
  */

  for(int i=0; i < mat->rows; i++){   //frees inner array first
    free(mat->data[i]);

  }
  free(mat->data);

  return 0;
}

int mm_print(matrix* mat)
{
  /*
  Notes:
  Print all the data values in your matrix
  Go row by row
  At the end of each row, print a newline
  Between each data value, insert a tab
  Use 2 digits of precision after the decimal (use "%10.2lf\t" as format string)
  See output.txt for expected output formatting

  */
  printf("\n/******** START of 2-D Matrix **********************************/\n");
  for (int i = 0; i < mat->rows; i++){   //for accessing the data
    for(int j =0; j < mat->cols; j++){
      char twos[3]=" ";
      if(mat->data[i][j] <10){     // to deterimine the spacing
          twos[1]=' ';
          twos[2]=' ';
      }
      else if(mat->data[i][j] <100){
         twos[1]=' ';
      }
      printf("   %s%2.2f\t", twos ,mat->data[i][j]);
    }
    printf("\n");
  }
 
  printf("/******** END of 2-D Matrix ************************************/\n");
  return 0;
}

int mm_read(char* filename, matrix* mat) 
{
  /*
  Notes:
  Use fopen to open the matrix file, then use fgets or getline to read lines
  The first line of the matrix contains integers for "#rows #columns"
  - Use these to allocate your arrays for matrix data
  Each subsequent line contains a single data value
  - You can use sscanf to parse each matrix entry
  - First value is data[0][0], next is data[0][1] ... data[#rows-1][#columns-1]
  */

  FILE * file;
  file = fopen(filename, "r");
  if(file == NULL){        //checks to see if the file can be opened
    printf("mm_read: failed to open file.\n");  //need to change to stdout
    exit(0);
  }

  char mat_val[10];        // each matrix value
  int empty = 0;           // check if the textfile is empty
  int check_mtx_val;       // amount of matrix values matches row and col
  int count_mtx_val=0;     // checks the amount of values that there should be
  int row, col;            // row and col of the matrix

  while(fgets(mat_val, sizeof(mat_val), file)!= NULL){     //goes line by line to read in from file
    if(empty==0){          // for the first round
      char row_char[3];    // row as a char
      char col_char[3];    // col as a char
      int swap =0;         // to swap where the next char in mat_val will be put
      int tracker=0;       // where to add in row or col if in the double digits

      for(int i =0; i<strlen(mat_val); i++){     //circles through mat_val to swap at the space
        if(mat_val[i]==' '){
          swap++;
          tracker=0;
        }
        else{
          if(swap>1){     // over a 2d matrix
            printf("mm_read: failed to read matrix dimensions.\n");
            exit(0);
          }
          if(swap==0){    // put the chars in row
            row_char[tracker]=mat_val[i];
            tracker++;
          }
          else{           // put the chars in col
            col_char[tracker]=mat_val[i];
            tracker++;
          }
        }
      }
      if(row_char[0]=='\0' || col_char[0]=='\0'){     //to check if the correct dimensions were added
        printf("mm_read: failed to read matrix dimensions.\n");
        exit (0);
      }


      row = atoi(row_char);   // change to ints
      col = atoi(col_char);

      if(row <= 0 || col <=0){     //to check if the correct dimensions were added
        printf("mm_alloc: allocation failed.\n");
        exit (0);
      }

      check_mtx_val = row*col+1;  
      mat->rows = row;
      mat->cols = col;
      mm_alloc(mat);
    }

    empty++;
    count_mtx_val++;
    if(count_mtx_val > check_mtx_val){     // if there are too many values to make the dimensions
      printf("mm_read: failed to read matrix dimensions.\n");
      exit(0);
    }
   //printf("%s", mat_val);
    if(count_mtx_val >1){
    int down = (count_mtx_val -2) / mat->cols;
    int over = (count_mtx_val-2) % mat->cols;
    float val = atof(mat_val);
    mat->data[down][over] = val;

  }

    memset(mat_val, '\0', 10);

  }

  if(empty==0){     //makes sure the file is not empty
    printf("mm_read: failed to read from file.\n");   //file is empty
    exit(0);
  }

  if(count_mtx_val < check_mtx_val){     // if there are too little values to make the dimensions
    printf("mm_read: failed to read matrix values.\n");
    exit(0);
  }

 
    
  

  return 0;
}


matrix* mm_matrix_mult(matrix* mat1, matrix* mat2)
{
  /*
  Notes:
  First check that it is actually possible to multiply the two inputs
  If so, construct a result matrix
  Then perform the multiplication
  Then return a pointer to your result matrix
  */
  matrix* result_matrix =(matrix*)malloc(sizeof(matrix));
  if(mat1->cols != mat2->rows){
    printf("mm_matrix mult: dimension mismatch between matrices.\n");       // to check the numbers before multiplication
    exit(0);
  }
  else{
    
    result_matrix->rows=mat1->rows;
    result_matrix->cols=mat2->cols;
    mm_alloc(result_matrix);
    int counter=0;
    for(int i =0; i < mat1->rows; i++){       // to move down the first mat 
      
      for(int j=0; j < mat2 ->cols; j++){     // to move over the second matrix
        float total=0;
        for(int x =0; x < mat1->cols; x++){    // to access the individual data
          total+=mat1->data[i][x]*mat2->data[x][j];
        }
        counter++;
        int down = (counter -1) / result_matrix->cols;
        int over = (counter-1) % result_matrix->cols; 
        result_matrix->data[down][over] = total;
      }
    }


  }

  return result_matrix;
}




int main()
{
  /*
  * you must keep this function AS IS. 
  * you cannot modify it!
  */
  char filename_A[256];
  char filename_B[256];
  matrix* A = (matrix*)malloc(sizeof(matrix));
  matrix* B = (matrix*)malloc(sizeof(matrix));
  matrix* C = NULL;

  printf("Please enter the matrix A data file name: ");
  if (1 != scanf("%s", filename_A)) {
    printf("main: scanf failed to read filename\n");
    exit(-1);
  }
  mm_read(filename_A, A);
  mm_print(A);

 
  printf("Please enter the matrix B data file name: ");
  if (1 != scanf("%s", filename_B)) {
    printf("main: scanf failed to read filename\n");
    exit(-1);
  }
  mm_read(filename_B, B);
  mm_print(B);

  C = mm_matrix_mult(A, B);
  mm_print(C);
 
  mm_free(A);
  mm_free(B);
  mm_free(C);
  free(A);
  free(B);
  free(C);
  

  return 0;
}
