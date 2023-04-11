/*
Brody Boucher
Data Structures
Submitted: 1 day late

In the main, there are two functions, one for comparing scores for a sort, 
and the other to create and export the score box. With these two functions the 
program correctly compute the score of a bowling game as well as prints out 
the score box and other stats.
*/


#include <iostream>
#include "bowl.h"
#include <fstream>
#include <cctype>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>

//cd /mnt/c/Users/bouch/OneDrive/Desktop/DataStructures/Homework/Homework2/
//clang++ -g main.cpp bowl.cpp -o output.exe -Wall -Wextra

bool compare_(std::string a, std::string b)
{
	std::string astrnum; //takes out the numbers in the string Ex "Gary Zot 300"->"300"
	for(char c: a ){
		if(isdigit(c)){
			astrnum+=c;
		}
	}
	int anum=std::stoi (astrnum); //turns it into an into to compare
//_________________________________________________________________________________________
	std::string bstrnum; //takes out the numbers in the string Ex "Gary Zot 300"->"300"
	for(char c: b ){
		if(isdigit(c)){
			bstrnum+=c;
		}
	}
	int bnum=std::stoi (bstrnum);  //turns it into an into to compare
//_________________________________________________________________________________________
	if(bnum>anum){ //return statement
	return false;
	}
	else {
	return true;
	}

}


void print_temp(const uint longest, std::vector<int> totals, std::vector<int> pins, std::string f, std::string l, std::ofstream &ostr)
{
	//gets the lengths of the dashed line and name line
	int length=longest+4+6*9+9;
	std::string line1;
	std::string space1;

 	ostr << std::setfill ('-') << std::setw (length) << "\n";
 	line1+= "| "+f+" "+l;
 	int len=longest-(line1.size()-2);
	for(int b=0;b< len; b++){
		space1+=" ";
	}
//_________________________________________________________________________________________	
 	ostr << line1;
 	ostr << space1;
 	ostr <<" |"; 

 	int count=0;
 	for (int i=0; i<9; i++) //prints the first 9 boxes of the score
 	{
 		std::string templine;
 	//_________________________________________________________________________________________	
 		if(pins[count]==10)  //checks for a strike
 		{   
 			templine+="   X |";
 			ostr << templine;
 			count++;
 		}
 	//_________________________________________________________________________________________		
 		else if(pins[count]+pins[count+1]==10)  //checks for a spare
 		{
 			std::string s;
 			if(pins[count]==0){  // checks for a gutter ball
 				s="-";
 			}
 			else{
 				s = std::to_string(pins[count]);
 			}
 			
 			templine+=" "+s+" / |"; //adds thr number/X/-/ to the temp string
 			ostr << templine;
 			count+=2;
 		}
 	//_________________________________________________________________________________________	
 		else
 		{
 			std::string t1;
 			std::string t;
 			if(pins[count]==0) //checks if the first number was a gutter
 			{
 				t="-";
 			}
 			else 
 			{  
 				t = std::to_string(pins[count]);
 			}

 			if(pins[count+1]==0) //checks if the second number was a gutter
 			{
 				t1="-";
 			}
 			else
 			{ 
 				t1 = std::to_string(pins[count+1]);
 			}
 			
 			templine+=" "+t+" "+t1+" |";  //adds to temp string
 			ostr << templine;
 			count+=2;	
 		}
 	}

 //_________________________________________________________________________________________	
 	std::string one;
 	std::string two;
 	std::string three;
 	std::string final_line;
//_________________________________________________________________________________________
// does the last box of the score box
 	if(pins[count]==10) //if the first throw was a strike
 	{
 		one="X";
 		if(pins[count+1]==10) //if the second throw was a strike
 		{
 			two="X";
 			if(pins[count+2]==10) //if the third throw was a stirke
 			{
 				three="X"; 
 				final_line+=" "+one+" "+two+" "+three+" |";
 				// EX: 10 10 10
 			}
 			else // if the third throw was not a strike
 			{
 				three=std::to_string(pins[count+2]); 
 				if(three=="0"){ three="-";}
 				final_line+=" "+one+" "+two+" "+three+" |";
 				// EX: 10 10 3
 			} 			
 		}
 		else // if the second throw was not a strike
 		{
 			two=std::to_string(pins[count+1]);
 			if(two=="0"){ two="-";}
 			if(pins[count+1]+pins[count+2]==10) //if the second and thrid shots were a spare
 			{ 
 				three="/";
 				final_line+=" "+one+" "+two+" "+three+" |";
 				// EX: 10 3 7
 			}
 			else //if the thrid throw was not a strike or spare
 			{
 				three=std::to_string(pins[count+2]); 
 				if(three=="0"){ three="-";}
 				final_line+=" "+one+" "+two+" "+three+" |";
 				// EX: 10 3 4 
 			}
 		}
 	}
//_________________________________________________________________________________________
 	else // if the 1st throw was not a strike
 	{ 
 		one=std::to_string(pins[count]); 
 		if(one=="0"){ one="-";}
 		if(pins[count]+pins[count+1]==10)  // if the 1st and 2nd throws made a spare
 		{ 
 			two="/";
 			
 			if(pins[count+2]==10)  // if the 3rd shot was a strike
 			{  
 				three="X";  
 				final_line+=" "+one+" "+two+" "+three+" |";
 				// EX: 3 7 10
 			}
 			else // if the 3rd shot was not a strike
 			{
 				three=std::to_string(pins[count+2]); 
 				if(three=="0"){ three="-";}
 				final_line+=" "+one+" "+two+" "+three+" |";
 				// EX: 3 7 4
 			}		
 		}
 		else // the 1st and 2nd shots were not spares or strikes
 		{
 			two=std::to_string(pins[count+1]); 
 			if(two=="0"){ two="-";}
 			final_line+=" "+one+" "+two+"   |";
 			// EX: 3 4
 		}
 	}
 	ostr << final_line << "\n";
//_________________________________________________________
 	// deals with the second row of the socre box
	int totalscore=0;
	ostr << "| " << std::setfill (' ') << std::setw(line1.size()+len) << " |"; 
	for (int i=0; i<10; i++)  // loops throuhg the array of the final box scores
	{

		std::string temp;
		totalscore+=totals[i];
		
		temp=std::to_string(totalscore);
		std::string space;
		for(uint b=0;b< 4-temp.size(); b++)  // adds spacing
		{
			space+=" ";
		}
		if(i==9){
			space+="  ";
		}
	
		ostr << space <<temp <<" |" ;
	}
	ostr << "\n";
}


