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

void decoder2(BIT I0, BIT I1, BIT* O0, BIT* O1, BIT* O2, BIT* O3)
{
  *O0 = and_gate(not_gate(I1), not_gate(I0));
  *O1 = and_gate(not_gate(I1), I0);
  *O2 = and_gate(I1, not_gate(I0));
  *O3 = and_gate(I1, I0);
  
  return;
}

BIT multiplexor2(BIT S, BIT I0, BIT I1)
{
  BIT x0 = and_gate(not_gate(S), I0);
  BIT x1 = and_gate(S, I1);
  return or_gate(x0, x1);  
}

BIT multiplexor4(BIT S0, BIT S1, BIT I0, BIT I1, BIT I2, BIT I3)
{
  BIT x0, x1, x2, x3 = FALSE;
  decoder2(S0, S1, &x0, &x1, &x2, &x3);
  
  BIT y0 = and_gate(x0, I0);
  BIT y1 = and_gate(x1, I1);
  BIT y2 = and_gate(x2, I2);
  BIT y3 = and_gate(x3, I3);
  
  BIT z0 = or_gate(y0, y1);
  BIT z1 = or_gate(y2, y3);
  
  return or_gate(z0, z1);  
} 


/******************************************************************************/
/* Checkpoint 1 functions */
/* Add helper functions as necessary. I did:
  - One for converting integer->2's complement binary
  - One for converting register string to binary representation */
/******************************************************************************/

void convert_instructions()
{
  char line[256] = {0};
  while (fgets(line, 256, stdin) != NULL) {
    BIT Output[32] = {FALSE};
        
    // TODO: perform conversion
    // My approach:
    // - Use sscanf on line to get strings for instruction and registers
    // - Use instructions to determine op code, funct, and shamt fields
    // - Convert immediate field and jump address field to binary
    // - Use registers to get rt, rd, rs fields
    // Note: I parse everything as strings, then convert to BIT array at end
    char * token = strtok(line, " ");
    int x = 0;
   // loop through the string to extract all other tokens
   while( token != NULL ) {
      //printf( " %s\n", token ); //printing each token
       if(token == "add"){
          printf( " %s\n", token );
        }
        else if (token == "lw"){

        }
        else if (token == "j"){

        }
      token = strtok(NULL, " ");




   }
    
  
    for (int i = 31; i >= 0; --i) {
      printf("%d", Output[i]);
    }
    printf("\n");
  }
  
  return;
}

/******************************************************************************/
/* Checkpoint 2 circuits */
/******************************************************************************/

void decoder3(BIT* I, BIT EN, BIT* O)
{
  // TODO: implement 3-to-8 decoder using gates
  // See lecture slides, book, and/or online resources for logic designs
  
  return;
}

void decoder5(BIT* I, BIT* O)
{
  // TODO: implement 5-to-32 decoder using 2-to-4 and 3-to-8 decoders
  // https://fci.stafpu.bu.edu.eg/Computer%20Science/4887/crs-12801/Files/hw4-solution.pdf
  
  return;
}


/******************************************************************************/
/* Checkpoint 3 circuits */
/******************************************************************************/

void convert_to_binary(int a, BIT* A)
{
  // TODO: convert integer to 2's complement BIT representation
  // Note: A[0] is least significant bit and A[31] is most significant bit
  // For this function ONLY: you're allowed to use logical if-else statements
  
}

void adder1(BIT A, BIT B, BIT CarryIn, BIT* CarryOut, BIT* Sum)
{
  // TODO: implement a 1-bit adder
  // Note: you can probably copy+paste this from your (or my) Lab 5 solution
  
}


void ALU1(BIT A, BIT B, BIT Binvert, BIT CarryIn, BIT Less, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut, BIT* Set)
{
  // TODO: implement a 1-bit ALU 
  // Note: this will need modifications from Lab 5 to account for 'slt'
  // See slide "MSB ALU" in csci2500-f21-ch03a-slides.pdf
  
}


void ALU32(BIT* A, BIT* B, BIT Binvert, BIT CarryIn, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut)
{
  // TODO: implement a 32-bit ALU
  // You'll need to essentially implement a 32-bit ripple adder here
  // See slide "New 32-bit ALU" in csci2500-f21-ch03a-slides.pdf
  
}

/******************************************************************************/
/* Insane in the membmain */
/******************************************************************************/
int main()
{
  // convert some arbitrary number of instructions from stdin
  convert_instructions();
  
  // Unit test for 5-to-32 decoder
  printf("\n===== Unit test for 5-to-32 decoder =====\n");
  printf("decoder( I4, I3, I2, I1, I0 ) | ( O31, O30, ..., O1, O0 )\n");
  printf("------------------------------|--------------------------------------------------------------------------------------------------\n" );
  BIT I[5] = {0};
  BIT O[32] = {0};
  for (I[4] = 0; I[4] < 2; ++I[4])
    for (I[3] = 0; I[3] < 2; ++I[3])
      for (I[2] = 0; I[2] < 2; ++I[2])
        for (I[1] = 0; I[1] < 2; ++I[1])
          for (I[0] = 0; I[0] < 2; ++I[0]) {
              decoder5(I, O);
              printf( "decoder( %2d, %2d, %2d, %2d, %2d, ) | ( ",
                I[4], I[3], I[2], I[1], I[0]);
              printf("%2d", O[31]);
              for (int i = 30; i >= 0; --i)
                printf(", %2d", O[i]);
              printf(" )\n");
            }

  return 0;
}

