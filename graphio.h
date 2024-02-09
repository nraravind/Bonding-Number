#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using std::cout;
using std::endl;
using std::vector;


vector<std::pair<int,int>> getEdges(char fname[50]);
void printEdges(vector<std::pair<int,int>> edges);
void addToFile(char fname[50],int lb,int ub,int pb);

