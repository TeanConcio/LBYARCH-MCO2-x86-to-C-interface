// Tean Concio XX22
// Nicole Ong S11

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>



// Dot Product function in x86_64 Assembly
extern void asmDotProduct();



// Dot Product function in C
float cDotProduct(int vectorSize, float* vectorA, float* vectorB) {

    float sdot = 0;

    // For vectorSize, total the product of elements in Vector A and B
    for (int i = 0; i < vectorSize; i++)
        sdot += vectorA[i] * vectorB[i];

    return sdot;
}



// Main
int main()
{
    // Initialize Variables
    int n = 5;
    float vectorA[5] = { 1, 2, 3, 4, 5 };
    float vectorB[5] = { 6, 7, 8, 9, 0 };
    float sdot = 0;

    // Time Function Call
    clock_t startTime = clock();
    sdot = cDotProduct(n, vectorA, vectorB);
    double time_taken = ((double)(clock() - startTime)) / CLOCKS_PER_SEC;

    // Print Outputs
    printf("%f\n", sdot);
    printf("%lf\n", time_taken);

    return 0;
}
