#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char BIT;
#define TRUE 1
#define FALSE 0
#define UNDEF -1


BIT not_gate(BIT A)
{
  if (A)
    return FALSE;
  else
    return TRUE;
}

BIT or_gate(BIT A, BIT B)
{
  // TODO: implement logical OR
  if (A || B)
    return TRUE;
  else
    return FALSE;
}

BIT and_gate(BIT A, BIT B)
{
  // TODO: implement logical AND
  if (A && B)
    return TRUE;
  else
    return FALSE;
}

BIT xor_gate(BIT A, BIT B)
{
  // TODO: implement logical XOR
  if (A ^ B)
    return TRUE;
  else
    return FALSE;
}

void adder1(BIT A, BIT B, BIT CarryIn, BIT* CarryOut, BIT* Sum)
{
  // TODO: implement a 1-bit adder
  BIT x0 = xor_gate(A, B);
  *Sum = xor_gate(CarryIn, x0);
  BIT y0 = and_gate(x0, CarryIn);
  BIT y1 = and_gate(A, B);
  *CarryOut = or_gate(y0, y1);
}


void adder4(BIT A[4], BIT B[4], BIT CarryIn, BIT* CarryOut, BIT Sum[4])
{
  // TODO: implement a 4-bit adder using the 1-bit adder as a helper function
  int i;
  BIT tempSum = 0;
	for(i = 3; i >= 0; i--){
		adder1(A[i], B[i], CarryIn, CarryOut, &tempSum);
		Sum[i] = tempSum;
		CarryIn = *CarryOut;
  }
}

void adder16(BIT A[16], BIT B[16], BIT CarryIn, BIT* CarryOut, BIT Sum[16]){
	int i;
	/*while(i < 5){
		//gen_and_prop(A, B, CarryIn)
	}*/
	BIT tempA[4];
	BIT tempB[4];
	BIT tempSum[4];
	for(i = 3; i >= 0; i--){
		memcpy(tempA, &A[4*i], 4);
		memcpy(tempB, &B[4*i], 4);
		memset(tempSum, 0, 4);
		adder4(tempA, tempB, CarryIn, CarryOut, tempSum);
		memcpy(&Sum[4*i], &tempSum[0], 4);
		CarryIn = *CarryOut;
	}
}

void to_binary(int x, BIT Z[16]){
	int i, b = 32768;
	if(x < 0)
		x += 65536;
	for(i = 15; i >= 0; i--) {
		if(b <= x) {
			x -= b;
			Z[15-i] = 1;
		}
		else
			Z[15-i] = 0;
		b = b/2;
	}
}

void combine(int x, BIT Y[32], BIT Z[16]) {
	int i;
	for(i = 0; i < 32; i++) {
		if(i < 16) {
			if(x < 0)
				Y[i] = 1;
			else
				Y[i] = 0;
		}
		else
			Y[i] = Z[i-16];
	}
}

int main(int argc, char **argv) {
	int i;
	char first[128], instruction, second[128], line[128], *temp, plus[3] = "+";
	fgets(line, 128, stdin);
	temp = strtok(line, " ");
	memcpy(first, &temp[0], strlen(temp));
	temp = strtok(NULL, " ");
	if(strcmp(temp, plus) == 0)
		instruction = '+';
	else
		instruction = '/';
	temp = strtok(NULL, " ");
	memcpy(second, &temp[0], strlen(temp));
 	second[strlen(second)-1] = '\0';
	//printf("%s %c %s\n", first, instruction, second);
	int f = atoi(first);
	int s = atoi(second);
	BIT A[32], tempA[16], B[32], tempB[16], Sum[32];
	to_binary(f, tempA);
	to_binary(s, tempB);
	BIT CarryOut, tempSum[16];
	BIT CarryIn = 0;
	adder16(tempA, tempB, CarryIn, &CarryOut, tempSum);
	combine(f, A, tempA);
	combine(s, B, tempB);
	if(f < 0)
		combine(f, Sum, tempSum);
	else
		combine(s, Sum, tempSum);
	for(i = 0; i < 32; i++)
		printf("%d", A[i]);
	printf("\n%c\n", instruction);
	for(i = 0; i < 32; i++)
		printf("%d", B[i]);
	printf("\n=\n");
	for(i = 0; i < 32; i++)
		printf("%d", Sum[i]);
	printf("\n");
	return 0; 
}