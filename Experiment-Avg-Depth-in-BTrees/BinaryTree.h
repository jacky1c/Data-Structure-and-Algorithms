//
//  BinaryTree.h
//
//  Created by Jacky on 2017-01-17.
//  Copyright © 2017 Jacky. All rights reserved.
//
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

#ifndef BinaryTree_h
#define BinaryTree_h
struct BTNode; // node of the tree
class BTree{
public:
    BTree(); // constructor
    ~BTree(); // destructor
    void insert();
    void showStructure() const;
    int getTotalDepth() const;
    int getTotalNodes() const;
private:
    BTNode* root; // root of the tree
    int totalDepth; // the sum of the level of all nodes in a tree
    int totalNodes; // the number of nodes in a tree
};
#endif /* BinaryTree_h */
