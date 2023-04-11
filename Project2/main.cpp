#include <fstream>
#include <iostream>

#include "LexicalAnalyzer.cpp"
#include "LexicalAnalyzer.h"
#include "Token.cpp"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream sourceCodeFile;
  LexicalAnalyzer *la;
  Token *nextToken;
  TokenCodes tc;

  sourceCodeFile.open(argv[1], ifstream::in);
  if  (sourceCodeFile.is_open())
  {
    la = new LexicalAnalyzer(&sourceCodeFile);
    do
    {
      nextToken = la->getNextToken();
      cout << *nextToken << endl;
      tc = nextToken->getTokenCode();
      delete nextToken;
    } while (tc != EOI);
    delete la;
  }
  else
    printf("ERROR - cannot open input file \n");

  return 0;
}
