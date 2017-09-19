//
//  HuffmansPrefixCodeTree.cpp
//
//  Created by Jacky on 2017-03-06.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "HuffmansPrefixCodeTree.h"

/*
 Read the file to be compressed (let’s call this the original file).
 Count the number of occurrences of each character in the file. 
 Store the characters and number of occurrences in a binary search tree. (key is character)
 */
void ReadFile(PCTreeNode *&root, int& charSize, string fileName){
    ifstream input;
    char x;
    charSize = 0; // number of different characters in a file - 1
    
    input.open(fileName);
    if(input.is_open()){
        input>> noskipws;
        input>> x;
        while(!input.eof()){
            UpdateNode(x, root, charSize);
            input>> x;
        }
        input.close();
    }
    else{
        cout<< "ERROR: Unable to open "<< fileName<< endl;
    }
    return;
}

// called by ReadFile
void UpdateNode(char x, PCTreeNode *&root, int& charSize){
    if(root == NULL){
        root = new PCTreeNode;
        root->character = x;
        root->frequency = 1;
        //root->bit = "";
        root->left = NULL;
        root->right = NULL;
        charSize++;
    }
    else{
        // cout<< root->character<< " "; // TEST
        if(x == root->character){ // this line is not stable in run time. Sometimes bad, sometimes good. Not sure why. Error: exc_bad_access code=exc_i386_gpflt
            root->frequency++;
        }
        else if(x < root->character)
            UpdateNode(x, root->left, charSize);
        else
            UpdateNode(x, root->right, charSize);
    }
}

void BuildHeap(PCTreeNode a[], PCTreeNode *root, int& elementCount){
    elementCount = 1;
    // copy all the nodes in root to heap
    CopyBSTreeToQueue(a, root, elementCount);
    elementCount--;
    int j = elementCount/2;
    int i = j;
    int child;
    while(i > 0){
        PCTreeNode temp;
        temp.character = a[i].character;
        temp.frequency = a[i].frequency;
        //temp.bit = a[i].bit;
        temp.left = a[i].left;
        temp.right = a[i].right;
        while(i*2 <= elementCount){
            child = i*2;
            if(child != elementCount && a[child+1].frequency<a[child].frequency)
                child++;
            if(a[child].frequency<temp.frequency)
                a[i] = a[child];
            else
                break;
            i = child;
        }
        a[i].character = temp.character;
        a[i].frequency = temp.frequency;
        //a[i].bit = temp.bit;
        a[i].left = temp.left;
        a[i].right = temp.right;
        j--;
        i = j;
    }
    return;
}

// called by BuildHeap
void CopyBSTreeToQueue(PCTreeNode a[], PCTreeNode *root, int& elementCount){
    if(root != NULL){
        a[elementCount].character = root->character;
        a[elementCount].frequency = root->frequency;
        //a[elementCount].bit = root->bit;
        //a[elementCount].left = root->left;
        //a[elementCount].right = root->right;
        elementCount++;
        CopyBSTreeToQueue(a, root->left, elementCount);
        CopyBSTreeToQueue(a, root->right, elementCount);
    }
}


// Binary heap
// called by Initialization and Build
void Insert(PCTreeNode t, PCTreeNode q[], int& elementCount){
    int i;
    elementCount++;
    i = elementCount;
    while(i>1 && t.frequency<q[i/2].frequency){
        q[i] = q[i/2];
//        q[i].character = q[i/2].character; // add
//        q[i].frequency = q[i/2].frequency; // add
//        //q[i].bit = q[i/2].bit; // add
//        q[i].left = q[i/2].left; // add
//        q[i].right = q[i/2].right; // add
        i = i/2;
    }
//    q[i].character = t.character; // add
//    q[i].frequency = t.frequency; // add
//    //q[i].bit = t.bit; // add
//    q[i].left = t.left; // add
//    q[i].right = t.right; // add
    q[i] = t;
}

