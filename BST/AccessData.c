#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "TokinList.h"

#define ASCII_DELTA 48

MyBool f_GetToken(FILE *File, Token *Tok /* out */, MyBool *IsEOF /* out */);

void *GetData(){
  FILE *Input = NULL;

  if ((Input = fopen("Input.txt","r")) == NULL){
    return NULL;
  }

  TokenList *List = CreateTokenList();
  Token Tok;
  MyBool IsEOF = MyBool_False;

  while (!IsEOF){
    MyBool result = f_GetToken(Input, &Tok, &IsEOF);
    if (result == MyBool_False){
      continue;
    }
    if (IsEOF){
      break;
    }
    TokenListElement *NewEl = CreateTokenElement(Tok);
    AddToTokenList(List, NewEl);
  }

  fclose(Input);
  return (void*)List;
}


MyBool f_GetToken(FILE *File, Token *Tok /* out */, MyBool *IsEOF /* out */){
  char C = getc(File);

  if (C == EOF){
    *IsEOF = MyBool_True;
    return MyBool_True;
  }

  if (C == ':' || isalpha(C) || C == '='){
    while (C == ':' || isalpha(C) || C == '='){
      C = getc(File);

      if (!isalpha(C) && C != EOF && C != '=' && C != ':'){
        fseek(File, -1, SEEK_CUR);
        break;
      }
    }
    return MyBool_False;
  }

  else if (C == ')'){
    Tok->Type = TokenType_CloseBracket;
  }
  else if (C == '('){
    Tok->Type = TokenType_OpenBracket;
  }
  else if (C == ' '){
    Tok->Type = TokenType_Empty;
  }
  else {
    MyBool IsFirst = MyBool_True;
    int CurNum = 0;

    while (isdigit(C)){

      if (!IsFirst){
        CurNum *= 10;
      }
      CurNum += ((int)C - ASCII_DELTA);

      C = getc(File);
      if (!isdigit(C) && C != EOF){
        fseek(File, -1, SEEK_CUR);
        Tok->Type = TokenType_Number;
        Tok->Number = CurNum;
        return MyBool_True;
      }

      if (C == EOF){
        *IsEOF = MyBool_True;
        return MyBool_True;
      }

      IsFirst = MyBool_False;
    }
  }
}
