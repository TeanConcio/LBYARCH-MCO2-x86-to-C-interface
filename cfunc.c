//#include <stdio.h>



// Dot Product Function in C
float cDotProduct(int vectorSize, float* vectorA, float* vectorB) {

    float sdot = 0;

    // For vectorSize, total the product of elements in Vector A and B
    for (int i = 0; i < vectorSize; i++)
        sdot += vectorA[i] * vectorB[i];

    return sdot;
}