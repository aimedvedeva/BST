#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "BST.h"
#include "AccessData.h"
#include "TokinList.h"

//размер матрицы можно посчитать заранее дополнительным вызовом функции initMatrixForPrint, просто подсчитывая конечные x и y
#define SIZE 20

Tree *f_CreateTreeTop();
void f_CreateNode(int DataForNewNode, TreeNode **NewNode /* out */);
void f_AddNode(TreeNode *Parent, TreeNode *NewNode, Tree *Tree, MyBool IsRightChild);
void f_FillTree(TreeNode *Parent, TokenListElement **CurToken, Tree *Tree /* For Add */, MyBool *IsRightChild /* For Add */);

void f_DestroyNode(TreeNode *Node);
void f_DestroyNode(TreeNode *Node);

void f_InitMatrixForPrint(int Y, int *X, TreeNode *Node, int **MatrixForPrint);
void f_PrintTreeMatrix(int **MatrixForPrint);
void f_InitMatrixByZero(int **MatrixForPrint);
int **f_CreateMatrix();
void f_DeleteMatrix(int **Matrix);

Tree *CreateTree(){
  TokenList *List = (TokenList*)GetData();
  TokenListElement *CurToken = List->Head;
  Tree *Tree = f_CreateTreeTop();
  MyBool IsRightChild = MyBool_False;
  f_FillTree(NULL, &(CurToken), Tree, &IsRightChild);
  DestroyList(List);

  return Tree;
}

void DeleteTree(Tree *Tree){
  PostOrder(Tree->TopNode, &(f_DestroyNode));
  free(Tree);
}

void PrintTree(Tree *Tree){
  int **MatrixForPrint = f_CreateMatrix();
  f_InitMatrixByZero(MatrixForPrint);

  int x = 0;
  f_InitMatrixForPrint(0, &x, Tree->TopNode, MatrixForPrint);
  f_PrintTreeMatrix(MatrixForPrint);
  f_DeleteMatrix(MatrixForPrint);
}

void PostOrder(TreeNode *CurEl, void (*Function) (TreeNode *Node)){
  if (CurEl != NULL)
  {
    PostOrder(CurEl->Left, Function);
    PostOrder(CurEl->Right, Function);
    Function(CurEl);
  }
}

void PreOrder(TreeNode *CurEl, void(*Function) (TreeNode *Node)){
  if (CurEl != NULL)
  {
    Function(CurEl);
    PreOrder(CurEl->Left, Function);
    PreOrder(CurEl->Right, Function);
  }
}

void InOrder(TreeNode *CurEl, void(*Function) (TreeNode *Node)){
  if (CurEl != NULL)
  {
    InOrder(CurEl->Left, Function);
    Function(CurEl);
    InOrder(CurEl->Right, Function);
  }
}

void f_DestroyNode(TreeNode *Node){
  free(Node);
}

Tree *f_CreateTreeTop(){
  Tree *NewTree = (Tree*)malloc(sizeof(Tree));
  NewTree->TopNode = NULL;
  return NewTree;
}

void f_CreateNode(int DataForNewNode, TreeNode **NewNode /* out */){
  *NewNode = (TreeNode*)malloc(sizeof(TreeNode));
  (*NewNode)->Left = (*NewNode)->Right = (*NewNode)->Parent = NULL;
  (*NewNode)->Data = DataForNewNode;
}

void f_AddNode(TreeNode *Parent, TreeNode *NewNode, Tree *Tree, MyBool IsRightChild){
  if (Parent == NULL){
    Tree->TopNode = NewNode;
  }
  else{

    if (IsRightChild == MyBool_False){
      Parent->Left = NewNode;
    }
    else if (IsRightChild == MyBool_True){
      Parent->Right = NewNode;
    }

    NewNode->Parent = Parent;
  }
}

void f_FillTree(TreeNode *Parent, TokenListElement **CurToken, Tree *Tree /* For Add */, MyBool *IsRightChild /* For Add */){

  if ((*CurToken)->Data.Type == TokenType_Empty){
    (*CurToken) = (*CurToken)->Next;
  }

  if ((*CurToken)->Data.Type == TokenType_Number){
    TreeNode *NewNode;
    f_CreateNode((*CurToken)->Data.Number, &(NewNode));

    f_AddNode(Parent, NewNode, Tree, *IsRightChild);
    Parent = NewNode;

    (*CurToken) = (*CurToken)->Next;

    if (*IsRightChild == MyBool_True){
      *IsRightChild = MyBool_False;
    }
  }

  if ((*CurToken)->Data.Type == TokenType_OpenBracket){
    (*CurToken) = (*CurToken)->Next;
    f_FillTree(Parent, CurToken, Tree, IsRightChild);
    if ((*CurToken) == NULL){
      return;
    }
  }

  if ((*CurToken)->Data.Type == TokenType_CloseBracket){
    (*CurToken) = (*CurToken)->Next;
    *IsRightChild = MyBool_True;
    return;
  }

  if ((*CurToken)->Next != NULL && (*CurToken)->Next->Data.Type != TokenType_CloseBracket){
    f_FillTree(Parent, CurToken, Tree, IsRightChild);
    if ((*CurToken) == NULL){
      return;
    }
  }
}

void f_InitMatrixForPrint(int Y, int *X, TreeNode *Node, int **MatrixForPrint){
  if (Node != NULL){
    f_InitMatrixForPrint(Y + 1, X, Node->Left, MatrixForPrint);

    (*X)++;
    MatrixForPrint[Y][*X] = Node->Data;

    f_InitMatrixForPrint(Y + 1, X, Node->Right, MatrixForPrint);
  }
}

void f_PrintTreeMatrix(int **MatrixForPrint){
  FILE *Output = NULL;

  if ((Output = fopen("Output.txt", "w")) == NULL){
    return;
  }

  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      if (MatrixForPrint[i][j] == 0){
        fprintf(Output, "  ");
      }
      else{
        fprintf(Output, "%i", MatrixForPrint[i][j]);
      }
    }
    fprintf(Output, "\n");
  }

  fclose(Output);
}

void f_InitMatrixByZero(int **MatrixForPrint){
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      MatrixForPrint[i][j] = 0;
    }
  }
}

int **f_CreateMatrix(){
  int **MatrixForPrint = (int**)malloc(sizeof(int*) * SIZE);
  for (int i = 0; i < SIZE; i++){
    MatrixForPrint[i] = (int*)malloc(sizeof(int) * SIZE);
  }
  return MatrixForPrint;
}

void f_DeleteMatrix(int **Matrix){
  for (int i = 0; i < SIZE; i++){
    free(Matrix[i]);
  }
  free(Matrix);
}

/*
void f_GetNumOfNodes(int *result){
  *result++;
}
int GetNodesNum(Tree *Tree){
  PreOrder(Tree->TopNode, &f_GetNumOfNodes);
}
*/