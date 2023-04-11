HOMEWORK 4: DVD LISTS


NAME:  < brody boucher >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com

Remember: Your implementation for this assignment must be done on your
Maown, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 8 hours >


ORDER NOTATION:
For each function, using the variables:
  d = number of different movie DVD titles
  k = average or maximum copies of each DVD
  c = number of customers
  p = average or maximum movies ranked on each customer’s preference list
Include a short description of your order notation analysis.

dvd: O(1) only needs to add copy amount

customer: O(p) needs to add each one 

add_preference: O(1) adds it in (work needed to get customer)

ship: O(c*p) goes through each customer and preference list

return_oldest: O(1) told popback  (work needed to get customer)

return_newest: O(1) told to remove back (work needed to get customer)

print_customer: O(K) has to go through movies held

print_dvd: O(1) only accesses once 



EXTRA CREDIT:
Describe the analysis you performed on customer satisfaction.  Paste
in a small amount of sample analysis output and/or specify a sample
output file.  Describe your improved algorithm and compare the
analysis results of your new algorithm.  Please be concise!



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






