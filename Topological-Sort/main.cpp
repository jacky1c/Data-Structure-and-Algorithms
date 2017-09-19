//
//  main.cpp
//
//  Created by Jacky on 2017-02-01.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "TopoSortGraph.h"



int main() {
    string inputFile = "input copy.txt";
    TopoSortGraph graph;
    int vertexCount = 0;
    Leader *head, *tail; // pointers pointing to the head and the tail of the graph
    head = graph.getHead();
    tail = graph.getTail();
    try{
        Initialization(head, tail, vertexCount, inputFile);
    }
    catch(string badFileName){// when input file doesn't exist program will warn user and then stop
        cout<< "WARNING: UNABLE TO FIND "<< badFileName<< endl;
        cout<< "Program stops..."<< endl;
        return 0;
    }
    
    // ShowGraphStructure(head, tail, vertexCount);
    cout<< "Find Start Vertex..."<< endl<< endl;
    FindStartVertex(head, tail);
    // ShowGraphStructure(head, tail, vertexCount);
    cout<< "Partial order:"<< endl;
    PartialOrder(head, tail, vertexCount);
    return 0;
}

// To do:
// define TopoSort as template class. Change element type to ItemType
// destructor