// Build Huffman tree
PCTreeNode* Build(PCTreeNode q[], int& elementCount){
    PCTreeNode t;
    PCTreeNode *t1, *t2;
    int n = elementCount - 1;
    cout<<endl<<"===== Progress in Build function (how Huffman tree is built)"<< endl;
    for(int i=1; i<=n; i++){
        try{
            t1 = new PCTreeNode;
            t = DeleteMin(q, elementCount);
            t1->character = t.character;
            t1->frequency = t.frequency;
            //t1->bit = t.bit; // add
            t1->left = t.left;
            t1->right = t.right;
            cout<<"t1:("<<t1->character<<","<<t1->frequency<<")"; // TEST
            try{
                t2 = new PCTreeNode;
                t = DeleteMin(q, elementCount);
                t2->character = t.character;
                t2->frequency = t.frequency;
                //t2->bit = t.bit; // add
                t2->left = t.left;
                t2->right = t.right;
                cout<<"+t2:("<<t2->character<<","<<t2->frequency<<") = "; // TEST
            }
            catch(bad_alloc){
                cout<< "t2 EXCEPTION: BAD_ALLOC"<< endl;
            }
        }
        catch(bad_alloc){
            cout<< "t1 EXCEPTION: BAD_ALLOC"<< endl;
        }
        t.character = NO_CHARACTER;
        t.frequency = t1->frequency + t2->frequency;
        //t.bit = ""; // add
        t.left = t1;
        t.right = t2;
        Insert(t, q, elementCount);
        cout<<"t:("<<t.character<<","<<t.frequency<<")"<< endl; // TEST
    }
    // cout<< "Element count in Build: "<< elementCount<< endl; // TEST: elementCount = 1
    t = DeleteMin(q, elementCount);
    t1 = new PCTreeNode;
    t1->character = t.character;
    t1->frequency = t.frequency;
    //t1->bit = t.bit; // add
    t1->left = t.left;
    t1->right = t.right;
    return t1;
}

// called by Build
PCTreeNode DeleteMin(PCTreeNode q[], int& elementCount){
    PCTreeNode t = q[1];
    PCTreeNode temp;
    int i=1;
    int child;
    
    q[1] = q[elementCount];
//    q[1].character = q[elementCount].character; // add
//    q[1].frequency = q[elementCount].frequency; // add
//    q[1].left = q[elementCount].left; // add
//    q[1].right = q[elementCount].right; // add
//    q[1].bit = q[elementCount].bit; // add
    elementCount--;
    temp = q[1];
    while(i*2 <= elementCount){
        child = i*2;
        if(child != elementCount && q[child+1].frequency < q[child].frequency)
            child++;
        if(q[child].frequency < temp.frequency)
            q[i] = q[child];
        else
            break;
        i = child;
    }
    q[i] = temp;
    return t;
}

// build the dictionary
void Encode(PCTreeNode *PCTree, DictionaryNode *&dictionary){
    string bit = "";
    dictionary = NULL;
    cout<< "===== In Encode fuction, display character and bit string pair"<< endl;
    EncodeHelper(PCTree, bit, dictionary);
    return;
}
void EncodeHelper(PCTreeNode *PCTree, string& bit, DictionaryNode *&dictionary){
    if(PCTree != NULL){
        if(PCTree->character == NO_CHARACTER){
            string left = bit+"0";
            string right = bit+"1";
            EncodeHelper(PCTree->left, left, dictionary);
            EncodeHelper(PCTree->right, right, dictionary);
        }
        else{
            DictionaryNode newNode;
            newNode.character = PCTree->character;
            newNode.bit = bit;
            cout<< "("<< newNode.character<< ","<< newNode.bit<< ")"<<endl; // TEST
            InsertNodeToDictionary(newNode, dictionary);
        }
    }
}

// store pairs of character and bit into dictionary
void InsertNodeToDictionary(DictionaryNode newNode, DictionaryNode *&root){
    if(root != NULL){
        if(newNode.character < root->character){
            InsertNodeToDictionary(newNode, root->left);
        }
        else if(newNode.character > root->character){
            InsertNodeToDictionary(newNode, root->right);
        }
    }
    else{
        root = new DictionaryNode;
        root->character = newNode.character;
        root->bit = newNode.bit;
        root->left = NULL;
        root->right = NULL;
    }
}

