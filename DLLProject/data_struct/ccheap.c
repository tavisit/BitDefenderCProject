#include "ccheap.h"
#include "common.h"



int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
    CC_UNREFERENCED_PARAMETER(MaxHeap);
    CC_UNREFERENCED_PARAMETER(InitialElements);
    if (MaxHeap == NULL)
    {
        return -1;
    }  

    CC_HEAP *auxMaxHeap = *MaxHeap;
    auxMaxHeap = (CC_HEAP*)malloc(sizeof(CC_HEAP));

    if (auxMaxHeap == NULL)
    {
        return -1;
    }

    auxMaxHeap->Type = true;
    auxMaxHeap->Data = (int *)malloc(sizeof(int));
    auxMaxHeap->Size = 0;

    if (InitialElements != NULL)
    {
        
        
        for (int i = 0; i < InitialElements->Size; ++i)
        {
            HpInsert(auxMaxHeap, InitialElements->Array[i]);
        }
    }
    
    *MaxHeap = auxMaxHeap;
    
    if (MaxHeap == NULL)
    {
        return -1;
    }
    return 0;
}

int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements)
{
    CC_UNREFERENCED_PARAMETER(MinHeap);
    CC_UNREFERENCED_PARAMETER(InitialElements);

    if (MinHeap == NULL)
    {
        return -1;
    }

    CC_HEAP* auxMinHeap = *MinHeap;
    auxMinHeap = (CC_HEAP*)malloc(sizeof(CC_HEAP));

    if (auxMinHeap == NULL)
    {
        return -1;
    }
    
    auxMinHeap->Type = false;
    auxMinHeap->Data = (int *)malloc(sizeof(int));
    auxMinHeap->Size = 0;

    for (int i = 0; InitialElements != NULL && i < InitialElements->Size; ++i)
    {
        HpInsert(auxMinHeap, InitialElements->Array[i]);
    }
 

    *MinHeap = auxMinHeap;
    
    if (MinHeap == NULL)
    {
        return -1;
    }
    return 0;
}

int HpDestroy(CC_HEAP **Heap)
{
    CC_UNREFERENCED_PARAMETER(Heap);

    if (NULL == Heap)
    {
        return -1;
    }

    CC_HEAP *auxHeap;
    auxHeap = *Heap;
    free(auxHeap->Data);
    free(auxHeap);
    auxHeap = NULL;
    *Heap = auxHeap;

    return 0;
}

int HpInsert(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Heap == NULL)
    {
        return -1;
    }
    if (Heap->Data == NULL)
    {
        return -1;
    }

    CC_VECTOR *auxHeapVector;
    VecCreate(&auxHeapVector);
    int i;
    for (i = 0; i < Heap->Size; ++i)
    {
        int retval = VecInsertTail(auxHeapVector, Heap->Data[i]);
        if (retval == -1)
        {
            return -1;
        }
    }
    free(Heap->Data);
    Heap->Data = auxHeapVector->Array;
    Heap->Data[Heap->Size++] = Value;
    HeapifyUp(Heap, Heap->Size - 1);
    return 0;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Heap == NULL)
    {
        return -1;
    }
    if (&Value == NULL)
    {
        return -1;
    }    
    if (Heap->Size == 0)
    {
        return 0;
    }

    boolean countingFinished = true;
    while (countingFinished)
    {
        countingFinished = false;
        for (int i = 0; i < Heap->Size; ++i)
        {
            if (Heap->Data[i] == Value)
            {
                countingFinished = true;
                swapValues(&Heap->Data[i], &Heap->Data[--Heap->Size]);
                HeapifyUp(Heap, i);
                HeapifyDown(Heap, i);
                return 0;
            }
        }
    }
    return 0;
}

int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);
    if (Heap == NULL) {
        return -1;
    }
    if(ExtremeValue == NULL)
    {
        return -1;
    }
    if (Heap->Size == 0)
    {
        return -1;
    }
    *ExtremeValue = Heap->Data[0];
    return 0;
}

int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);
    if (Heap == NULL) 
    {
        return -1;
    }
    if (ExtremeValue == NULL)
    {
        return -1;
    }
    if(Heap->Size == 0)
    {
        return -1;
    }
    *ExtremeValue = Heap->Data[0];
    swapValues(&Heap->Data[0], &Heap->Data[--Heap->Size]);
    HeapifyDown(Heap, 0);
    return 0;
}

int HpGetElementCount(CC_HEAP *Heap)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    if (Heap == NULL)
    {
        return -1;
    }

    return Heap->Size;
}

int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(SortedVector);
    if (Heap == NULL || SortedVector == NULL)
    {
        return -1;
    }
    if (Heap->Size == 0)
    {

        return 0;
    }


    while (HpGetElementCount(Heap) != 0)
    {
        int popValue, retVal;
        retVal = HpPopExtreme(Heap, &popValue);
        if (retVal == -1)
        {
            return -1;
        }

        if (Heap->Type == false)
        {
            VecInsertTail(SortedVector, popValue);
        }
        if (Heap->Type == true)
        {
            VecInsertHead(SortedVector, popValue);
        }
    }

    for (int i = 0; i < SortedVector->Size; ++i)
    {
        HpInsert(Heap, SortedVector->Array[i]);
    }

    return 0;
}

void HeapifyDown(CC_HEAP *heap, int Position) {


    int nextElement = 0;
    while (nextElement != -1)
    {
        nextElement = -1;
        if ((Position << 1) + 1 < heap->Size)
        {
            nextElement = (Position << 1) + 1;
            if (heapifyDown(<) && heap->Type == false)
            {
                nextElement = (Position << 1) + 2;
            }
            if (heapifyDown(>) && heap->Type == true)
            {
                nextElement = (Position << 1) + 2;
            }
            if (heap->Data[nextElement] < heap->Data[Position])
            {
                nextElement = -1;
            }
        }
        if (nextElement != -1)
        {
            swapValues(&heap->Data[nextElement], &heap->Data[Position]);
            Position = nextElement;
        }
    }
    
}
void HeapifyUp(CC_HEAP *heap, int Position) {

    if (heap == NULL)
    {
        return;
    }

    while (heapifyUp(< )&&heap->Type == false)
    {
        swapValues(&heap->Data[Position], &heap->Data[(Position - 1) >> 1]);
        Position = (Position - 1) >> 1;
    }
    
    while (heapifyUp(>) && heap->Type == true)
    {
        swapValues(&heap->Data[Position], &heap->Data[(Position - 1) >> 1]);
        Position = (Position - 1) >> 1;
    }
    
}