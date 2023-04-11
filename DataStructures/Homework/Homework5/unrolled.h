#ifndef UnrolledLL_h_
#define UnrolledLL_h_
#include <iostream>
#include <vector>
#include <cassert>

// -----------------------------------------------------------------
// NODE CLASS
template <class T> 
class Node {
public:
  Node(){   //a basic constructor
    next=NULL;
    prev=NULL;
    size=0;
  }
  Node(const T& v){
    next=NULL;
    prev=NULL;
    size=1;
    array[0]=v;
  }
  
  //Variables
  Node<T>* next;
  Node<T>* prev;
  T array[6];
  int size;  
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:

  list_iterator(Node<T>* p=NULL) : ptr(p), index(0) {} //constructor


  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { 
  return ptr->array[index];  
  }

  // pre-increment
  list_iterator<T> operator++() { 
    if(ptr->size == index+1 ) {
      ptr=ptr->next;
      index=0;
    }
    else {
      index++;
      
    }
    return *this;
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    Node<T>* temp = ptr;
    if(ptr->size == index+1 ) {
      ptr=ptr->next;
      index=0;
    }
    else {
      index++;
      
    }
    return temp;
  }

  //pre -incrimaent
  list_iterator<T> operator--() { 
    if(index == 0){
      ptr=ptr->prev;
      index = ptr->size-1;
    }
    else{
      index--;
    }
    return *this;
  }

  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
     Node<T>* temp = ptr;
     if(index == 0){
      ptr=ptr->prev;
      index = ptr->size-1;
    }
    else{
      index--;
    }
    return temp;
  }

  
  friend class UnrolledLL<T>;

  bool operator==(const list_iterator<T>& r) const { //checks if = to eachother
    return ptr == r.ptr; }
  bool operator!=(const list_iterator<T>& r) const { //checks if != to eachoter
    return ptr != r.ptr; }

private:
 //variables
  Node<T>* ptr;
  int index;  
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
template <class T>
class UnrolledLL {
public:

  UnrolledLL() { //basic constructor
    size_=0;
    head_=NULL;
    tail_=NULL;
  }
  UnrolledLL( UnrolledLL<T>& old) { copy_list(old); } //copy constructot
  UnrolledLL& operator= (const UnrolledLL<T>& old);  // set = to (copy)
  ~UnrolledLL() { destroy_list(); }  // destructor

  typedef list_iterator<T> iterator;


  unsigned int size() const { return size_; }  //returns size
  void clear() { destroy_list();  }  //clears list

// access the first or last element
  const T& front() const {  return head_->array[0]; }   
  T& front() { return head_->array[0]; }
  const T& back() const { return tail_->array[tail_->size-1]; }
  T& back() { return tail_->array[tail_->size-1]; }


  void push_front(const T& v);  // adds to beginning
  void pop_front();             //removes begininng
  void push_back(const T& v);   // adds to back
  void pop_back();              //removes back
  void print(std::ostream& out); //helper print function

  iterator erase(iterator itr);                 //deletes a value
  iterator insert(iterator itr, const T& v);    // adds a value
  iterator begin() { return iterator(head_); }  // points to head
  iterator end() { return iterator(NULL); }     // points to NULL

private:

  void copy_list( UnrolledLL<T>& old);  //copy helper function
  void destroy_list();                  // destruction helper function
  
  //varaibles
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;
};

// -----------------------------------------------------------------

//set equal to
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  //this.copy_list(old);
  //destroy_list(old);

}

//add to front
template <class T>
void UnrolledLL<T>::push_front(const T& v) {
  if(head_->size<6){
    for(int i=head_->size;i>0;i--){
        head_->array[i]=head_->array[i-1];
    }
    head_->array[0]=v;
    head_->size+=1;
  }
  else{
    Node<T>* temp = new Node<T>;
    temp->array[0]=v;
    head_->prev=temp;
    temp->next=head_;
    head_=temp;
    head_->size=1;
  }
  size_++;
}

//remove from front
template <class T>
void UnrolledLL<T>::pop_front() 
{
  //T val = head_->array[0];
  //std::cout << val << std::endl;
  if(head_->size==1)
  {
    Node<T>* temp;
    if(head_==tail_){
      temp=head_;
      head_=NULL;
      tail_=NULL;
      delete temp;
    }
    else{
    temp=head_;
    head_=head_->next;
    head_->prev=NULL;
    delete temp;
    }
  }
  else
  {
    for (int i=0; i<head_->size-1;i++) {
          head_->array[i]=head_->array[i+1];
      }

    head_->size-=1;
  }
  size_--;
}

