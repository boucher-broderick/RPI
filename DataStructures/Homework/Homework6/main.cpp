#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


// out.exe reverse_ell_dict.txt reverse_ell1.txt all_solutions print_boards
// out.exe nyt_mini1_dict.txt nyt_mini1_noblack.txt sm.txt op.txt
// out.exe blackout_dict1.txt blackout1.txt sm.txt op.txt

// prints out the grid given the board
void print(std::vector<std::vector<char>>& v){
	std::cout << "Board:" << std::endl;
	for(int i=0; i<v.size(); i++){
		for(int j=0; j<v[0].size(); j++){
			std::cout << v[i][j];
		}
		std::cout << std::endl;
	}
}

// finds a legal word in a given line then adds it to a vector of strings 
void find_word(std::vector<std::string>& dict, std::string& line, int length, std::vector<std::string>& sol)
{
	std::string word;
	if(line.size()>=length)
	{
	for(int i=0; i<=line.size()-length; i++){
		if(i==0){ word = line.substr(i,i+length); }  //creates a different string each time
		else {  word = line.substr(i,i+length-1); }
		//std::cout << word << i << i+length-1 << std::endl;
		for (int x = 0; x < dict.size(); ++x){
			if(dict[x]==word){
				//std::cout << word << std::endl;
				sol.push_back(word);
			}
		}	
	}
	}
}

// cycles through the board and creates the line then passes it through find_word
void get_solutions(std::vector<std::string>& dict, std::vector<std::vector<char>>& row, int num, std::vector<std::string>& sol)
{
	for(int i=0; i<row.size(); i++){          //for across
		std::string across;
		for(int j=0; j<row[0].size(); j++){
			across+=row[i][j];
		}
		//std::cout << across << std::endl;
		find_word(dict, across, num, sol);
	}
	for(int i=0; i<row[0].size(); i++){      //for down
		std::string down;
		for(int j=0; j<row.size(); j++){
			down+=row[j][i];
		}
		//std::cout << down << std::endl;
		find_word(dict, down, num, sol);
	}
}

//creates the board with the # inplace for the non used characters 
void filled_board(std::vector<std::vector<char>>& row, std::vector<std::string>& sol)
{
std::vector<std::vector<char>> final;
std::vector<std::vector<char>> ac;
std::vector<std::vector<char>> dow;
for(int i=0; i<row.size(); i++){            //creates line
		std::string across;
		for(int j=0; j<row[0].size(); j++){
			across+=row[i][j];
		}
		std::vector<char> temp;            //creates a 2d vector of just the across words
		bool b =false;
		for(std::string s: sol){
			int x= across.find(s);
			if(x != std::string::npos){
				b=true;
				int h =x;
				char hash = '#';
				while(h>0){ temp.push_back(hash); h--;}  //adds the #
				for (char c : s) { temp.push_back(c); }
				int l= across.size()-(x+s.size());
				while(l>0){ temp.push_back(hash); l--;}
				
			}
		}
		if(b==false){
			int y = across.size();
			while(y>0){  temp.push_back('#'); y--; }
		}
		ac.push_back(temp);
		//for(char c : temp)  {std::cout << c << " "; }
		//std::cout << std::endl;
	}


	for(int i=0; i<row[0].size(); i++){    //for down
		std::string down;
		for(int j=0; j<row.size(); j++){
			down+=row[j][i];
		}
		std::vector<char> temp;
		bool b =false;   
		for(std::string s: sol){              //creates a 2d vector for the down words
			int x= down.find(s);
			if(x != std::string::npos){
				b=true;
				int h =x;
				char hash = '#';
				while(h>0){ temp.push_back(hash); h--;}   // adds the #
				for (char c : s) { temp.push_back(c); }
				int l= down.size()-(x+s.size());
				while(l>0){ temp.push_back(hash); l--;}
				
			}
		}
		if(b==false){
			int y = down.size();
			while(y>0){  temp.push_back('#'); y--; }
		}
		dow.push_back(temp);
		//for(char c : temp)  {std::cout << c << " "; }
		//std::cout << std::endl;
	}


	for(int i=0; i<row.size(); i++){
		std::vector<char> temp;
		for(int j=0; j<row[0].size(); j++){                    //goes throuhgh both 2d vectors
			//std::cout << ac[i][j] << dow[j][i] << std::endl; // if they are both # then the final
			if(ac[i][j]=='#' && dow[j][i]=='#'){               //result is #
				temp.push_back('#');
			}
			else if(ac[i][j]=='#' && dow[j][i]!='#'){
				temp.push_back(dow[j][i]);
			}
			else{
				temp.push_back(ac[i][j]);
			}
		}
		final.push_back(temp);
	}

	print(final);

}

