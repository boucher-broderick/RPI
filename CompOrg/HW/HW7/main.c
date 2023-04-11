/* 
Lab 6: Decoding the instructions
CSCI-2500 Fall 2021
*/

/******************************************************************************/
/* Usual suspects to include  */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// define BIT type as a char (i.e., one byte)
typedef char BIT;
#define TRUE 1
#define FALSE 0
#define UNDEF -1

BIT ONE[32] = {TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE};
BIT ZERO[32] = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE};


/******************************************************************************/
/* Normal circuits */
/* Modify/add additional circuits as necessary (e.g., 3-input AND gate) */
/******************************************************************************/
BIT not_gate(BIT A)
{
  if (A)
    return FALSE;
  else
    return TRUE;
}

BIT or_gate(BIT A, BIT B)
{
  if (A || B)
    return TRUE;
  else
    return FALSE;
}

BIT and_gate(BIT A, BIT B)
{
  if (A && B)
    return TRUE;
  else
    return FALSE;
}

BIT and_gate3(BIT A, BIT B, BIT C)
{
  return and_gate(A, and_gate(B, C));
}

BIT xor_gate(BIT A, BIT B)
{
  if (A ^ B)
    return TRUE;
  else
    return FALSE;
}


void convert_instructions()
{
  int term1, term2;   //converts the input into usable stuff
  char line[256] = {0};
  char newString[10][10]; 
    int i,j,ctr;
  fgets(line, 256, stdin);
    j=0; ctr=0;
    for(i=0;i<=(strlen(line));i++)  //does the parse
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(line[i]==' '||line[i]=='\0')
        {
            newString[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            newString[ctr][j]=line[i];
            j++;
        }
    }
     term1 = atoi(newString[0]); //converts num
      term2 = atoi(newString[2]);
    //printf("%d, %d, %s", term1, term2, newString[1]);


void adder1(BIT A, BIT B, BIT CarryIn, BIT* CarryOut, BIT* Sum) //1 bit adder
{
  // TODO: implement a 1-bit adder
  BIT x0 = xor_gate(A, B);
  *Sum = xor_gate(CarryIn, x0);
  
  BIT y0 = and_gate(x0, CarryIn);
  BIT y1 = and_gate(A, B);
  *CarryOut = or_gate(y0, y1);
}


void add4(BIT A[4], BIT B[4], BIT CarryIn, BIT* CarryOut, BIT Sum[4])   // 4 bit adder
{
  
  
  BIT tempSum = 0;
  for(int j = 3; j >= 0; j--){
    adder1(A[j], B[j], CarryIn, CarryOut, &tempSum);
    
   
    
     CarryIn = *CarryOut;
     Sum[j] = tempSum;
  }
}

void binvert(BIT a[32]){  // changes a negative to a positive when the actual add happens
  for(int i =0; i<32; i++){
    a[i]= not_gate(a[i]);
  }
  a[0]=TRUE;

}
void add16(BIT a[32], BIT b[32], BIT CarryIn, BIT* CarryOut, BIT Sum[32]){   //the a6 bit adder
  BIT tA[4];
  BIT tB[4];
  BIT tS[4];


  for(int j = 3; j >= 0; j--){
    memcpy(tA, &a[4*j], 4);
    memcpy(tB, &b[4*j], 4);
    memset(tS, 0, 4);


    add4(tA, tB, CarryIn, CarryOut, tS);
    CarryIn = *CarryOut;
    memcpy(&Sum[4*j], &tS[0], 4);
    
   
  }
}


    BIT a[32];
    BIT b[32];
      
      if(term2<0) {term2=term2*-1; b[31]=TRUE;} else b[31]= FALSE;   //converts the nums to binary
      //printf("%d", term2);
      int num=2;
      for(int x=30;  x>-1; x--){
        
        num=2;
        for(int y=0; y< x-1;y++){
          num=num*2;
        }
        if(term2==1 && x==0)
          {a[0]=TRUE; break;}


        if(num<=term2)
        {
        term2-=num;
        a[x]=TRUE;
      }
      else a[x]=FALSE;

      }


      if(term1<0) {term1=term1*-1; a[31]=TRUE;} else a[31]= FALSE;
      //printf("%d", term2);  //converts to binary
      num=2;
      for(int x=30;  x>-1; x--){
        
        num=2;
        for(int y=0; y< x-1;y++){
          num=num*2;
        }
        if(term1==1 && x==0)
          {b[0]=TRUE; break;}


        if(num<=term1)
        {
        term1-=num;
        b[x]=TRUE;
      }
      else b[x]=FALSE;

      }


      if(term1<0) binvert(a);  //changes negative to positive
      if(term2<0) binvert(b);

      for(int h=31; h>-1; h--){ //prints
        if(a[h]) printf("1"); else printf("0");
      }
      printf("\n%c\n", newString[1][0]);

       for(int h=31; h>-1; h--){
        if(b[h]) printf("1"); else printf("0");
      }

      
      printf("\n=\n");
      BIT CarryIn = 0; //runs the add
      BIT result[32];
      BIT carryout[32];
     add16(a, b, CarryIn, carryout, result);
     for(int h=31; h>-1; h--){ //prints
        if(result[h]) printf("1"); else printf("0");
      }




  return;

}







int main()
{
  // convert some arbitrary number of instructions from stdin
  convert_instructions();


  return 0;
}
