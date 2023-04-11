

template <class T> class JaggedArray {
	
public:
	//TYPEDEFS
	typedef T* iterator;

	//CONSTRUCTORS, ASSIGNMNENT OPERATOR, & DESTRUCTOR
	JaggedArray(int size) { this->create(size); } //constuctor
	JaggedArray( JaggedArray& J){copy(J); }       //copy constructor
	void operator=( JaggedArray& J);              // = operation
	~JaggedArray() { del(); }                     // delete operation

	 // MEMBER FUNCTIONS AND OTHER OPERATORS
	int numElements() { return num_elements; }    //returns the num of elements in array
	int numBins() { return num_bins; }            //returns num of bins in the array
	int numElementsInBin(uint x);                 //returns how many elements are in a bin
	T& getElement(uint x, uint y);                //returns an element from the array
	bool isPacked();                              //check if packed or unpacked

	void addElement(uint pos, const T& t);        //adds element to the array
	void removeElement(int x, int y);             //removes element from the array
	void clear();                                 //clears the elements adn bins
	void print();                                 //prints data in the array
	void pack();                                  //turns array into packed format
	void unpack();                                //turns array into unpacked format


private:
	void create(int size);              //helper function for constructor
	void copy( JaggedArray& J);         //helper function for copy constructor
	void del();                         //helper function for delete operation

	uint num_elements, num_bins;        //contains bin size and element size
	int* counts;                        //points to first element in array of ints unpacked
	int* offsets;                       //points to first element in arrat of ints packed
	T** unpacked_values;                //points to array of pointers to another array
	T* packed_values;                   //points to an array of added type

};

//Called when in the consturctor, creates the array and sets the variables
template <class T> void JaggedArray<T>::create(int size) {
	num_elements=0;
	num_bins=size;
	offsets=NULL;
	packed_values=NULL;

	int* t= new int[size];
	counts=t;
	T** t1= new T*[size];
	unpacked_values=t1;
	for(int i=0; i<size; i++)  
	{ counts[i]=0; unpacked_values[i]=NULL; } //sets pointers to NULL
	
}

//Takes one JaggedArray and makes a copy of it for the copy constructor
template <class T> void JaggedArray<T>::copy( JaggedArray& J) {
	num_elements=J.numElements();
	num_bins=J.numBins();

	if(J.isPacked()) //for packed version
	{
		counts=NULL;
		unpacked_values=NULL;
		offsets = new int[J.numBins()]; 
		packed_values= new T[J.numElements()];
		for(int i =0; i<J.numBins(); i++){ offsets[i]=J.offsets[i]; }
		for(int i =0; i<J.numElements(); i++){ packed_values[i]=J.packed_values[i]; }
		num_bins=J.numBins();
		num_elements=J.numElements();
	}
	else  //for unpacked version
	{
		offsets=NULL;
		packed_values=NULL;
		T* t2;
		counts = new int[J.numBins()]; 
		unpacked_values= new T*[J.numBins()];
		for(int i =0; i<J.numBins(); i++){ counts[i]=J.counts[i]; }
		for(int i =0; i<J.numBins(); i++)  //for the 2D array
		{ 
			
			if(counts[i]==0) { t2=NULL; } //check
			else {t2 = new T[counts[i]];}
			for(int x=0; x<counts[i]; x++) //sets values
			{	
				t2[x]=J.getElement(i, x);
			}
			unpacked_values[i]=t2;
		}

	}
}

//Checks to see the varables (b=b) are the same then deletes and copies
template <class T> void JaggedArray<T>::operator=( JaggedArray& J) {
	if(this != &J)
	{
		this->del();  //calls delete helper
		this -> copy(J);   //calls copy helper
	}
}

//helper function to delete everything so there are no leaks
template <class T> void JaggedArray<T>::del() {
	if(isPacked())
	{
		delete [] packed_values;
		delete [] offsets;
	}
	else
	{
		for (uint i = 0; i < num_bins; ++i) //goes inside and deletes pointers
      	{
     	    delete [] unpacked_values[i];
     	 }
		delete [] unpacked_values;
		delete [] counts;
	}
	num_bins=0;
	num_elements=0;
}

//adds a variable to a certian bin, creates array in the process
template <class T> void JaggedArray<T>::addElement(uint pos, const T& t) {
	counts[pos]=counts[pos]+1;
		if(counts[pos]>0){
		T* temp2= new T[counts[pos]];
		if(counts[pos]==0) { temp2=NULL; }
		for(int i=0; i<counts[pos]; i++){   //sorts through old array adding to the new one
			if(i==counts[pos]-1)
				temp2[i]=t;
			else
				temp2[i]=unpacked_values[pos][i];
		}
		if(counts[pos]!=1)
		delete [] unpacked_values[pos]; //deletes any array previously in
		unpacked_values[pos]=temp2;
	
	num_elements++;
}
	
}

