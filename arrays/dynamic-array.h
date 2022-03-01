#ifndef C_PRACTICE_DYNAMIC_ARRAY_H
#define C_PRACTICE_DYNAMIC_ARRAY_H

#include <stdbool.h>

//TODO - Add comments describing function logic
//TODO - Add additional functions for user demonstration if needed. ie: function to print the values in the array

const int minimumCapacity = 16;
const int growthFactor = 2;
const int shrinkFactor = 4;

typedef struct dynamicArray {
    int size;
    int capacity;
    int *data;
} dArray;

dArray* newDynamicArray(int capacity);

int determineTrueCapacity(int capacity);

int size(dArray *arrayPtr);

int capacity(dArray *arrayPtr);

bool isEmpty(dArray *arrayPtr);

int at(dArray *arrayPtr, int index);

void resizeArray(dArray *arrayPtr, int newCapacity);

void upsizeArray(dArray *arrayPtr);

void downsizeArray(dArray *arrayPtr);

void pushValue(dArray *arrayPtr, int value);

void insertValue(dArray *arrayPtr, int index, int value);

void prepend(dArray *arrayPtr, int value);

int pop(dArray *arrayPtr);

void deleteAt(dArray *arrayPtr, int index);

void removeValue(dArray *arrayPtr, int value);

int findValue(dArray *arrayPtr, int value);

#endif //C_PRACTICE_DYNAMIC_ARRAY_H
