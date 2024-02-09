*** Computing Bonding Numbers ***

This project computes lower and upper bounds for

(a) the bonding number of a graph;

(b) the bonding number when each node chooses only among its lowest-degree neighbors;

(c) the bonding number when each node chooses only among its highest-degree neighbors.

The input graph must be connected (otherwise the program terminates with an error message).


*** Instructions to compile and run ***

The project consists of two header files and three cpp files.
The names of these files are:

graphio.h, mygraphlib.h,
graphio.cpp, mygraphlib.cpp, main.cpp.

No additional software or libraries are used and compilation is standard with gcc,
as below.

1. Put the source network files (edgeList format) in the same folder.

2. g++ -c *.cpp

3. g++ -o out *.o

4. Run ./out or out# Bonding-Number