//add to back
template <class T>
void UnrolledLL<T>::push_back(const T& v) 
{

  if(tail_==NULL){
    Node<T>* temp = new Node<T>;
    temp->array[0]=v;
    temp->size=1;
    head_=temp;
    tail_=temp;
  }
  else if(tail_->size==6)  
  {
    Node<T>* newp = new Node<T>;
     
    newp->array[0]=v;
    newp->size=1;
    newp->prev = tail_;
    tail_->next = newp;
    tail_ = newp;
  }
  else
  {
      tail_->array[tail_->size]=v;
      tail_->size++;
  }
  size_++;

}


//remove from back
template <class T>
void UnrolledLL<T>::pop_back() {
  //T val = tail_->array[tail_->size-1];
  //std::cout << val << std::endl;
  if(tail_->size==1)
  {
    Node<T>* temp;
    if(tail_==head_){
      temp=tail_;
      tail_=NULL;
      head_=NULL;
      delete temp;
    }
    else{
    temp=tail_;
    tail_=tail_->prev;
    tail_->next=NULL;
    delete temp;
    }
  }
  else
  {
    tail_->size-=1;
  }
  size_--;
}

//checks equal to returns bool
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) 
{
  if(left.size()!=right.size()) return false;
  typename UnrolledLL<T>::iterator itr1 = left.begin();
  typename UnrolledLL<T>::iterator itr2 = right.begin();

  while(itr1 != left.end()){
        if(*itr1!=*itr2){
      return false;
    }
    itr1++;
    itr2++;
  }
  return true;
}

//checks if not equal to
template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  if(itr.ptr->size==1){
    if(itr.ptr==head_){
     std::cout << *(itr) << std::endl;
      Node<T>* temp;
      temp=head_;
      head_=head_->next;
      head_->prev=NULL;
      itr.ptr=head_;
      delete temp;
      
    }
    else if(itr.ptr==tail_){
     // std::cout << *(itr) << std::endl;
      Node<T>* temp;
      temp=tail_;
      tail_=tail_->prev;
      tail_->next=NULL;
      itr.ptr=NULL; 
      delete temp;
      
    }
    else{
     // std::cout << *(itr) << std::endl;
      Node<T>* temp;
      temp=itr.ptr;
      itr.ptr->prev->next=itr.ptr->next;
      itr.ptr->next->prev=itr.ptr->prev;
      itr.ptr=itr.ptr->next;
      delete temp;
      
    }
  }
  else{
    //std::cout << *(itr) << std::endl;
    if(itr.index==itr.ptr->size-1){
      itr.ptr->size-=1;
      itr.ptr=itr.ptr->next;
      itr.index=0;
    }
    else{
      for(int i=itr.index; i<itr.ptr->size-1; i++){
        itr.ptr->array[i]=itr.ptr->array[i+1];
      }
      itr.ptr->size-=1;
    }
    
  }

  size_--;
  return itr;
}

//inserts an element
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
if(itr.ptr->size<6){
  for(int i=itr.ptr->size;i>itr.index;i--){
    itr.ptr->array[i]=itr.ptr->array[i-1];
  }
  itr.ptr->array[itr.index]=v;
  itr.ptr->size+=1;
}
else{
  Node<T>* newp = new Node<T>;
  newp->array[0]=v;
  newp->size=1;
  int var=0;
  for(int i=itr.index;i<itr.ptr->size;i++)
  {
    newp->array[newp->size]=itr.ptr->array[i];
    newp->size+=1;
    var++;
  }
  itr.ptr->size-=var;
  itr.ptr->next->prev=newp;
  newp->next=itr.ptr->next;
  newp->prev=itr.ptr;
  itr.ptr->next=newp;
  itr.ptr=itr.ptr->next;
}
size_++;
return itr;
}

// copy helper function
template <class T>
void UnrolledLL<T>::copy_list( UnrolledLL<T>& old) 
{
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == 0) {
    head_ = tail_ = 0;
    return;
  }
  // Create a new head node.
  head_ = new Node<T>();
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    tail_->next_ = new Node<T>(old_p->value_);
    tail_->next_->prev_ = tail_;
    tail_ = tail_->next_;
    old_p = old_p->next_;
  }

}
 //destructor helper funciton
template <class T>
void UnrolledLL<T>::destroy_list() {
   Node<T> *n = head_;
    while (n)
    {
        Node<T> *next = n->next;
        delete n;
        n = next;
    }
    head_=NULL;
    tail_=NULL;

}

//print helper function
template <class T>
void UnrolledLL<T>::print(std::ostream& out) 
{
  for(iterator itr = head_; itr != NULL; itr++)
  {
    out << " " << *itr;
  }
  out << "\n";
}

#endif

// cd /mnt/c/Users/Bouchb4/OneDrive/Desktop/DataStructures/Homework/Homework5