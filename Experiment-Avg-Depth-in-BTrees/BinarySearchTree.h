//
//  BinarySearchTree.h
//
//  Created by Jacky on 2017-01-20.
//  Copyright © 2017 Jacky. All rights reserved.
//


#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

#ifndef BinarySearchTree_h
#define BinarySearchTree_h
struct BSTNode; // node of the tree
class BSTree{
public:
    BSTree(); // constructor
    ~BSTree(); // destructor
    void insert();
    void showStructure() const;
    int getTotalDepth() const;
    int getTotalNodes() const;
    
    int getTotalDepth2(); // tets use
private:
    BSTNode* root; // root of the tree
    int totalDepth; // the sum of the level of all nodes in a tree
    int totalNodes; // the number of nodes in a tree
};
#endif /* BinarySearchTree_h */
