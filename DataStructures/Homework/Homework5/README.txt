HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Brody Boucher >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< c++.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 9 hours >



TESTING & DEBUGGING STRATEGY:
I made tests for functions that were not in the basic test and mainly used print lines to help with debugging.



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

size  O(1)
front O(1)
back  O(1)
push_back O(2)
pop_back  O(2)
push_front O(n) n= number of elements in an array
pop_front O(n) n= number of elements in an array
erase  O(n) n= number of elements in an arrayv
insert  O(n) n= number of elements in an array

UnrolledLL's main difference is the number of nodes. When in th dslist you need a node for every value,
which takes up a lot of space, the unrolledLL needs one node for every X values. The Unrolled LL is less
effective when it comes to adding or removing elements. For a link list all you need to do is change the 
pointets but in the UnrolledLL you have to go through and fix the array which takes more time. The average
elements per node is around 4-5, since the nodes are not always full but usually have more than less elements.


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


