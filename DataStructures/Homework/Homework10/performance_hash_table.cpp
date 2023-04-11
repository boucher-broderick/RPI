#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();



template <class T>
void hash_table_sort(std::unordered_map<T,int> &ht, std::ostream &ostr, int &output_count) {
 std::unordered_map<T,int> temp = ht;
  
 int count=0;
  while(temp.size()!=0){
  	typename std::unordered_map<T,int>::iterator small = temp.begin();
  	for(typename std::unordered_map<T,int>::iterator it1 = temp.begin();it1!=ht.end(); it1++){
  		
  		if(it1->first < small->first){
  			
  			small=it1;;
  		}
 	}
 	for(int x= small->second; x>0; x--){
 		ostr << small->first <<"\n";
 		count++;
 	}
 	temp.erase(small);
 	
  }
  output_count=count;
  
  //for(int x=0; x <i; x++){
  //	 typename std::unordered_map<int, std::unordered_map<T,int>>::const_iterator got = order.find (x);
 //	ostr << got->second << "\n";
 // }


}

template <class T>
void hash_table_remove_duplicates(const std::unordered_map<T,int> &ht, std::ostream &ostr, int &output_count) { 
	int x=0;
  for(auto it1 = ht.begin(); it1!=ht.end(); it1++){
 	ostr << it1->first << "\n";
 	x++;
  }
  output_count=x;
}

template <class T>
void hash_table_mode(std::unordered_map<T,int> &ht, std::ostream &ostr, int &output_count) {
	int max=0;
	T mode;
	for(auto it1 = ht.begin(); it1!=ht.end(); it1++){
		if(it1->second>max){
			max=it1->second;
			mode=it1->first;
		}
	}
	ostr << mode << "\n";
	output_count=1;
}

void hash_table_closest_pair(std::unordered_map<int,int> &ht, std::ostream &ostr, int &output_count) {
	
}

template <class T>
void hash_table_first_sorted( std::unordered_map<T,int> &ht, std::ostream &ostr, int &output_count, int optional_arg) {
	std::unordered_map<T,int> temp = ht;
  
 int count=0;
  while(temp.size()!=0){
  	typename std::unordered_map<T,int>::iterator small = temp.begin();
  	for(typename std::unordered_map<T,int>::iterator it1 = temp.begin();it1!=ht.end(); it1++){
  		
  		if(it1->first < small->first){
  			
  			small=it1;;
  		}
 	}

 	for(int x= small->second; x>0; x--){
 		if(count==optional_arg) break;
 		ostr << small->first <<"\n";
 		count++;
 	}
 	temp.erase(small);
 	
  }
  output_count=count;
}

void hash_table_longest_substring(  std::unordered_map<std::string,int>  &ht, std::ostream &ostr, int &output_count) {

}


void hash_table_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {


if (type == "string") {
    // load the data into a hash_table of strings
    std::unordered_map<std::string,int> ht;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      ht[s]++;
      input_count++;
    }
    if      (operation == "sort")              { hash_table_sort              (ht,ostr,output_count); }
    else if (operation == "remove_duplicates") { hash_table_remove_duplicates (ht,ostr,output_count); }
    else if (operation == "mode")              { hash_table_mode              (ht,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { hash_table_first_sorted      (ht,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { hash_table_longest_substring (ht,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a hash_table of integers
    std::unordered_map<int,int> ht;
    int s;
    input_count = 0;
    while (istr >> s) {
      ht[s]++;
      input_count++;
    }
    if      (operation == "sort")              { hash_table_sort              (ht,ostr,output_count); }
    else if (operation == "remove_duplicates") { hash_table_remove_duplicates (ht,ostr,output_count); }
    else if (operation == "mode")              { hash_table_mode              (ht,ostr,output_count); }
    else if (operation == "closest_pair")      { hash_table_closest_pair      (ht,ostr,output_count); }
    else if (operation == "first_sorted")      { hash_table_first_sorted      (ht,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
