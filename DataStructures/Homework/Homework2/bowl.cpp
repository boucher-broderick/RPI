/*
	This file holds the 2 functions, one for comparing names for sort,
	and the other for computing the score with strikes and spares.
*/

#include "bowl.h"
#include <vector>
#include <iostream>

std::vector<int> end_score(Bowl &b) //adds up with the correct scoring
{
	int total_score=0;
	std::vector<int> p=b.getpins();
	std::vector<int> total;
	int count=0;
	for (int i=0; i<10; i++)  //loops through 10 times for the number of boxes
	{
		int round=0;
		int temp_score=0;
		while(round<2 && temp_score<10) //for if the first number is not a strike
		{
			temp_score+=p[count];
			if(round==0 && temp_score==10) // strike
			{
				temp_score+=p[count+1];
				temp_score+=p[count+2];
			}
			else if(round==1 && temp_score==10) //spare
			{
				temp_score+=p[count+1];
			}
			count++;
			round++;
		}
		total.push_back(temp_score); //adds to the vector
		total_score+=temp_score;
	}
	return total;
}

bool compare_names(Bowl &a, Bowl &b)
{
	if(a.getlast()<b.getlast()){  //last name
		return true;
	}
	else if(a.getlast()==b.getlast() && a.getfirst()<b.getlast()){ //same last name
		return true;
	}
	else if(a.getlast()==b.getlast() && a.getfirst()>b.getlast()){ //same last name
		return false;
	}
	else if(a.getlast()>b.getlast()){ //last name
		return false;
	}
	else{ //same full name
		return false;
	}
}

