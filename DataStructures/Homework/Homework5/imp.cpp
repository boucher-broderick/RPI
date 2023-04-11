#ifndef UnrolledLL_h_
#define UnrolledLL_h_
#include <iostream>
#include <vector>
// A simplified implementaztion of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined:a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  Node() : next_(NULL), prev_(NULL), array_size(0) {}
  Node(const T& v) : next_(NULL), prev_(NULL), array_size(1) 
  {
    array[0]=v;
  }

  // REPRESENTATION
  int array_size;
  T array[5];
  Node<T>* next_;
  Node<T>* prev_;
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator(Node<T>* p=NULL) : ptr_(p), index(0) {}
  // NOTE: the implicit compiler definitions of the copy constructor,
  // assignment operator, and destructor are correct for this class

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->array[index];  }

  // increment & decrement operators

  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
    if(index==5){
      ptr_ = ptr_->next_;
      index=0;
    }
    else{
      index++;
    }
    return temp;
  }
  
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    if(index==0)
    {
      ptr_ = ptr_->prev_;
      index=ptr_->array_size;
    }
    else
    {
      index--;
    }
    return temp;
  }
  // the UnrolledLL class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_; }
  bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_; }

private:
  // REPRESENTATION
  Node<T>* ptr_;
  int index;    // ptr to node in the list
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
  UnrolledLL& operator= (const UnrolledLL<T>& old);
  ~UnrolledLL() { destroy_list(); }

  typedef list_iterator<T> iterator;

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { destroy_list(); }

  // read/write access to contents
  const T& front() const { return head_->array[0];  }
  T& front() { return head_->array[0]; }
  const T& back() const { return tail_->array[tail_->array_size]; }
  T& back() { return tail_->array[tail_->array_size]; }

  // modify the linked list structure
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();
  void print(std::ostream& out);

  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& v);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(NULL); }

private:
  // private helper functions
  void copy_list(const UnrolledLL<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}

template <class T>
void UnrolledLL<T>::push_front(const T& v) {





}

template <class T>
void UnrolledLL<T>::pop_front() {




}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {
  // special case: initially empty list
  if (!tail_)  //NEW LIST
  {
    Node<T>* newp = new Node<T>(v);
    head_ = tail_ = newp;
  } 
  else 
  {
    // normal case: at least one node already
    if(tail_->array_size==6)  //NEEDS A NEW NODE
    {
    Node<T>* newp = new Node<T>(v);
    newp->prev_ = tail_;
    tail_->next_ = newp;
    tail_ = newp;
    }
    else
    {
      tail_->array[tail_->array_size]=v;
      tail_->array_size++;

    }
  }
  ++size_;
}

template <class T>
void UnrolledLL<T>::pop_back() {





}

// do these lists look the same (length & contents)?
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
  if (left.size() != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}

template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  assert (size_ > 0);
  --size_;
  iterator result(itr.ptr_->next_);
  // One node left in the list.
  if (itr.ptr_ == head_ && head_ == tail_) {
    head_ = tail_ = 0;
  }
  // Removing the head in a list with at least two nodes
  else if (itr.ptr_ == head_) {
    head_ = head_->next_;
    head_->prev_ = 0;
  }
  // Removing the tail in a list with at least two nodes
  else if (itr.ptr_ == tail_) {
    tail_ = tail_->prev_;
    tail_->next_ = 0;
  }
  // Normal remove
  else {
    itr.ptr_->prev_->next_ = itr.ptr_->next_;
    itr.ptr_->next_->prev_ = itr.ptr_->prev_;
  }
  delete itr.ptr_;
  return result;
}


template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  ++size_ ;
  Node<T>* p = new Node<T>(v);
  p->prev_ = itr.ptr_->prev_;
  p->next_ = itr.ptr_;
  itr.ptr_->prev_ = p;
  if (itr.ptr_ == head_)
    head_ = p;
  else
    p->prev_->next_ = p;
  return iterator(p);
}


template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == 0) {
    head_ = tail_ = 0;
    return;
  }
  // Create a new head node.
  head_ = new Node<T>(old.head_->value_);
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

template <class T>
void UnrolledLL<T>::destroy_list() {







}

template <class T>
void UnrolledLL<T>::print(std::ostream& out) {




}

#endif

// /mnt/c/Users/Bouchb4/OneDrive/Desktop/DataStructures/Homework/Homework5