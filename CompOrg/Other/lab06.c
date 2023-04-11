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
void r_calc(char r1[],char *r){
	  	if(!strcmp(r1,"t0")){
  			strcpy(r,"01000");
  		}
  		if(!strcmp(r1,"s0")){
  			strcpy(r,"10000");
  		}
}
void convert_binary(int n, BIT *A){
	if(n > 0){
		for(int i=0;i<32;i++){    
				A[i]= (n%2 == 1);    
				n=n/2;    
		}   
	}
	if(n < 0){
		for(int i=0;i<32;i++){    
				A[i]= (n%2 == 0);     
				n=n/2;    
		}   
	}

}

BIT convertToBit(char bit) {
	if (bit == '1') {
		return TRUE;
	}
	else {
		return FALSE;
	}
}


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
  	char operation[10];
  	char one[3];
  	char two[3];
    char rd[6];
    char rt[6];
    char rs[6];


    char after[3];
  	char three[3];
  	char funct[7];
  	char shamt[6];
  	char opcode[7];
  	char instruction[256];
  	
  	sscanf(line,"%s %s %s %s %s",operation,one,two,three, after);
    //printf("%s",operation)

  	if(!strcmp(operation,"add")){
  		strcpy(funct, "100000");
  		strcpy(shamt,"00000");
  		strcpy(rd,one);

  		if(!strcmp(rd,"t0")){
  			strcpy(rd,"01000");
  		}
  		else{
  			strcpy(rd,"10000");
  		}
  		strcpy(rt,two);
  		if(!strcmp(rt,"t0")){
  			strcpy(rt,"01000");
  		}
  		else{
  			strcpy(rt,"10000");
  		}
  		strcpy(rs,three);
  		if(!strcmp(rs,"t0")){
  			strcpy(rs,"01000");
  		}
  		else{
  			strcpy(rs,"10000");
  		}
  		strcpy(opcode,"000000");

  		sprintf(instruction, "%s%s%s%s%s%s", opcode,rt,rs,rd,shamt,funct);

  		for(int i = 31; i >=0; --i){
  			Output[31-i] = convertToBit(instruction[i]);
  		}
     



  	}
  	if(!strcmp(operation,"lw")){
  		strcpy(funct,"100011");
  		strcpy(shamt,"00000");
  		r_calc(one,rd);
  		r_calc(two,rt);


  		strcpy(opcode,"000011");
  		int n = atoi(three);
      int t = atoi(after);
      n= n * t;
  		BIT A[32] = {FALSE};
  		convert_binary(n, A);
      strcpy(rd,A);
      sprintf(instruction, "%s%s%s%s%s%s", opcode,rs,rt,rd,shamt,funct);

      for(int i = 31; i >=0; --i){
        Output[31-i] = convertToBit(instruction[i]);
      }


  	}
  	if(!strcmp(operation,"j")){
  		strcpy(funct,"000010");
  		strcpy(shamt,"00000");
  		strcpy(opcode,"000010");
	  	int n = atoi(three);
		  BIT A[32] = {FALSE};
	  	convert_binary(n, A);

      sprintf(instruction, "%s%s", opcode,A);

      for(int i = 31; i >=0; --i){
        Output[31-i] = convertToBit(instruction[i]);
      }

  	}

    for (int i = 31; i >= 0; --i) {
      printf("%d", Output[i]);
    }
    printf("\n");
    return;
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
  O[7]=and_gate(EN, and_gate3(I[2],                      I[1],               I[0]));
  O[6]=and_gate(EN, and_gate3(I[2],                      I[1],      not_gate(I[0])));
  O[5]=and_gate(EN, and_gate3(I[2],             not_gate(I[1]),              I[0]));
  O[4]=and_gate(EN, and_gate3(I[2],             not_gate(I[1]),     not_gate(I[0])));
  O[3]=and_gate(EN, and_gate3(not_gate(I[2]),            I[1],               I[0]));
  O[2]=and_gate(EN, and_gate3(not_gate(I[2]),            I[1],      not_gate(I[0])));
  O[1]=and_gate(EN, and_gate3(not_gate(I[2]),   not_gate(I[1]),              I[0]));
  O[0]=and_gate(EN, and_gate3(not_gate(I[2]),   not_gate(I[1]),     not_gate(I[0])));
  return;
}

void decoder5(BIT* I, BIT* O)
{
  // TODO: implement 5-to-32 decoder using 2-to-4 and 3-to-8 decoders
  // https://fci.stafpu.bu.edu.eg/Computer%20Science/4887/crs-12801/Files/hw4-solution.pdf
  BIT first_output[4] = {0};
  decoder2(I[3],I[4],&first_output[0],&first_output[1],&first_output[2],&first_output[3]);
  BIT *output_ptr=&O[0];
  decoder3(I,first_output[0],output_ptr);
  output_ptr=&O[8];
  decoder3(I,first_output[1],output_ptr);
  output_ptr=&O[16];
  decoder3(I,first_output[2],output_ptr);
  output_ptr=&O[24];
  decoder3(I,first_output[3],output_ptr);
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
  if(a > 0){
    for(int i=0;i<32;i++){    
        A[i]= (a%2 == 1);    
        a=a/2;    
    }   
  }
  if(a < 0){
    for(int i=0;i<32;i++){    
        A[i]= (a%2 == 0);     
        a=a/2;    
    }   
  }
  
}

void adder1(BIT A, BIT B, BIT CarryIn, BIT* CarryOut, BIT* Sum)
{
	*Sum = xor_gate(xor_gate(A,B),CarryIn);
	*CarryOut = or_gate(and_gate(CarryIn,xor_gate(A,B)),and_gate(A,B));
  
}


void ALU1(BIT A, BIT B, BIT Binvert, BIT CarryIn, BIT Less, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut, BIT* Set)
{
  // TODO: implement a 1-bit ALU 
  // Note: this will need modifications from Lab 5 to account for 'slt'
  // See slide "MSB ALU" in csci2500-f21-ch03a-slides.pdf
  
  BIT Sum = TRUE;
  adder1(A, multiplexor2(Binvert, B, not_gate(B)), CarryIn, CarryOut, &Sum);
  *Set = Sum;
  *Result = multiplexor4(Op0, Op1, and_gate(A, multiplexor2(Binvert, B, not_gate(B))),
                         or_gate(A, multiplexor2(Binvert, B, not_gate(B))), Sum, Less);

}


void ALU32(BIT* A, BIT* B, BIT Binvert, BIT CarryIn, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut)
{
  // TODO: implement a 32-bit ALU
  // You'll need to essentially implement a 32-bit ripple adder here
  // See slide "New 32-bit ALU" in csci2500-f21-ch03a-slides.pdf
  BIT Less = FALSE;
  BIT Set = FALSE;
  ALU1(A[0],B[0],Binvert,CarryIn,Less,Op0,Op1,&Result[0],CarryOut,&Set);
  for(unsigned int i = 0; i < 32; i++){
    ALU1(A[i],B[i],Binvert,*CarryOut,Less,Op0,Op1,&Result[i],CarryOut,&Set);
  }
  Less = Set;
  ALU1(A[0],B[0],Binvert,CarryIn,Less,Op0,Op1,&Result[0],CarryOut,&Set);

  
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
/*
  BIT x = FALSE;
  ALU32(TWO, THREE, TRUE, x, x, x , RESULT, Carry);
  for(int i =0; i <32; i++){
    if(RESULT[i]== TRUE){
      printf("1");
    }
    else
      printf("0");
  }
  */
  return 0;
}


