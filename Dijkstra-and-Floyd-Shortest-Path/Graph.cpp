//
//  DijkstrasGraph.cpp
//
//  Created by Jacky on 2017-02-05.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "Graph.h"


//struct Follower{
//    ItemType vertex;
//    int distance;
//    Follower *nextFollower;
//};
//struct Leader{
//    ItemType vertex;
//    bool known;
//    int distance;
//    Follower *firstFollower;
//};

/******************
 Function: Initialization(Leader a[], string fileName)
 Purpose: Initialize the array of leader nodes and build linked lists of follower nodes
 Input: An array of leader nodes a[]. Input file name
 Algorithm: 
 (1) Create an array of leader nodes and initializa all nodes to default value:
        vertex = 0
        distance = HIGH_VALUE
        firstFollower = NULL
 (2) Read data from input file and build linked lists of follower nodes. Each linked list is pointed by firstFollower node of leader node
 ******************/
void Initialization(Leader a[], string fileName){
    ItemType x, y, z;
    Follower *p;
    ifstream input;
    input.open(fileName);

    if(input.is_open()){
        // initialize the array of leader nodes
        for(int i=1; i<NO_OF_VERTICES; i++){
            a[i].vertex = 0;
            a[i].known = false;
            a[i].distance = HIGH_VALUE;
            a[i].firstFollower = NULL;
        }
        // read data from input file and build linked lists of follower nodes
        input>> x;
        while (!input.eof()){
            input>> y;
            input>> z;
            p = new Follower;
            p->vertex = y;
            p->distance = z;
            p->nextFollower = a[x].firstFollower;
            a[x].firstFollower = p;
            input>> x;
        }
    }
    else // Exception handling
        throw fileName;
    return;
}

/******************
 Function: FindNextVertex(Leader a[])
 Purpose:
 Input:
 Output:
 Algorithm:
 ******************/
ItemType FindNextVertex(Leader a[]){
    ItemType nextVertex = NO_VERTEX_FOUND;
    int shortestDistance = HIGH_VALUE;
    for(int i=1; i<NO_OF_VERTICES; i++){
        if ((a[i].distance < shortestDistance) && (a[i].known == false)){
            nextVertex = i;
            shortestDistance = a[i].distance;
        }
    }
    return nextVertex;
}


/******************
 Function:
 Purpose:
 Input:
 Output:
 Algorithm:
 ******************/
void Search(Leader a[], ItemType startVertex){
    int i;
    Follower *p;
    // set the start vertex
    a[startVertex].vertex = startVertex;
    a[startVertex].distance = 0;

    // determine the shortest path from the start vertex
    // to every other vertex
    while(true){
        i = FindNextVertex(a);
        if(i == NO_VERTEX_FOUND)
            break;
        a[i].known = true;
        p = a[i].firstFollower;
        while(p!=NULL){
            if (a[p->vertex].known == false){
                if ((a[i].distance + p->distance) < (a[p->vertex].distance)){
                    a[p->vertex].distance = a[i].distance + p->distance;
                    a[p->vertex].vertex = i;
                }
            }
            p = p->nextFollower;
        }
    }
    return;
}

/******************
 Function:
 Purpose:
 Input:
 Output:
 Algorithm:
 ******************/
void Paths(Leader a[]){
    for(int i=1; i<NO_OF_VERTICES; i++){
        if(a[i].known == true){
            int j = i;
            while(j!=a[j].vertex){
                cout<< j<< "<- ";
                j = a[j].vertex;
            }
            cout<< j<< endl;
        }
    }
    return;
}

/******************
 Function:
 Purpose:
 Input:
 Output:
 Algorithm:
 ******************/
void ShowStructure(Leader a[]){
    for(int i=1; i<NO_OF_VERTICES; i++){
        cout<< "Node "<< i<< endl;
        cout<< a[i].vertex<< endl;
        if(a[i].known)
            cout<< "Known"<< endl;
        else
            cout<< "Unknown"<< endl;
        cout<< "Distance: "<< a[i].distance<< endl;
        cout<< "Followers: "<< endl;
        Follower *f;
        f = a[i].firstFollower;
        if(f == NULL)
            cout<< "No follower"<< endl;
        while(f!=NULL){
            cout<< f->vertex<< " "<< f->distance<<endl;
            f = f->nextFollower;
        }
        cout<< endl;
    }
    cout<< endl<< endl;
}


//////////////////////////////////////////////////////////
/******************
 Function:
 Purpose:
 Input:
 Output:
 Algorithm:
 ******************/
void Initialization (int d[][NO_OF_VERTICES], int v[][NO_OF_VERTICES], int n, string fileName){
    ifstream input;
    input.open(fileName);
    
    if(input.is_open()){
        for(int i=1; i<n; i++){
            for(int j=1; j<n; j++){
                d[i][j] = HIGH_VALUE;
                v[i][j] = i;
                if(i==j)
                    d[i][j] = 0;
            }
        }
        // input
        int i, j, distance;
        input>> i;
        while(!input.eof()){
            input>> j;
            input>> distance;
            if(distance< d[i][j])
                d[i][j] = distance;
            input>> i;
        }
    }
    else // Exception handling
        throw fileName;
    return;
}


/******************
 Function:
 Purpose:
 Input:
 Output:
 Algorithm:
 ******************/
void Search (int d[][NO_OF_VERTICES], int v[][NO_OF_VERTICES], int n){
    for (int k=1; k<n; k++){
        for (int i=1; i<n; i++){
            if((i==k) || (d[i][k] == HIGH_VALUE))
                continue;
            else{
                for(int j=1; j<n; j++){
                    if((i==j) || (j==k) || (d[k][j]==HIGH_VALUE))
                        continue;
                    if(d[i][k]+d[k][j] < d[i][j]){
                        d[i][j] = d[i][k]+d[k][j];
                        v[i][j] = v[k][j];
                    }
                }
            }
        }
    }
    return;
}


/******************
 Function:
 Purpose:
 Input:
 Output:
 Algorithm:
 ******************/
void Paths (int d[][NO_OF_VERTICES], int v[][NO_OF_VERTICES], int i, int j){
    int length = d[i][j];
    cout<< j;
    while(i!=v[i][j]){
        cout<< "<-"<< v[i][j];
        j = v[i][j];
    }
    cout<< "<-"<< i<< "(Length="<< length<< ")"<< endl;
    return;
}





