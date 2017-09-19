//
//  main.cpp
//
//  Created by Jacky on 2017-03-06.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "HuffmansPrefixCodeTree.h"

int main(int argc, const char * argv[]) {
    PCTreeNode q[128];
    PCTreeNode *PCTree; // the same as var t in Dr. Hilderman's pseudo code
    PCTreeNode *root; // Store the characters and number of occurrences in a binary search tree.
    DictionaryNode *dictionary;
    int elementCount = 0;
    int charSize = 0;
    string fileName = "text.txt";
    
    // 1) Read the file to be compressed
    root = NULL;
    ReadFile(root, charSize, fileName);
    cout<< "===== There are "<< charSize<< " different characters in the file"<< endl<< endl; // TEST

    // 2) Transfer the contents of the binary search tree to a priority queue.
    // The priority queue should be a min-heap ordered by the number of occurrences of each character
    BuildHeap(q, root, elementCount);
    cout<< "===== Print the min heap priority queue"<< endl;
    for(int i=1; i<=elementCount; i++)
        cout<< i<< ": "<< q[i].character<< ", "<< q[i].frequency<< endl;
    cout<< endl<< endl;
    
    // 3) Generate the optimal prefix code tree using HuffmansPrefixCode algorithm
    PCTree = Build(q, elementCount); // PCTree is the result of HuffmansPrefixCodeTree
    cout<< endl<< endl<< "===== Huffman tree: "<< endl;
    ShowStructure(PCTree); // TEST
    cout<< endl;
    
    // Traverse the prefix code tree and transfer the encoding scheme back to the binary search tree
    Encode(PCTree, dictionary);
    cout<< endl;
    //ShowStructure(dictionary);
    
    // Read the input file again, this time compressing it into an output file using the encoding scheme in the binary search tree.
    string compressedFile = "compression.txt";
    string decompressedFile = "decompression.txt";
    ifstream inFile;
    ofstream outFile;
    
    // Compression
    inFile.open(fileName);
    outFile.open(compressedFile);
    if(!inFile.is_open()){
        cout<< "Cannot open file: "<< fileName<< endl;
    }
    else if(!outFile.is_open()){
        cout<< "Cannot open file: "<< compressedFile<< endl;
    }
    else{
        cout<< "===== Compressed file:"<< endl;
        Compress(inFile, outFile, dictionary);
    }
    cout<< endl<< endl;
    inFile.close();
    outFile.close();
    
    
    
    // Decompression
    inFile.open(compressedFile);
    outFile.open(decompressedFile);
    if(!inFile.is_open()){
        cout<< "Cannot open file: "<< compressedFile<< endl;
    }
    else if(!outFile.is_open()){
        cout<< "Cannot open file"<< decompressedFile<< endl;
    }
    else{
        cout<< "===== Decompressed file:"<< endl;
        Decompress(inFile, outFile, PCTree);
    }
    cout<< endl;
    inFile.close();
    outFile.close();
    
    return 0;
}
