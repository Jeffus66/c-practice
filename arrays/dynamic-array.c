#include <string.h>
#include <assert.h>

dArray* newDynamicArray(int capacity) {
    int trueCapacity = determineTrueCapacity(capacity);

    dArray *array = malloc(sizeof(dArray));

    validateMemory(array);

    array -> size = 0;
    array -> capacity = trueCapacity;
    array -> data = malloc(sizeof(int) * trueCapacity);

    validateMemory(array -> data);

    return array;
}

int determineTrueCapacity(int capacity) {
    int trueCapacity = minimumCapacity;

    if (capacity > trueCapacity) {
        for (int i = 16; i < capacity; i *= growthFactor) {
            trueCapacity *= growthFactor;
        }
    }

    return trueCapacity;
}

int size(dArray *arrayPtr) {
    return arrayPtr -> size;
}

int capacity(dArray *arrayPtr) {
    return arrayPtr -> capacity;
}

bool isEmpty(dArray *arrayPtr) {
    return arrayPtr -> size == 0;
}

int at(dArray *arrayPtr, int index) {
    if (index >= arrayPtr -> size || index < 0) {
        printf("Error: Invalid Index");
        exit(EXIT_FAILURE);
    }

    return *(arrayPtr -> data + index);
}

void resizeArray(dArray *arrayPtr, int newCapacity) {
    if (arrayPtr->size < newCapacity) {
        if (arrayPtr->size == arrayPtr->capacity) {

            upsizeArray(arrayPtr);
        }
    } else if (arrayPtr->size > newCapacity) {
        if (arrayPtr->size < arrayPtr->capacity / shrinkFactor) {

            downsizeArray(arrayPtr);
        }
    }
}

void upsizeArray(dArray *arrayPtr) {
    int newCapacity = determineTrueCapacity(arrayPtr -> capacity + 1);
    int *newData = realloc(arrayPtr -> data, sizeof(int) * newCapacity);

    arrayPtr -> data = newData;
    arrayPtr -> capacity = newCapacity;
}

void downsizeArray(dArray *arrayPtr) {
    int newCapacity = arrayPtr -> capacity / growthFactor;

    if(newCapacity < minimumCapacity) {
        newCapacity = minimumCapacity;
    }

    if (newCapacity != arrayPtr->capacity) {
        int *newData = realloc(arrayPtr->data, sizeof(int) * newCapacity);

        arrayPtr->data = newData;
        arrayPtr->capacity = newCapacity;
    }
}

void pushValue(dArray *arrayPtr, int value) {
    resizeArray(arrayPtr, arrayPtr -> size + 1);

    *(arrayPtr -> data + arrayPtr -> size) = value;
    arrayPtr -> size++;
}

void insertValue(dArray *arrayPtr, int index, int value) {
    if (index > arrayPtr -> size || index < 0) {
        printf("Error: Invalid Index\n");
        exit(EXIT_FAILURE);
    }

    resizeArray(arrayPtr, arrayPtr -> size + 1);
    memmove(arrayPtr -> data + index + 1, arrayPtr -> data + index, sizeof(int) * (arrayPtr -> size - index));

    *(arrayPtr -> data + index) = value;
    arrayPtr -> size++;
}

void prepend(dArray *arrayPtr, int value) {
    insertValue(arrayPtr, 0, value);
}

int pop(dArray *arrayPtr) {
    resizeArray(arrayPtr, arrayPtr -> size - 1);

    int lastValue = * (arrayPtr -> data + (arrayPtr -> size - 1));
    arrayPtr -> size--;

    return lastValue;
}

void deleteAt(dArray *arrayPtr, int index) {
    if (index > arrayPtr -> size || index < 0) {
        printf("Error: Invalid Index\n");
        exit(EXIT_FAILURE);
    }

    resizeArray(arrayPtr, arrayPtr -> size - 1);
    memmove(arrayPtr -> data + index, arrayPtr -> data + index + 1, sizeof(int) * (arrayPtr -> size - index));

    arrayPtr -> size--;
}

