/*
	This file is the header for the Bowl class and initializes the
	bowlers as well as has getters and the functions in bowl.cpp
*/

#include <iostream>
#include <vector>
#include <string>

class Bowl
{
private:
	std::vector<int> pins;
	std::vector<std::string> name;
	
public:
	Bowl(std::vector<int> p, std::vector<std::string> n)
	{
	 pins=p;
     name=n;
	}

	//getters:
	const std::string getfirst() const { return  name[0]; }
	const std::string getlast() const { return  name[1]; }
	const std::vector<int> getpins() const { return  pins; }
	

};

std::vector<int> end_score(Bowl &b); //gets final score in a vector

bool compare_names(Bowl &a, Bowl &b); //for sort



