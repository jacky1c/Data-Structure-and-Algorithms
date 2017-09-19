//
//  DAC_ClosestPair.cpp
//  CS340A4Q1
//
//  Created by Jacky on 2017-03-15.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "spacePanic.h"

ClosePair* ClosestPair(Point pX[], int startIndex, int endIndex, int& numOfClosePair){
    ClosePair *clP = new ClosePair [endIndex-startIndex+1];
    ClosePair *clPL = new ClosePair [(endIndex-startIndex)/2];
    ClosePair *clPR = new ClosePair [(endIndex-startIndex)/2+1];
    ClosePair *clPB = new ClosePair [endIndex-startIndex+1];
    int numOfClosePairL=0;
    int numOfClosePairR=0;
    int numOfClosePairB=0;

    // if there are no more than 3 points, find the closest pair
    if(endIndex-startIndex+1<=3)
        clP = BruteForce(pX, startIndex, endIndex, numOfClosePair);
    // if there are more than 3 points, divide pX into half
    else{
        clPL = ClosestPair (pX, startIndex, (startIndex+endIndex)/2, numOfClosePairL);
        clPR = ClosestPair (pX, (startIndex+endIndex)/2+1, endIndex, numOfClosePairR);
        clP = Combine(clPL, numOfClosePairL, clPR, numOfClosePairR, numOfClosePair);
        clPB = CheckBoundaryPoints(pX, startIndex, endIndex, numOfClosePairB);
        clP = Combine(clP, numOfClosePair, clPB, numOfClosePairB, numOfClosePair);
    }
    return clP;
}

// called by ClosestPair
// Purpose: return the closest pair among no more than 3 points
ClosePair* BruteForce (Point pX[], int startIndex, int endIndex, int& numOfClosePair){
    float d = 0;
    ClosePair *clP = new ClosePair [endIndex-startIndex+1];
    
    // if there are at least 2 points
    if(endIndex-startIndex+1 >= 2){
        // if distance between first 2 points is 1.4, append this pair to clP array
        d = Distance(pX[startIndex], pX[startIndex+1]);
        if(d>1 && d<2){
            clP[numOfClosePair].dMin = d;
            clP[numOfClosePair].p1.x = pX[startIndex].x;
            clP[numOfClosePair].p1.y = pX[startIndex].y;
            clP[numOfClosePair].p2.x = pX[startIndex+1].x;
            clP[numOfClosePair].p2.y = pX[startIndex+1].y;
            numOfClosePair++;
        }
        // if there exists a third point
        if(endIndex-startIndex+1 == 3){
            // if distance between point 1 and 3 is 1.4, append this pair to clP array
            d = Distance(pX[startIndex], pX[endIndex]);
            if(d>1 && d<2){
                clP[numOfClosePair].dMin = d;
                clP[numOfClosePair].p1.x = pX[startIndex].x;
                clP[numOfClosePair].p1.y = pX[startIndex].y;
                clP[numOfClosePair].p2.x = pX[endIndex].x;
                clP[numOfClosePair].p2.y = pX[endIndex].y;
                numOfClosePair++;
            }
            // if distance between point 2 and 3 is 1.4, append this pair to clP array
            d = Distance(pX[startIndex+1], pX[endIndex]);
            if(d>1 && d<2){
                clP[numOfClosePair].dMin = d;
                clP[numOfClosePair].p1.x = pX[startIndex+1].x;
                clP[numOfClosePair].p1.y = pX[startIndex+1].y;
                clP[numOfClosePair].p2.x = pX[endIndex].x;
                clP[numOfClosePair].p2.y = pX[endIndex].y;
                numOfClosePair++;
            }
        }
    }
    else{
        // if there is only one point or there is no pair of points have distance 1.4, clP is HIGH_VALUE
        clP[0].dMin = HIGH_VALUE;
        clP[0].p1.x = HIGH_VALUE;
        clP[0].p1.y = HIGH_VALUE;
        clP[0].p2.x = HIGH_VALUE;
        clP[0].p2.y = HIGH_VALUE;
    }
    return clP;
}

// called by ClosestPair
// Purpose: return the closest pair between 2 pairs of points
ClosePair Min(ClosePair clPL, ClosePair clPR){
    ClosePair clP;
    if(clPL.dMin < clPR.dMin){
        clP.dMin = clPL.dMin;
        clP.p1.x = clPL.p1.x;
        clP.p1.y = clPL.p1.y;
        clP.p2.x = clPL.p2.x;
        clP.p2.y = clPL.p2.y;
    }
    else{
        clP.dMin = clPR.dMin;
        clP.p1.x = clPR.p1.x;
        clP.p1.y = clPR.p1.y;
        clP.p2.x = clPR.p2.x;
        clP.p2.y = clPR.p2.y;
    }
    return clP;
}

// called by ClosestPair
ClosePair* CheckBoundaryPoints(Point pX[], int startIndex, int endIndex, int& numOfClosePairB){
    ClosePair *clPB = new ClosePair[endIndex-startIndex+1];
    // x is the x-value of the boundary
    int x = pX[(startIndex+endIndex)/2].x;
    Point* pYC;
    pYC = new Point[endIndex-startIndex+1];
    int k = 0; // number of elements in pYC
    int m = 0;
    int j = 0; // use j to scan pYC
    float d;
    
    // for each point pX[i]
    for(int i=startIndex; i<=endIndex; i++){
        // put all points in pX whose x lies within |dMin| from the boundary line to pYC
        // pYC array sorted by y value
        if(pX[i].x >= x-1.4 && pX[i].x <= x+1.4){
            j = 0;
            while(j<k && (pX[i].y > pYC[j].y || (pX[i].y == pYC[j].y && pX[i].x > pYC[j].x) )){
                j++;
            }
            m = k;
            while(m>j){
                pYC[m].x = pYC[m-1].x;
                pYC[m].y = pYC[m-1].y;
                m--;
            }
            pYC[j].x = pX[i].x;
            pYC[j].y = pX[i].y;
            k++;
        }
    }
    for(int i=0; i<=k-2; i++){
        for(int j=i+1; j<=k-1; j++){
            if(abs(pYC[j].y-pYC[i].y) > 1){
                break;
            }
            d = Distance(pYC[i], pYC[j]);
            if(d>1 && d<2){ // add this pair to clP array
                clPB[numOfClosePairB].dMin = d;
                clPB[numOfClosePairB].p1.x = pYC[i].x;
                clPB[numOfClosePairB].p1.y = pYC[i].y;
                clPB[numOfClosePairB].p2.x = pYC[j].x;
                clPB[numOfClosePairB].p2.y = pYC[j].y;
                numOfClosePairB++;
            }
        }
    }
    delete[] pYC;
    return clPB;
}

// called by CheckBoundaryPoints and BruteForce
// Formula: sqrt( (y1-y0)^2 + (x1-x0)^2 )
float Distance(Point a, Point b){
    float out = sqrt( pow((b.y-a.y),2) + pow((b.x-a.x),2) );
    return out;
}

ClosePair* Combine(ClosePair* clPL, int numOfClosePairL, ClosePair* clPR, int numOfClosePairR, int& numOfClosePair){
    numOfClosePair = 0;
    ClosePair *out = new ClosePair[numOfClosePairL+numOfClosePairR];
    for(int i=0; i<numOfClosePairL; i++){
        out[numOfClosePair] = clPL[i];
        numOfClosePair++;
    }
    for(int i=0; i<numOfClosePairR; i++){
        out[numOfClosePair] = clPR[i];
        numOfClosePair++;
    }
    return out;
}
