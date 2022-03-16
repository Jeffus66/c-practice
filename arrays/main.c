#include "stdio.h"
#include "stdlib.h"
#include "dynamic-array.h"
#include "dynamic-array.c"

void userDemo();
void runTests();

int main(void) {
    runTests();

    userDemo();

    return 0;
}

void userDemo() {
    int desiredCapacity;
    int userValueChoice;
    int userIndexChoice;

    printf("User Demo\n");

    printf("How many values would you like to store?\n");

    scanf("%d", & desiredCapacity);

    dArray* arrayPtr = newDynamicArray(desiredCapacity);

    printf("Pushing values into array\n");

    addValuesToArray(arrayPtr, desiredCapacity);

    printf("Check and make sure the array got filled\n");

    printf("Array is empty = %s\n\n", isEmpty(arrayPtr) ? "true" : "false");

    printArrayValues(arrayPtr);

    printf("Enter an index to print its value\n");

    scanf("%d", & userIndexChoice);

    printf("The value at index %d is %d\n", userIndexChoice, at(arrayPtr, userIndexChoice));

    printf("Enter a value to insert into the array\n");

    scanf("%d", & userValueChoice);

    printf("Now enter the index where you would like to put the value\n");

    scanf("%d", & userIndexChoice);

    printf("Inserting %d at index %d\n\n", userValueChoice, userIndexChoice);

    insertValue(arrayPtr, userIndexChoice, userValueChoice);

    printArrayValues(arrayPtr);

    printf("Enter a value to place at the front of the array\n");

    scanf("%d", & userValueChoice);

    printf("Placing %d at the beginning of the array\n\n", userValueChoice);

    prepend(arrayPtr, userValueChoice);

    printArrayValues(arrayPtr);

    printf("Automatically popping the last value\n\n");

    pop(arrayPtr);

    printArrayValues(arrayPtr);

    printf("Enter an index corresponding to a value you would like to delete\n");

    scanf("%d", & userIndexChoice);

    printf("Removing %d at index %d\n\n", at(arrayPtr, userIndexChoice), userIndexChoice);

    deleteAt(arrayPtr, userIndexChoice);

    printArrayValues(arrayPtr);

    printf("Enter a value you would like to remove from the array\n");

    scanf("%d", & userValueChoice);

    printf("Removing %d from index %d\n\n", userValueChoice, findValue(arrayPtr, userValueChoice));

    removeValue(arrayPtr, userValueChoice);

    printArrayValues(arrayPtr);

    printf("Lastly, enter a value to find in the array(will return first occurrence)\n");

    scanf("%d", & userValueChoice);

    printf("Value %d is at index %d", userValueChoice, findValue(arrayPtr, userValueChoice));
}

void runTests() {
    printf("Running Tests\n");

    testNewDynamicArray();
    testDetermineTrueCapacity();
    testSize();
    testCapacity();
    testIsEmpty();
    testAt();
    testResizeArray();
    testUpsizeArray();
    testDownsizeArray();
    testPushValue();
    testInsertValue();
    testPrepend();
    testPop();
    testDeleteAt();
    testRemoveValue();
    testFindValue();

    printf("Tests Successful\n\n");
}
