#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <iterator>
#include <algorithm>

typedef std::map<std::string, int> COSTUMES;
typedef std::map<std::string, std::string> CUSTOMERS;

// adds costume to the inventory map or increases the quantity available
void addCostume(COSTUMES& inventory, std::string& c, int q);
// Checks if a customer can rent a costume and associates the person with the costume
void rentCostume(COSTUMES& inventory, CUSTOMERS& people, std::string& name, std::string& c, std::vector<std::string>& curr);
// finds a costume and prints the amount available and the amount rented at the moment and by who
void lookup(COSTUMES& inventory, CUSTOMERS& people, std::string& c, std::vector<std::string>& curr);
// prints everybody who is a costumer as wll as what costume they have
void printPeople(CUSTOMERS& people,  std::vector<std::vector<std::string>>& names);
// helper function that determines what function should be called based on the input
void do_action(COSTUMES& inventory, CUSTOMERS& people, std::vector<std::string>& temp, std::vector<std::vector<std::string>>& names, std::vector<std::string>& curr);

int main() {
  // two data structures store all of the information for efficiency
  COSTUMES inventory;
  CUSTOMERS people;

  std::vector<std::vector<std::string>> names;
  std::vector<std::string> temp;
  std::vector<std::string> curr;
  bool first = false;
  std::string c;

  //Goes through the input document
  while (std::cin >> c) {
    bool size =false;
    //checks whether the program should run the functions
    if(c.size()==1 && !isdigit(c[0])){          
      size=true;
      if(first==false) { temp.push_back(c); } //adds if first time through
    }
    //if not, adds to a temp vector for later use
    else{
      temp.push_back(c);
    }
    //checks to make sure the credentials are met and runs it
    if(first==true && size==true){
      do_action(inventory, people, temp, names, curr);
      temp.clear();
      temp.push_back(c);
    }
    first=true;
  }
  //runs the last group
  do_action(inventory, people, temp, names, curr);

  /*  // prints the inventory
  std::cout << "\nINVENTORY:" << std::endl; 
  COSTUMES::const_iterator it;
  for (it = inventory.begin(); it != inventory.end(); ++it) {
    std::cout << it->first << "\t" << it->second << std::endl;
  }
  //*/
}

// helper function that determines what function should be called based on the input
void do_action(COSTUMES& inventory, CUSTOMERS& people, std::vector<std::string>& temp, std::vector<std::vector<std::string>>& names, std::vector<std::string>& curr){
  if (temp[0] == "a")    // calls addCostume
  {
    int quant = std::stoi(temp[2]);
    addCostume(inventory, temp[1], quant);
  } 
  else if (temp[0] == "r") // calls rentCostume
  {
    //adds the name to another vector that will help with the print order
    std::vector<std::string> last;
    last.push_back(temp[2]);
    last.push_back(temp[1]);
    if(0 == std::count (names.begin(), names.end(), last)){
      names.push_back(last);
    }
    std::string name = temp[1] + " " + temp[2];
    rentCostume(inventory, people, name, temp [3], curr);
  } 
  else if (temp[0] == "l") // calls lookup
  {
    lookup(inventory, people, temp[1], curr);
  } 
  else if (temp[0] == "p") // calls printPeople
  {
    printPeople(people, names);
  } 
  else   // if the input is invalid
  {
    std::cerr << "error unknown char " << temp[0] << std::endl;
    exit(0);
  }

}


// adds costume to the inventory map or increases the quantity available
void addCostume(COSTUMES& inventory, std::string& c, int q) {
  inventory[c] = inventory[c] + q;   // adds costume or updates quant
  // formating for output
  std::string plural;
  if(q>1) { plural = " costumes."; }
  else { plural = " costume."; }
  std::cout << "Added " << q << " " << c << plural << std::endl;
}

