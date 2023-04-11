#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();

template <class T>
void list_sort(std::list<T> &lst, std::ostream &ostr, int &output_count) {
	lst.sort();
	typename std::list<T>::iterator it;
	for ( it=lst.begin(); it != lst.end(); ++it){
		ostr << *it << "\n";
		output_count++;
	}
    
}
template <class T>
void list_remove_duplicates(const std::list<T> &lst, std::ostream &ostr, int &output_count) {
	output_count = 0;
    
	for ( typename std::list<T>::const_iterator it1=lst.begin(); it1 != lst.end(); ++it1){
    bool dup = false;
    for ( typename std::list<T>::const_iterator it2=lst.begin(); it2 != it1; ++it2){
      
      if (it2!=it1 && *it1 == *it2) {
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup) {
      ostr << *it1 << "\n";
      output_count++;
    }
  }
}

template <class T>
void list_mode(std::list<T> &lst, std::ostream &ostr, int &output_count){
	int max_mode=0;
	T mode;
	for ( typename std::list<T>::const_iterator it1=lst.begin(); it1 != lst.end(); ++it1){
		int temp_mode=0;
		for ( typename std::list<T>::const_iterator it2=lst.begin(); it2 != lst.end(); ++it2){
			if(*it1 == *it2)  temp_mode++;
		}
		if( temp_mode>max_mode){
			max_mode=temp_mode;
			mode=*it1;
		}
	}
	ostr << mode << "\n";
	output_count=1;
}

void list_closest_pair(std::list<int> &lst, std::ostream &ostr, int &output_count) {
	lst.sort();
	typename std::list<int>::const_iterator it2=lst.begin();
	typename std::list<int>::const_iterator it1=lst.begin();
	it2++;
	int small = *it2-*it1;
	int one = *it1;
	int two = *it2;
	
	for (; it2 != lst.end(); ++it1, ++it2){
		if((*it2-*it1)<small)
		{
			small=(*it2-*it1);
			one= *it1;
			two= *it2;
		}
	}
	output_count = 2;
  	ostr << one << "\n";
  	ostr << two << "\n";
}

template <class T>
void list_first_sorted(std::list<T> &lst, std::ostream &ostr, int &output_count, int optional_arg){
	assert (optional_arg >= 1);
	assert (lst.size() >= optional_arg);
	lst.sort();
	typename std::list<T>::const_iterator it1=lst.begin();
	for(int i=0; i<optional_arg; i++){
		ostr << *it1 << "\n";
		it1++;
	}
	output_count = optional_arg;
}

void list_longest_substring(std::list<std::string> &lst, std::ostream &ostr, int &output_count) {
	std::string longest = "";
	for ( typename std::list<std::string>::const_iterator it1=lst.begin(); it1 != lst.end(); ++it1){
		for(int x=0; x < (*it1).size(); x++){
     		for(int y=x; y < (*it1).size(); y++){
     			std::string sub = (*it1).substr(x,y);
    			for ( typename std::list<std::string>::const_iterator it2=lst.begin(); it2 != lst.end(); ++it2){
    				if(it1!=it2 && *it1!=*it2){
    					int pos= (*it2).find(sub);
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



void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  if(type == "string"){
  	std::list<std::string> lst;
  	std::string s;
  	input_count =0;
  	while(istr >> s) {
  		lst.push_back(s);
  		input_count++;
  	}

  	if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { list_longest_substring (lst,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  else{
  	assert(type == "integer");
  	std::list<int> lst;
  	int s;
  	input_count =0;
  	while(istr >> s) {
  		lst.push_back(s);
  		input_count++;
  	}
  	if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    else if (operation == "closest_pair")      { list_closest_pair      (lst,ostr,output_count); }
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    // "closest_pair" not available for strings
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }

  }
  

}
