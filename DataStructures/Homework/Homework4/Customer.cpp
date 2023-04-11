#include <iostream>
#include <list>
#include <string>
#include <cassert>
#include "Customer.h"

//prints the customer out to the output file
void Customer::print(std::ostream &ostr)
{
	if(size_held==0) //different syntax for different questions
	{
		ostr <<  name << " has no movies" << std::endl << " preference list:" << std::endl;
		for(std::string x: p){
			ostr << "  " << x <<std::endl;
		}
	}
	else{
		ostr <<  name << " has " << size_held << " movies" << std::endl;
		for(std::string x: h){
			ostr << "  " << x <<std::endl;
		}
	}
}

// adds the movie to the preference
void Customer::add_preference(std::string t) 
 { 
 	p.push_back(t); 
 }

// adds a movie to the held movies
 void Customer::add_holding(std::string t)
 { 
 	h.push_back(t); 
 	size_held+=1;
 }

//returns the movie that was remnoved in order to adjust available copies (takes oldest movie)
std::string Customer::return_old()
{

	assert(!h.empty());
	std::string temp= h.front();
	h.pop_front();
	size_held-=1;
	return temp;
}

// //returns the movie that was remnoved in order to adjust available copies (takes newest movie)
std::string Customer::return_new()
{
	assert(!h.empty());
	std::string temp= h.back();
	h.pop_back();
	size_held-=1;
	p.remove(temp);
	return temp;

}

// tells how many movies are in the held and checks if over 3
bool Customer::has_max_num_movies(){
	if(size_held==3) return true;
	else return false;
}

//checks is the list is empty
bool Customer::preference_list_empty(){
	if(p.empty()) return true;
	else return false;
}