#ifndef C_PRACTICE_DYNAMIC_ARRAY_H
#define C_PRACTICE_DYNAMIC_ARRAY_H

#include <stdbool.h>

const int minimumCapacity = 16;
const int growthFactor = 2;
const int shrinkFactor = 4;

typedef struct dynamicArray {
    int size;
    int capacity;
    int *data;
} dArray;

// Creates a new dynamicArray with capacity to hold the requested amount of values.
dArray* newDynamicArray(int capacity);

// Calculates capacity based on an established minimum capacity/growthFactor and how many values the user would like to store.
int determineTrueCapacity(int capacity);

// Returns the number of values in the passed in array.
int size(dArray *arrayPtr);

// Returns the total capacity of the passed in array.
int capacity(dArray *arrayPtr);

// Checks that the passed in array has at least one value.
bool isEmpty(dArray *arrayPtr);

// Returns the value at the passed in index.
// If the passed in index is invalid, it returns an error message and exits.
int at(dArray *arrayPtr, int index);

// Determines if the passed in array needs to grow or shrink based on the requested newCapacity.
void resizeArray(dArray *arrayPtr, int newCapacity);

// Increases the capacity of the passed in array. Capacity is determined by calling determineTrueCapacity().
void upsizeArray(dArray *arrayPtr);

// Decreases the capacity of the passed in array. Capacity is determined by halving the current capacity.
void downsizeArray(dArray *arrayPtr);

// Adds the passed in value to the end of the passed in array.
// Determines if the array needs to be resized first and upsizes it if so.
void pushValue(dArray *arrayPtr, int value);

// Inserts desired value at the specified index by shifting the existing value at that index and all values after it to the right.
// Array resizes if needed.
// Will return an error if the passed in index is invalid.
void insertValue(dArray *arrayPtr, int index, int value);

// Places the passed in value at the start of the passed in array
void prepend(dArray *arrayPtr, int value);

// Removes the last value from the passed in array
// Determines if the array needs to shrink and reduces the capacity if so.
// Returns the value that was removed
int pop(dArray *arrayPtr);

// Deletes the value at the specified index by shifting all elements to the right of the index to the left.
// Downsizes if needed
void deleteAt(dArray *arrayPtr, int index);

// Removes the passed in value by locating it in the array then calling deleteAt()
// Returns error message if the value is not found
void removeValue(dArray *arrayPtr, int value);

// Returns the index of the passed in value
int findValue(dArray *arrayPtr, int value);

// Checks to make sure memory was allocated successfully. Exits if not
void validateMemory(void *ptr);

// Adds the passed in number of values to the array utilizing pushValue.
void addValuesToArray(dArray *arrayPtr, int desiredCapacity);

// Prints array values and their indices as well as the current size and capacity values.
void printArrayValues(dArray *arrayPtr);

// Used for unit tests, frees the passed in array data and array
void destroyArray(dArray *arrayPtr);

//Unit tests
void testNewDynamicArray();
void testDetermineTrueCapacity();
void testSize();
void testCapacity();
void testIsEmpty();
void testAt();
void testResizeArray();
void testUpsizeArray();
void testDownsizeArray();
void testPushValue();
void testInsertValue();
void testPrepend();
void testPop();
void testDeleteAt();
void testRemoveValue();
void testFindValue();

#endif //C_PRACTICE_DYNAMIC_ARRAY_H
