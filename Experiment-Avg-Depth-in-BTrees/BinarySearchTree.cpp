//
//  BinarySearchTree.cpp
//
//  Created by Jacky on 2017-01-20.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "BinarySearchTree.h"


struct BSTNode{
    int info;
    BSTNode* left;
    BSTNode* right;
};

/******************
 Function: BSTree()
 Purpose: Default constructor
 ******************/
BSTree::BSTree(){
    root = NULL;
    totalDepth = 0;
    totalNodes = 0;
}

/******************
 Function: ~BSTree()
 Purpose: Destructor that frees all the dynamic allocated spaces
 ******************/
/******************
 Function: clearHelper(BSTNode*& tree)
 Purpose: This is a recursive function. Use post traversal to clear all nodes in a tree
 Algorithm:
 Base case: If tree points to NULL, we are done.
 General case: Call clearHelper to clear left subtree and right subtree. Delete current node.
 ******************/
void clearHelper(BSTNode*& tree);
BSTree::~BSTree(){
    clearHelper(root);
    root = NULL;
}
void clearHelper(BSTNode*& tree){
    if (tree != NULL){
        clearHelper(tree->left);
        clearHelper(tree->right);
        delete tree;
    }
}

/******************
 Function: insert()
 Purpose: Insert random number into the tree.
 Algorithm:
 1) Randomly generate a number.
 2) Call insertHelper(tree, data, levelOfNewNode). insertHelper should modify levelOfNewNode.
 3) If a new nodes can be inserted, add levelOfNewNode on totalDepth and increment totalNodes
    Otherwise, call insert again
 ******************/
/******************
 Function: insertHelper(BTNode*& tree, int data, int& level)
 Purpose: Recursively call itself until a new node is inserted
 Algorithm:
 Base case: When tree points to NULL, insert a node. The new node contains data
 General case: 
    When tree points to a node, we need to go down one level. Which subtree should be chosen depends on the data.
    (1) Increment level
    (2) If data is less than tree->info, we call insertHelper(tree->left, data, level);
        if data is greater than tree->info, we call insertHelper(tree->right, data, level);
        if data = tree->info, we call insert().
 ******************/
bool insertHelper(BSTNode*&, int, int&);
void BSTree::insert(){
    int levelOfNewNode=0;
    int data = rand()%5000; // create a random number which is in the interval of [0,5000]
    // if [data] is not in the tree, we increment totalNodes and add levelOfNewNode to totalDepth
    if(insertHelper(root,data,levelOfNewNode)){
        totalDepth+=levelOfNewNode;
        totalNodes++;
    }
    // if we happen to have a random number which is already in the tree, we call insert again
    else{
        insert();
    }
}
bool insertHelper(BSTNode*& tree, int data, int& level){
    if(tree == NULL){
        tree = new BSTNode;
        tree->info = data;
        tree->left = NULL;
        tree->right = NULL;
        return true;
    }
    else{
        if (data < tree->info){ // go to left subtree
            level++;
            return insertHelper(tree->left, data, level);
        }
        else if (data > tree->info){ // go to right subtree
            level++;
            return insertHelper(tree->right, data, level);
        }
        else{ // data == tree->info. Call insert again
            return false;
        }
    }
}

/******************
 Function: getTotalDepth() const
 Purpose: getter for totalDepth
 ******************/
int BSTree::getTotalDepth() const{
    return totalDepth;
}

/******************
 Function: getTotalDepth() const
 Purpose: getter for totalNodes
 ******************/
int BSTree::getTotalNodes() const{
    return totalNodes;
}

/******************
 Function: getTotalDepth()
 Purpose: getter for totalDepth
 Algorithm:
 
 ******************/
/******************
 Function: getDepth(AVLTNode*& tree, int level, int& totalDepth)
 Purpose: traverse the whole tree to get the sum of all nodes' level
 Parameters: [tree] points to a node in the tree; [level] is the level of current node; totalDepth is the accumulator
 Algorithm:
 Base case: if [tree] is NULL, we reach the bottom. Add [level] to [totalDepth]
 General case: if tree points to a node in the tree, add [level] to [totalDepth]. Call getDepthHelper(tree->left, level+1, totalDepth) and getDepthHelper(tree->left, level+1, totalDepth).
 ******************/
void getDepthHelper(BSTNode*&, int, int&);
int BSTree::getTotalDepth2(){
    totalDepth = 0;
    if(root == NULL)
        return totalDepth;
    else{
        getDepthHelper(root, 0, totalDepth);
        return totalDepth;
    }
}
void getDepthHelper(BSTNode*& tree, int level, int& totalDepth){
    if(tree!=NULL){
        totalDepth += level;
        getDepthHelper(tree->left, level+1, totalDepth);
        getDepthHelper(tree->right, level+1, totalDepth);
    }
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
void showHelper(BSTNode*, int);
void BSTree::showStructure() const{
    if ( root == 0 )
        cout << "Empty tree" << endl;
    else{
        cout << endl;
        showHelper(root,1);
        cout << endl;
    }
}
void showHelper(BSTNode *p, int level){
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

