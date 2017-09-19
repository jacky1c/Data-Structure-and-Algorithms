//
//  main.cpp
//  CS340A3Q1
//
//  Created by Jacky on 2017-03-03.
//  Copyright © 2017 Jacky. All rights reserved.
//
#include "KruskalsMST.h"

int main(int argc, const char * argv[]) {
    Edge q[MAX_SIZE_OF_ARRAY];
    Edge t[MAX_SIZE_OF_ARRAY];
    SetNode *s = NULL;
    int edgeCount = 0;
    int vertexCount = 0;
    int length_of_t;
    string fileName = "graph.txt";
    
    Initialization(q, edgeCount, s, vertexCount, fileName);
    // size of q is edgeCount
    cout<< endl<< "Show binary heap structure"<< endl;
    ShowBinaryHeapStructure(q, edgeCount);
    cout<< endl<< "Show AVL tree structure in pair of (vertex, height)"<< endl;
    ShowAVLTreeStructure(s);
    cout<< "edgeCount: "<< edgeCount<< endl;
    cout<< "vertexCount: "<< vertexCount<< endl;
    Search (q, edgeCount, s, vertexCount, t, length_of_t);
    cout<< endl<< "Print out the edges in the minimum spanning tree"<< endl;
    Tree (t, length_of_t);
    return 0;
}
