//
//  PatternMatching.h
//
//  Created by Jacky on 2017-03-15.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
using namespace std;

const unsigned long SUBSTRING_NOT_FOUND = 99999999;

#ifndef PatternMatching_h
#define PatternMatching_h

unsigned long BruteForce(string t, unsigned long startIndex, string p, unsigned long& comparisonCounter);
unsigned long BoyerMoore(string t, unsigned long startIndex, string p, unsigned long& comparisonCounter);
unsigned long Last(char c, string p, unsigned long& comparisonCounter);
unsigned long Min(unsigned long a, unsigned long b);
unsigned long KnuthMorrisPratt(string t, unsigned long startIndex, string p, unsigned long& comparisonCounter);
void Failure(int f[], string p, unsigned long& comparisonCounter);
string ReadFile(string fileName);
int FindLineNumber (string p, unsigned long indexOfPattern, unsigned long& indexOfNewLine );

#endif /* PatternMatching_h */
