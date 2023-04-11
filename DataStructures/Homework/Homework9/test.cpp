#include <iostream>
#include <string>
#include <math.h>
#include <vector>


int function(std::string x){
	int number=0;
	for(int i=0; i<x.size(); i++){
		if(x[i]=='a') number+=pow(1,i+1);
		if(x[i]=='t') number+=pow(2,i+1);
		if(x[i]=='c') number+=pow(3,i+1);
		if(x[i]=='g') number+=pow(4,i+1);
	}
	return (number*10%999);
};

int main(){
	int kmer =10;
	while(true){
		std::string query;
		std::cout << "Enter the first digits: ";;
		std::cin >> query;

		if(query == "quit") break;
		int limit = kmer/2;
		std::cout << function(query.substr(0,limit)) <<std::endl;
		std::vector<int> *table;

	}
	std::vector<int> t;
	t.resize(100);
	t[98]=98;
	std::cout << t[98];
};