// Checks if a customer can rent a costume and associates the person with the costume
void rentCostume(COSTUMES& inventory, CUSTOMERS& people, std::string& name, std::string& c, std::vector<std::string>& curr) {
  bool inin = false;
  //makes sure the costume is in the shop
  if(inventory.count(c)==1){
    if(inventory[c] >0){ inin= true; }
    else{ std::cout << "No " << c << " costumes available." << std::endl; }
  }
  else{ std::cout << "The shop doesn't carry " << c << " costumes." << std::endl; }
  //if the persom is not in the system yet, it adds them and rents costume
  bool perrent = false;
  if(people.count(name)==0){
    people[name]="none";
    if(inin==true){
      inventory[c]-=1;
      people[name]=c;
      std::cout << name << " rents a " << c << " costume." << std::endl;
      perrent=true;
    }
  }
  else{
    // if the cuustomer already has the costume that they want to rent
    if(people[name] == c){
      std::cout << name << " already has a " << c << " costume." << std::endl;
    }
    // when the person does not already have a costume
    else if(people[name] == "none"){
       if(inin==true){
        inventory[c]-=1;
        people[name]=c;
        std::cout << name << " rents a " << c << " costume." << std::endl;
        perrent = true;
      }
    }
    else{
      // if they are renting a costume but will return it to get a new one
      if(inin == true){
        std::cout << name << " returns a " << people[name] << " costume before renting a " << c << " costume." << std::endl;
        inventory[people[name]]+=1;    
        inventory[c]-=1;
        people[name]=c;
        perrent= true;
      }
    }
  }
  //updates the vector of how recently someone rented
  if(perrent ==true && inin ==true){
    std::vector<std::string>::iterator it;
    for(it = curr.begin(); it!=curr.end(); it++){
      if(*it==name){
        curr.erase(it);
        break;
      }
    }
    curr.push_back(name);
  }
}

// finds a costume and prints the amount available and the amount rented at the moment and by who
void lookup(COSTUMES& inventory, CUSTOMERS& people, std::string& c, std::vector<std::string>& curr) {
  // if the costume is not rented out in the store
  if(inventory.count(c)==0){
    std::cout << "The shop doesn't carry " << c << " costumes." << std::endl;
  }
  else{
    // prints the amount in the store that are available
    std::cout << "Shop info for " << c << " costumes:" << std::endl;
    int q =inventory[c];
    if(q > 0){
      std::string cop;
      if(q==1){ cop = " copy"; }
      else { cop = " copies"; }
      std::cout << "  " << q << cop << " available" << std::endl;
    }
    // runs through people to find who is currently renting said costume
    int count =0;
    std::vector<std::string> n;
    CUSTOMERS::const_iterator it;
    for(it=people.begin(); it !=people.end(); it++){
      if(it->second==c){
        n.push_back(it->first);
        count++;
      }
    }
    //prints out in a order by recently rented
    std::string bop;
    if(count==1){ bop = " copy"; }
    else { bop = " copies"; }
    if(count>0){
      std::cout << "  " << count << bop << " rented by:" << std::endl;
      for(std::string i : curr){
        for(std::string x : n){
          if(i==x){
            std::cout << "    " << x << std::endl;
          }
        }
      } 
    }
  }
}

// prints everybody who is a costumer as wll as what costume they have
void printPeople(CUSTOMERS& people, std::vector<std::vector<std::string>>& names) {
  //formatting things
  std::string attend;
  int q =people.size();
  if(q>1) { attend = "attendees:"; }
  else { attend = "attendee:"; }
  //sorts by last name
  sort(names.begin(), names.end());
  // prints out who has what costume
  std::cout << "Costume info for the " << q << " party " << attend << std::endl;
  for(std::vector<std::string> t : names){
    std::string a = t[1]+ " "+ t[0];
    CUSTOMERS::const_iterator it;
    for (it = people.begin(); it != people.end(); ++it) {
      if(it->first == a){  
        if(it->second == "none"){
          std::cout << "  " << it->first << " does not have a costume." << std::endl;
          break;
        }
        else{
          std::cout << "  " <<  it->first << " is wearing a " << it->second << " costume." << std::endl;
          break;
        }
      }
    }
  } 
}


