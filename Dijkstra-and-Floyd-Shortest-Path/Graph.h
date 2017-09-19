//
//  DijkstrasGraph.h
//
//  Created by Jacky on 2017-02-05.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include<iostream>
#include<fstream>
using namespace std;


typedef int ItemType;
const int NO_OF_VERTICES = 10;// must be greater or equal to number of vertices+1
const int HIGH_VALUE = 999;
const int NO_VERTEX_FOUND = -999;

// For Dijkstras Algorithm
#ifndef Graph_h
#define Graph_h

struct Follower{
    ItemType vertex;
    int distance;
    Follower *nextFollower;
};
struct Leader{
    ItemType vertex;
    bool known;
    int distance;
    Follower *firstFollower;
};

#endif /* Graph_h */

void Initialization(Leader a[], string fileName);
ItemType FindNextVertex(Leader a[]);
void Search(Leader a[], ItemType startVertex);
void Paths(Leader a[]);
void ShowStructure(Leader a[]);





// For Floyds ALgorithm
void Initialization (int [][NO_OF_VERTICES], int [][NO_OF_VERTICES], int, string);
void Search (int [][NO_OF_VERTICES], int [][NO_OF_VERTICES], int);
void Paths (int [][NO_OF_VERTICES], int [][NO_OF_VERTICES], int, int);

