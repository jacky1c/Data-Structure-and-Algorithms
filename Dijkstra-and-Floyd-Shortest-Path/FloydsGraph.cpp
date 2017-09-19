//
//  FloydsGraph.cpp
//
//  Created by Jacky on 2017-02-09.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "FloydsGraph.h"

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
