#include "cctree.h"
#include "common.h"
#include "stdio.h"
int TreeCreate(CC_TREE **Tree)
{

    CC_UNREFERENCED_PARAMETER(Tree);

    CC_TREE *auxTree = (CC_TREE*)malloc(sizeof(CC_TREE));
    
    if (auxTree == NULL)
    {
        return -1;
    }

    auxTree->data = INT_MIN;
    auxTree->left = NULL;
    auxTree->right = NULL;
    auxTree->multiplicity = 0;
    *Tree = auxTree;
    
    if (Tree == NULL)
    {
        return -1;
    }

    return 0;
}

int TreeDestroy(CC_TREE **Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (Tree == NULL)
    {
        return -1;
    }

    CC_TREE *Tr = *Tree;

    Tr->data = 0;
    Tr->multiplicity = 0;

    if (Tr->left != NULL)TreeDestroy(&Tr->left);
    if (Tr->right != NULL)TreeDestroy(&Tr->right);

    free(Tr->left);
    free(Tr->right);

    free(Tr);

    *Tree = NULL;


    return 0;
}

int TreeInsert(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }
    if (NULL == &Value)
    {
        return -1;
    }

    Tree = insertElement(Tree, Value);

    if (Tree == NULL)
    {
        return -1;
    }

    return 0;
}

int TreeRemove(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);


    if (NULL == Tree)
    {
        return -1;
    }
    if (&Value == NULL)
    {
        return -1;
    }
    if (Tree->left == NULL && Tree->right == NULL)
    {
        if (Tree->data == Value) {
            int retVal = TreeClear(Tree);
            return retVal;
        }
        return 0;
    }
    else
    {
        Tree = removeElement(Tree, Value);
        if (Tree == NULL || Tree->data == -572662307)
        {
            TreeCreate(&Tree);
        }
    }

    if (Tree != NULL)
    {
        Tree->height = TreeGetHeight(Tree);
    }
    return 0;
}

int TreeContains(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Tree == NULL)
    {
        return 0;
    }
    if (Tree->data == Value)
    {
        return 1;
    }
    
    CC_TREE *auxTree = Tree;
    while(NULL != auxTree)
    {
        if (auxTree->data > Value)
        {
            auxTree = auxTree->left;

        }
        else if (auxTree->data < Value )
        {
            auxTree = auxTree->right;
        }
        else
        {
            return 1;
        }
    }
    return 0;

}

int TreeGetCount(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    if (NULL == Tree || Tree->data == -572662307)
    {
        return -1;
    }
    if (Tree->data == INT_MIN )
    {
        return 0;
    }
    unsigned int count = 0;
    if (Tree != NULL) {
        count = CountingNodes(Tree);
    }
    return count;
}

int TreeGetHeight(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    int leftHeight, rightHeight;
    if (Tree == NULL)
        return -1;

    if (Tree->left == NULL)
        leftHeight = 0;
    else
        leftHeight = 1 + Tree->left->height;

    if (Tree->right == NULL)
        rightHeight = 0;
    else
        rightHeight = 1 + Tree->right->height;

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    return rightHeight + 1;
}

int TreeClear(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    if (NULL == Tree)
    {
        return -1;
    }

    if(Tree->left != NULL) TreeDestroy(&Tree->left);
    if(Tree->right != NULL) TreeDestroy(&Tree->right);
    
    Tree->multiplicity = 0;
    Tree->data = INT_MIN;
    Tree->height = 0;

    if (NULL == Tree)
    {
        return -1;
    }
    return 0;
}

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (Tree == NULL)
    {
        return -1;
    }
    if (Value == NULL || *Value<0 || *Value>TreeGetCount(Tree))
    {
        return -1;
    }
    if (&Index == NULL)
    {
        return -1;
    }

    int indexPreOrder = 0;
    PreOrder(Tree, Index, Value, &indexPreOrder);

    return 0;
}

int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Tree == NULL)
    {
        return -1;
    }
    if (Value == NULL || *Value < 0 || *Value>TreeGetCount(Tree))
    {
        return -1;
    }
    if (&Index == NULL)
    {
        return -1;
    }

    int IndexInOrder = 0;
    InOrder(Tree, Index, Value, &IndexInOrder);

    return 0;

}

int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Tree == NULL)
    {
        return -1;
    }
    if (Value == NULL || *Value<0 || *Value>TreeGetCount(Tree))
    {
        return -1;
    }
    if (&Index == NULL)
    {
        return -1;
    }

    int indexPostOrder = 0;
    PostOrder(Tree, Index, Value, &indexPostOrder);

    return 0;
}

