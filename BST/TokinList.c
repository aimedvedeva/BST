#include <stdlib.h>
#include "TokinList.h"

void f_CopyTokenElementData(TokenListElement *Element, Token Data);
void f_destroyTokenElement(TokenListElement *Element);

TokenList *CreateTokenList(){
  TokenList *NewList = (TokenList*)malloc(sizeof(TokenList));
  NewList->Head = NewList->Tail = NULL;
  return NewList;
}

void DestroyList(TokenList *List){
  TokenListElement *CurEl = List->Head;
  TokenListElement *NextEl = NULL;

  while (CurEl != NULL){
    NextEl = CurEl->Next;
    f_destroyTokenElement(CurEl);
    CurEl = NextEl;
  }

  free(List);
}

TokenListElement *CreateTokenElement(Token Data){
  TokenListElement *NewEl = (TokenListElement*)malloc(sizeof(TokenListElement));
  f_CopyTokenElementData(NewEl, Data);
  NewEl->Next = NULL;
  return NewEl;
}

void AddToTokenList(TokenList *List, TokenListElement *NewEl){
  if (List->Tail == NULL){
    List->Head = List->Tail = NewEl;
  }
  else if (List->Tail != NULL){
    List->Tail->Next = NewEl;
    List->Tail = List->Tail->Next;
  }
  return;
}

void f_CopyTokenElementData(TokenListElement *Element, Token Data){
  Element->Data.Number = Data.Number;
  Element->Data.Type = Data.Type;
  return;
}

void f_destroyTokenElement(TokenListElement *Element){
  free(Element);
}