int main (int argc, char* argv[]) {

  // check the arguments and open the input file for reading
  if (argc != 4) {
    std::cerr << "ERROR: Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }
  std::ifstream istr(argv[1]);
  if (!istr.good()) {
    std::cerr << "ERROR: the file " << argv[1] << " was not successfully opened for reading." << std::endl;
    return 1;
  }


 
  std::vector<Bowl> bowlers;
  int num_str=0;
  std::vector<std::string> name(2);
  std::vector<int> pins;
  std::string input;
  while(istr) //loops through the input file
  {
  	istr >> input;  // sets a value to input
  	if(isalpha(input[0])) //checks if it is an alpha
  	{
  		num_str++;
  		if(num_str==3) //if there is a new person
  		{
  			bowlers.push_back(Bowl(pins, name)); // adds a new bowler
  			pins.clear();
  			num_str=1; 
  		}
  		name[num_str-1]=input;  //adds to temporary variable for name
  	}
  	else
  	{
  		int temp_num = std::stoi(input); //converts string to int
  		pins.push_back(temp_num);  //adds to temp vector for pins
   	}	
  }
  bowlers.push_back(Bowl(pins, name)); //adds the last bowler




  
  uint longest=0;
  for(Bowl b:bowlers) //finds the longest name
  {
  	std::string full_name;
  	full_name.append(b.getfirst());
  	full_name.append(" ");
  	full_name.append(b.getlast());
  	if(longest<full_name.size())
  		longest=full_name.size();
  }


 
  std::ofstream ostr(argv[2]);
  std::vector<std::string> score_order;
  sort(bowlers.begin(),bowlers.end(),compare_names); //sorts into name order

  int high=0;
  int low=300;
  int three00=0;


  for(Bowl b:bowlers) //for printing the function
  {
  	std::string f=b.getfirst();
  	std::string l=b.getlast();
	std::vector<int> totals = end_score(b);
	print_temp(longest, totals, b.getpins(), f, l, ostr); //prints the score box

	int final_total=0; //gets the final score of the player
	for(int x: totals)
	{
		final_total+=x;
	}

	int spaces=longest-(f.size()+l.size()+1)+5-std::to_string(final_total).size();  //find the spaces for the score first output
	std::string space;
	for(int b=0;b<spaces; b++)
	{

		space+=" ";
	}
	space+=std::to_string(final_total);
	std::string score_=f+" "+l+space;
	score_order.push_back(score_); //adds to a vector 



	if(final_total>high){ //deals witht eh custom statistics
		high=final_total;
	}
	if(final_total<low){
		low=final_total;
	}
	if(final_total==300)
	{
		three00++;
	}


  }

	int length=longest+4+6*9+10;
 	ostr << std::setfill ('-') << std::setw (length) << "\n\n"; //prints last line


 	sort(score_order.begin(),score_order.end(),compare_); //sorts names/scores, score first
 	
 	for(std::string a: score_order){  //prints them to textfile
 		ostr << a << "\n";
 	}
 	std::string cust = argv[3];
 	if(cust=="custom") // if they want standard of custom with stats
 	{
 		ostr << "\nThe greatest difference between the scores was: " << high-low << "\n";
 		ostr << "Number of perfect games: " << three00  << "  (12 strikes)";


 	}

}

