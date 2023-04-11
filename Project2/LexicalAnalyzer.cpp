#include <iostream>
#include <fstream>
#include <cctype>
#include "LexicalAnalyzer.h"  
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{
  currentChar = '\n';
  currentCharIndex = 0;
  sourceCodeFile = scf;
  line = "\n";

}

bool LexicalAnalyzer::isEOI()
{
  if (sourceCodeFile->eof() & currentCharIndex == line.size()){
    return true;
  } else{
    return false;
  }
}

void LexicalAnalyzer::readNextLine()
{
  getline(*sourceCodeFile, line);
      // getNextChar();
}

void LexicalAnalyzer::getNextChar()
{
  if (currentCharIndex == line.size()){
    readNextLine();
    currentCharIndex = 0;
    currentChar = line[currentCharIndex];
  } else{
    currentChar= line[++currentCharIndex];
  }
}

Token* LexicalAnalyzer::checkKeywordOrIdentifier(string lexeme){
  Token *t;
  // check if keyword
  if (lexeme == "bool") {
    t = new Token(BOOLSYM, "bool");
  } else if (lexeme == "do") {
    t = new Token(DOSYM, "do");
  } else if (lexeme == "else") {
    t = new Token(ELSESYM, "else");
  } else if (lexeme == "false") {
    t = new Token(FALSESYM, "false");
  } else if (lexeme == "float") {
    t = new Token(FLOATSYM, "float");
  } else if (lexeme == "for") {
    t = new Token(FORSYM, "for");
  } else if (lexeme == "if") {
    t = new Token(IFSYM, "if");
  } else if (lexeme == "int") {
    t = new Token(INTSYM, "int");
  } else if (lexeme == "printf") {
    t = new Token(PRINTFSYM, "printf");
  } else if (lexeme == "return") {
    t = new Token(RETURNSYM, "return");
  } else if (lexeme == "scanf") {
    t = new Token(SCANFSYM, "scanf");
  } else if (lexeme == "true") {
    t = new Token(TRUESYM, "true");
  } else if (lexeme == "void") {
    t = new Token(VOIDSYM, "void");
  } else if (lexeme == "while") {
    t = new Token(WHILESYM, "while");
  } else {
    // identifier
    t = new Token(IDENT, lexeme);
  }
  return t;
}

Token* LexicalAnalyzer::checkOperator(string lexeme){
  Token* t;
  if (currentChar == '+') {
      t = new Token(PLUS, "+");
      getNextChar();
    } else if (currentChar == '-') {
      t = new Token(MINUS, "-");
      getNextChar();
    } else if (currentChar == '*') {
      t = new Token(TIMES, "*");
      getNextChar();
    } else if (currentChar == '/') {
      t = new Token(SLASH, "/");
      getNextChar();
    } else if (currentChar == '%') {
      t = new Token(MOD, "%");
      getNextChar();
    } else if (currentChar == '(') {
      t = new Token(LPAREN, "(");
      getNextChar();
    } else if (currentChar == ')') {
      t = new Token(RPAREN, ")");
      getNextChar();
    } else if (currentChar == '{') {
      t = new Token(LBRACE, "{");
      getNextChar();
    } else if (currentChar == '}') {
      t = new Token(RBRACE, "}");
      getNextChar();
    } else if (currentChar == ',') {
      t = new Token(COMMA, ",");
      getNextChar();
    } else if (currentChar == ';') {
      t = new Token(SEMICOLON, ";");
      getNextChar();
    } else if (currentChar == '|') {
      getNextChar();
      if (currentChar == '|') {
        t = new Token(OR, "||");
        getNextChar();
      } else {
        t = new Token(NAL, "");
      }
    } else if (currentChar == '&') {
      getNextChar();
      if (currentChar == '&') {
        t = new Token(AND, "&&");
        getNextChar();
      } else {
        t = new Token(NAL, "");
      }
    } else if (currentChar == '=') {
      getNextChar();
      if (currentChar == '=') {
        t = new Token(EQL, "==");
        getNextChar();
      } else {
        t = new Token(ASSIGN, "=");
      }
    } else if (currentChar == '!') {
      getNextChar();
      if (currentChar == '=') {
        t = new Token(NEQ, "!=");
        getNextChar();
      } else {
        t = new Token(NOT, "!");
      }
    } else if (currentChar == '<') {
      getNextChar();
      if (currentChar == '=') {
        t = new Token(LEQ, "<=");
        getNextChar();
      } else {
        t = new Token(LSS, "<");
      }
    } else if (currentChar == '>') {
      getNextChar();
      if (currentChar == '=') {
        t = new Token(GEQ, ">=");
        getNextChar();
      } else {
        t = new Token(GTR, ">");
      }
    } else {
      getNextChar();
      t = new Token(NAL, "not a lexeme");
    }
  



  return t;
}

Token* LexicalAnalyzer::getNextToken()
{
  Token *t;
  string lexeme = "";
  while(currentChar == ' ' || currentChar == '\t' || currentChar == '\n'){
    getNextChar();
  }
  if (isEOI()) {
    t = new Token(EOI, "EOI");
  } else if (isalpha(currentChar)) {
    while (isalnum(currentChar)) {
      lexeme += currentChar;
      getNextChar();
    }
    t = checkKeywordOrIdentifier(lexeme);
  } else if (isdigit(currentChar)) {
    while (isdigit(currentChar)) {
      lexeme += currentChar;
      getNextChar();
    }
    t = new Token(NUMLIT, lexeme);
  } else {
    t = checkOperator(lexeme);
  }
  return t;
}
