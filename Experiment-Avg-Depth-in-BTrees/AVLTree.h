//
//  AVLTree.h
//
//  Created by Jacky on 2017-01-20.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

#ifndef AVLTree_h
#define AVLTree_h
struct AVLTNode; // node of the tree
class AVLTree{
public:
    AVLTree(); // constructor
    ~AVLTree(); // destructor
    void insert();
    void showStructure() const;
    int getTotalDepth();
    int getTotalNodes() const;
private:
    AVLTNode* root; // root of the tree
    int totalDepth; // the sum of the level of all nodes in a tree
    int totalNodes; // the number of nodes in a tree
};

#endif /* AVLTree_h */