void removeValue(dArray *arrayPtr, int value) {
    bool valueFound = false;

    for (int i = 0; i < arrayPtr -> size; i++) {
        int arrayValue = *(arrayPtr -> data + i);

        if (arrayValue == value) {
            deleteAt(arrayPtr, i);
            valueFound = true;
            arrayPtr -> size--;
        }
    }

    if (!valueFound) {
        printf("Error: Value not found\n");
    }
}

int findValue(dArray *arrayPtr, int value) {
    int indexWithValue = -1;

    for (int i = 0; i < arrayPtr -> size; i++) {
        int arrayValue = * (arrayPtr -> data + i);

        if (arrayValue == value) {
            indexWithValue = i;
            break;
        }
    }

    return indexWithValue;
}

void validateMemory(void *ptr) {
    if (ptr == NULL) {
        printf("Error Allocating Memory\n");
        exit(EXIT_FAILURE);
    }
}

void addValuesToArray(dArray *arrayPtr, int desiredCapacity) {
    for (int i = 1; i <= desiredCapacity; i++) {
        pushValue(arrayPtr, i);
    }
}

void printArrayValues(dArray *arrayPtr) {
    printf("Current Array Status\n");

    for (int i = 0; i < arrayPtr -> size; i++) {
        printf("%d is at index %d\n", *(arrayPtr -> data + i), i);
    }

    printf("Size of the array is %d\n", size(arrayPtr));
    printf("Capacity of the array is %d\n\n", capacity(arrayPtr));
}

void destroyArray(dArray *arrayPtr) {
    free(arrayPtr -> data);
    free(arrayPtr);
}

void testNewDynamicArray() {
    printf("Testing newDynamicArray()\n");

    dArray* arrayPtr = newDynamicArray(10);

    assert(arrayPtr -> size == 0);
    assert(arrayPtr -> capacity == 16);

    destroyArray(arrayPtr);
}

void testDetermineTrueCapacity() {
    printf("Testing determineTrueCapacity()\n");
    int result;

    result = determineTrueCapacity(10);
    assert(result == 16);

    result = determineTrueCapacity(20);
    assert(result == 32);
}

void testSize() {
    printf("Testing size()\n");

    dArray* arrayPtr = newDynamicArray(10);
    pushValue(arrayPtr,1);

    int result = size(arrayPtr);
    assert(result == 1);

    destroyArray(arrayPtr);
}

void testCapacity() {
    printf("Testing capacity()\n");

    dArray* arrayPtr = newDynamicArray(10);

    int result = capacity(arrayPtr);
    assert(result == 16);

    destroyArray(arrayPtr);
}

void testIsEmpty() {
    printf("Testing isEmpty()\n");
    dArray* arrayPtr;
    bool result;

    arrayPtr = newDynamicArray(10);

    result = isEmpty(arrayPtr);
    assert(result == true);

    destroyArray(arrayPtr);

    arrayPtr = newDynamicArray(10);

    pushValue(arrayPtr,1);
    result = isEmpty(arrayPtr);
    assert(result == false);

    destroyArray(arrayPtr);
}

void testAt() {
    printf("Testing at()\n");

    dArray* arrayPtr = newDynamicArray(10);

    pushValue(arrayPtr,1);
    pushValue(arrayPtr, 2);

    int result = at(arrayPtr, 1);

    assert(result == 2);

    destroyArray(arrayPtr);
}

void testResizeArray() {
    printf("Testing resizeArray()\n");

    dArray* arrayPtr;

    arrayPtr= newDynamicArray(16);
    assert(arrayPtr -> capacity == 16);

    for(int i = 0; i < 16; i++) {
        pushValue(arrayPtr, i + 1);
    }

    resizeArray(arrayPtr, 17);

    assert(arrayPtr -> capacity == 32);

    destroyArray(arrayPtr);

    arrayPtr = newDynamicArray(32);

    for(int i = 0; i < 5; i++) {
        pushValue(arrayPtr, i + 1);
    }
    assert(arrayPtr -> capacity == 32);

    resizeArray(arrayPtr, 4);

    assert(arrayPtr -> capacity == 16);

    destroyArray(arrayPtr);
}

