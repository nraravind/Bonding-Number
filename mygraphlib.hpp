#include<iostream>
#include<utility>
#include<vector>
#include<unordered_map>
#include<map>
#include<unordered_set>
#include<algorithm>
#include<string.h>
using std::cout;
using std::endl;
using std::unordered_map;
using std::vector;
using std::unordered_set;
using std::map;
using std::pair;

// Defines a graph with a partition, i.e. color classes, and demands on each vertex
// Supports the merging of color classes by a direct implementation of disjoint set data structure

class coloredGraph
{
private:
    int n; //number of vertices
    int m; //number of edges


    unordered_map<int,unordered_set<int>> adjList;
    unordered_map<int,vector<pair<int,double>>> tieWeights;
    unordered_map<int,int> degree;
    unordered_map<int,int> demand;

    unordered_map<int,int> parent; //Defines the color classes via disjoint set structure
    unordered_map<int,int> next; // Defines a circular linked list in each color class for traversal
    unordered_map<int,int> prev; // The reverse of next
    map<int,int> setSize; //Stores root, set-size pairs
    unordered_map<int,int> border; // Stores root and a vertex with neighbors outside

public:

    int numColors;

    void printStats();
    void printAdjList();
    void printDegrees();
    void printDemands();
    void printSetSizes();
    void printSet(int u);
    void printSets();
    void printBorders();


    bool isEdge(const int u, const int v);

    void addVertex(const int vertexID); // Adds a new vertex with degree zero and in a separate color class
    void addEdge(const int u,const int v); //Adds an edge uv and if u or v is not in the graph, adds it using addVertex.
    void addEdges(vector<std::pair<int,int>> edges);

    void removeEdge(const int u,const int v);
    void removeIsolatedVertex(const int u);

    void setDemand(int d);

    int findRoot(const int v); //Returns the color of v
    int mergePair(const int u,const int v); //Merges u and v's color classes and returns the smaller color

    int numConnected(); // Returns the number of connected components

    void cleanEdges(); // Deletes the edges inside all color classes and updates demands
    void cleanVertices(); // Deletes vertices of degree zero.

    int colorDegree(int u, int v); //Finds the degree of u in the color class of v
    bool reduceOnce();


    // Retains low-degree neighbors if flag=true and mutual low-degree otherwise
    // If deg(v)>dth smallest degree in N(u) and deg(u)>dth smallest in N(v)
    coloredGraph chooseLowDegree(int d,bool flag);

    coloredGraph();
    coloredGraph(const coloredGraph& G);
    ~coloredGraph(){};
    coloredGraph mergeSaturated(); //Merges all adjacent pairs u,v such that u or v is saturated to obtain a reduced instance
    coloredGraph reduceGraph(int d);


    int giant(); // Returns root of giant component
    int lowerBound(int d);
    pair<int,int> findBounds(int d);

    bool isAttached(int d);
    int findAN();
    pair<int,int> findlowdegBounds(int D, bool flag);



};
