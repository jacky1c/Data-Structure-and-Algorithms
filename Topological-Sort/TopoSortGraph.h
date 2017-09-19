//
//  TopoSort.h
//
//  Created by Jacky on 2017-02-01.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;
typedef int ItemType;

#ifndef TopoSortGraph_h
#define TopoSortGraph_h

//struct Leader;
//struct Follower;

struct Follower;
struct Leader{
    ItemType vertex;
    int inDegree;
    Leader *nextLeader;
    Follower *firstFollower = NULL;
};
struct Follower{
    Leader *adjacentLeader;
    Follower *nextFollower;
};

// Define a class for the graph which encapsulates the information about the graph:
// the head, tail, and the number of vertices
class TopoSortGraph{
private:
    Leader* head;
    Leader* tail;
    int vertexCount;
public:
    TopoSortGraph(); // default constructor
    ~TopoSortGraph(); // destructor
    Leader* getHead(); // getter for head
    Leader* getTail(); // getter for tail
    int getVertexCount(); // getter for vertexCount
};


// Functions used for Topological Sort
void Initialization (Leader*&, Leader*&, int&, string); // initialize the graph
Leader* BuildList (int, Leader*&, Leader*&, int&); // called by initialization
void FindStartVertex (Leader*&, Leader*&); // head and start will points to the starting node
void PartialOrder (Leader*, Leader*, int); // sort the graph and output the result
void UpdateFollower (Leader*&, Leader*&);
void ShowGraphStructure (Leader*, Leader*, int);


#endif /* TopoSort_h */
