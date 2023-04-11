/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree {
friend class BPlusTreeNode<T>;
public:

	//default constructor 
	BPlusTree(const int md) : root(NULL), max_degree(size), size(0) {}
 	//copy constructor
 	BPlusTree(const BPlusTree<T>& old) : size(old.size) { 
    	root = this->copy_tree(old.root, NULL); 
    }
    //equal to operation
    BPlusTree& operator=(const BPlusTree<T>& old) {
	    if (&old != this) {
	    	this->destroy_tree(root);
	    	root = this->copy_tree(old.root,NULL);
	    	size = old.size;
	    }
	    return *this;
	}
	//destructor
    ~BPlusTree() {
    	this->destroy_tree(root);
    	root = NULL;
  	}


  	//find function
  	BPlusTreeNode<T>* find(const T& key_value){ find(key_value, root);	}
  	//insert function
  	void insert(const T& key_value){ insert(key_value, root, NULL);	}
	//print sideways
	void print_sideways(std::ostream& ostr) const {	print_sideways(ostr, root, 0);}

	void print_BFS(std::ostream& ostr) const {	print_sideways(ostr, root, 0);}

	void print_BFS_pretty(std::ostream& ostr) const {	print_sideways(ostr, root, 0);}


private:
	BPlusTreeNode<T>* root;
	int max_degree;
	int size;

	//PRIVATE FUNCTIONS

	//Helper copy  function
	BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* the_parent){

	}

	//Helper destroy function
	void destroy_tree(BPlusTreeNode<T>* root){

	}
	//finds a value and returns the Node it is in
	BPlusTreeNode<T>* find(const T& key_value, BPlusTreeNode<T>* root){

	}

	//inserts an unique value into the tree
	void insert(const T& key_value, BPlusTreeNode<T>*& p, BPlusTreeNode<T>* the_parent){

	}

	//prints the tree in a sideways direction
	void print_sideways(std::ostream& ostr, const BPlusTreeNode<T>* p, int depth) const {

	}
};




#endif
