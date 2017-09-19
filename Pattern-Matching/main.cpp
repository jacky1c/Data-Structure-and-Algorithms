//
//  main.cpp
//
//  Created by Jacky on 2017-03-15.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "PatternMatching.h"

int main(int argc, const char * argv[]) {
    string textFileName = "text.txt";
    string patternFileName = "patterns.txt";
    string text = ReadFile(textFileName);
    string substring = ReadFile(textFileName);
    string pattern;
    ifstream input;
    unsigned long indexOfMatch;
    unsigned long linePosOfMatch;
    int lineNumberOfMatch;
    unsigned long indexOfNewLine;
    unsigned long comparisonCounter;
    unsigned long totalComparison = 0;
    
    input.open(patternFileName);
    
    // if we can open pattern file
    if(input.is_open()){
        getline(input, pattern);
        
        do{
            // initializa text to original string
            string text = ReadFile(textFileName);
            // initializa the comparison counter for a new pattern
            totalComparison = 0;
            // try to find the pattern in original text string
            indexOfMatch = BruteForce(text, 0, pattern, comparisonCounter);
            // add # of comparison to total comparison
            totalComparison += comparisonCounter;
            
            // if we can find the pattern, print out the first appearance of the pattern and keep searching
            if(indexOfMatch != SUBSTRING_NOT_FOUND){
                indexOfNewLine = -1; // used to handle when indexOfPattern is in the first line
                // find the line number of the pattern
                lineNumberOfMatch = FindLineNumber(text, indexOfMatch, indexOfNewLine);
                cout<< pattern<< "-> FOUND at"<< endl;
                linePosOfMatch = indexOfMatch - indexOfNewLine;
                cout<< "line="<< lineNumberOfMatch<< ", "<< linePosOfMatch<< "th character"<< endl;
                
                // try to find next matched pattern
                // index of new match in whole string = index of new match in substring + index of old match in whole string + 1
                indexOfMatch = BruteForce(text, indexOfMatch+1, pattern, comparisonCounter) + indexOfMatch + 1; // index of match2 in the whole text
                totalComparison += comparisonCounter;
                while(indexOfMatch < SUBSTRING_NOT_FOUND){
                    lineNumberOfMatch = FindLineNumber(text, indexOfMatch, indexOfNewLine);
                    linePosOfMatch = indexOfMatch - indexOfNewLine;
                    cout<< "line="<< lineNumberOfMatch<< ", "<< linePosOfMatch<< "th character"<< endl;
                    //cout<< " indexOfMatch "<< indexOfMatch<< endl;
                    indexOfMatch = BruteForce(text, indexOfMatch+1, pattern, comparisonCounter) + indexOfMatch + 1;
                    totalComparison += comparisonCounter;
                }
            }
            
            // if we can't find the pattern, prompt user pattern doesn't exist
            else{
                cout<< pattern<< "-> NOT FOUND!"<< endl;
            }
            
            
            // print out total comparison number
            cout<< '\t'<< "number of comparisons = "<< totalComparison<< endl<< endl;
            // read the next pattern string
            getline(input, pattern);
        } while(!input.eof());
        
        input.close();
    }
    else{
        cout<< "ERROR: Unable to open "<< patternFileName<< endl;
    }
    
    return 0;
}
