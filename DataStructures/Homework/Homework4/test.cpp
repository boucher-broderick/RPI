#include <list>
#include "DVD.h"
#include "Customer.h"
#include <iostream>

// cd /mnt/c/Users/bouch/OneDrive/Desktop/DataStructures/Homework/Homework4
int main()
{
	//For DVD.h
	///*
	std::list<DVD> my_list;
	std::string m="mama mia";
	DVD temp(m);
	temp.copies+=4;
	my_list.push_back(temp);
	std::list<DVD>::iterator i = my_list.begin();
	std::cout << i->title << std::endl;
	DVD temp1 = *i;
	temp1.taken_out();
	temp1.print();
	//*/
	/*
	std::list<Customer> my_list;
	std::string m="nacy mia";
	Customer temp(m);
	temp.add_preference("hi");
	my_list.push_back(temp);
	std::list<Customer>::iterator i = my_list.begin();
	std::cout << i->name << std::endl;
	i->add_preference("where the wild things are");
	i->add_preference("why are you here");
	i->add_preference("goodbye");
	std::cout << i->p.back() << std::endl;
	i->add_holding("goodbye");
	std::string x= i->return_old();
	std::cout << x << std::endl;
	i->print();
	//*/
};