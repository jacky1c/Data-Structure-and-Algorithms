//
//  EdmondsCarpMaxFlow.h
//
//  Created by Jacky on 2017-03-06.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int HIGH_VALUE = 200;
const int ARRAY_SIZE = 9; // ARRAY_SIZE should always be number of vertices+1

#ifndef EdmondsCarpMaxFlow_h
#define EdmondsCarpMaxFlow_h

void Initialization(int r[][ARRAY_SIZE], int n, string fileName);
int Search(int r[][ARRAY_SIZE], int n, int source, int sink);
bool BreadthFirstSearch(int r[][ARRAY_SIZE], int p[], int n, int source, int sink);
void Paths(int r[][ARRAY_SIZE], int n, int source, int sink, int maxFlow);
void ShowStructure(int r[][ARRAY_SIZE], int n);

#endif /* EdmondsCarpMaxFlow_h */
