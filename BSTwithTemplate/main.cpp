#include "BST.h"
#include "BST.cpp"

int main()
{
    BST<int> bst;
    for(int i = 0; i < 5; i++)
        bst.add(i+1);
    bst.treePrint();
    bst.balanceTree();
    bst.treePrint();
}