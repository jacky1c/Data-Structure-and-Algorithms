//
//  FloydsGraph.h
//
//  Created by Jacky on 2017-02-09.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include"DijkstrasGraph.h"

#ifndef FloydsGraph_h
#define FloydsGraph_h

void Initialization (int d[][NO_OF_VERTICES], int v[][NO_OF_VERTICES], int n, string fileName);
void Search (int d[][NO_OF_VERTICES], int v[][NO_OF_VERTICES], int n);
void Paths (int d[][NO_OF_VERTICES], int v[][NO_OF_VERTICES], int i, int j);


#endif /* FloydsGraph_h */
