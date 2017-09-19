//
//  AVLTree.cpp
//
//  Created by Jacky on 2017-01-20.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "AVLTree.h"

struct AVLTNode{
    int info;
    AVLTNode* left;
    AVLTNode* right;
    int height;
};

/******************
 Function: AVLTree()
 Purpose: Default constructor
 ******************/
AVLTree::AVLTree(){
    root = NULL;
    totalDepth = 0;
    totalNodes = 0;
}

/******************
 Function: ~AVLTree()
 Purpose: Destructor that frees all the dynamic allocated spaces
 ******************/
/******************
 Function: clearHelper(AVLTNode*& tree)
 Purpose: This is a recursive function. Use post traversal to clear all nodes in a tree
 Algorithm:
 Base case: If tree points to NULL, we are done.
 General case: Call clearHelper to clear left subtree and right subtree. Delete current node.
 ******************/
void clearHelper(AVLTNode*& tree);
AVLTree::~AVLTree(){
    clearHelper(root);
    root = NULL;
}
void clearHelper(AVLTNode*& tree){
    if (tree != NULL){
        clearHelper(tree->left);
        clearHelper(tree->right);
        delete tree;
    }
}

/******************
 Function: insert()
 Purpose: Insert a random number into the tree.
 Algorithm:
 1) Randomly generate a number and assign it to data.
 2) Call insertHelper(root, data)
 3) If a new node can be inserted to the tree, increment totalNodes
    Otherwise, call insert again.
 ******************/
/******************
 Function: insertHelper(BTNode*& tree, int data)
 Purpose: Recursively call itself until a new node is inserted
 Algorithm:
 Base case: if tree points to NULL, insert a new node
 General case: 
    When tree points to a node, we need to go down one level. Which subtree should be chosen depends on the data.
    (1) If data is less than tree->info, we call insertHelper(tree->left, data). If a new node can be inserted, we balance the tree's left subtree and right subtree (when necessary).
    (2) if data is greater than tree->info, we call insertHelper(tree->right, data). If a new node can be inserted, we balance the tree's left subtree and right subtree (when necessary).
    (3) if data = tree->info, we call insert().
 
 ******************/
bool insertHelper(AVLTNode*&, int);
int getHeight(AVLTNode*&);
void LL(AVLTNode*&);
void LR(AVLTNode*&);
void RL(AVLTNode*&);
void RR(AVLTNode*&);
void AVLTree::insert(){
    int data = rand()%5000; // create a random number which is in the interval of [0,5000]
    // if [data] has not been inserted, we increment totalNodes and add levelOfNewNode to totalDepth
    if(insertHelper(root,data)){
        totalNodes++;
    }
    // if we happen to have a random number which is already in the tree, we call insert again
    else{
        insert();
    }
}
bool insertHelper(AVLTNode*& tree, int data){
    if(tree==NULL){
        tree = new AVLTNode;
        tree->info = data;
        tree->left = NULL;
        tree->right = NULL;
        tree->height =((getHeight(tree->left) > getHeight(tree->right)) ? getHeight(tree->left)+1 : getHeight(tree->right)+1);
        return true;
    }
    else{
        if (data < tree->info){ // go to left subtree
            if(insertHelper(tree->left, data)){
                // balance
                if(getHeight(tree->left) - getHeight(tree->right)==2){
                    if (data < tree->left->info)
                        LL(tree);
                    else
                        LR(tree);
                }
                tree->height =((getHeight(tree->left) > getHeight(tree->right)) ? getHeight(tree->left)+1 : getHeight(tree->right)+1);
                return true;
            }
            else
                return false;
        }
        else if (data > tree->info){ // go to right subtree
            if(insertHelper(tree->right, data)){
                // balance
                if(getHeight(tree->right) - getHeight(tree->left)==2){
                    if (data > tree->right->info)
                        RR(tree);
                    else
                        RL(tree);
                }
                tree->height =((getHeight(tree->left) > getHeight(tree->right)) ? getHeight(tree->left)+1 : getHeight(tree->right)+1);
                return true;
            }
            else
                return false;
        }
        else{ // data == tree->info. Call insert again
            return false;
        }
    }
}
int getHeight(AVLTNode*& tree){
    if(tree==NULL)
        return -1;
    else
        return tree->height;
}
void LL(AVLTNode*& p){
    AVLTNode *q = p->left;
    p -> left = q -> right;
    q -> right = p;
    p -> height = ((getHeight(p->left) > getHeight(p->right)) ? getHeight(p->left)+1 : getHeight(p->right)+1);
    q -> height = ((getHeight(p->left) > getHeight(p->right)) ? getHeight(p->left)+1 : getHeight(p->right)+1);
    p = q;
}
void LR(AVLTNode*& p){
    RR(p->left);
    LL(p);
}
void RL(AVLTNode*& p){
    LL(p->right);
    RR(p);
}
void RR(AVLTNode*& p){
    AVLTNode *q = p->right;
    p -> right = q -> left;
    q -> left = p;
    p -> height = ((getHeight(p->left) > getHeight(p->right)) ? getHeight(p->left)+1 : getHeight(p->right)+1);
    q -> height = ((getHeight(p->left) > getHeight(p->right)) ? getHeight(p->left)+1 : getHeight(p->right)+1);
    p = q;
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
void getDepthHelper(AVLTNode*&, int, int&);
int AVLTree::getTotalDepth(){
    totalDepth = 0;
    if(root == NULL)
        return totalDepth;
    else{
        getDepthHelper(root, 0, totalDepth);
        return totalDepth;
    }
}
void getDepthHelper(AVLTNode*& tree, int level, int& totalDepth){
    if(tree!=NULL){
        totalDepth += level;
        getDepthHelper(tree->left, level+1, totalDepth);
        getDepthHelper(tree->right, level+1, totalDepth);
    }
}
/******************
 Function: getTotalDepth() const
 Purpose: getter for totalNodes
 ******************/
int AVLTree::getTotalNodes() const{
    return totalNodes;
}



/***************************************************************************************
 * Works Cited
 *    Title: showStructure and showHelper functions source code
 *    Authors: Brandle, Geisler, Roberge and Whittington
 *    Date: 2009
 *    Availability: http://www.cs.uregina.ca/links/class-info/210/ftp/BinaryTree/Binary_Tree.zip
 *    Comment: I modified part of the show structure functions based on CS210 lab
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
void showHelper(AVLTNode*, int);
void AVLTree::showStructure() const{
    if ( root == 0 )
        cout << "Empty tree" << endl;
    else{
        cout << endl;
        showHelper(root,1);
        cout << endl;
    }
}
void showHelper(AVLTNode *p, int level){
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
