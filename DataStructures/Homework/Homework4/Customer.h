#include <list>
#include <iostream>

class Customer
{
public:
	
	Customer(std::string &n){    //constructor
		name=n; 
		size_held=0;
	};

	std::string name;   //customer name
	std::list<std::string> p;  //holds preferences
	std::list<std::string> h;  //holds movies held
	int size_held;  //amount of held movies

	void print(std::ostream &ostr);         //prints
	void add_preference(std::string t);     //adds a movie preference
	void add_holding(std::string t);        //adds a movie holding
	std::string return_old();               //deletes a held movie
	std::string return_new();			    //deletes a held movie
	bool has_max_num_movies();				//checks max movie
	bool preference_list_empty();           //checks empty
	std::list<std::string> get_preferences() {return p;}   //returns preferences list
	std::list<std::string> get_held() {return h;}          //returns held list
};