//void Traverse(PCTreeNode *PCTree){
//    string bit = "";
//    TraverseHelper(PCTree, bit);
//    return;
//}
//void TraverseHelper(PCTreeNode *PCTree, string& bit){
//    if(PCTree != NULL){
//        if(PCTree->character == NO_CHARACTER){
//            string left = bit+"0";
//            string right = bit+"1";
//            TraverseHelper(PCTree->left, left);
//            TraverseHelper(PCTree->right, right);
//        }
//        else{
//            PCTree->bit = bit+'\0';
//            string left = bit+"0";
//            string right = bit+"1";
//            TraverseHelper(PCTree->left, left);
//            TraverseHelper(PCTree->right, right);
//        }
//    }
//    return;
//}



// Compression
void Compress(ifstream& inFile, ofstream& outFile, DictionaryNode *root){
    char character;
    string bit;
    
    inFile>> noskipws;
    outFile<< noskipws;
    inFile>> character;
    while(!inFile.eof()){
        bit = PairCharAndBit(character, root);
        cout<< bit;
        outFile<< bit;
        inFile>> character;
    }
    
    return;
}

string PairCharAndBit(char character, DictionaryNode *root){
    DictionaryNode* result;
    
    result = PairCharAndBitHelper(character, root);
    return result->bit;
}

DictionaryNode* PairCharAndBitHelper(char character, DictionaryNode *root){
    if(character < root->character)
        return PairCharAndBitHelper(character, root->left);
    else if(character > root->character)
        return PairCharAndBitHelper(character, root->right);
    else
        return root;
    
}


// Decompression
//void Decompress(ifstream& inFile, ofstream& outFile, DictionaryNode *root){
//    char nextBit;
//    string bitString = "";
//    string bitStringCopy;
//    char character;
//    //inFile>> noskipws;
//    outFile<< noskipws;
//    
//    inFile>> nextBit;
//    while(!inFile.eof()){
//        bitString += nextBit;
//        bitStringCopy = bitString;
//        character = PairCharAndBit(bitStringCopy, root);
//        if(character != NO_CHARACTER){ // we find the char
//            //outFile<< character;
//            //outFile<< bitString<< endl; // TEST
//            bitString = "";
//            inFile>> nextBit;
//        }
//        else{ // never get executed
//            outFile<< bitString<< endl; // TEST
//            cout<< "ha";
//            inFile>> nextBit;
//        }
//    }
//}
//char PairCharAndBit(string bitString, DictionaryNode *root){
//    DictionaryNode* result;
//    
//    result = PairCharAndBitHelper(bitString, root);
//    return result->character;
//}
//DictionaryNode* PairCharAndBitHelper(string bitString, DictionaryNode *root){
//    if(bitString.length() == 0){
//        return root;
//    }
//    else if(bitString.length() == 1){
//        if(bitString[0] == '0'){
//            return root->left;
//        }
//        else{
//            return root->right;
//        }
//    }
//    else{
//        if(bitString[0] == '0'){
//            bitString = bitString.substr(1);
//            return PairCharAndBitHelper(bitString, root->left);
//        }
//        else{
//            bitString =bitString.substr(1);
//            return PairCharAndBitHelper(bitString, root->right);
//        }
//    }
//}
void Decompress(ifstream& inFile, ofstream& outFile, PCTreeNode *root){
    char nextBit;
    string bitString = "";
    string bitStringCopy;
    char character;
    inFile>> noskipws;
    outFile<< noskipws;
    
    inFile>> nextBit;
    while(!inFile.eof()){
        bitString += nextBit;
        character = PairCharAndBit(bitString, root);
        if(character != NO_CHARACTER){ // we find the character
            outFile<< character;
            cout<< character;
            //outFile<< bitString<< endl; // TEST
            bitString = "";
            inFile>> nextBit;
        }
        else{ // cannot find the character
            //outFile<< bitString<< endl; // TEST
            //cout<< "ha";
            inFile>> nextBit;
        }
    }
}
char PairCharAndBit(string bitString, PCTreeNode *root){
    PCTreeNode* result;
    
    result = PairCharAndBitHelper(bitString, root);
    return result->character;
}
PCTreeNode* PairCharAndBitHelper(string bitString, PCTreeNode *root){
    if(bitString.length() == 0){
        return root;
    }
    else if(bitString.length() == 1){
        if(bitString[0] == '0'){
            return root->left;
        }
        else{
            return root->right;
        }
    }
    else{
        if(bitString[0] == '0'){
            bitString = bitString.substr(1);
            return PairCharAndBitHelper(bitString, root->left);
        }
        else{
            bitString =bitString.substr(1);
            return PairCharAndBitHelper(bitString, root->right);
        }
    }
}


