HOMEWORK 3: JAGGED ARRAY


NAME:  < Brody Boucher >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< cplusplus.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 7 hours >


ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements in the largest bin


numElements
 unpacked:  O(1)
 packed:    O(1)

numBins
 unpacked:  O(1)
 packed:    O(1)

numElementsInBin
 unpacked:  O(e)
 packed:    

getElement
 unpacked:  O(1)
 packed:    O(1)

isPacked
 unpacked:   O(1)
 packed:     O(1)

clear
 unpacked:  O(k^2)
 packed:    O(e)

addElement
 unpacked:   O(e)
 packed:     O(e)

removeElement
 unpacked:   O(e)
 packed:

pack
 unpacked:  O(k^2)
 packed:

unpack
 unpacked:
 packed:    O(k^2)

print 
 unpacked:   O(e^2)
 packed:     O(e)

constructor w/ integer argument
 unpacked:  O(b)
 packed:    

copy constructor
 unpacked:  O(k^2)
 packed:    O(e)

destructor
 unpacked:  O(k^2)
 packed:	O(e)

assignment operator
 unpacked:  O(k^2)
 packed:    0(e)




MISC. COMMENTS TO GRADER:  
I cannot figure out this leak, it doesn't affect the data at all. It only happens with the first
element of the first pointer is being added, and bc of it I am losing 4 points. Hopefully you 
can find it, thankyou.

