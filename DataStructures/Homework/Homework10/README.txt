HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  < insert name >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest  |
|          | sort     | dups     | mode     | pair     | sorted   | substr   | 
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| vector   | O(nlogn) | O(nlogn) | O(n^2)   | O(nlogn) |O(f+nlogn)|O(l^2n^2) |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| list     | O(nlogn) | O(nlogn) | O(n^2)   | O(nlogn) |O(f+nlogn)|O(l^2n^2) |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| bst      |    x     |     x    | O(n)     | O(n)     | O(f)     |O(l^2n^2) |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| pq       | x (min)  |  O(n)    | O(n^2)   | O(n)     |  O(f+n)  |O(l^2n^2) |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| hash     | o(n)     |  o(n)    |  O(n)    |  O(n)    | O(n+f)   |O(l^2n^2) |
------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

< insert your performance measurements and coefficient estimates >






DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  


For the most part my predictions match the results. As I thought, list and vector would have
a similar result as well as hash table and bst having similar results too. Some of the results 
did surprise me since I thought that the vector would preform well, but it was all around slower
and took up a decent amount of memory. These results will impact what I code in the future, since 
the bst and the hash table made it easy to find and use the unique values and the duplicate values
since that information was held in the second position. I also found interesting how the datastructures matched up when accessing an element was taken out of the picture. Typically having easy access to an element is curcial, but for this program it was not and it showed through which data structures were helpful.


< insert your discussion of the results, including your answers to the
above questions >



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
