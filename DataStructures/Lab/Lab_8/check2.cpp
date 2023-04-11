#include <map>
#include <iostream>
#include <string>

int main(){

	std::map<int, int> map;
	std::map<int, int>::iterator itr;
	int biggest=1;

	int x[11]={19, 83, -12, 83, 65, 19, 45, -12, 45, 19, 45};

	for(int i : x){
		itr=map.find(i);
		if(itr==map.end())
		{
			map.insert(std::pair<int,int>(i,1));
		}
		else
		{
			itr->second++;
			if(itr->second >biggest)
				biggest = itr->second;
		}
		
	}


	for(itr=map.begin(); itr!=map.end(); ++itr){
		if(itr->second == biggest){
			std::cout << itr->first << " is a mode" << std::endl;
		}
	}

};
