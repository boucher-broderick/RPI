#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void main() {
	int *p1 = malloc(2*sizeof(int));  //creates an array to hold 4 ints
	p1[0] = 5; p1[1] = 6; 
	p1 = realloc(p1, 5*sizeof(int));
	p1[2] = 7;
	printf("%d %d %d", p1[0],p1[1],p1[2]);
	p1= calloc(2, sizeof(int));
	printf("%d %d %d", p1[0],p1[1],p1[2]);
	free(p1);

}
