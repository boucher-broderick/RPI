#include <iostream>
#include <map>
#include <string>
using namespace std;

// add a number, name pair to the phonebook
void add(map<int,std::string> &phonebook, int number, std::string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(map<int, std::string> & phonebook, int number) {
  map<int, std::string>::iterator iter = phonebook.find(number);
  if (iter ==phonebook.end()) 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
 map<int,std::string> phonebook;

  // add several names to the phonebook
  add(phonebook, 111111111, "fred");
  add(phonebook, 987893843, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 987893843);
  identify(phonebook, 4444);
}