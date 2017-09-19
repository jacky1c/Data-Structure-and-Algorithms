//
//  TopoSort.cpp
//
//  Created by Jacky on 2017-02-01.
//  Copyright © 2017 Jacky. All rights reserved.
//
#include "TopoSortGraph.h"

/******************
 Function: TopoSortGraph()
 Purpose: default constructor
 ******************/
TopoSortGraph::TopoSortGraph(){
    head = NULL;
    tail = NULL;
    vertexCount = 0;
}

/******************
 Function: ~TopoSortGraph()
 Purpose: destructor
 ******************/
TopoSortGraph::~TopoSortGraph(){
    // to do
}

/******************
 Function: getHead()
 Purpose: return head
 ******************/
Leader* TopoSortGraph::getHead(){
    return head;
}

/******************
 Function: getTail()
 Purpose: return tail
 ******************/
Leader* TopoSortGraph::getTail(){
    return tail;
}

/******************
 Function: getVertexCount()
 Purpose: return vertexCount
 ******************/
int TopoSortGraph::getVertexCount(){
    return vertexCount;
}

/******************
 Function: BuildList (ItemType w, Leader*& head, Leader*& tail, int& vertexCount)
 Purpose: Build leader node linked list (called by initialization function)
 Input: Vertex data [w]. Leader node pointer [head] and [tail]. Vertex counter [vertexCount]
 Output: Return the pointer pointing to the node which contains vertex [w]. Update head, tail, and vertexCount
 Algorithm:
 (1) Assign [w] to tail's vertex
 (2) [h] scanns the leader node linked list from left to right and points to the left most node which contains vertex [w]
 (3) If [h] stops before tail, that means [w] is already in the list. Go to step4
     Otherwise, the node containing [w] is a new node.
        (3.1) tail points to a new leader node
        (3.2) increment vertexCount
        (3.3) initialize the inDegree of [h] to 0; firstFollower of [h] to NULL; and nextLeader of [h] to tail
 (4) Return pointer [h] and end of the function
 ******************/
Leader* BuildList (ItemType w, Leader*& head, Leader*& tail, int& vertexCount){
    Leader *h = head;
    tail->vertex = w;
    while (h->vertex!=w){
        h = h->nextLeader;
    }
    if(h == tail){
        tail = new Leader;
        vertexCount++;
        h->inDegree = 0;
        h->firstFollower = NULL;
        h->nextLeader = tail;
    }
    return h;
}

/******************
 Function: Initialization(Leader*& head, Leader*& tail, int& vertexCount, string fileName)
 Purpose: Build a linked list of leader nodes. Build the connection between each leader node and its follower nodes as linked lists. The order of the leader nodes in linked list is the same order of input data but each data only appears once in the linked list. The order of follower nodes in linked list is the inverse order of the input data.
 Input: Leader node pointer [head] and [tail]. Vertex counter [vertexCount]. Input file name [fileName]
 Output: head should point to the first leader node of the linked list. tail should point to the last leader node which is an empty leader node
 Algorithm:
 (1) Initializa head and tail pointing to the same empty leader node
 (2) Read in [x] (x is the leader of y, in the graph: x->y)
 (3) As long as [x] doesn't reach the end of the file
    (3.1) Read in [y]
    (3.2) Call BuildList function to build leader nodes which contain [x] and [y]. Leader node pointer p points to the node which contains [x] and q points to the leader node which contains [y]
    (3.3) Build follower node of [x] node. One of the follower nodes points to [y] node and increment the inDegree of [y] node
    (3.4) Read a new [x] and go to step3
 (4) End of function
 ******************/
void Initialization (Leader*& head, Leader*& tail, int& vertexCount, string fileName){
    ifstream input;
    input.open(fileName);
    if(input.is_open()){
        ItemType x, y;
        // *p points to the input leader vertex, *q points to the input follower vertex
        // i.e. in the graph, p->q
        Leader *p, *q;
        Follower *f;
        
        head = new Leader;
        tail = head;
        // input
        input >> x;
        while(!input.eof()){
            input >> y;
            p = BuildList(x, head, tail, vertexCount);
            q = BuildList(y, head, tail, vertexCount);
            f = new Follower;
            f->adjacentLeader = q;
            f->nextFollower = p->firstFollower;
            p->firstFollower = f;
            q->inDegree ++;
            input >> x;
        }
        input.close();
    }
    else // Exception handling
        throw fileName;
    return;
}

/******************
 Function: FindStartVertex (Leader*& head, Leader*& tail)
 Output: head and tail will point to the start node(s).
    If there is only one start node, they will point to the same node. nextLeader of that node would be NULL
    If there are more than one start nodes, tail will point to the left most start node (whose nextLeader would be NULL) in the leader node list and head will point to the right most start node in the list.
 
 Purpose:
 Algorithm:
 (1) Initialize leader node [p] and [r] to point to head and tail. Make head and tail point to NULL. Note: [r] points to an empty node
 (2) Use [p] to scann all the leader node in linked list. As long as [p] doesn't point the the empty node, do the following
    (2.1) [q] points to [p] and move [p] to next node
    (2.2) If [q] points to a start node (i.e. inDegree equals to 0)
        (2.2.1) nextLeader of [q] points to head and head points to [q]
        (2.2.2) If at this time tail still points to NULL, make tail points to [q] as well
 (3) End of function
 ******************/
