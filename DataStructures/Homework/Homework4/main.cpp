// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include "DVD.h"
#include "Customer.h"
#include <algorithm> 

// several type defs to keep things neat
// (hint, these are STL lists)
typedef std::list<DVD> inventory_type;
typedef std::list<Customer> customers_type;
typedef std::list<std::string> preference_type;


// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name);

// The main algorithm for DVD distribution
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr);

// ==================================================================


void usage(const char* program_name) {
  std::cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
  exit(1);
}


int main(int argc, char* argv[]) {

  if (argc < 3 || argc > 5) {
    usage(argv[0]);
  }

  // open input and output file streams
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    usage(argv[0]); 
  }
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
    usage(argv[0]); 
  }

  // optional parameters for extra credit
  bool use_improved_algorithm = false;
  bool print_analysis = false;
  for (int i = 3; i < argc; i++) {
    if (std::string(argv[i]) == "--improved") {
      use_improved_algorithm = true;
    } else if (std::string(argv[i]) == "--analysis") {
      print_analysis = true;
    } else {
      usage(argv[0]);
    }
  }


  // stores information about the DVDs
  inventory_type inventory;
  // stores information about the customers
  customers_type customers;


  // read in and handle each of the 8 keyword tokens
  std::string token;
  while (istr >> token) {
    if (token == "dvd") {
      std::string dvd_name = read_dvd_name(istr);
      int copies;
      istr >> copies;
      //creates DVD
      DVD temp(dvd_name);
      temp.copies+=copies;
      inventory.push_back(temp);
      //grammer
      if(copies==1){
         ostr << copies << " copy of " << dvd_name << " added" << std::endl;
      }
      else{
      ostr << copies << " copies of " << dvd_name << " added" << std::endl;
      }
    } else if (token == "customer") {
      std::string customer_name = read_customer_name(istr);
      int num_movies;
      istr >> num_movies;

      //creates customer and runs through adding preferences
      Customer temp(customer_name);

      for (int i = 0; i < num_movies; i++) {
        std::string dvd_name = read_dvd_name(istr);
        temp.add_preference(dvd_name);

      }
      customers.push_back(temp);
      ostr <<  "new customer: " << customer_name << std::endl;

    } else if (token == "ship") {

      //calls ship
      shipping_algorithm(inventory,customers,ostr);

      
    } else if (token == "return_oldest") {
      std::string customer_name = read_customer_name(istr);

      //finds customer
      customers_type::iterator customer_itr = customers.begin();
      while (customer_itr != customers.end()) {
        if(customer_itr->name == customer_name)
        {
           std::string movie =customer_itr->return_old();

           //cahnges availability of movie
          for(DVD d: inventory){
            if(movie==d.title){
              d.returned();
              ostr <<customer_name << " returns " << movie <<std::endl;
              break;
            }
        }
        break;
      }
      customer_itr++;
      }

    } else if (token == "return_newest") {
      std::string customer_name = read_customer_name(istr);

     //finds customer
      customers_type::iterator customer_itr = customers.begin();
      while (customer_itr != customers.end()) {
        if(customer_itr->name == customer_name)
        {
           std::string movie =customer_itr->return_new();

           //cahnges availability of movie
          for(DVD d: inventory){
            if(movie==d.title){
              d.returned();
              ostr <<customer_name << " returns " << movie <<std::endl;
              break;
            }
        }
        break;
      }
      customer_itr++;
      }




    } else if (token == "print_customer") {
      std::string customer_name = read_customer_name(istr);

      //finds customer and prints
      customers_type::iterator customer_itr = customers.begin();
      while (customer_itr != customers.end()) {
          if(customer_itr->name==customer_name){
          customer_itr->print(ostr);
          break;
        }
        customer_itr++;
        }

    } else if (token == "print_dvd") {
      std::string dvd_name = read_dvd_name(istr);

      //DVD and prints
     inventory_type::iterator inv_itr = inventory.begin();
      while (inv_itr != inventory.end()) {
        if(inv_itr->title==dvd_name){
          inv_itr->print(ostr);
          break;
        }
        inv_itr++;
      }


    } else if (token == "add_preference") {
      std::string customer_name = read_customer_name(istr);
      std::string dvd_name = read_dvd_name(istr);

/*  was supposed to weed out the movies not on the inventory, but did not work well
       bool b=false;
      inventory_type::iterator inv_itr = inventory.begin();
      while (inv_itr != inventory.end()) {
        if(inv_itr->title == dvd_name)
          b=true;
        break;
      }
      if(inv_itr->title==dvd_name) b=true;

      if(b){
        */
      //finds customer then adds to the preference
      customers_type::iterator customer_itr = customers.begin();
      while (customer_itr != customers.end()) {
        if(customer_itr->name == customer_name)
        {
          customer_itr->add_preference(dvd_name);
          break;
        }
        customer_itr++;
      }
      //}  else print out error


    } else {
      std::cerr << "ERROR: Unknown token " << token << std::endl;
      exit(1);
    }
  }
}


