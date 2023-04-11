/* 
Class Project: The logical conclusion (v1.1)
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

// useful constants
BIT ONE[32] = {TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE};
BIT ZERO[32] = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE};
BIT REG_THIRTY_ONE[5] = {TRUE, TRUE, TRUE, TRUE, TRUE};
BIT THIRTY_TWO[32] = {FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, 
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE};

/******************************************************************************/
/* Function prototypes */
/******************************************************************************/
BIT not_gate(BIT A);
BIT or_gate(BIT A, BIT B);
BIT or_gate3(BIT A, BIT B, BIT C);
BIT and_gate(BIT A, BIT B);
BIT and_gate3(BIT A, BIT B, BIT C);
BIT xor_gate(BIT A, BIT B);
BIT nor_gate(BIT A, BIT B);
BIT nand_gate(BIT A, BIT B);

void decoder2(BIT I0, BIT I1, BIT* O0, BIT* O1, BIT* O2, BIT* O3);
BIT multiplexor2(BIT S, BIT I0, BIT I1);
void multiplexor2_32(BIT S, BIT* I0, BIT* I1, BIT* Output);
BIT multiplexor4(BIT S0, BIT S1, BIT I0, BIT I1, BIT I2, BIT I3);

void copy_bits(BIT* A, BIT* B);
void print_binary(BIT* A);
void convert_to_binary(int a, BIT* A, int length);
void convert_to_binary_char(int a, char* A, int length);
int binary_to_integer(BIT* A);

int get_instructions(BIT Instructions[][32]);

void Instruction_Memory(BIT* ReadAddress, BIT* Instruction);
void Control(BIT* OpCode,
  BIT* RegDst, BIT* Jump, BIT* Branch, BIT* MemRead, BIT* MemToReg,
  BIT* ALUOp, BIT* MemWrite, BIT* ALUSrc, BIT* RegWrite, BIT* numberadd, BIT* Jlink, BIT* Jreturn);
void Read_Register(BIT* ReadRegister1, BIT* ReadRegister2,
  BIT* ReadData1, BIT* ReadData2);
void Write_Register(BIT RegWrite, BIT* WriteRegister, BIT* WriteData);
void ALU_Control(BIT* ALUOp, BIT* funct, BIT* ALUControl);
void ALU(BIT* ALUControl, BIT* Input1, BIT* Input2, BIT* Zero, BIT* Result);
void Data_Memory(BIT MemWrite, BIT MemRead, 
  BIT* Address, BIT* WriteData, BIT* ReadData);
void Extend_Sign16(BIT* Input, BIT* Output);
void updateState();
  
/******************************************************************************/
/* Functions provided for your convenience */
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

