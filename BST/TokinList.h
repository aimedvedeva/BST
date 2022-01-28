#pragma once

typedef enum{
  MyBool_False,
  MyBool_True,
}MyBool;

typedef enum{
  TokenType_OpenBracket,
  TokenType_CloseBracket,
  TokenType_Empty,
  TokenType_Number
}TokenType;

typedef struct tag_tokin{
  TokenType Type;
  int Number;
}Token;

typedef struct tag_TokenListElement{
  struct tag_TokenListElement *Next;
  Token Data;
}TokenListElement;

typedef struct tag_TokenList{
  TokenListElement *Head;
  TokenListElement *Tail;
}TokenList;

TokenList *CreateTokenList();
void DestroyList();

TokenListElement *CreateTokenElement(Token Data);
void AddToTokenList(TokenList *List, TokenListElement *NewEl);