void FindStartVertex (Leader*& head, Leader*& tail){
    Leader *p, *r, *q;
    p = head;
    head = NULL;
    r = tail;
    tail = NULL;
    while(p != r){
        q = p;
        p = p->nextLeader;
        if(q->inDegree == 0){
            q->nextLeader = head;
            head = q;
            if(tail == NULL){
                tail = q;
            }
        }
    }
    return;
}

/******************
 Function: PartialOrder (Leader* head, Leader* tail, int vertexCount)
 Purpose: Order all the vertices
 Input: head and tail should always point to the head and tail of the list with all nodes of inDegree 0
 Output: Sort all leader nodes and print their vertex in order
    Note: after running this function, tail will point to the node containing the last vertex and head will point to NULL. [nextLeader] in each leader node will point to next leader node in order and [nextLeader] in the last leader node will point to NULL. [inDegree] in all leader node will be 0.
 Algorithm:
 (1) As long as head doesn't point to NULL, do the following
    (1.1) Use leaderScanner to scan the list where all nodes have inDegree 0. Use nodesCounter to count the number of nodes that could be printed concurrently and print them in the same line
    (1.2) Call UpdateFollower function [nodesCounter] times to update all the followers of the nodes that have been printed
    (1.3) Set nodesCounter back to 0 for the next loop
    (1.4) Start a new line and go to step1. Now head should point to a new node in next depth with inDegree 0
 (2) End of function
 ******************/
void PartialOrder (Leader* head, Leader* tail, int vertexCount){
    Leader *leaderScanner;
    int nodesCounter = 0;

    while (head!=NULL){
        leaderScanner = head;
        while(leaderScanner!=NULL){
            if(leaderScanner->inDegree == 0){
                nodesCounter++;
                cout<< leaderScanner->vertex<< " ";
            }
            leaderScanner = leaderScanner->nextLeader;
        }
        
        for(int i=0; i<nodesCounter; i++)
            UpdateFollower(head, tail);
        
        nodesCounter = 0;
        cout<< endl;
    }
}

/******************
 Function: UpdateFollower(Leader*& head, Leader*& tail)
 Input: head and tail should always point to the head and tail of the list with all nodes of inDegree 0
 Purpose: update all followers of head and move head to next leader node
 Algorithm:
 (1) Make [f] point to the first follower of head
 (2) Move head to next leader node
 (3) As long as [f] is not NULL, do the following
    (3.1) [p] points to the leader node that [f] is pointed to. Decrement the inDegree of [p] node
    (3.2) If [p] node inDegree is 0, add [p] node to the end of the list where all nodes have inDegree 0
        If at this time head points to NULL, make head point to tail;
    (3.3) Move [f] to its next follower, go to step3
 (4) End of function
 ******************/
void UpdateFollower(Leader*& head, Leader*& tail){
    Follower *f;
    Leader *p;
    
    f = head->firstFollower;
    head = head->nextLeader;
    while(f != NULL){
        p = f->adjacentLeader;
        p->inDegree --;
        if(p->inDegree == 0){
            p->nextLeader = NULL;
            tail->nextLeader = p;
            tail = p;
            if(head == NULL)
                head = tail;
        }
        f = f->nextFollower;
    }
}

/******************
 Function: ShowGraphStructure(head, tail, vertexCount)
 Purpose: template
 Algorithm:
 template
 ******************/
void ShowGraphStructure (Leader* head, Leader* tail, int vertexCount){
    Follower *f;
    Leader *p;
    cout<< "Show graph structure:"<< endl;
    cout<< "VertexCount: "<< vertexCount<< endl ;
    cout << "Head: ";
    if(head == NULL)
        cout << "NULL"<< endl;
    else
        cout << head->vertex<< endl;
    cout << "Tail: ";
    if(tail == NULL)
        cout << "NULL"<< endl;
    else
        cout << tail->vertex<< endl;
    cout<< endl;
    while(head!=NULL){
        cout<< "Vertex "<< head->vertex<< endl;
        cout<< "inDegree: "<< head->inDegree<< endl;
        cout<< "nextLeader: ";
        if(head->nextLeader == NULL)
            cout<< "NULL"<< endl;
        else
            cout<< head->nextLeader->vertex<< endl;
        cout<< "followers: ";
        f = head->firstFollower;
        while(f!=NULL){
            p = f->adjacentLeader;
            cout<< p->vertex<< " ";
            f = f->nextFollower;
        }
        cout<< endl<< endl<< endl;
        head = head->nextLeader;
    }
    
    cout<< endl;
}
