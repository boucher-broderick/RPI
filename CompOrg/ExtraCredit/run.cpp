#include <iostream>
#include <fstream>
#include <string>
#include <vector>



int main() {
	std::vector<int> numbers;
	std::string line;
	std::ifstream myfile("first.txt");
	if (myfile.is_open())
	{
   		while ( getline (myfile,line) )
  	 	{
  			int num = std::stoi(line);
  			numbers.push_back(num);
   		}
	}

	

}