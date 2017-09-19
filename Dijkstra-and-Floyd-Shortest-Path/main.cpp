//
//  main.cpp
//
//  Created by Jacky on 2017-02-05.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "DijkstrasGraph.h"
//#include "FloydsGraph.h"
int main() {
    string fileName = "input.txt";

    /***** Dijkstra ******/
//    int startVertex = 1;
//    Leader a [NO_OF_VERTICES];
//    Initialization(a, fileName);
//    ShowStructure(a);
//    Search(a, startVertex);
//    // ShowStructure(a);
//    Paths(a);
    
    /***** Floyd ******/
    int d[NO_OF_VERTICES][NO_OF_VERTICES];
    int v[NO_OF_VERTICES][NO_OF_VERTICES];
    int n = NO_OF_VERTICES;
    Initialization(d, v, n, fileName);
    Search(d, v, n);
    for(int i=1; i<NO_OF_VERTICES; i++)
        for(int j=1;j<NO_OF_VERTICES; j++)
            if((i!=j) && d[i][j]!=HIGH_VALUE)
                Paths(d, v, i, j);
    
    return 0;
}
