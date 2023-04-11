#include <vector>
#include <iostream>


int main(){
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(6);

	vec.erase(2);
	for(int i : vec){
		std::cout << i << std::endl;
	}
}