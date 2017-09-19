//
//  PatternMatching.cpp
//
//  Created by Jacky on 2017-03-15.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "PatternMatching.h"

// read all the characters from input file, including empty space character
string ReadFile(string fileName){
    ifstream input;
    string out = "";
    char x;
    
    input.open(fileName);
    if(input.is_open()){
        input>> noskipws;
        input>> x;
        while(!input.eof()){
            out += x;
            input>> x;
        }
        input.close();
    }
    else{
        cout<< "ERROR: Unable to open "<< fileName<< endl;
    }
    return out;
}

unsigned long BruteForce(string text, unsigned long startIndex, string p, unsigned long& comparisonCounter){
    if (startIndex>=text.length())
        return SUBSTRING_NOT_FOUND;
    string t = text.substr(startIndex);
    unsigned long m = p.length();
    unsigned long n = t.length();
    if(m>n)
        return SUBSTRING_NOT_FOUND;
    comparisonCounter = 0;
    
    for(int i=0; i<=n-m; i++){
        int j=0;
        
        if(j<m){
            if(t[i+j]==p[j]){ // go in to while loop
                while (j<m && t[i+j]==p[j]){
                    comparisonCounter++;
                    j++;
                }
                // now we see what condition makes while loop end
                if(j<m)
                    comparisonCounter++;
            }
            else{ // while loop is not executed but there is one comparison
                comparisonCounter++;
            }
        }// if "j>=m", while loop won't be executed and there is no comparison
        
        if(j==m)
            return i;
    }
    return SUBSTRING_NOT_FOUND;
}

unsigned long BoyerMoore(string text, unsigned long startIndex, string p, unsigned long& comparisonCounter){
    if (startIndex>=text.length())
        return SUBSTRING_NOT_FOUND;
    string t = text.substr(startIndex);
    unsigned long n = t.length();
    unsigned long m = p.length();
    if(m>n)
        return SUBSTRING_NOT_FOUND;
    unsigned long i = m-1;
    unsigned long j = m-1;
    comparisonCounter = 0;
    
    do{
        comparisonCounter++;
        if(p[j]==t[i]){
            if(j==0)
                return i;
            else{
                i--;
                j--;
            }
        }
        else{
            i = i+m-Min(j,1+Last(t[i],p, comparisonCounter));
            j = m-1;
        }
    } while (i<=n-1);
    return SUBSTRING_NOT_FOUND;
}

// used in BoyerMoore
unsigned long Min(unsigned long a, unsigned long b){
    return a>b ? b:a;
}

// used in BoyerMoore
unsigned long Last(char c, string p, unsigned long& comparisonCounter){
    unsigned long m = p.length();
    for(unsigned long i=m; i>=1; i--){ // the same as "for i = m - 1 to 0". i is unsigned so can't make it to be negative to end the loop
        comparisonCounter++;
        if(c==p[i-1])
            return i-1;
    }
    return -1;
}


unsigned long KnuthMorrisPratt(string text, unsigned long startIndex, string p, unsigned long& comparisonCounter){
    if (startIndex>=text.length())
        return SUBSTRING_NOT_FOUND;
    
    string t = text.substr(startIndex);
    unsigned long m = p.length();
    unsigned long n = t.length();
    if(m>n)
        return SUBSTRING_NOT_FOUND;
    
    int f[m];
    int i=0;
    int j=0;
    comparisonCounter = 0;
    Failure(f, p, comparisonCounter);
    
    while (i<n){
        comparisonCounter++;
        if(p[j]==t[i]){
            if(j == m-1)
                return i-m+1;
            i++;
            j++;
        }
        else if(j>0){
            j = f[j-1];
            if(i-j+m>n)
                break;
        }
        else{
            i++;
            if(i+m>n){
                break;
            }
        }
    }
    return SUBSTRING_NOT_FOUND;
}

// used in KnuthMorrisPratt
void Failure(int f[], string p, unsigned long& comparisonCounter){
    unsigned long m = p.length();
    int i = 1;
    int j = 0;
    f[0] = 0;
    while(i<m){
        comparisonCounter++;
        if(p[j] == p[i]){
            f[i] = j+1;
            i++;
            j++;
        }
        else if(j>0){
            j = f[j-1];
        }
        else{
            f[i] = 0;
            i++;
        }
    }
    return;
}

int FindLineNumber (string p, unsigned long indexOfPattern, unsigned long& indexOfNewLineCharacter ){
    int lineNumber = 1;
    
    for(int i=0; i<indexOfPattern; i++){
        if(p[i] == '\n'){
            lineNumber++;
            indexOfNewLineCharacter = i;
        }
    }
    
    return lineNumber;
}
