//
//  main.cpp
//
//  Created by Jacky on 2017-03-06.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "EdmondsCarpMaxFlow.h"

int main() {
    int r[ARRAY_SIZE][ARRAY_SIZE];
    int n = 8; // number of vertices
    int source = 1;
    int sink = 8;
    int maxFlow;
    string fileName = "input.txt";
    
    Initialization(r, n, fileName);
    cout<< "Print out the r array(print empty space if element is -1)"<< endl;
    cout<< "After Initialization phase"<< endl<< endl;
    ShowStructure(r, n);
    cout<< "In Search phase"<< endl;
    maxFlow = Search(r, n, source, sink); // there is an infinite loop
    cout<< "Print the paths and capacities when the max flow has been determined:"<< endl;
    Paths(r, n, source, sink, maxFlow);
    return 0;
}
