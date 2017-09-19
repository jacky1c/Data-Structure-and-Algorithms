//
//  KruskalsMST.cpp
//  CS340A3Q1
//
//  Created by Jacky on 2017-03-03.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include <stdio.h>
#include "KruskalsMST.h"


void Initialization (Edge q[], int& edgeCount, SetNode*& s, int& vertexCount, string fileName){
    Object x, y, z;
    ifstream input;
    bool result;
    SetNode* v;
    
    input.open(fileName);
    if (input.is_open()){
        input>> x;
        while(!input.eof()){
            input>> y;
            input>> z;
            // insert the edge with vertices x and y as endpoints into the priority queue
            Insert(x, y, z, q, edgeCount);
            // insert vertex x into the AVL tree
            result = Insert(x, s, vertexCount);
            if(result){
                //cout<< "s->vertex: "<< s->vertex<< ", height: "<< s->height<< endl; // TEST
                v = Find(x, s);
                //cout<< "v->vertex: "<< v->vertex<< ", height: "<< v->height<< endl; // TEST
                MakeSet(v);
            }
            // insert vertex y into AVL tree
            // cout<< "s->vertex: "<< s->vertex<< ", height: "<<s->height<< endl; // TEST
            result = Insert(y, s, vertexCount);
            if(result){
                //cout<< "s->vertex: "<< s->vertex<< ", height: "<< s->height<< endl; // TEST
                v = Find(y, s);
                //cout<< "v->vertex: "<< v->vertex<< ", height: "<< v->height<< endl; // TEST
                MakeSet(v);
            }
            input>> x;
        }
        
        input.close();
    }
    else{
        cout<< "Unable to open file: "<< fileName<< endl;
    }
    
    return;
}

// called by Initialization
// insert the edge with vertices x and y as endpoints into the priority queue
void Insert (Object x, Object y, Object z, Edge q[], int& edgeCount){
    Edge e;
    int i;
    
    e.vertex1 = x;
    e.vertex2 = y;
    e.distance = z;
    // increment number of edges in tree
    edgeCount++;
    // determine where e should be placed in the priority queue
    i = edgeCount;
    // percolate up
    while(i>1 && e.distance<q[i/2].distance){
        q[i] = q[i/2];
        i = i/2;
    }
    q[i] = e;
}

// called by Initialization
// insert vertex x into the AVL tree
bool Insert (Object w, SetNode*& s, int& vertexCount){
    bool result;
    if(s == NULL){
        // insert new leaf node here
        try{
            s = new SetNode;
        }
        catch(bad_alloc){
            cout<< "Bad Alloc Exception"<< endl;
            return false;
        }
        s->vertex = w;
        s->left = NULL;
        s->subset = NULL;
        s->right = NULL;
        s->height = 0;
        vertexCount++;
        result = true;
    }
    else if(w < s->vertex){
        // traverse to left subtree
        result = Insert(w, s->left, vertexCount);
        if(result){
            if(Height(s->left) - Height(s->right) == 2){
                if(w < s->left->vertex)
                    LL(s);
                else
                    LR(s);
            }
        }
    }
    else if (w > s->vertex){
        // traverse to right subtree
        result = Insert(w, s->right, vertexCount);
        if(result){
            if(Height(s->right) - Height(s->left) == 2){
                if(w > s->right->vertex)
                    RR(s);
                else
                    RL(s);
            }
        }
    }
    else
        // duplicates are not allowed
        result = false;
    if(result){
        s->height = Height(s->left) > Height(s->right) ? Height(s->left)+1 : Height(s->right)+1;
        //cout<< "Height: "<< s->height<< endl; // TEST
    }
    return result;
}

///////////////// Height, LL, LR, RL, RR are used in Insert AVL tree
int Height (SetNode* p){
    if (p == NULL)
        return -1;
    else
        return (Height(p->left) > Height(p->right)) ? Height(p->left)+1 : Height(p->right)+1;
}
void LL(SetNode*& p){
    SetNode *q = p->left;
    p -> left = q -> right;
    q -> right = p;
    p -> height = ((Height(p->left) > Height(p->right)) ? Height(p->left)+1 : Height(p->right)+1);
    q -> height = ((Height(p->left) > Height(p->right)) ? Height(p->left)+1 : Height(p->right)+1);
    p = q;
}
void LR(SetNode*& p){
    RR(p->left);
    LL(p);
}
void RL(SetNode*& p){
    LL(p->right);
    RR(p);
}
void RR(SetNode*& p){
    SetNode *q = p->right;
    p -> right = q -> left;
    q -> left = p;
    p -> height = ((Height(p->left) > Height(p->right)) ? Height(p->left)+1 : Height(p->right)+1);
    q -> height = ((Height(p->left) > Height(p->right)) ? Height(p->left)+1 : Height(p->right)+1);
    p = q;
}
////////////////// End of the definitions of Height, LL, LR, RL, RR (used in Insert AVL tree)