// ==================================================================


// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr) {
  std::string first, last;
  istr >> first >> last;
  return first + " " + last;
}


// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr) {
  std::string token;
  istr >> token;
  assert (token[0] == '"');
  std::string answer = token;
  while (answer[answer.size()-1] != '"') {
    istr >> token;
    answer += " " + token;
  }
  return answer;
}


// A helper function to find a DVD from the inventory
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name) {
  for (inventory_type::iterator inventory_itr = inventory.begin(); 
       inventory_itr != inventory.end(); inventory_itr++) {
    if (inventory_itr->title == dvd_name) {
      return inventory_itr;
    }
  }
  // if the DVD is not found, return the .end() iterator
  return inventory.end();
}


// ==================================================================

//
// A basic algorithm for determining which movies to ship to each customer
//
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr) {

  


  ostr << "Ship DVDs" << std::endl;

  // Loop over the customers in priority order
  //
  // Note that we edit the customers list as we go, to add customers
  // to the back of the list if they receive a DVD.  This allows a
  // customer to receive multiple DVDs in one shipment cycle, but only
  // after all other customers have had a chance to receive DVDs.
  //
  customers_type::iterator customer_itr = customers.begin();
  while (customer_itr != customers.end()) {

    // skip this customer if they already have 3 movies or if their
    // preference list is empty (no outstanding requests)
    if (customer_itr->size_held == 3 || customer_itr->preference_list_empty()) {
      // move on to the next customer
      customer_itr++;
      continue;
     
    }

    // a helper flag variable
    bool sent_dvd = false;
    // loop over the customer's preferences
    const preference_type &preferences = customer_itr->get_preferences();
   
    for (preference_type::const_iterator preferences_itr = preferences.begin(); 
         preferences_itr != preferences.end(); preferences_itr++) {

      const preference_type &held = customer_itr->get_held();
      bool b =true;
      for(std::string h: held)
      {
        if(*preferences_itr==h) {
        b=false;
        break;
        }     
      }

      // locate this DVD in the inventory
     if(b) //used for checking if the person already has the movie
    {
  
      inventory_type::iterator inventory_itr = find_DVD(inventory,*preferences_itr);
      if (inventory_itr != inventory.end() && inventory_itr->available()) { 


        // if the DVD is available, ship it to the customer!
        ostr << "  " << customer_itr->name << " receives " << *preferences_itr << std::endl;
        inventory_itr->taken_out();
        customer_itr->add_holding(*preferences_itr);
       

        
        // move this customer to the back of the priority queue
        // they will get a chance to receive another DVD, but only
        // after everyone else gets a chance
        customers.push_back(*customer_itr);
        customer_itr = customers.erase(customer_itr);

        // after setting the flag to true, leave the iteration over preferences
        sent_dvd = true;        
        break;

      }
      }
       
    }

    // if no DVD was sent to this customer, then we move on to the next customer 
    // (do not change this customer's priority for tomorrow's shipment)
    if (!sent_dvd) {
      customer_itr++;
    }
  }

  

}

// ==================================================================
