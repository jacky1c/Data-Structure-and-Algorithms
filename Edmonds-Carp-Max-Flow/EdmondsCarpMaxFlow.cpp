//
//  EdmondsCarpMaxFlow.cpp
//
//  Created by Jacky on 2017-03-06.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "EdmondsCarpMaxFlow.h"

void Initialization(int r[][ARRAY_SIZE], int n, string fileName){
    ifstream input;
    int i, j, capacity;
    
    for(int i=0; i<=n; i++){
        for(int j=0; j<=n; j++){
            if(i==0 || j==0) // initializa all non usable elements to 0
                r[i][j] = -2;
            else // initialize all usable elements to -1
                r[i][j] = -1;
        }
    }
    // input
    input.open(fileName);
    if(input.is_open()){
        input>> i;
        while(!input.eof()){
            input>> j;
            input>> capacity;
            r[i][j] = capacity;
            r[j][i] = 0;
            input>> i;
        }
        input.close();
    }
    else{
        cout<< "Cannot open file: "<< fileName<< endl;
    }
    return;
}

int Search(int r[][ARRAY_SIZE], int n, int source, int sink){
    int maxFlow = 0;
    int pathFlow, i, j;
    int p[n+1];

    bool pathFound = BreadthFirstSearch(r, p, n, source, sink);
    while (pathFound){ // infinite loop here, pathFound always true
        pathFlow = HIGH_VALUE;
        j = sink;
        while(j != source){
            i = p[j];
            pathFlow = ((pathFlow < r[i][j]) ? pathFlow : r[i][j]);
            j = i;
        }
        j = sink;
        while(j != source){
            i = p[j];
            r[i][j] = r[i][j] - pathFlow;
            r[j][i] = r[j][i] + pathFlow;
            j = i;
        }
        maxFlow = maxFlow + pathFlow;
        pathFound = BreadthFirstSearch(r, p, n, source, sink);
        //cout<< "pathFound: "<< (pathFound? "True":"False")<< endl; // TEST
        cout<< endl;
        ShowStructure(r, n);
    }
    return maxFlow;
}

// called by search
bool BreadthFirstSearch(int r[][ARRAY_SIZE], int p[], int n, int source, int sink){
    bool v[n+1];
    int q[n+1];
    int head, tail, i;
    //cout<< "sink is: "<< sink; // TEST
    
    for (int i=1; i<=n; i++){
        v[i] = false;
    }
    head = 1;
    tail = 1;
    q[tail] = source;
    tail++;
    v[source] = true;
    while (head != tail){ // infinite loop here
        i = q[head];
        head++;
        for (int j=1; j<=n; j++){
            if (v[j] == false && r[i][j]>0){
                q[tail] = j;
                tail++;
                p[j] = i;
                v[j] = true;
            }
        }
    }
    ////// TEST
//    cout<< endl<< "Breadth First Search";
//    cout<< endl<< "Show p: "<< endl;
//    for(int i=1; i<=n; i++)
//        cout<< p[i]<< " ";
//    cout<< endl<< "Show v: "<< endl;
//    for(int i=1; i<=n; i++)
//        cout<< (v[i] ? "T":"F")<< " ";
//    cout<< endl<< "Show q: "<< endl;
//    for(int i=1; i<=n; i++)
//        cout<< q[i]<< " ";
//    cout<< endl;
    ///// END OF TEST
    
    return v[sink];
}

void Paths(int r[][ARRAY_SIZE], int n, int source, int sink, int maxFlow){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(r[i][j] != -1){
                cout<< i<< "-("<< r[i][j]<< ")-"<< j<< endl;
            }
        }
    }
    cout<< "MAXFLOW="<< maxFlow<< endl;
    return;
}

void ShowStructure(int r[][ARRAY_SIZE], int n){
    int width = 2;
    cout<< "  |";
    for (int i=1; i<=n; i++){
        cout<< right<< setw(width)<< setfill(' ')<< i;
    }
    cout<< endl;
    for (int i=0; i<=n*width+4; i++){
        cout<< '-';
    }
    cout<< endl;
    
    for (int i=1; i<ARRAY_SIZE; i++){
        cout<< i<< " |";
        for(int j=1;j<ARRAY_SIZE; j++){
            cout<<  right<< setw(width)<< setfill(' ');
            if(r[i][j]==-1)
                cout<< " ";
            else
                cout<< r[i][j];
        }
        cout<< endl;
    }
    cout<< endl;
}
