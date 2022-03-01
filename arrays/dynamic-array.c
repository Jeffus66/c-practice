#include <string.h>

//TODO - Add more error handling to functions that need it. ie: check pointer addresses are valid, guard against index out ouf bounds.
//TODO - Write unit tests for functions and implement any helper methods needed

dArray* newDynamicArray(int capacity) {
    int trueCapacity = determineTrueCapacity(capacity);

    dArray *array = malloc(sizeof(dArray));
    array->size = 0;
    array->capacity = trueCapacity;
    array->data = malloc(sizeof(int) * trueCapacity);

    return array;
}

int determineTrueCapacity(int capacity) {
    int trueCapacity = minimumCapacity;

    if(capacity > trueCapacity) {
        for(int i = 16; i < capacity; i *= growthFactor) {
            trueCapacity = trueCapacity * growthFactor;
        }
    }
    return trueCapacity;
}

int size(dArray *arrayPtr) {
    return arrayPtr->size;
}

int capacity(dArray *arrayPtr) {
    return arrayPtr->capacity;
}

bool isEmpty(dArray *arrayPtr) {
    return arrayPtr->size == 0;
}

int at(dArray *arrayPtr, int index) {
    return *(arrayPtr->data + index);
}

void resizeArray(dArray *arrayPtr, int newCapacity) {
    if(arrayPtr->size < newCapacity) {

        if(arrayPtr->size == arrayPtr->capacity) {

            upsizeArray(arrayPtr);

        } else if (arrayPtr->size > newCapacity) {

            if(arrayPtr->size < arrayPtr->capacity / shrinkFactor) {

                downsizeArray(arrayPtr);
            }
        }
    }
}

void upsizeArray(dArray *arrayPtr) {
    int newCapacity = determineTrueCapacity(arrayPtr->capacity + 1);

    int *newData = realloc(arrayPtr->data, sizeof (int) * newCapacity);

    arrayPtr->data = newData;

    arrayPtr->capacity = newCapacity;
}

void downsizeArray(dArray *arrayPtr) {
    int newCapacity = arrayPtr->capacity / growthFactor;

    int *newData = realloc(arrayPtr->data, sizeof(int) * newCapacity);

    arrayPtr->data = newData;

    arrayPtr->capacity = newCapacity;
}

void push(dArray *arrayPtr, int value) {
    resizeArray(arrayPtr, arrayPtr->size + 1);

    *(arrayPtr->data + arrayPtr->size) = value;

    arrayPtr->size++;
}

void insertValue(dArray *arrayPtr, int index, int value) {
    resizeArray(arrayPtr, arrayPtr->size + 1);

    memmove( arrayPtr->data + index + 1, arrayPtr->data + index, sizeof(int) * (arrayPtr->size - index));

    *(arrayPtr->data + index) = value;

    arrayPtr->size++;
}

void prepend(dArray *arrayPtr, int value) {
    insertValue(arrayPtr, 0, value);
}

int pop(dArray *arrayPtr) {
    resizeArray(arrayPtr, arrayPtr->size - 1);

    int lastValue = *(arrayPtr->data + (arrayPtr->size - 1));

    arrayPtr->size--;

    return lastValue;
}

void deleteAt(dArray *arrayPtr, int index) {
    resizeArray(arrayPtr, arrayPtr->size  - 1);

    memmove(arrayPtr->data + index, arrayPtr->data + index + 1, sizeof(int) * (arrayPtr->size - index));

    arrayPtr->size--;
}

void removeValue(dArray *arrayPtr, int value) {
    for(int i = 0; i < arrayPtr->size; i++) {
        int arrayValue = *(arrayPtr->data + i);

        if(arrayValue == value) {
            deleteAt(arrayPtr, i);
        }
    }
}

int findValue(dArray *arrayPtr, int value) {
    int indexWithValue = -1;

    for(int i = 0; i < arrayPtr->size; i++) {
        int arrayValue  = *(arrayPtr->data + i);

        if(arrayValue == value) {
            indexWithValue = i;
            break;
        }
    }

    return indexWithValue;
}