void testUpsizeArray() {
    printf("Testing upsizeArray()\n");

    dArray* arrayPtr = newDynamicArray(16);

    for(int i = 0; i < 16; i++) {
        pushValue(arrayPtr, i + 1);
    }

    upsizeArray(arrayPtr);

    assert(arrayPtr -> capacity == 32);
    assert(*(arrayPtr -> data + 1) == 2);

    destroyArray(arrayPtr);
}

void testDownsizeArray() {
    printf("Testing downsizeArray()\n");

    dArray* arrayPtr = newDynamicArray(32);

    for(int i = 0; i < 3; i++) {
        pushValue(arrayPtr, i + 1);
    }

    downsizeArray(arrayPtr);

    assert(arrayPtr -> capacity == 16);
    assert(*(arrayPtr -> data + 1) == 2);

    destroyArray(arrayPtr);
}

void testPushValue() {
    printf("Testing pushValue()\n");

    dArray* arrayPtr = newDynamicArray(16);

    pushValue(arrayPtr, 1);

    assert(*(arrayPtr -> data) == 1);
    assert(arrayPtr -> size == 1);
    assert(arrayPtr -> capacity == 16);

    destroyArray(arrayPtr);
}

void testInsertValue() {
    printf("Testing insertValue()\n");

    dArray* arrayPtr = newDynamicArray(16);

    for(int i = 0; i < 4; i++) {
        pushValue(arrayPtr, i + 1);
    }

    assert(*(arrayPtr -> data + 2) == 3);

    insertValue(arrayPtr, 2, 66);

    assert(*(arrayPtr -> data + 2) == 66);

    destroyArray(arrayPtr);
}

void testPrepend() {
    printf("Testing prepend()\n");

    dArray* arrayPtr = newDynamicArray(16);

    for(int i = 0; i < 4; i++) {
        pushValue(arrayPtr, i + 1);
    }

    assert(*(arrayPtr -> data) == 1);

    prepend(arrayPtr, 66);

    assert(*(arrayPtr -> data) == 66);

    destroyArray(arrayPtr);
}

void testPop() {
    printf("Testing pop()\n");

    dArray* arrayPtr = newDynamicArray(16);

    for(int i = 0; i < 4; i++) {
        pushValue(arrayPtr, i + 1);
    }

    assert(arrayPtr -> size == 4);

    int result = pop(arrayPtr);

    assert(result == 4);
    assert(arrayPtr -> size == 3);

    destroyArray(arrayPtr);
}

void testDeleteAt() {
    printf("Testing deleteAt()\n");

    dArray* arrayPtr = newDynamicArray(16);

    for(int i = 0; i < 4; i++) {
        pushValue(arrayPtr, i + 1);
    }

    assert(arrayPtr -> size == 4);
    assert(*(arrayPtr -> data + 1) == 2);

    deleteAt(arrayPtr, 1);

    assert(arrayPtr -> size == 3);
    assert(*(arrayPtr -> data + 1) == 3);

    destroyArray(arrayPtr);
}

void testRemoveValue() {
    printf("Testing removeValue()\n");

    dArray* arrayPtr = newDynamicArray(16);

    for(int i = 0; i < 4; i++) {
        pushValue(arrayPtr, 2);
    }

    pushValue(arrayPtr, 5);

    assert(arrayPtr -> size == 5);

    removeValue(arrayPtr, 2);

    assert(arrayPtr -> size == 1);

    destroyArray(arrayPtr);
}

void testFindValue() {
    printf("Testing findValue()\n");

    dArray* arrayPtr = newDynamicArray(16);

    for(int i = 0; i < 4; i++) {
        pushValue(arrayPtr, i + 1);
    }

    assert(*(arrayPtr -> data + 1) == 2);

    int result = findValue(arrayPtr, 2);

    assert(result == 1);

    destroyArray(arrayPtr);
}