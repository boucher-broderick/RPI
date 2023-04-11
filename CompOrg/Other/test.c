#include <stdio.h>
#include <string.h>
#include <math.h>

void triangle( int x){
	int i;
	for(i=x; i>0; --i){
		int mem =i*2;
		char temp[mem];
		memset(temp, '*', (mem-1));
		printf("%s \n", temp);
		memset(temp, '\0', (mem-1));
	}
}

void triangle1(int x){
	for(int i=x; i>0; i--){
		for(int ast=0; ast<i*2-1; ast++){
			printf("*");
		}
		printf("\n");
	}
}

void hypoth(int n){
	int length=n;
	int height=n*2-1;
	long x = length*length + height*height;
	double result =sqrt(x);
	printf("Length of the Hypothesis %1.2f\n", result);
}

long fib(long x)
{
	if(x==1){
		return 1;
	}
	if(x==0){
		return 0;
	}
	else{
		return (fib(x-1) + fib(x-2));
	}
}

void fib1(int x){
	long n =x;
	long result = fib(n);
	printf("Fibonacci %ld\n", result);
}


void fib2(int x){
	int i = x-1;
	long num1=1;
	long num0=0;
	long curr;
	for(int j=i; j>0; --j){
		curr=num1+num0;
		num0=num1;
		num1=curr;
	}
	printf("Fibonacci %ld\n", curr);

}


int main (void){

	int n;
	printf("What is n? ");
	scanf("%d", &n);
	triangle1(n);
	triangle(n);
	hypoth(n);
	int m;
	printf("What is n? ");
	scanf("%d", &m);
	fib1(m);
	fib2(m);
	
	return 0;

}