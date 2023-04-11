#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#ifndef dna_hash_h
#define dna_hash_h


class Hash;
class HashNode
{
  public:    
    //Constructor of hashnode 
    HashNode(std::string key, int v)
    {
        value.push_back(v);
        key = key;
    }
    friend class Hash;
  private:
    std::vector<int> value;
    std::string key;
};
  
class HashNode;
//Our own Hash class
class Hash
{
  friend class HashNode;
  private:
    //hash element array
    std::vector<HashNode> table;
    int size, inputs;
    int multiplier;
  
  public:
    Hash(int n)
    {
      //Initial capacity of hash array
      table.resize(n);
      size=n;
      inputs=0;
      multiplier=1;    
    }
    // This implements hash function to find index
    // for a key
    int hashCode(std::string key)
    {
      int number=0;
      for(int i=0; i<key.size(); i++){
        if(key[i]=='a') number+=pow(1,i+1);
        if(key[i]=='t') number+=pow(2,i+1);
        if(key[i]=='c') number+=pow(3,i+1);
        if(key[i]=='g') number+=pow(4,i+1);
      }
      return (number*multiplier%(size-1));
    }
      
    //Function to add key value pair
    void insert(std::string key, int position)
    {
        
    }

      
    
};
  

#endif