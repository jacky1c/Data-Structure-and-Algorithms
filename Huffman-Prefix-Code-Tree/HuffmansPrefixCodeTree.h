//
//  HuffmansPrefixCodeTree.h
//
//  Created by Jacky on 2017-03-06.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const char NO_CHARACTER = '~';

#ifndef HuffmansPrefixCodeTree_h
#define HuffmansPrefixCodeTree_h

struct PCTreeNode{
    char character = NO_CHARACTER;
    int frequency;
    PCTreeNode *left;
    PCTreeNode *right;
};

struct DictionaryNode{
    char character = '\0';
    string bit;
    DictionaryNode *left;
    DictionaryNode *right;
};

// Read the file to be compressed (let’s call this the original file) and count the number of occurrences of each character in the file. Store the characters and number of occurrences in a binary search tree.
void ReadFile(PCTreeNode *&root, int& charSize, string fileName);
void UpdateNode(char x, PCTreeNode *&root, int& charSize);

// Transfer the contents of the binary search tree to a priority queue(ordered by frequency)
void BuildHeap(PCTreeNode a[], PCTreeNode *root, int& elementCount);
void CopyBSTreeToQueue(PCTreeNode a[], PCTreeNode *root, int& elementCount); // called by BuildHeap

// Huffman code
void Initialization(PCTreeNode q[], int& elementCount, PCTreeNode *root);
void InitializationHelper(PCTreeNode q[], int& elementCount, PCTreeNode *tree);

PCTreeNode* Build(PCTreeNode q[], int& elementCount); // Build Huffman tree
void Insert(PCTreeNode t, PCTreeNode q[], int& elementCount);
PCTreeNode DeleteMin(PCTreeNode q[], int& elementCount);

// Traverse the prefix code tree and transfer the encoding scheme to dictionary(a binary search tree)
void Encode(PCTreeNode *PCTree, DictionaryNode *&dictionary);
void EncodeHelper(PCTreeNode *PCTree, string &bit, DictionaryNode *&dictionary);
//void Traverse(PCTreeNode *PCTree);
//void TraverseHelper(PCTreeNode *PCTree, string &bit);
void InsertNodeToDictionary(DictionaryNode node, DictionaryNode *&root);

// Compression use dictionary tree
void Compress(ifstream& inFile, ofstream& outFile, DictionaryNode *root);
string PairCharAndBit(char character, DictionaryNode *root);
DictionaryNode* PairCharAndBitHelper(char character, DictionaryNode *root);

// Decompression use huffman tree
void Decompress(ifstream& inFile, ofstream& outFile, PCTreeNode *root);
char PairCharAndBit(string bit, PCTreeNode *root);
PCTreeNode* PairCharAndBitHelper(string bit, PCTreeNode *root);

// Display structure of data
void ShowStructure(PCTreeNode* s);
void ShowHelper(PCTreeNode*, int);
void ShowStructure(DictionaryNode* s);
void ShowHelper(DictionaryNode *p, int level);
void ShowTree(PCTreeNode *p);
void ShowTreeHelper(PCTreeNode *p);
void ShowEncodingScheme(PCTreeNode* s);
void ShowEncodingSchemeHelper(PCTreeNode *p);
//void ShowDictionaryStructure(DictionaryNode* s);



#endif /* HuffmansPrefixCodeTree_h */
