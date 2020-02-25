#include "ccvector.h"
#include "common.h"
#include "string.h"
#include "stdlib.h"

#define INITIAL_SIZE    100

int VecCreate(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = NULL;

    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
    if (NULL == vec)
    {
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc( sizeof(int) * INITIAL_SIZE );
    if (NULL == vec->Array) 
    {
        free(vec);
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    

    if (NULL == Vector)
    {
        return -1;
    }
    CC_VECTOR *vec = *Vector;
    free(vec);

    *Vector = NULL;

    return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }
    if (NULL == &Value)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        Vector->Array = realloc(Vector->Array, sizeof(int)*(Vector->Count + 1));
        return -1;
    }

    Vector->Array[Vector->Count] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }
    if (NULL == &Value)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        Vector->Array = realloc(Vector->Array, sizeof(int)*(Vector->Count + 1));
        return -1;
    }

    for (int i = Vector->Count-1; i >= 0; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }
    if (&Value == NULL)
    {
        return -1;
    }
    if (&Index == NULL)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        Vector->Array = realloc(Vector->Array, sizeof(int)*(Vector->Count + 1));
        return -1;
    }
    if (Index == -1) {
        int retVal = VecInsertHead(Vector, Value);
        return retVal;
    }
    if (Index == Vector->Count) {
        int retVal = VecInsertTail(Vector, Value);
        return retVal;
    }

    if (!indexValid(Index, Vector->Count)) return -1;

    for (int i = Vector->Count; i > Index + 1; i--)
    {
        Vector->Array[i] = Vector->Array[i-1];
    }
    Vector->Array[Index+1] = Value;
    Vector->Count++;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    
    if (NULL == Vector)
    {
        return -1;
    }
    if (&Index == NULL)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        Vector->Array = realloc(Vector->Array, sizeof(int)*(Vector->Count + 1));
        return -1;
    }

    if (!indexValid(Index, Vector->Count)) return -1;


    for (int i = Index; i < Vector->Count-1; i++)
    {
        Vector->Array[i] = Vector->Array[i+1];
    }
    Vector->Count--;

    return 0;

}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }
    if (Value == NULL)
    {
        return -1;
    }
    if (&Index == NULL)
    {
        return -1;
    }

    if (!indexValid(Index, Vector->Count)) return -1;

    int temp = Vector->Array[Index];
    *Value = temp;

    return 0;
}


int VecGetCount(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    if (NULL == Vector)
    {
        return -1;
    }
    if (Vector->Count >= Vector->Size)
    {
        Vector->Array = realloc(Vector->Array, sizeof(int)*(Vector->Count + 1));
        return -1;
    }

    return Vector->Count;
}

int VecClear(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    
    if (NULL == Vector) {
        return -1;
    }

    free(Vector->Array);
    Vector->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    Vector->Count = 0;
    
    return Vector->Count;
}

int VecSort(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    if (NULL == Vector) {
        return -1;
    }
    if (Vector->Count >= Vector->Size)
    {
        Vector->Array = realloc(Vector->Array, sizeof(int)*(Vector->Count + 1));
        return -1;
    }
    sortCCVector(Vector->Array, 0, Vector->Size-1);
    reverseVector(Vector->Array,0,Vector->Size);
    return 0;
}

int VecAppend(CC_VECTOR *DestVector, CC_VECTOR *SrcVector)
{
    CC_UNREFERENCED_PARAMETER(DestVector);
    CC_UNREFERENCED_PARAMETER(SrcVector);
    if (DestVector->Count >= DestVector->Count+SrcVector->Count)
    {
        DestVector->Array = realloc(DestVector->Array, sizeof(int)*(DestVector->Count + SrcVector->Count));
        return -1;
    }

    for (int i = 0; i < SrcVector->Size; i++) {
        DestVector->Array[i + DestVector->Count] = SrcVector->Array[i];
    }
    DestVector->Count += SrcVector->Count;

    return 0;
}

