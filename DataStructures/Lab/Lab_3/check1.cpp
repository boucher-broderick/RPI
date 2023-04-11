#include <iostream>

void compute_square(const unsigned int n, int a[], int b[])
{
	int *i=a;
	int *x=b;
	for(int j=0; j<n; j++)
	{
		
		*x=*i * *i;
		std::cout << *i << " squared is " << *x << std::endl;
		x++;
		i++;
	}
}


int main()
{
	unsigned int n=4;
	int a[n]={2,3,4,9};
	int b[n];

	compute_square(n,a,b);

}