// Show data structure
void ShowStructure(PCTreeNode* s) {
    if ( s == NULL )
        cout << "Empty tree" << endl;
    else{
        cout << endl;
        ShowHelper(s,1);
        cout << endl;
    }
}
void ShowHelper(PCTreeNode *p, int level){
    int j;   // Loop counter
    if ( p != NULL ){
        // Error: thread 1 exc_bad_access (code=exc_i386_gpflt)
        ShowHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << "(" << p->character<< ","<< p->frequency<< ")";   // Output key
        if ( ( p->left != 0 ) && ( p->right != 0 ) ) // Output "connector"
            cout << "<";
        else if ( p->right != 0 )
            cout << "/";
        else if ( p->left != 0 )
            cout << "\\";
        cout << endl;
        ShowHelper(p->left,level+1);          // Output left subtree
    }
}
void ShowStructure(DictionaryNode* s) {
    if ( s == NULL )
        cout << "Empty tree" << endl;
    else{
        cout << endl;
        ShowHelper(s,1);
        cout << endl;
    }
}
void ShowHelper(DictionaryNode *p, int level){
    int j;   // Loop counter
    if ( p != NULL ){
        // Error: thread 1 exc_bad_access (code=exc_i386_gpflt)
        ShowHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        //cout << "(" << p->character<< ","<< p->bit<< ")";   // Output key
        cout << "(" << p->character<< ")";   // Output key
        if ( ( p->left != 0 ) && ( p->right != 0 ) ) // Output "connector"
            cout << "<";
        else if ( p->right != 0 )
            cout << "/";
        else if ( p->left != 0 )
            cout << "\\";
        cout << endl;
        ShowHelper(p->left,level+1);          // Output left subtree
    }
}




//void ShowDictionaryHelper(DictionaryNode* p, int level){
//    int j;   // Loop counter
//    if ( p != 0 ){
//        ShowDictionaryHelper(p->right,level+1);         // Output right subtree
//        for ( j = 0 ; j < level ; j++ )    // Tab over to level
//            cout << "\t";
//        cout << "(" << p->character<< ")";   // Output key
//        if ( ( p->left != 0 ) &&           // Output "connector"
//            ( p->right != 0 ) )
//            cout << "<";
//        else if ( p->right != 0 )
//            cout << "/";
//        else if ( p->left != 0 )
//            cout << "\\";
//        cout << endl;
//        ShowDictionaryHelper(p->left,level+1);          // Output left subtree
//    }
//}
//void ShowDictionaryStructure(DictionaryNode* s){
//    if ( s == NULL )
//        cout << "Empty tree" << endl;
//    else{
//        cout << endl;
//        ShowDictionaryHelper(s,1);
//        cout << endl;
//    }
//
//}
void ShowTree(PCTreeNode* s) {
    if ( s == NULL )
        cout << "Empty tree" << endl;
    else{
        cout << endl;
        ShowTreeHelper(s);
        cout << endl;
    }
}
void ShowTreeHelper(PCTreeNode *p){
    if(p != NULL){
        cout<< p->character<< " - "<< p->frequency<< endl;
        ShowTreeHelper(p->left);
        ShowTreeHelper(p->right);
    }
}

//void ShowEncodingScheme(PCTreeNode* s) {
//    if ( s == NULL )
//        cout << "Empty tree" << endl;
//    else{
//        cout << endl;
//        ShowEncodingSchemeHelper(s);
//        cout << endl;
//    }
//}
//void ShowEncodingSchemeHelper(PCTreeNode *p){
//    if(p != NULL){
//        if(p->character!=NO_CHARACTER && p->bit != "")
//            cout<< p->character<< " - "<< p->bit<< endl;
//        ShowEncodingSchemeHelper(p->left);
//        ShowEncodingSchemeHelper(p->right);
//    }
//}
