#pragma once

typedef struct _CC_TREE {
    // Members
    int data;
    int multiplicity;
    struct _CC_TREE *left, *right;
    int height;
} CC_TREE;

int TreeCreate(CC_TREE **Tree);
int TreeDestroy(CC_TREE **Tree);

// Duplicates are allowed
int TreeInsert(CC_TREE *Tree, int Value);

// Removes all elements equal to Value
int TreeRemove(CC_TREE *Tree, int Value);


//  Returns:
//       1  - Tree contains Value
//       0  - Tree does not contain Value
//      -1  - Error or invalid parameter
int TreeContains(CC_TREE *Tree, int Value);

// Returns the number of elements in Tree or -1 in case of error or invalid parameter
int TreeGetCount(CC_TREE *Tree);

// Returns the height of Tree or -1 in case of error or invalid parameter
int TreeGetHeight(CC_TREE *Tree);

// Removes every element of the tree
int TreeClear(CC_TREE *Tree);

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value);

//Counting Nodes function
//Count all the nodes in the tree
unsigned int CountingNodes(CC_TREE *Tree);

//CC_TREE * functions to perform the removal of an element and the insertion of an element
CC_TREE* removeElement(CC_TREE *T, int Value);
CC_TREE* insertElement(CC_TREE *T, int Value);
CC_TREE* smallestRightNode(CC_TREE* T);

void PostOrder(CC_TREE *Tree, int Index, int *Value, int *IndexPostOrder);
void InOrder(CC_TREE *Tree, int Index, int *Value, int *IndexInOrder);
void PreOrder(CC_TREE *Tree, int Index, int *Value, int *IndexPreOrder);