//deletes a certain element from a certian bin, creates array in the process
template <class T> void JaggedArray<T>::removeElement(int x, int y) {
	if(counts[x]==1) 
		unpacked_values[x]=NULL;  //sets to NULL if nothing left
	else{
		T* temp3 = new T[counts[x]-1];
		int counter=0;
		for(int i=0; i<counts[x]; i++){   //adds to new array, not the removed value 
			if(i!=y){
				temp3[counter]=unpacked_values[x][i];
				counter++;
			}
		}
		delete [] unpacked_values[x];  //deletes previous values
		unpacked_values[x]=temp3;
	}
	counts[x]-=1;
	num_elements--;
}

//clears all of the data in a Jagged array (delets then creates a new Jagged array)
template <class T> void JaggedArray<T>::clear() {
	int x =num_bins; //remebers size
	del();
	this->create(x);  //creates with same size
}

//helper function for checking for bugs, prints information
template <class T> void JaggedArray<T>::print() {
	
	std::cout << "num_elements: " << num_elements << std::endl;
	std::cout << "num_bins: " << num_bins << std::endl;

	if(!isPacked()) //for the unpacked version
	{
		for(uint i=0; i<num_bins; i++){       
			std::cout << counts[i] << " :";
			if(unpacked_values[i]==NULL) 
				{ std::cout << " /"; }
			else
			{
				for(int x=0; x < counts[i]; x++)//prints the inner contents
				{
				std::cout << " " << unpacked_values[i][x];
				}
			}
			std::cout << std::endl;
		}
	std::cout << "offsets: NULL" << std::endl << "packed_values: NULL" << std::endl;
	}
	else //for packed version
	{
		std::cout << "counts: NULL" << std::endl << "unpacked_values: NULL" << std::endl;
		for(uint i=0; i<num_bins; i++) { std::cout << offsets[i] << " "; }
		std::cout << std::endl;
		for(uint i=0; i<num_elements; i++) { std::cout << packed_values[i] << " ";}
		std::cout << std::endl;
	}

}

//checks whether ispacked then returns number of elements in a bin
template <class T> int JaggedArray<T>::numElementsInBin(uint x) {
	if(isPacked()){
		if(x==num_bins-1) return (num_elements-offsets[x]);  //if the bin is the final
		else return (offsets[x+1]-offsets[x]);   //math to find elements in bin
	}
	else {
		return counts[x];
	}
}

//checks whether ispacker then returns an element in a bin
template <class T> T& JaggedArray<T>::getElement(uint x, uint y) {
	if(isPacked()){
		
		return packed_values[offsets[x]+y];   //packed
	}
	else {
		return unpacked_values[x][y];  //unpacked
	}
}

//checks if the array is packed or not returns true if packed
template <class T> bool JaggedArray<T>::isPacked() {
	if(counts==NULL) { return true; }  //checks counts
	else { return false; }
	
}

//turns the array into the packed version
template <class T> void JaggedArray<T>::pack() {
	int* temp4 = new int[num_bins];
	T* temp5 = new T[num_elements];
	int count=0;

	for(uint i=0; i<num_bins; i++)   //loops through
	{
		temp4[i]=count;
		for(int x=0; x<counts[i]; x++)   //condenses inner contents to one array
		{
			temp5[count]=getElement(i,x);
			count++;
		}
		delete [] unpacked_values[i];  //deletes all the pointers

	}
	
	delete [] unpacked_values;  //deletes and set the other values
	delete [] counts;
	unpacked_values=NULL;
	counts=NULL;
	offsets=temp4;
	packed_values=temp5;


}

//turns the array into the unpacked version
template <class T> void JaggedArray<T>::unpack() {
	int* t=new int[num_bins];
	for(uint i=0; i<num_bins;i++)   //loops through to find the elements in the bins
	{
		if(i==num_bins-1)
			t[i]= (num_elements-offsets[i]);
		else
			t[i]= (offsets[(i+1)]-offsets[i]);
	}
	counts=t;
	delete [] offsets;  //deletes and sets values
	offsets=NULL;
	int count1=0;
	T** t1 =new T*[num_bins];
	for(uint i=0; i<num_bins;i++)   //expands the inner array to a 2d array
	{
		T* t2 = new T[counts[i]];
		for(int x=0; x<counts[i]; x++)
		{
			t2[x]=packed_values[count1];
			count1++;
		}
		t1[i]=t2;
	}
	delete [] packed_values;  //deletes and sets values
	unpacked_values=t1;

}

