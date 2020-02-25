#include "ccstack.h"
#include "common.h"
#include "stdlib.h"
#include "string.h"

#define INITIAL_SIZE 100

int StCreate(CC_STACK **Stack)
{
    CC_STACK *stk = NULL;

    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    stk = (CC_STACK*)malloc(sizeof(CC_STACK));
    if (NULL == stk)
    {
        return -1;
    }

    memset(stk, 0, sizeof(*stk));

    VecCreate(&stk->Vector);

    stk->Vector->Count = 0;
    stk->Vector->Size = INITIAL_SIZE;
    stk->Vector->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    if (NULL == stk->Vector->Array)
    {
        free(stk);
        return -1;
    }

    *Stack = stk;

    return 0;
}

int StDestroy(CC_STACK **Stack)
{

    CC_UNREFERENCED_PARAMETER(Stack);
    if (NULL == Stack)
    {
        return -1;
    }
    CC_STACK *stk = *Stack;
    free(stk);

    *Stack = NULL;

    return 0;
}

int StPush(CC_STACK *Stack, int Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }
    CC_VECTOR *vect = Stack->Vector;

    int retVal = VecInsertHead(vect, Value);

    return retVal;
}

int StPop(CC_STACK *Stack, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);
    if (NULL == Stack)
    {
        return -1;
    }

    CC_VECTOR *vec = NULL;
    VecCreate(&vec);

    *vec = *Stack->Vector;
    int foundVal = 0;
    int retVal = VecGetValueByIndex(vec, 0, &foundVal);
    int val = VecRemoveByIndex(vec, 0);

    *Value = foundVal;
    *Stack->Vector = *vec;

    VecDestroy(&vec);

    return retVal&&val;
}

int StPeek(CC_STACK *Stack, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }

    CC_VECTOR *vec = NULL;
    VecCreate(&vec);

    *vec = *Stack->Vector;
    int foundVal = 0;
    int retVal = VecGetValueByIndex(vec, 0, &foundVal);   
    *Value = foundVal;

    VecDestroy(&vec);

    return retVal;
}

int StIsEmpty(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    if (NULL == Stack) 
    {
        return -1;
    }

    if (Stack->Vector->Count == 0) 
    {
        return 1;
    }

    return 0;
    
    
}

int StGetCount(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack) {
        return -1;
    }

    return Stack->Vector->Count;
}

int StClear(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    if (NULL == Stack)
    {
        return -1;
    }

    free(&Stack->Vector->Array);
    Stack->Vector->Count = 0;

    return 0;
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(StackToPush);
    if (NULL == Stack || NULL == StackToPush)
    {
        return -1;
    }
    VecAppend(Stack->Vector, StackToPush->Vector);
    return 0;
}
