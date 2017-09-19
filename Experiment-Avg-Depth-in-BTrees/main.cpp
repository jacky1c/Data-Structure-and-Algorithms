//
//  main.cpp
//
//  Created by Jacky on 2017-01-17.
//  Copyright © 2017 Jacky. All rights reserved.
//
//
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
using namespace std;

int main(){
    srand (1); // set the seed of random numbers
    // The following 3 variables are repeatedly used by BTree, BSTree, and AVLTree.
    // For n = 8, 64, 512, and 4096 nodes, generate 16, 128, 1024, and 8192 trees.
    // So numOfNodes would be 8 and multiply by 8 each time in the for-loop.
    // numOfTrees would always be 2 times of numOfNodes.
    // For each n I want to always get 16 dots in print progress. So printFrequency would be numOfNodes/8.
    
    cout<< "==================Binary Search Tree=================="<< endl;
    // Create a tree as a demo and do not count its depth into binaryTreeTotalDepth
    cout<< "Randomly generate a binary tree with 8 nodes and print it out in order to show my program works:"<< endl;
    BSTree tree;
    for(int i=0; i<4096; i++){
        tree.insert();
    }
    //tree.showStructure();
    cout<< "Total number of nodes is: "<< tree.getTotalNodes()<< endl;
    
    cout<< "Total depth is: "<< tree.getTotalDepth()<< endl;
    cout<< "Total depth(test) is: "<< tree.getTotalDepth2()<< endl;
    tree.~BSTree();
    
    return 0;
}
