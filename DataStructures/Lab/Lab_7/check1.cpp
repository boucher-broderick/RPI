#include <iostream>

int recurse(int x, int y)
{
	int p=0;
	int q=0;
	if(x==0 && y==0){
		return 1;
	}
	if(x>0){
	 p=recurse(x-1,y);
	}
	if(y>0){
	 q=recurse(x,y-1);
	}
	return p+q;

}

int main(){

	std::cout << recurse(2,2) <<std::endl;


};