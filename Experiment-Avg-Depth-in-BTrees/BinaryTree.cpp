//
//  BinaryTree.cpp
//
//  Created by Jacky on 2017-01-17.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "BinaryTree.h"

struct BTNode{
    int info;
    BTNode* left;
    BTNode* right;
};

/******************
 Function: BTree()
 Purpose: Default constructor
 ******************/
BTree::BTree(){
    root = NULL;
    totalDepth = 0;
    totalNodes = 0;
}

/******************
 Function: ~BTree()
 Purpose: Destructor that frees all the dynamic allocated spaces
 ******************/
/******************
 Function: clearHelper(BTNode*& tree)
 Purpose: This is a recursive function. Use post traversal to clear all nodes in a tree
 Algorithm:
 Base case: If tree points to NULL, we are done.
 General case: Call clearHelper to clear left subtree and right subtree. Delete current node.
 ******************/
void clearHelper(BTNode*& tree);
BTree::~BTree(){
    clearHelper(root);
    root = NULL;
}
void clearHelper(BTNode*& tree){
    if (tree != NULL){
        clearHelper(tree->left);
        clearHelper(tree->right);
        delete tree;
    }
}

/******************
 Function: insert()
 Purpose: Insert 0 and 1 randomly into the tree with the equal possibilities
 Algorithm:
 1) Randomly generate 0 or 1. 0 for left and 1 for right.
 2) Call insertHelper(tree, direction, levelOfNewNode). insertHelper should modify levelOfNewNode.
 3) Add levelOfNewNode on totalDepth
 4) Increment totalNodes
 ******************/
/******************
 Function: insertHelper(BTNode*& tree, int direction, int& level)
 Purpose: Recursively call itself until a new node is inserted
 Algorithm:
 Base case: When tree points to NULL, insert a node. The new node contains the value of direction
 General case: When tree points to a node, we need to go down one level. Which subtree should be chosen depends on the direction, 0 for left and 1 for right subtree. Generate a new direction, increment level, and call insertHelper.
 ******************/
void insertHelper(BTNode*&, int, int&);
void BTree::insert(){
    int levelOfNewNode=0;
    int direction = rand()%2; // direction = 0 or 1
    insertHelper(root,direction,levelOfNewNode);
    totalDepth+=levelOfNewNode;
    totalNodes++;
}

void insertHelper(BTNode*& tree, int direction, int& level){
    if(tree == NULL){
        tree = new BTNode;
        tree->info = direction;
        tree->left = NULL;
        tree->right = NULL;
    }
    else{
        if (direction == 0){ // go to left subtree
            direction = rand()%2;
            level++;
            insertHelper(tree->left, direction, level);
        }
        else{ // go to right subtree
            direction = rand()%2;
            level++;
            insertHelper(tree->right, direction, level);
        }
    }
}

/******************
 Function: getTotalDepth() const
 Purpose: getter for totalDepth
 ******************/
int BTree::getTotalDepth() const{
    return totalDepth;
}

/******************
 Function: getTotalDepth() const
 Purpose: getter for totalNodes
 ******************/
int BTree::getTotalNodes() const{
    return totalNodes;
}



/***************************************************************************************
 * Works Cited
 *    Title: showStructure and showHelper functions source code
 *    Authors: Brandle, Geisler, Roberge and Whittington
 *    Date: 2009
 *    Availability: http://www.cs.uregina.ca/links/class-info/210/ftp/BinaryTree/Binary_Tree.zip
 *    Comment: the show structure functions are from CS210 lab
 ***************************************************************************************/
/******************
 Function: showStructure() const
 // Outputs the keys in a binary search tree. The tree is output
 // rotated counterclockwise 90 degrees from its conventional
 // orientation using a "reverse" inorder traversal. This operation is
 // intended for testing and debugging purposes only.
 ******************/
/******************
 Function: showHelper (BTNode *p, int level)
 // Recursive helper for showStructure.
 // Outputs the subtree whose root node is pointed to by p.
 // Parameter level is the level of this node within the tree.
 ******************/
void showHelper(BTNode*, int);
void BTree::showStructure() const{
    if ( root == 0 )
        cout << "Empty tree" << endl;
    else{
        cout << endl;
        showHelper(root,1);
        cout << endl;
    }
}
void showHelper(BTNode *p, int level){
    int j;   // Loop counter
    if ( p != 0 ){
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->info;   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
            ( p->right != 0 ) )
            cout << "<";
        else if ( p->right != 0 )
            cout << "/";
        else if ( p->left != 0 )
            cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}


