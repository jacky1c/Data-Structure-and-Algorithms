//
//  BruteForce_ClosestPair.cpp
//  CS340A4Q1
//
//  Created by Jacky on 2017-03-17.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "spacePanic.h"

// Traverse the pX array to determine the close pairs. Load the close pairs into the clP array.
// A close pair is any pair of points where the distance between them is greater than one and less than two.
// we for each point P in pX array, scan all the points after it. If we find another point where the distance between it and point P is in interval (1,2), add this pair of points in clP
ClosePair* BF_ClosestPair(Point pX[], int startIndex, int endIndex, int& numOfClosePairs){
    ClosePair *clP = new ClosePair[endIndex-startIndex+1];
    int n=0; // clP index
    float distance = 0;
    for(int i=0; i<=endIndex-1; i++){ // scan each point P in pX from the first point to the second from last point
        for(int j=i+1; j<=endIndex; j++){ // scan all the points after point P
            distance = Distance(pX[i], pX[j]);
            if(distance>1 && distance<2){
                clP[n].dMin = distance;
                clP[n].p1 = pX[i];
                clP[n].p2 = pX[j];
                n++;
            }
        }
    }
    numOfClosePairs = n;
    return clP;
}
