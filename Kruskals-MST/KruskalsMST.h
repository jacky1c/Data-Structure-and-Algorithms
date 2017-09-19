//
//  KruskalsMST.h
//  CS340A3Q1
//
//  Created by Jacky on 2017-03-03.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;
typedef int Object;
const int MAX_SIZE_OF_ARRAY = 25;

#ifndef KruskalsMST_h
#define KruskalsMST_h

struct Edge{
    Object vertex1;
    Object vertex2;
    int distance;
};

struct VertexNode{
    Object vertex;
    VertexNode *next;
};

struct SubsetNode{
    int size;
    VertexNode *firstVertex;
};

struct SetNode{
    Object vertex;
    SetNode *left = NULL;
    SubsetNode *subset = NULL;
    SetNode *right = NULL;
    int height;
};

#endif /* KruskalsMST_h */

void Initialization (Edge q[], int& edgeCount, SetNode*& s, int& vertexCount, string fileName);

void Insert (Object x, Object y, Object z, Edge q[], int& edgeCount); // binary tree

bool Insert (Object w, SetNode*& s, int& vertexCount); // AVL tree

void MakeSet (SetNode*& v);

void Search (Edge q[], int edgeCount, SetNode*& s, int vertexCount, Edge t[], int& length_of_t);

Edge DeleteMin (Edge q[], int& edgeCount);

void Union (SetNode*& vTo, SetNode*& vFrom, SetNode*& s);

void Tree (Edge t[], int length_of_t);

// The following functions are not provided in Dr.Hilderman's pseudo code

SetNode* Find (Object x, SetNode* s);

// Height, LL, LR, RL, RR are used in Insert AVL tree
int Height (SetNode*);

void LL(SetNode*&);
void LR(SetNode*&);
void RL(SetNode*&);
void RR(SetNode*&);

void ShowBinaryHeapStructure(Edge q[], int edgeCount);

void ShowHelper(SetNode*, int);
void ShowAVLTreeStructure(SetNode* s);