BIT or_gate3(BIT A, BIT B, BIT C)
{
  return or_gate(A, or_gate(B, C));
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

BIT and_gate6(BIT A, BIT B, BIT C, BIT D, BIT E, BIT F)
{
  return and_gate(and_gate3(A, B, C), and_gate3(D, E, F));
}

BIT xor_gate(BIT A, BIT B)
{
  if (A ^ B)
    return TRUE;
  else
    return FALSE;
}

BIT nor_gate(BIT A, BIT B)
{
  return not_gate(or_gate(A, B));
}

BIT nand_gate(BIT A, BIT B)
{
  return not_gate(and_gate(A, B));
}

void decoder2(BIT I0, BIT I1, BIT* O0, BIT* O1, BIT* O2, BIT* O3)
{
  // Note: The input -> output mapping is slightly modified from before
  *O0 = and_gate(not_gate(I1), not_gate(I0));
  *O1 = and_gate(not_gate(I1), I0);
  *O2 = and_gate(I1, not_gate(I0));
  *O3 = and_gate(I1, I0);
  return;                       
}

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

BIT multiplexor2(BIT S, BIT I0, BIT I1)
{
  BIT x0 = and_gate(not_gate(S), I0);
  BIT x1 = and_gate(S, I1);
  return or_gate(x0, x1);  
}

void multiplexor2_32(BIT S, BIT* I0, BIT* I1, BIT* Output)
{
  for (int i = 0; i < 32; ++i) {
    BIT x0 = and_gate(not_gate(S), I0[i]);
    BIT x1 = and_gate(S, I1[i]);
    Output[i] = or_gate(x0, x1);
  }
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
/* Helper functions */
/******************************************************************************/
void copy_bits(BIT* A, BIT* B)
{
  for (int i = 0; i < 32; ++i)
    B[i] = A[i]; 
}

void print_binary(BIT* A)
{
  for (int i = 31; i >= 0; --i)
    printf("%d", A[i]); 
}

void convert_to_binary(int a, BIT* A, int length)
{
  /* Use your implementation from Lab 6 */
   if(a > 0){
      for(int i=0;i<length;i++){    
          //if a%2 == 1, A[i] = TRUE, If a%2 != 1 A[i] = False
          if(a%2 == 1){
            A[i] = TRUE;
          }
          else{
            A[i] = FALSE;
          }  
          a=a/2;    
      }   
    }
    if(a < 0){
      for(int i=0;i<length;i++){  
          //if a%2 == 0, A[i] = TRUE, If a%2 != 0 A[i] = False
          if(a%2 == 0){
            A[i] = TRUE;
          }
          else{
            A[i] = FALSE;
          }
          a=a/2;    
      }   
    }
}

void convert_to_binary_char(int a, char* A, int length)
{
  /* Use your implementation from Lab 6 */
   if(a > 0){
      for(int i=0;i<length;i++){    
          //if a%2 == 1, A[i] = '1', If a%2 != 1 A[i] = '0'
          if(a%2 == 1){
            A[i] = '1';
          }
          else{
            A[i] = '0';
          }  
          a=a/2;    
      }   
    }
    if(a < 0){
      for(int i=0;i<length;i++){  
          //if a%2 == 0, A[i] = '1', If a%2 != 0 A[i] = '0'
          if(a%2 == 0){
            A[i] = '1';
          }
          else{
            A[i] = '0';
          }
          a=a/2;    
      }   
    }
}
  
int binary_to_integer(BIT* A)
{
  unsigned a = 0;
  unsigned mult = 1;
  
  for (int i = 0; i < 32; ++i) {
    a += A[i]*mult;
    mult *= 2;
  }
  
  return (int)a;
}


/******************************************************************************/
/* Parsing functions */
/******************************************************************************/

// TODO: Implement any helper functions to assist with parsing
//register_calc
void r_calc(char op[],char *r){
      if(!strcmp(op,"t0")){
        strcpy(r,"00010");
      }
      if(!strcmp(op,"t1")){
        strcpy(r,"10010");
      }
      if(!strcmp(op,"s0")){
        strcpy(r,"00001");
      }
      if(!strcmp(op,"s1")){
        strcpy(r,"10001");
      }
      if(!strcmp(op,"a0")){
        strcpy(r,"00100");
      }
      if(!strcmp(op,"v0")){
        strcpy(r,"01000");
      }
      if(!strcmp(op,"zero")){
        strcpy(r,"00000");
      }
      if(!strcmp(op,"sp")){
        strcpy(r,"10111");
      }
      return;
}

void opcode_calc(char op[],char *r){
  if(!strcmp(op,"lw")){
    strcpy(r,"100011");
  }
  if(!strcmp(op,"lw")){
    strcpy(r,"101011");
  }
  if(!strcmp(op,"beq")){
    strcpy(r,"000100");
  }
  if(!strcmp(op,"and") || !strcmp(op,"or") || !strcmp(op,"add") || !strcmp(op,"sub") || !strcmp(op,"slt") || !strcmp(op,"jr")){
    strcpy(r,"000000");
  }
  if(!strcmp(op,"j")){
    strcpy(r,"000010");
  }
  if(!strcmp(op,"jal")){
    strcpy(r,"000011");
  }
  return;
}

void funct_calc(char op[],char *r){
  if(!strcmp(op,"and")){
    strcpy(r,"100100");
  }
  if(!strcmp(op,"or")){
    strcpy(r,"100101");
  }
  if(!strcmp(op,"add")){
    strcpy(r,"100000");
  }
  if(!strcmp(op,"sub")){
    strcpy(r,"100010");
  }
  if(!strcmp(op,"slt")){
    strcpy(r,"100011");
  }
}


int get_instructions(BIT Instructions[][32])
{     
    // TODO: perform conversion of instructions to binary
    // Input: coming from stdin via: ./a.out < input.txt
    // Output: Convert instructions to binary in the instruction memory
    // Return: Total number of instructions
    // Note: you are free to use if-else and external libraries here
    // Note: you don't need to implement circuits for saving to inst. mem.
    // My approach:
    // - Use sscanf on line to get strings for instruction and registers
    // - Use instructions to determine op code, funct, and shamt fields
    // - Convert immediate field and jump address field to binary
    // - Use registers to get rt, rd, rs fields
    // Note: I parse everything as strings, then convert to BIT array at end
    
    char line[256] = {0};
    int instruction_count = 0;  
    while(fgets(line, 256, stdin) != NULL){
      BIT Output[32] = {FALSE};
      char operation[16] = {0};
      char reg1[16] = {0};
      char reg2[16] = {0};
      char reg3[16] = {0};
      char opcode[6] = {0};
      sscanf(line, "%s ", operation);
      if (strcmp(operation,"lw") == 0 || strcmp(operation,"sw") == 0 || strcmp(operation,"beq") == 0 || strcmp(operation,"addi") == 0) {
        sscanf(line, "%s %s %s %s", operation, reg1, reg2, reg3);
        char rs[5] = {0};
        char rt[5] = {0};
        char immediate[16] = {0};

      }
      if (strcmp(operation,"and") == 0 || strcmp(operation,"or") == 0 || strcmp(operation,"add") == 0 || strcmp(operation,"sub") == 0 || strcmp(operation,"slt") == 0 ) {
        sscanf(line, "%s %s %s %s", operation, reg1, reg2, reg3);
        char rs[5] = {0};
        char rt[5] = {0};
        char rd[5] = {0};
        char shamt[5] = "0000";
        char funct[6] = {0};

      }
      if (strcmp(operation,"j") == 0 || strcmp(operation,"jal") == 0 || strcmp(operation,"jr") == 0) {
        sscanf(line, "%s %s", operation, reg1);
        
      }

  
  }
  return instruction_count;
}


/******************************************************************************/
/* Program state - memory spaces, PC, and control */
/******************************************************************************/
BIT PC[32]                  = {FALSE};
BIT MEM_Instruction[32][32] = {FALSE};
BIT MEM_Data[32][32]        = {FALSE};
BIT MEM_Register[32][32]    = {FALSE};

BIT RegDst    = FALSE;
BIT Jump      = FALSE;
BIT Branch    = FALSE;
BIT MemRead   = FALSE;
BIT MemToReg  = FALSE;
BIT ALUOp[2]  = {FALSE};
BIT MemWrite  = FALSE;
BIT ALUSrc    = FALSE;
BIT RegWrite  = FALSE;
BIT Zero      = FALSE;
BIT ALUControl[4] = {FALSE};
BIT numberadd = FALSE;
BIT Jlink= FALSE;
BIT Jreturn = FALSE;

void print_instruction()
{
  unsigned pc = binary_to_integer(PC);
  printf("PC: %d\n", pc);
  printf("Instruction: ");
  print_binary(MEM_Instruction[pc]);
  printf("\n");
}

void print_state()
{
  printf("Data: ");
  for (int i = 0; i < 32; ++i) {
    printf("%d ", binary_to_integer(MEM_Data[i]));
  } 
  printf("\n");  
  
  printf("Register: ");
  for (int i = 0; i < 32; ++i) {
    printf("%d ", binary_to_integer(MEM_Register[i]));
  } 
  printf("\n");
}


/******************************************************************************/
/* Functions that you will implement */
/******************************************************************************/
void Instruction_Memory(BIT* ReadAddress, BIT* Instruction)
{
  // TODO: Implement instruction memory
  // Input: 32-bit instruction address
  // Output: 32-bit binary instruction
  // Note: Useful to use a 5-to-32 decoder here
  BIT AR1[32];
  decoder5(ReadAddress, AR1);
  for(int i = 0; i < 32; i++){
    for(int j = 0; j < 32; i++){
      BIT Input = AR1[i];
      Instruction[j] = multiplexor2(Input, Instruction[j], MEM_Instruction[i][j]);
    }
  }
}

void Control(BIT* OpCode,
  BIT* RegDst, BIT* Jump, BIT* Branch, BIT* MemRead, BIT* MemToReg,
  BIT* ALUOp, BIT* MemWrite, BIT* ALUSrc, BIT* RegWrite, BIT* numberadd, BIT* Jlink, BIT* Jreturn)
{
  // TODO: Set control bits for everything
  // Input: opcode field from the instruction
  // OUtput: all control lines get set 
  // Note: Can use SOP or similar approaches to determine bits

   // 100011
  BIT lw = and_gate6( OpCode[0], OpCode[1], OpCode[5], not_gate(OpCode[2]), not_gate(OpCode[3]), not_gate(OpCode[4]));   
  // 101011    
  BIT sw = and_gate6(OpCode[0], OpCode[1], OpCode[3], OpCode[5], not_gate(OpCode[2]), not_gate(OpCode[4]));       
  // 000100
  BIT beq =  and_gate6(OpCode[2], not_gate(OpCode[0]), not_gate(OpCode[1]), not_gate(OpCode[3]), not_gate(OpCode[4]), not_gate(OpCode[5]));     
  // 001000
  BIT addi = and_gate6(OpCode[3], not_gate(OpCode[0]), not_gate(OpCode[1]), not_gate(OpCode[2]), not_gate(OpCode[4]), not_gate(OpCode[5]));

  BIT typeI = or_gate(or_gate(lw,sw),or_gate(beq,addi));

  *Branch = beq;
  *MemRead = lw;
  *MemWrite = sw;
  *numberadd = addi;
  *ALUSrc = or_gate(lw,sw);
  *RegWrite = or_gate(not_gate(beq), not_gate(sw));

  // 100100
  BIT and = and_gate6( OpCode[2], OpCode[5], not_gate(OpCode[0]), not_gate(OpCode[1]), not_gate(OpCode[3]), not_gate(OpCode[4]));   
  // 100101     
  BIT or = and_gate6(OpCode[0], OpCode[2], OpCode[5], not_gate(OpCode[1]), not_gate(OpCode[3]), not_gate(OpCode[4]));
  //  100000       
  BIT add =  and_gate6( OpCode[5], not_gate(OpCode[0]), not_gate(OpCode[1]), not_gate(OpCode[2]), not_gate(OpCode[3]), not_gate(OpCode[4]));     
  // 100010
  BIT sub = and_gate6(OpCode[1], OpCode[5], not_gate(OpCode[0]), not_gate(OpCode[2]), not_gate(OpCode[3]), not_gate(OpCode[4]));    
  // 101010
  BIT slt = and_gate6(OpCode[1], OpCode[3], OpCode[5], not_gate(OpCode[0]), not_gate(OpCode[2]), not_gate(OpCode[4]));    
  
  BIT typeR = or_gate3(and, or, or_gate3(add, sub, slt));

  *RegDst = typeR;
  *MemToReg = or_gate(lw, typeR);

  //000010
  BIT j = and_gate6( OpCode[1], not_gate(OpCode[0]), not_gate(OpCode[2]), not_gate(OpCode[3]), not_gate(OpCode[4]), not_gate(OpCode[5]));  
  //001000
  BIT jr = and_gate6( OpCode[3], not_gate(OpCode[0]), not_gate(OpCode[1]), not_gate(OpCode[2]), not_gate(OpCode[4]), not_gate(OpCode[5]));  
  //000011
  BIT jal = and_gate6(OpCode[0], OpCode[1], not_gate(OpCode[2]), not_gate(OpCode[3]), not_gate(OpCode[4]), not_gate(OpCode[5]));  

  BIT typeJ = or_gate3(j, jr, jal);

  *Jump = typeJ;
  *Jlink = jal;
  *Jreturn = jr;


  ALUOp[1]= typeR;
  ALUOp[0]= beq;


  
}

void Read_Register(BIT* ReadRegister1, BIT* ReadRegister2,
  BIT* ReadData1, BIT* ReadData2)
{
  // TODO: Implement register read functionality
  // Input: two 5-bit register addresses
  // Output: the values of the specified registers in ReadData1 and ReadData2
  // Note: Implementation will be very similar to instruction memory circuit
  
  BIT AR1[32];
  BIT AR2[32];
  decoder5(ReadRegister1, AR1);
  decoder5(ReadRegister2, AR2);
  for(int i = 0; i < 32; i++){
    for(int j = 0; j < 32; j++){
      BIT Input1 = AR1[i];
      BIT Input2 = AR2[i];
      ReadData1[j] = multiplexor2(Input1, ReadData1[j], MEM_Register[i][j]);
      ReadData2[j] = multiplexor2(Input2, ReadData1[j], MEM_Register[i][j]);
    }
  }
}

void Write_Register(BIT RegWrite, BIT* WriteRegister, BIT* WriteData)
{
  // TODO: Implement register write functionality
  // Input: one 5-bit register address, data to write, and control bit
  // Output: None, but will modify register file
  // Note: Implementation will again be similar to those above
  BIT AR1[32];
  decoder5(WriteRegister, AR1);
  for(int i = 0; i < 32; i++){
    for(int j = 0; j < 32; j++){
      BIT Input = and_gate(AR1[i], RegWrite);
      MEM_Register[i][j] = multiplexor2(Input, MEM_Register[i][j], WriteData[j]);
    }
  }
  
}

void ALU_Control(BIT* ALUOp, BIT* funct, BIT* ALUControl)
{
  // TODO: Implement ALU Control circuit
  // Input: 2-bit ALUOp from main control circuit, 6-bit funct field from the
  //        binary instruction
  // Output:4-bit ALUControl for input into the ALU
  // Note: Can use SOP or similar approaches to determine bits
  ALUControl[0] = or_gate(  ALUOp[0], and_gate(ALUOp[1], funct[1]));
  ALUControl[1] = and_gate( ALUOp[1], or_gate( funct[0], funct[3]));
  ALUControl[2] = nand_gate(ALUOp[1],                    funct[2]);
}

void adder1(BIT A, BIT B, BIT CarryIn, BIT* CarryOut, BIT* Sum)
{
  *Sum = xor_gate(xor_gate(A,B),CarryIn);
  *CarryOut = or_gate(and_gate(CarryIn,xor_gate(A,B)),and_gate(A,B));
  
}

void ALU1(BIT A, BIT B, BIT Binvert, BIT CarryIn, BIT Less, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut, BIT* Set)
{
  
  BIT Sum = TRUE;
  adder1(A, multiplexor2(Binvert, B, not_gate(B)), CarryIn, CarryOut, &Sum);
  *Set = Sum;
  *Result = multiplexor4(Op0, Op1, and_gate(A, multiplexor2(Binvert, B, not_gate(B))),
                         or_gate(A, multiplexor2(Binvert, B, not_gate(B))), Sum, Less);

}

void ALU(BIT* ALUControl, BIT* Input1, BIT* Input2, BIT* Zero, BIT* Result)
{   
  // TODO: Implement 32-bit ALU
  // Input: 4-bit ALUControl, two 32-bit inputs
  // Output: 32-bit result, and zero flag big
  // Note: Can re-use prior implementations (but need new circuitry for zero)
  BIT Less = FALSE;
  BIT Set = FALSE;
  BIT CarryOut[1] = {FALSE};
  //run 1 bit alu once
  ALU1(Input1[0],Input2[0],ALUControl[0],ALUControl[1],Less,ALUControl[1],ALUControl[2],&Result[0],CarryOut,&Set);
  //run 32 times
  for(unsigned int i = 0; i < 32; i++){
    ALU1(Input1[i],Input2[i],ALUControl[0],ALUControl[1],Less,ALUControl[1],ALUControl[2],&Result[i],CarryOut,&Set);
  }
  Less = Set;
  ALU1(Input1[0],Input2[0],ALUControl[0],ALUControl[1],Less,ALUControl[1],ALUControl[2],&Result[0],CarryOut,&Set);

  *Zero = FALSE;
  int i = 0;
  while(i < 32){
    *Zero  = or_gate(*Zero, Result[i]);
    i++;
  }
  *Zero = not_gate(*Zero);
}

void Data_Memory(BIT MemWrite, BIT MemRead, 
  BIT* Address, BIT* WriteData, BIT* ReadData)
{
  // TODO: Implement data memory
  // Input: 32-bit address, control flags for read/write, and data to write
  // Output: data read if processing a lw instruction
  // Note: Implementation similar as above
  BIT AR1[32];
  BIT Temp[5];
  Temp[0] = Address[0];
  Temp[1] = Address[1];
  Temp[2] = Address[2];
  Temp[3] = Address[3];
  Temp[4] = Address[4];
  decoder5(Temp, AR1);
  for(int i = 0; i < 32; i++){
    for(int j = 0; j < 32; j++){
      BIT Input1 = and_gate(AR1[i], MemWrite);
      BIT Input2 = and_gate(AR1[i], MemRead);
      MEM_Data[i][j] = multiplexor2(Input1, MEM_Data[i][j], WriteData[j]);
      ReadData[j] = multiplexor2(Input2, ReadData[j], MEM_Data[i][j]);
    }
  }


}

void Extend_Sign16(BIT* Input, BIT* Output)
{
  // TODO: Implement 16-bit to 32-bit sign extender
  // Copy Input to Output, then extend 16th Input bit to 17-32 bits in Output
  BIT Sixteenth = Input[15];
  for(int i = 0; i < 16; i++){
    Output[i] = Input[i];
  }
  for(int i = 16; i < 32; i++){
    Output[i] = Sixteenth;
  }
}

void updateState()
{
  // TODO: Implement the full datapath here
  // Essentially, you'll be figuring out the order in which to process each of 
  // the sub-circuits comprising the entire processor circuit. It makes it 
  // easier to consider the pipelined version of the process, and handle things
  // in order of the pipeline. The stages and operations are:
  // Fetch - load instruction from instruction memory
  // Decode - set control bits and read from the register file
  // Execute - process ALU
  // Memory - read/write data memory
  // Write Back - write to the register file
  // Update PC - determine the final PC value for the next instruction


  BIT Instruct[32] = {FALSE};
  Instruction_Memory(PC, Instruct);

  BIT OP[6];
  OP[0] = Instruct[26];
  OP[1] = Instruct[27];
  OP[2] = Instruct[28];
  OP[3] = Instruct[29];
  OP[4] = Instruct[30];
  OP[5] = Instruct[31];

  Control(OP, &RegDst, &Jump, &Branch, &MemRead, &MemToReg, ALUOp, &MemWrite, &ALUSrc, &RegWrite, &numberadd, &Jlink, &Jreturn);

  BIT ReadReg1[5];
  BIT ReadReg2[5];
  BIT WriteReg[5];
  BIT function[5];
  BIT ReadData1[32];
  BIT ReadData2[32];

  for(int x= 11; x<16; x++){
    WriteReg[x-11] = Instruct[x];
  }
  for(int x =16; x <21; x++){
    ReadReg2[x-16] = Instruct[x];
  }
  for(int x =21; x < 26; x++){
     ReadReg1[x-21] = Instruct[x];
  }

  Read_Register(ReadReg1,ReadReg2,ReadData1,ReadData2);


  function[0] = Instruct[0];
  function[1] = Instruct[1];
  function[2] = Instruct[2];
  function[3] = Instruct[3];
  function[4] = Instruct[4];
  function[5] = Instruct[5];
    
  BIT signExtend16[16];
  BIT signExtend32[32];

  for(int x = 0; x < 16; x++){
    signExtend16[x] = Instruct[x];
  }
  Extend_Sign16(signExtend16, signExtend32);

  BIT is_jr = and_gate6(function[3], not_gate(function[0]), not_gate(function[1]), not_gate(function[2]), not_gate(function[4]), not_gate(function[5]));

  BIT ALUOuput[4];
  ALU_Control(ALUOp,function, ALUOuput);
  ALUOuput[1] = multiplexor2(numberadd, ALUOuput[1], numberadd); 


    BIT Result[32];
    BIT Output[32];
    BIT output_mux[5];
    multiplexor2_32(and_gate(ALUSrc,not_gate(Branch)), ReadData2, signExtend32, Output);
    ALU(ALUOuput, ReadData1, Output, &Zero, Result);
    Data_Memory(MemWrite, MemRead, Result, ReadData2, MEM_Data);
    
    for (int x = 0; x < 5; ++x) {
      output_mux[x] = multiplexor2(RegDst, ReadReg2[x], WriteReg[x]);
    }


    BIT temporary[32];
    for (int x = 0; x < 32; ++x) {
      temporary[x] = multiplexor2(MemToReg, Result[x], MEM_Data[x]);
    }
    Write_Register(and_gate(RegWrite, not_gate(is_jr)), output_mux, temporary);


    BIT Alu_OP[4] = {FALSE, TRUE, FALSE, FALSE}; 
    BIT temp_zero[32]; 
    BIT temp_PC[32];
    BIT branch_PC[32];
    

    ALU(Alu_OP, PC, ONE, temp_zero, temp_PC);
    ALU(Alu_OP, temp_PC, signExtend32, temp_zero, branch_PC);
    
    BIT RA[5] = {TRUE, TRUE, TRUE, TRUE, TRUE};
    Write_Register(Jlink, RA, temp_PC);
    
    for(int x = 0; x < 32; x++){
      PC[x] = multiplexor2(and_gate(Zero,Branch), temp_PC[x], branch_PC[x]);
    } 

    for(int x = 0; x < 32; x++){
      PC[x] = multiplexor2(or_gate(Jlink, Jump), PC[x], signExtend32[x]);
    } 
   
 
    BIT Return[32];
    Read_Register(RA, ZERO, Return, temp_zero);

    for (int x = 0; x < 32; x++) {
      PC[x] = multiplexor2(and_gate(Jreturn, is_jr), PC[x], Return[x]);
    }

  









  
}


/******************************************************************************/
/* Main */
/******************************************************************************/

int main()
{
  setbuf(stdout, NULL);
    
  // parse instructions into binary format
  int counter = get_instructions(MEM_Instruction);
  // load program and run
  copy_bits(ZERO, PC);
  copy_bits(THIRTY_TWO, MEM_Register[29]);
  
  while (binary_to_integer(PC) < counter) {
    print_instruction();
    updateState();
    print_state();
  }

  return 0;
}