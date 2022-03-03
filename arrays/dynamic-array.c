#include <string.h>

//TODO - Write unit tests for functions

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
    if (arrayPtr -> size < newCapacity) {
        if (arrayPtr -> size == arrayPtr -> capacity) {

            upsizeArray(arrayPtr);

        } else if (arrayPtr -> size > newCapacity) {
            if (arrayPtr -> size < arrayPtr -> capacity / shrinkFactor) {

                downsizeArray(arrayPtr);
            }
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
    int *newData = realloc(arrayPtr -> data, sizeof(int) * newCapacity);

    arrayPtr -> data = newData;
    arrayPtr -> capacity = newCapacity;
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
