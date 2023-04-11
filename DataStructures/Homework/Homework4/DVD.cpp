#include "DVD.h"
#include <iostream>


//prints out the dvd and copies to the output file
void DVD::print(std::ostream &ostr){ 
	ostr << title <<  std::endl;
	std::string s;
	if(given_out==0){   //no movies taken out
		if(copies==1)   //1 copy
			ostr << " "<< copies << " copy available" <<std::endl;
		else
			ostr << " " << copies << " copies available" <<std::endl;
	}
	else if(given_out==1)  //1 movie taken out
	{
		s=" copy checked out ";
		ostr << " " << given_out << s; 
		if(copies==1)                    //1 copy
			ostr << copies << " copy available" <<std::endl;
		else
			ostr << copies << " copies available" <<std::endl;
	}
	else   //multiple movies taken out
	{
 		s=" copies checked out ";
 		ostr << " " << given_out << s;
 		if(copies==1)                     //1 copy
			ostr << copies << " copy available" <<std::endl;
		else
			ostr << copies << " copies available" <<std::endl;
	}

	
}		

//checks if a movie is in stock
bool DVD::available(){
	if(given_out==copies) return false;
	else return true;
} 