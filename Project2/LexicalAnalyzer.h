#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>

#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class LexicalAnalyzer
{
  private:
    char currentChar;
    int currentCharIndex;
    ifstream *sourceCodeFile;
    string line;


    bool isEOI();
    void readNextLine();
    void getNextChar();


  public:
    LexicalAnalyzer(ifstream*);
    Token* checkKeywordOrIdentifier(string);
    Token* checkOperator(string);
    Token* getNextToken();
};

#endif
