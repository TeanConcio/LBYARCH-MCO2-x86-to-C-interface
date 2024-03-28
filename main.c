// Tean Concio XX22
// Nicole Ong S11



// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>



// Constants
#define DEBUG_MODE 0

#define TWO_DEBUG 16
#define MAX_FLOAT 100.0



// Import C Dot Product Function
#include "cfunc.c"



// Import x86_64 Assembly Dot Product Function
extern float asmDotProduct(int vectorSize, float* vectorA, float* vectorB);



// Generate Random Values into Vector
void generateRandomVector(int vectorSize, float* vector) {

    // Debug
    if (DEBUG_MODE == 1) {
        for (int i = 0; i < TWO_DEBUG; i++)
            vector[i] = i * 10 + i + i * 0.1 + i * 0.01;
        return;
    }
    

    int powCounter = 0;
    int pow2 = 1;

    for (int i = 0; i < vectorSize; i++) {
        
        //vector[i] = RAND_MAX * (float)rand() / RAND_MAX;
        vector[i] = (float)rand() / (float)(RAND_MAX / (MAX_FLOAT * 2));
        vector[i] = (int)(vector[i] * MAX_FLOAT) / MAX_FLOAT;
        vector[i] -= MAX_FLOAT;
        
        // Check Progress
        if (i == pow2 - 1) {
            printf("%i (%i), ", pow2, powCounter);

            powCounter++;
            pow2 *= 2;
        }
    }
}



// Display Vector for Debugging
void printVector(int vectorSize, float* vector) {

    printf("{ ");

    for (int i = 0; i < vectorSize - 1; i++) {

        printf("%f, ", vector[i]);
    }

    printf("%f }\n", vector[vectorSize - 1]);
}



// Main
int main()
{
    // Initialize Variables
    int n = 0;
    float* vectorA = (float*)malloc((int)pow(2, 28) * sizeof(float));
    float* vectorB = (float*)malloc((int)pow(2, 28) * sizeof(float));
    float sdot = 0;

    // Time Variables
    clock_t startTime;
    double timeTaken;

    // Randomize Vectors
    srand((unsigned int)time(NULL));
    printf("Generating Vector A...\n");
    generateRandomVector((int)pow(2, 28), vectorA);
    printf("Vector A Generated\n\n");
    printf("Generating Vector B...\n");
    generateRandomVector((int)pow(2, 28), vectorB);
    printf("Vector B Generated\n\n");



    if (DEBUG_MODE == 1) {

        printf("Vector A: ");
        printVector(TWO_DEBUG, vectorA);
        printf("Vector B: ");
        printVector(TWO_DEBUG, vectorB);
        printf("\n");

        printf("---------- ---------- ---------- ----------\n");

        printf("\nCase 0 (Debug) : Vector Size n = %i\n\n", TWO_DEBUG);
        n = TWO_DEBUG;

        // Time C Function Call
        printf("C Dot Product Function Call:\n");
        startTime = clock();
        sdot = cDotProduct(n, vectorA, vectorB);
        startTime = clock() - startTime;
        timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
        printf("\tsdot Float Result: %f\n", sdot);
        printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdot);
        printf("\tExecution Time: %f\n\n", timeTaken);

        // Time C Function Call
        printf("Assembly Dot Product Function Call:\n");
        startTime = clock();
        sdot = asmDotProduct(n, vectorA, vectorB);
        startTime = clock() - startTime;
        timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
        printf("\tsdot Float Result: %f\n", sdot);
        printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdot);
        printf("\tExecution Time: %f\n\n", timeTaken);

        free(vectorA);
        free(vectorB);
        return 0;
    }



    printf("---------- ---------- ---------- ----------\n");

    n = (int)pow(2, 20);
    printf("\nCase 1 : Vector Size n = 2^20 = %i\n\n", n);

    // Time C Function Call
    printf("C Dot Product Function Call:\n");
    startTime = clock();
    sdot = cDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Float Result: %f\n", sdot);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdot);
    printf("\tExecution Time: %f\n\n", timeTaken);

    // Time C Function Call
    printf("Assembly Dot Product Function Call:\n");
    startTime = clock();
    sdot = asmDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Float Result: %f\n", sdot);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdot);
    printf("\tExecution Time: %f\n\n", timeTaken); 
    

    
    printf("---------- ---------- ---------- ----------\n");

    n = (int)pow(2, 24);
    printf("\nCase 2 : Vector Size n = 2^24 = %i\n\n", n);

    // Time C Function Call
    printf("C Dot Product Function Call:\n");
    startTime = clock();
    sdot = cDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Float Result: %f\n", sdot);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdot);
    printf("\tExecution Time: %f\n\n", timeTaken);

    // Time C Function Call
    printf("Assembly Dot Product Function Call:\n");
    startTime = clock();
    sdot = asmDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Float Result: %f\n", sdot);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdot);
    printf("\tExecution Time: %f\n\n", timeTaken); 
    
    

    printf("---------- ---------- ---------- ----------\n");

    n = (int)pow(2, 28);
    printf("\nCase 3 : Vector Size n = 2^28 = %i\n\n", n);
    

    // Time C Function Call
    printf("C Dot Product Function Call:\n");
    startTime = clock();
    sdot = cDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Float Result: %f\n", sdot);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdot);
    printf("\tExecution Time: %f\n\n", timeTaken);

    // Time C Function Call
    printf("Assembly Dot Product Function Call:\n");
    startTime = clock();
    sdot = asmDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Float Result: %f\n", sdot);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdot);
    printf("\tExecution Time: %f\n\n", timeTaken);



    // Free Memory Allocation
    free(vectorA);
    free(vectorB);

    return 0;
}
