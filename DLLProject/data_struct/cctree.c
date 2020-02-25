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

    if (Tr->left != NULL)TreeDestroy(&Tr->left);
    if (Tr->right != NULL)TreeDestroy(&Tr->right);

    free(Tr->left);
    free(Tr->right);

    Tr->left = NULL;
    Tr->right = NULL;


    free(Tr);

    *Tree = NULL;


    return 0;
}

int TreeInsert(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

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



    if (&Value == NULL)
    {
        return -1;
    }
    if (Tree->left == NULL && Tree->right == NULL)
    {
        int retVal = TreeClear(Tree);
        return retVal;
    }
    else
    {
        Tree = removeElement(Tree, Value);
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
        return -1;
    }
    if (Tree->data == Value)
    {
        return 1;
    }
    else
    {
        if (Tree->data > Value && Tree->left != NULL)
        {
            return TreeContains(Tree->left, Value);

        }
        else if (Tree->data < Value && Tree->right != NULL)
        {
            return TreeContains(Tree->right, Value);
        }
        else
        {
            return 0;
        }
    }

}

int TreeGetCount(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    if (NULL == Tree)
    {
        return -1;
    }
    if (Tree->data == INT_MIN)
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

    TreeDestroy(&Tree);
    TreeCreate(&Tree);

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

    static int count = 0;
    if (count <= Index) {

        count++;

        if (count == Index)
        {
            *Value = Tree->data;
        }

        TreeGetNthInorder(Tree->left, Index, Value);

        TreeGetNthInorder(Tree->right, Index, Value);
    }
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

    static int count = 0;
    if (count <= Index) {

        TreeGetNthInorder(Tree->left, Index, Value);
        count++;

        if (count == Index)
        {
            *Value = Tree->data;
        }

        TreeGetNthInorder(Tree->right, Index, Value);
    }

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

    static int count = 0;
    if (count <= Index) {

        TreeGetNthInorder(Tree->left, Index, Value);
        TreeGetNthInorder(Tree->right, Index, Value);
        count++;

        if (count == Index)
        {
            *Value = Tree->data;
        }
    }
    return 0;
}

unsigned int CountingNodes(CC_TREE *Tree)
{
    unsigned int count = 1;
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
                //data to be deleted is found
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
    if (Tree == NULL)
    {
        Tree = (CC_TREE*)malloc(sizeof(CC_TREE));
        Tree->data = Value;
        Tree->left = NULL;
        Tree->right = NULL;
        return Tree;
    }
    else if (Tree->data == INT_MIN)
    {
        Tree->data = Value;
        return (Tree);
    }
    else
    {
        if (Value > Tree->data)
        {
            Tree->right = insertElement(Tree->right, Value);
        }
        else
            if (Value < Tree->data)
            {
                Tree->left = insertElement(Tree->left, Value);
            }
    }
    Tree->height = TreeGetHeight(Tree);

    return(Tree);
}