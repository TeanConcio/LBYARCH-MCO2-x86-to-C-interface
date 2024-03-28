// Tean Concio XX22
// Nicole Ong S11



// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>



// Constants
#define TWO_DEBUG 4
#define TWO_TWENTY 1048576
#define TWO_TWENTY_FOUR 16777216
#define TWO_THIRTY 1073741824
#define MAX_FLOAT 100.0



// Import C Dot Product Function
#include "cfunc.c"



// Import x86_64 Assembly Dot Product Function
extern float asmDotProduct(int vectorSize, float* vectorA, float* vectorB);



// Generate Random Values into Vector
void generateRandomVector(int vectorSize, float* vector) {

    vector[0] = 1.11f;
    vector[1] = 2.22f;
    vector[2] = 3.33f;
    vector[3] = 4.44f;
    return;

    int pow = 0;
    int pow2 = 1;

    for (int i = 0; i < vectorSize; i++) {
        
        vector[i] = (float)rand() / (float)(RAND_MAX / (MAX_FLOAT * 2));
        //vector[i] = (int)(vector[i] * MAX_FLOAT) / MAX_FLOAT;
        vector[i] -= MAX_FLOAT;
        
        // Check Progress
        if (i == pow2 - 1) {
            printf("%i (%i), ", pow2, pow);

            pow++;
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
    float* vectorA = (float*)malloc(TWO_THIRTY * sizeof(float));
    float* vectorB = (float*)malloc(TWO_THIRTY * sizeof(float));
    float sdot = 0;

    // Time Variables
    clock_t startTime;
    double timeTaken;

    // Randomize Vectors
    srand((unsigned int)time(NULL));
    printf("Generating Vector A...\n");
    generateRandomVector(TWO_THIRTY, vectorA);
    printf("Vector A Generated\n\n");
    printf("Generating Vector B...\n");
    generateRandomVector(TWO_THIRTY, vectorB);
    printf("Vector B Generated\n\n");
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
    printf("\tsdot Result: %f\n", sdot);
    printf("\tExecution Time: %lf\n\n", timeTaken);

    // Time C Function Call
    printf("Assembly Dot Product Function Call:\n");
    startTime = clock();
    sdot = asmDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Result: %f\n", sdot);
    printf("\tExecution Time: %lf\n\n", timeTaken);

    free(vectorA);
    free(vectorB);
    return 0;



    printf("---------- ---------- ---------- ----------\n");

    printf("\nCase 1 : Vector Size n = 2^20\n\n");
    n = TWO_TWENTY;

    // Time C Function Call
    printf("C Dot Product Function Call:\n");
    startTime = clock();
    sdot = cDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Result: %f\n", sdot);
    printf("\tExecution Time: %lf\n\n", timeTaken);

    // Time C Function Call
    printf("Assembly Dot Product Function Call:\n");
    startTime = clock();
    sdot = asmDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Result: %f\n", sdot);
    printf("\tExecution Time: %lf\n\n", timeTaken); 
    

    
    printf("---------- ---------- ---------- ----------\n");

    printf("\nCase 2 : Vector Size n = 2^24\n\n");
    n = TWO_TWENTY_FOUR;

    // Time C Function Call
    printf("C Dot Product Function Call:\n");
    startTime = clock();
    sdot = cDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Result: %f\n", sdot);
    printf("\tExecution Time: %lf\n\n", timeTaken);

    // Time C Function Call
    printf("Assembly Dot Product Function Call:\n");
    startTime = clock();
    sdot = asmDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Result: %f\n", sdot);
    printf("\tExecution Time: %lf\n\n", timeTaken); 
    
    

    printf("---------- ---------- ---------- ----------\n");

    printf("\nCase 3 : Vector Size n = 2^30\n\n");
    n = TWO_THIRTY;

    // Time C Function Call
    printf("C Dot Product Function Call:\n");
    startTime = clock();
    sdot = cDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Result: %f\n", sdot);
    printf("\tExecution Time: %lf\n\n", timeTaken);

    // Time C Function Call
    printf("Assembly Dot Product Function Call:\n");
    startTime = clock();
    sdot = asmDotProduct(n, vectorA, vectorB);
    startTime = clock() - startTime;
    timeTaken = ((double)startTime) / CLOCKS_PER_SEC;
    printf("\tsdot Result: %f\n", sdot);
    printf("\tExecution Time: %lf\n\n", timeTaken);



    // Free Memory Allocation
    free(vectorA);
    free(vectorB);

    return 0;
}
