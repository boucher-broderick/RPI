#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();
template <class T>
void bst_sort(std::map<T,int> &mp, std::ostream &ostr, int &output_count) {
	int count=0;
	for(typename std::map<T,int>::iterator it=mp.begin(); it!=mp.end(); ++it){
		int x=it->second;
		for(; x>0 ; x--){
			ostr << it->first << "\n";
			count++;
		}
		
	}
	output_count=count;
}
template <class T>
void bst_remove_duplicates(const std::map<T,int> &mp, std::ostream &ostr, int &output_count) {
	int x=0;
	for(typename std::map<T,int>::const_iterator it=mp.begin(); it!=mp.end(); ++it){
		ostr << it->first << "\n";
		x++;	
	}
	output_count=x;
}
template <class T>
void bst_mode(std::map<T,int> &mp, std::ostream &ostr, int &output_count){
	T mode;
	int biggest=0;
	for(typename std::map<T,int>::iterator it=mp.begin(); it!=mp.end(); ++it){
		if(it->second > biggest){
			biggest=it->second;
			mode=it->first;
		}
	}
	ostr << mode << "\n";
	output_count=1;
}
void bst_closest_pair(std::map<int,int> &mp, std::ostream &ostr, int &output_count) {
	typename std::map<int,int>::iterator it1=mp.begin();
	typename std::map<int,int>::iterator it2=mp.begin();

	int index1=it1->second, index2=(it2->second)-1;
	it2++;
	int small = it2->first-it1->first;
	int one = it1->first;
	int two = it2->first;
	it2--;

	while(++it2!=mp.end()){
		it2--;
		if(index1==0){
			it1++;
			index1=it1->second;
		}
		if(index2==0){
			it2++;
			index2=it2->second;
		}
		if(small>( it2->first-it1->first)){
			small=( it2->first-it1->first);
			one=it1->first;
			two=it2->first;
		}
		index1--;
		index2--;

	}
	output_count = 2;
  	ostr << one << "\n";
  	ostr << two << "\n";
}

template <class T>
void bst_first_sorted(std::map<T,int> &mp, std::ostream &ostr, int &output_count, int optional_arg){
	typename std::map<T,int>::iterator it1=mp.begin();
	for(int i=0; i < optional_arg;){
		int x = it1->second;
		while(x>0 && i != optional_arg){
			i++;
			ostr << it1->first << "\n";
			x--;
		}
		it1++;
	}
	output_count=optional_arg;
}
void bst_longest_substring(std::map<std::string,int> &mp, std::ostream &ostr, int &output_count) {
	std::string longest = "";
		for ( typename std::map<std::string,int>::iterator it1=mp.begin(); it1 != mp.end(); ++it1){
			for(int x=0; x < (it1->first).size(); x++){
	     		for(int y=x; y < (it1->first).size(); y++){
	     			std::string sub = (it1->first).substr(x,y);
	    			for ( typename std::map<std::string,int>::iterator it2=mp.begin(); it2 != mp.end(); ++it2){
	    				if(it1!=it2){
	    					int pos= (it2->first).find(sub);
	    					if(pos!=std::string::npos && sub.size()>longest.size()){
	             				longest=sub; 
	           				}
	    				}
	    			}
	     		}
	     	}
		}

		output_count=1;
	  	ostr << longest << "\n";



}
void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {

	if(type == "string") {
		std::map<std::string,int> mp;
		std::string s;
  		input_count =0;
  		while(istr >> s) {
  			mp[s]++;
  			input_count++;
  		}
  		if      (operation == "sort")              { bst_sort              (mp,ostr,output_count); }
	    else if (operation == "remove_duplicates") { bst_remove_duplicates (mp,ostr,output_count); }
	    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
	    // "closest_pair" not available for strings
	    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
	    else if (operation == "longest_substring") { bst_longest_substring (mp,ostr,output_count); }
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }

	}
	else{
		assert(type == "integer");
		std::map<int,int> mp;
		int s;
  		input_count =0;
  		while(istr >> s) {
  			mp[s]++;
  			input_count++;
  		}
  		if      (operation == "sort")              { bst_sort              (mp,ostr,output_count); }
	    else if (operation == "remove_duplicates") { bst_remove_duplicates (mp,ostr,output_count); }
	    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
	    else if (operation == "closest_pair")      { bst_closest_pair      (mp,ostr,output_count); }
	    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
	    // "closest_pair" not available for strings
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
	}

  // 

}
