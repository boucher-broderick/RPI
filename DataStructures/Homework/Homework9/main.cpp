#include <iostream>
#include <string>
#include <fstream>
#include "dna_hash.h"

int main(){
	
	std::string file;
	int table_size, kmer;
	double occupancy;
	std::cout << "genome ";
	std::cin >> file;
	std::cout << "table_size ";
	std::cin >> table_size;
	std::cout << "occupancy ";
	std::cin >> occupancy;
	std::cout << "kmer ";
	std::cin >> kmer;

	std::string genome;
	std::ifstream myfile (file);
 	if (myfile.is_open()){
 		std::string line;
    	while ( myfile >> line ){
      		std::cout << line;
      		genome+=line;
    	}
    	myfile.close();
  	}
	else std::cout << "Unable to open file";
	int x=0;
	for(int i=0; i<genome.size()-2*kmer; i++){
		x++;//std::cout << "\n" << genome.substr(i, kmer+i-1);
	}
	std::cout << x;

	Hash table(100);
};