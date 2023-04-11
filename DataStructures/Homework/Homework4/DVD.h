#include <string>
#include <iostream>

class DVD
{
	public: 

		std::string title;
		int copies;
		int given_out;

		DVD(std::string &name)
		{
			title=name;   //name of the person
			copies=0;     //number of copies
			given_out=0;  //number ofmovies given out
		};


		void returned() { given_out-=1; }   // returns movie +1 availability
		void taken_out() { given_out+=1; }  // takes movie -1 availability
		void print(std::ostream &ostr);     // prints to output 
		bool available();                   // checks if available
};


