#include "stdio.h"
#include "stdlib.h"
#include "dynamic-array.h"
#include "dynamic-array.c"

//TODO - Implement a more thorough demonstration that utilizes all functions and shows the dynamic implementation in action

int main(void) {
    int desiredCapacity;

    printf("How many numbers would you like to store?\n");

    scanf("%d", &desiredCapacity);

    dArray* arrayPtr = newDynamicArray(desiredCapacity);

    for(int i = 0; i <= desiredCapacity; i++) {
        push(arrayPtr, i);
    }

    printf("Current Numbers\n");

    for(int i = 0; i < arrayPtr->size - 1; i++) {
        printf("Number %d is at index %d\n", *(arrayPtr->data + (i + 1)), i);
    }

    return 0;
}