// called by Initialization
SetNode* Find (Object x, SetNode *s){
    SetNode *result = s;
    if(x < result->vertex){
        if(s->left != NULL){
            result = s->left;
            result = Find(x, result);
        }
        else
            result = NULL;
    }
    else if(x > result->vertex){
        if(s->right != NULL){
            result = s->right;
            result = Find(x, result);
        }
        else
            result = NULL;
    }

    return result;
}

// called by Initialization
void MakeSet (SetNode*& v){
    try{
        v->subset = new SubsetNode;
        v->subset->size = 1;
        try{
            v->subset->firstVertex = new VertexNode;
            v->subset->firstVertex->vertex = v->vertex;
            v->subset->firstVertex->next = NULL;
        }
        catch (bad_alloc){
            cout<< "Bad Alloc Exception when create new VertexNode in MakeSet function"<< endl;
            return;
        }
    }
    catch (bad_alloc){
        cout<< "Bad Alloc Exception when create new SubsetNode in Makeset function"<< endl;
        return;
    }
    
    return;
}

void Search (Edge q[], int edgeCount, SetNode*& s, int vertexCount, Edge t[], int& length_of_t) {
    Edge e;
    SetNode *v1, *v2;
    length_of_t = 0;
    // build the minimum spanning tree
    
    while ( length_of_t < vertexCount-1){
        // e is the shortest edge in the priority queue
        e = DeleteMin(q, edgeCount);
        // v1 is a pointer to the node in the avl tree containing vertex1
        v1 = Find(e.vertex1, s);
        // v2 is a pointer to the node in the avl tree containing vertex2
        v2 = Find(e.vertex2, s);
        if(v1->subset != v2->subset){
            // e is added to the edges in the minimum spanning tree
            // InsertUnsorted (e);
            t[length_of_t] = e;
            length_of_t++;
            // merge the two subsets in the AVL tree
            // always move the smaller subset to the larger subset
            if(v1->subset->size >= v2->subset->size)
                Union(v1, v2, s);
            else
                Union(v2, v1, s);
        }
    }
}

// called by Search
Edge DeleteMin (Edge q[], int& edgeCount){
    // root of q is the edge with the shortest distance
    Edge e, temp;
    int i, child;
    
    e = q[1];
    // move the last edge in the tree to the root
    q[1] = q[edgeCount];
    edgeCount--;
    // percolate down
    temp = q[1];
    i = 1;
    while (i*2 <= edgeCount){
        child = i*2;
        if(child != edgeCount && q[child+1].distance < q[child].distance)
            child++;
        if (q[child].distance < temp.distance)
            q[i] = q[child];
        else
            break;
        i = child;
    }
    q[i] = temp;
    return e;
}

// called by Search
void Union (SetNode*& vTo, SetNode*& vFrom, SetNode*& s){
    VertexNode *v;
    vTo->subset->size = vTo->subset->size + vFrom->subset->size;
    v = vTo->subset->firstVertex;
    while(v->next != NULL)
        v = v->next;
    v->next = vFrom->subset->firstVertex;
    delete vFrom->subset;
    v = v->next;
    while(v!=NULL){
        vFrom = Find(v->vertex, s);
        vFrom->subset = vTo->subset;
        v = v->next;
    }
}

void Tree (Edge t[], int length_of_t){
    for(int i = 0; i <= length_of_t-1; i++){
        cout<< t[i].vertex1<< " -- "<< t[i].vertex2<< " (Length= "<< t[i].distance<< ")"<< endl;
    }
}


void ShowBinaryHeapStructure(Edge e[], int edgeCount){
    for(int i=1; i<=edgeCount; i++){
        cout<< e[i].vertex1<< "-"<< e[i].vertex2<< " distance: "<< e[i].distance<< endl;
    }
}

void ShowHelper(SetNode*, int);
void ShowAVLTreeStructure(SetNode* s) {
    if ( s == NULL )
        cout << "Empty tree" << endl;
    else{
        cout << endl;
        ShowHelper(s,1);
        cout << endl;
    }
}
void ShowHelper(SetNode *p, int level){
    int j;   // Loop counter
    if ( p != 0 ){
        ShowHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->vertex<< ","<< p->height;   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
            ( p->right != 0 ) )
            cout << "<";
        else if ( p->right != 0 )
            cout << "/";
        else if ( p->left != 0 )
            cout << "\\";
        cout << endl;
        ShowHelper(p->left,level+1);          // Output left subtree
    }
}
