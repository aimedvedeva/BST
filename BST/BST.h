#pragma once
typedef enum{
  ChildPosition_Left,
  ChildPosition_Right,
}ChildPosition;

typedef struct tag_TreeNode{
  struct tag_TreeNode *Parent;
  struct tag_TreeNode *Left;
  struct tag_TreeNode *Right;
  int Data;
}TreeNode;

typedef struct tag_Tree{
  TreeNode *TopNode;
}Tree;

Tree *CreateTree();
void DeleteTree(Tree *Tree);

void PrintTree(Tree *Tree);

void PostOrder(TreeNode *CurEl, void(*Function) (TreeNode *Node));
void PreOrder(TreeNode *CurEl, void(*Function) (TreeNode *Node));
void InOrder(TreeNode *CurEl, void(*Function) (TreeNode *Node));