unsigned int CountingNodes(CC_TREE *Tree)
{
    unsigned int count = Tree->multiplicity;
    if (Tree->left != NULL) {
        count += CountingNodes(Tree->left);
    }
    if (Tree->right != NULL) {
        count += CountingNodes(Tree->right);
    }
    return count;
}

CC_TREE * removeElement(CC_TREE *Tree, int Value)
{
    CC_TREE *auxTree;

    if (Tree == NULL)
    {
        return NULL;
    }
    else
        if (Value > Tree->data)
        {
            Tree->right = removeElement(Tree->right, Value);
        }
        else
            if (Value < Tree->data)
            {
                Tree->left = removeElement(Tree->left, Value);
            }
            else
            {

                if (Tree->right != NULL)
                {
                    auxTree = Tree->right;

                    while (auxTree->left != NULL)
                        auxTree = auxTree->left;

                    Tree->data = auxTree->data;
                    Tree->right = removeElement(Tree->right, auxTree->data);

                }
                else
                    return(Tree->left);
            }
    if (Tree != NULL)
    {
        Tree->height = TreeGetHeight(Tree);
    }
    else
    {

    }
    return(Tree);

}
CC_TREE * insertElement(CC_TREE *Tree, int Value)
{
    if (Tree == NULL || Tree->data == -572662307)
    {
        Tree = (CC_TREE*)malloc(sizeof(CC_TREE));
        Tree->data = Value;
        Tree->left = NULL;
        Tree->right = NULL;
        Tree->multiplicity = 1;
        return Tree;
    }
    else if (Tree->data == INT_MIN)
    {
        Tree->data = Value;
        Tree->multiplicity = 1;
        return (Tree);
    }
    else
    {
        if (Tree->data == Value)
        {
            Tree->multiplicity += 1;
            return Tree;
        }
        if (Value > Tree->data)
        {
            Tree->right = insertElement(Tree->right, Value);
        }
        else
            if (Value < Tree->data)
            {
                Tree->left = insertElement(Tree->left, Value);
            }
            else
            {
                if (Tree->right == NULL && Tree->left != NULL && Tree->left->data<Value)
                {
                    Tree->right = insertElement(Tree->right, Value);
                }
                else if (Tree->left == NULL && Tree->right != NULL && Tree->right->data > Value)
                {
                    Tree->left = insertElement(Tree->left, Value);
                }
                else
                {
                    if (Tree->right == NULL)
                    {
                        Tree->right = insertElement(Tree->right, Value);
                    }
                    Tree->left = insertElement(Tree->left, Value);
                }
            }
    }
    Tree->height = TreeGetHeight(Tree);

    return(Tree);
}

void PreOrder(CC_TREE *Tree, int Index, int *Value, int *IndexPreOrder)
{
    if (Tree == NULL)
    {
        return;
    }
    *IndexPreOrder = *IndexPreOrder + 1;
    if (*IndexPreOrder == Index)
    {
        *Value = Tree->data;
        return;
    }

    PreOrder(Tree->left, Index, Value, IndexPreOrder);
    PreOrder(Tree->right, Index, Value, IndexPreOrder);
    return;
}

void InOrder(CC_TREE *Tree, int Index, int *Value, int *IndexInOrder)
{
    if (Tree == NULL)
    {
        return;
    }
    InOrder(Tree->left, Index, Value, IndexInOrder);
    *IndexInOrder = *IndexInOrder + 1;
    if (*IndexInOrder == Index)
    {
        *Value = Tree->data;
        return;
    }
    InOrder(Tree->right, Index, Value, IndexInOrder);
    return;
}

void PostOrder(CC_TREE *Tree, int Index, int *Value, int *IndexPostOrder)
{
    if (Tree == NULL)
    {
        return;
    }
    PostOrder(Tree->left, Index, Value, IndexPostOrder);
    PostOrder(Tree->right, Index, Value, IndexPostOrder);
    *IndexPostOrder = *IndexPostOrder + 1;
    if (*IndexPostOrder == Index)
    {
        *Value = Tree->data;
        return;
    }
    return;
}
CC_TREE * smallestRightNode(CC_TREE * Tree)
{
    CC_TREE *currentNode = Tree;
    while (currentNode && currentNode->left != NULL)
    {
        currentNode = currentNode->left;
    }
    return currentNode;
}