#include <stdio.h>
#include <crtdbg.h>
#include "BST.h"
#include "TokinList.h"


int main(){
  Tree *MyTree = CreateTree();
  PrintTree(MyTree);
  DeleteTree(MyTree);
  _CrtDumpMemoryLeaks();
  return 0;
}