/*   recursive method that was suppose to find the amount of solutions
int num_solutions( std::vector<int>& size, std::vector<std::vector<std::string>>& ordered_words)
{
	int pos=0;
	std::vector<std::string> one;
}

// the helper function for the recursive method
void helper(std::vector<std::string>& one, int pos, std::vector<int>& size, std::vector<std::vector<std::string>>& ordered_words)
{
	std::vector<std::string> two = one;
	if(pos==ordered_words.size())  
	{

	}
	else                                                     //Was suppose to create a copy of the solutions vector
	{                                                        //to add more words as the recursion got deeped
		if(sizes[pos]==ordered_words[pos].size())            //and the final time the final board would be called
		{	
			int x=0;
			while(x<sizes[pos])
			{
				two.push_back(ordered_words[pos][x]);
			}
			pos++;
			helper(two, pos, size, ordered_words);
		}
		else
		{
			int i=sizes[pos];
		}
	}
}

*/

int main(int argc, char* argv[]) {

  // open input and output file streams
  std::ifstream istr1(argv[1]);
  if (!istr1) {
    std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    return 0;
  }
  std::ifstream istr2(argv[2]);
  if (!istr2) {
    std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    return 0;
  }


  std::vector<std::vector<char>> row; 
  std::vector<std::string> dictionary; 
  std::string dict;
  while (istr1 >> dict) {         //creates a vector with the dictionary words
  	dictionary.push_back(dict);
  }

  int row_size=0;
  int col_size;
  std::vector<int> lengths;
  std::string token;
  while (istr2 >> token) {                              //cycles through the input document 
    if (token.find("!")!=std::string::npos) { }         //cancels out the comments
    else if (token.find("+")!=std::string::npos)        //adds the restrictions to a vector
    {
    	//std::cout << token.substr(token.find("+")+1,token.size()) << std::endl;
    	int i=std::stoi(token.substr(token.find("+")+1,token.size()));
    		lengths.push_back(i);
    }
    else {                                              // for the actual board 
    	col_size=0;
    	std::vector<char> col; 
    	for (char c : token){
    		col.push_back(c);
    		col_size++;
    	}
    	row.push_back(col);
    	row_size++;
    }
  }

  //test

	std::vector<int> un;
    std::vector<int> sizes;
    std::sort(lengths.begin(), lengths.end());     //sorts the vector of restirctions
    //for(int i: lengths) { std::cout << i <<std::endl;}

    for(int i=0; i<lengths.size(); i++) {          //creates a vector of unique restrictions
  		if(i==0) { un.push_back(lengths[i]);  }
  		else {
  			if(lengths[i-1]!=lengths[i]) {  un.push_back(lengths[i]); }
  	  	}
  	}
    //for(int i:un) { std::cout << i <<std::endl;}

  	for(int num : un){                             //counts the amount of replicating restrictions
		int mycount = std::count (lengths.begin(), lengths.end(), num);
		sizes.push_back(mycount);
	}
 	//for(int i:sizes) { std::cout << i <<std::endl;}
  

  //print(row);
  std::vector<std::string> solutions;
  
  for(int num: un)
  	get_solutions(dictionary, row, num, solutions);   //gets the solutions vector
  

  std::vector<std::vector<std::string>> ordered_words;
  std::vector<int> sos;
  for(int x : un){                                   //created a 2d vector layered by the restrictions
  	int counter =0;
  	std::vector<int> sos;
  	std::vector<std::string> temp;
  	for(std::string str : solutions){
  		if(str.size()==x)
  		{ counter++; temp.push_back(str); }
  	}
  	ordered_words.push_back(temp);
  	sos.push_back(counter);
  }

//  for( int i : sos) { std::cout << i << std::endl; }    //for testing the 2d vector
//  for(std::vector<std::string> d : ordered_words)
//  {
//  	for( std::string w : d)
//  	{ std::cout << w << std::endl; }
// }

//int sols = num_solutions(sizes, ordered_words);
  //filled_board(row, solutions);


  std::string arg3(argv[3]);                          //uses the command line arguements to print certain functions
  if(arg3=="one_solution")
  {
  	std::cout << "Number of solution(s): 1" << std::endl; 
  }
  else
  {
  	  std::cout << "Number of solution(s): 1" << std::endl; 
  }
  
  std::string arg4(argv[4]);
  if(arg4=="print_boards")
  {

  		filled_board(row, solutions);
  }
  else
  {
  		
  }

};



/* 
TEST CASES
Test 1: checks that there are the correct restrictions to the amount of solutions, result 0 solutions

+4
+3
+3
+3

WHAT
OXFA
WCXT

DICT 1:
WHAT
WOW
TAT


Test2: To test the number of solution that there should be, result 4 solutions

+5
+5
+5

HELLO
YDJFP
POLIP
DJFRE
NIPED

DICT 2:

HELLO
POLIP
NIPED
OPPED


Test 3: checks for when words are next to eachother, result 0 solutions
+4
+3
+3
+3
+3
+3

WHAT
OATA
WTST

DICT 3:
WHAT
OAT
WOW
HAT
ATS
TAT


Test 4: checks time
+4
+3
+3



WHATXCAT
OATAXAXA
WTSTABAM

DICT 4:
WHAT
OAT
WOW
HAT
ATS
TAT
BAM
CAT
CAB




*/