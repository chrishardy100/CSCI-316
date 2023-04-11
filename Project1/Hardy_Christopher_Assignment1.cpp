#include <fstream>
#include <iostream>
#include <string>

using namespace std;

char currentChar;
int currentCharIndex;
ifstream *sourceCodeFile;
string line;

bool isEOF()
{
  if (sourceCodeFile->eof() & currentCharIndex == line.size()){
    return true;
  } else{
    return false;
  }
}

void readNextLine()
{
  getline(*sourceCodeFile, line);
  line += '\n';
}

void getChar()
{
  if (currentCharIndex == line.size()){
    readNextLine();
    currentCharIndex = 0;
    currentChar = line[currentCharIndex];
  } else{
    currentChar= line[++currentCharIndex];
  }
}

int main(int argc, char *argv[])
{
  currentChar = '\n';
  currentCharIndex = 0;
  line = "\n";
  sourceCodeFile = new ifstream();

  sourceCodeFile->open(argv[1], ifstream::in);
  if (sourceCodeFile->is_open())
  {
    while (!isEOF())
    {
      getChar();
      cout << currentChar;
    }
  }
  else
    printf("ERROR - cannot open input file \n");

  return 0;
}