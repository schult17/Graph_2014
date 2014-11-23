Graph_2014
==========

Implementation of a adjacency list graph in C++ with shortest paths (released to fellow classmates for study purposes)

Graph Implementation
Tanner Young-Schultz

For the purpose of studying for our exam and preperation for next semester (Design Course)

Couple Recourses:

	youtube video explaining algorithm (best I could find, and what I used):
	
		https://www.youtube.com/watch?v=0nVYi3o161A

	C++ guide (with pseudocode) describing algorithm:
	
		http://www.cprogramming.com/tutorial/computersciencetheory/dijkstra.html

Compile from a directory with just these files in it:
	
	g++ -g *.cpp -o Graph

If you want to play around with inputs:
	
	./Graph

If you want to see my example inputs:
	
	./Graph < input1.txt
		or
	./Graph < input2.txt


Have not run valgrind on it, I am pretty sure I delete all dynamic memory but I am not 100%
sure... don't yell at me if there is leakage
