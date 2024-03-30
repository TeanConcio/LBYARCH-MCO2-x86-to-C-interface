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
#define TRIAL_NO 30
#define MAX_FLOAT 100.0f



// C Dot Product Function
float cDotProduct(int vectorSize, float* vectorA, float* vectorB) {

    float sdot = 0.0f;

    // For vectorSize, total the product of elements in Vector A and B
    for (int i = 0; i < vectorSize; i++) {

        if (DEBUG_MODE == 1) {
            printf("(%lf * %lf) = ", vectorA[i], vectorB[i]);
            printf("%lf + ", vectorA[i] * vectorB[i]);
        }

        sdot += vectorA[i] * vectorB[i];
    }

    if (DEBUG_MODE == 1) {
        printf("\n");
    }

    return sdot;
}



// Import x86_64 Assembly Dot Product Function
extern float asmDotProduct(int vectorSize, float* vectorA, float* vectorB);



// Generate Random Values into Vector
void generateRandomVector(int vectorSize, float* vector) {

    // Debug
    if (DEBUG_MODE == 1) {
        for (int i = 0; i < TWO_DEBUG; i++)
            vector[i] = i * 10.0f + i + i * 0.1f + i * 0.01f;
        return;
    }
    

    int powCounter = 0;
    int pow2 = 1;

    for (int i = 0; i < vectorSize; i++) {
        
        //vector[i] = RAND_MAX * (float)rand() / RAND_MAX;
        vector[i] = ((float)rand() / (float)(RAND_MAX)) * MAX_FLOAT;
        vector[i] = (int)(vector[i] * MAX_FLOAT) / MAX_FLOAT;

        if (rand() % 2 == 0)
            vector[i] /= -1;
        
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

        printf("%0.2f, ", vector[i]);
    }

    printf("%0.2f }\n", vector[vectorSize - 1]);
}



double computeAverageTime(double* timesTaken) {

    double average = 0.0;

    for (int i = 0; i < TRIAL_NO; i++)
        average += timesTaken[i];

    return average / TRIAL_NO;
}



// Display Times Taken
void printTimes(double* timesTaken) {

    printf("{ ");

    for (int i = 0; i < TRIAL_NO - 1; i++)
        printf("%0.3f, ", timesTaken[i]);


    printf("%0.3f }\n", timesTaken[TRIAL_NO - 1]);
}



// Main
int main()
{
    // Initialize Variables
    int n = 0;
    float* vectorA = (float*)malloc((int)pow(2, 28) * sizeof(float));
    float* vectorB = (float*)malloc((int)pow(2, 28) * sizeof(float));
    float sdot = 0;
    float sdotC = 0;
    float sdotAsm = 0;

    // Time Variables
    clock_t startTime;
    double cTimesTaken[TRIAL_NO];
    double cAvgTimeTaken;
    double asmTimesTaken[TRIAL_NO];
    double asmAvgTimeTaken;

    // Randomize Vectors
    srand((unsigned int)time(NULL));
    printf("Generating Vector A...\n");
    generateRandomVector((int)pow(2, 28), vectorA);
    printf("Vector A Generated\n\n");
    printf("Generating Vector B...\n");
    generateRandomVector((int)pow(2, 28), vectorB);
    printf("Vector B Generated\n\n");

    printf("Vector A first %i Values: ", TWO_DEBUG);
    printVector(TWO_DEBUG, vectorA);
    printf("\n");
    printf("Vector B first %i Values: ", TWO_DEBUG);
    printVector(TWO_DEBUG, vectorB);



    if (DEBUG_MODE == 1) {

        printf("\n---------- ---------- ---------- ---------- ----------\n");

        printf("\nCase 0 (Debug) : Vector Size n = %i\n\n", TWO_DEBUG);
        n = TWO_DEBUG;

        // Time C Function Call
        printf("C Dot Product Function Call Trials:\n");
        for (int i = 0; i < TRIAL_NO; i++) {
            startTime = clock();
            sdot = cDotProduct(n, vectorA, vectorB);
            startTime = clock() - startTime;
            cTimesTaken[i] = ((double)startTime) / CLOCKS_PER_SEC;
        }
        sdotC = sdot;
        cAvgTimeTaken = computeAverageTime(cTimesTaken);
        printf("\tsdot Float Result: %f\n", sdotC);
        printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdotC);
        printf("\tExecution Times: ");
        printTimes(cTimesTaken);
        printf("\tAverage Execution Time: %lf\n\n", cAvgTimeTaken);

        // Time x86_64 Function Call
        printf("x86_64 Dot Product Function Call Trials:\n");
        for (int i = 0; i < TRIAL_NO; i++) {
            startTime = clock();
            sdot = asmDotProduct(n, vectorA, vectorB);
            startTime = clock() - startTime;
            asmTimesTaken[i] = ((double)startTime) / CLOCKS_PER_SEC;
        }
        sdotAsm = sdot;
        asmAvgTimeTaken = computeAverageTime(asmTimesTaken);
        printf("\tsdot Float Result: %f\n", sdotAsm);
        printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdotAsm);
        printf("\tExecution Times: ");
        printTimes(asmTimesTaken);
        printf("\tAverage Execution Time: %lf\n\n", asmAvgTimeTaken);

        // Results
        printf("Results:\n");
        printf("\tSimilarity: %.2f %%\n", sdotC * 100 / sdotAsm);
        if (asmAvgTimeTaken <= 0)
            printf("\tTime Difference: 0 (0 %% faster)\n");
        else {
            printf("\tTime Difference: %lf ", cAvgTimeTaken - asmAvgTimeTaken);

            if (cAvgTimeTaken > asmAvgTimeTaken)
                printf("(x86_64 is %.2lf times faster)\n", cAvgTimeTaken / asmAvgTimeTaken);
            else
                printf("(C is %.2lf times faster)\n", asmAvgTimeTaken / cAvgTimeTaken);
        }

        free(vectorA);
        free(vectorB);
        return 0;
    }



    printf("\n---------- ---------- ---------- ---------- ----------\n");

    n = (int)pow(2, 20);
    printf("\nCase 1 : Vector Size n = 2^20 = %i\n\n", n);

    // Time C Function Call
    printf("C Dot Product Function Call Trials:\n");
    for (int i = 0; i < TRIAL_NO; i++) {
        startTime = clock();
        sdot = cDotProduct(n, vectorA, vectorB);
        startTime = clock() - startTime;
        cTimesTaken[i] = ((double)startTime) / CLOCKS_PER_SEC;
    }
    sdotC = sdot;
    cAvgTimeTaken = computeAverageTime(cTimesTaken);
    printf("\tsdot Float Result: %f\n", sdotC);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdotC);
    printf("\tExecution Times: ");
    printTimes(cTimesTaken);
    printf("\tAverage Execution Time: %lf\n\n", cAvgTimeTaken);

    // Time x86_64 Function Call
    printf("x86_64 Dot Product Function Call Trials:\n");
    for (int i = 0; i < TRIAL_NO; i++) {
        startTime = clock();
        sdot = asmDotProduct(n, vectorA, vectorB);
        startTime = clock() - startTime;
        asmTimesTaken[i] = ((double)startTime) / CLOCKS_PER_SEC;
    }
    sdotAsm = sdot;
    asmAvgTimeTaken = computeAverageTime(asmTimesTaken);
    printf("\tsdot Float Result: %f\n", sdotAsm);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdotAsm);
    printf("\tExecution Times: ");
    printTimes(asmTimesTaken);
    printf("\tAverage Execution Time: %lf\n\n", asmAvgTimeTaken);

    // Results
    printf("Results:\n");
    printf("\tSimilarity: %.2f %%\n", sdotC * 100 / sdotAsm);
    if (asmAvgTimeTaken <= 0)
        printf("\tTime Difference: 0 (0 %% faster)\n");
    else {
        printf("\tTime Difference: %lf ", cAvgTimeTaken - asmAvgTimeTaken);

        if (cAvgTimeTaken > asmAvgTimeTaken)
            printf("(x86_64 is %.2lf times faster)\n", cAvgTimeTaken / asmAvgTimeTaken);
        else
            printf("(C is %.2lf times faster)\n", asmAvgTimeTaken / cAvgTimeTaken);
    }
    

    
    printf("\n---------- ---------- ---------- ---------- ----------\n");

    n = (int)pow(2, 24);
    printf("\nCase 2 : Vector Size n = 2^24 = %i\n\n", n);

    // Time C Function Call
    printf("C Dot Product Function Call Trials:\n");
    for (int i = 0; i < TRIAL_NO; i++) {
        startTime = clock();
        sdot = cDotProduct(n, vectorA, vectorB);
        startTime = clock() - startTime;
        cTimesTaken[i] = ((double)startTime) / CLOCKS_PER_SEC;
    }
    sdotC = sdot;
    cAvgTimeTaken = computeAverageTime(cTimesTaken);
    printf("\tsdot Float Result: %f\n", sdotC);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdotC);
    printf("\tExecution Times: ");
    printTimes(cTimesTaken);
    printf("\tAverage Execution Time: %lf\n\n", cAvgTimeTaken);

    // Time x86_64 Function Call
    printf("x86_64 Dot Product Function Call Trials:\n");
    for (int i = 0; i < TRIAL_NO; i++) {
        startTime = clock();
        sdot = asmDotProduct(n, vectorA, vectorB);
        startTime = clock() - startTime;
        asmTimesTaken[i] = ((double)startTime) / CLOCKS_PER_SEC;
    }
    sdotAsm = sdot;
    asmAvgTimeTaken = computeAverageTime(asmTimesTaken);
    printf("\tsdot Float Result: %f\n", sdotAsm);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdotAsm);
    printf("\tExecution Times: ");
    printTimes(asmTimesTaken);
    printf("\tAverage Execution Time: %lf\n\n", asmAvgTimeTaken);

    // Results
    printf("Results:\n");
    printf("\tSimilarity: %.2f %%\n", sdotC * 100 / sdotAsm);
    if (asmAvgTimeTaken <= 0)
        printf("\tTime Difference: 0 (0 %% faster)\n");
    else {
        printf("\tTime Difference: %lf ", cAvgTimeTaken - asmAvgTimeTaken);

        if (cAvgTimeTaken > asmAvgTimeTaken)
            printf("(x86_64 is %.2lf times faster)\n", cAvgTimeTaken / asmAvgTimeTaken);
        else
            printf("(C is %.2lf times faster)\n", asmAvgTimeTaken / cAvgTimeTaken);
    }
    
    

    printf("\n---------- ---------- ---------- ---------- ----------\n");

    n = (int)pow(2, 28);
    printf("\nCase 3 : Vector Size n = 2^28 = %i\n\n", n);
    

    // Time C Function Call
    printf("C Dot Product Function Call Trials:\n");
    for (int i = 0; i < TRIAL_NO; i++) {
        startTime = clock();
        sdot = cDotProduct(n, vectorA, vectorB);
        startTime = clock() - startTime;
        cTimesTaken[i] = ((double)startTime) / CLOCKS_PER_SEC;
    }
    sdotC = sdot;
    cAvgTimeTaken = computeAverageTime(cTimesTaken);
    printf("\tsdot Float Result: %f\n", sdotC);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdotC);
    printf("\tExecution Times: ");
    printTimes(cTimesTaken);
    printf("\tAverage Execution Time: %lf\n\n", cAvgTimeTaken);

    // Time x86_64 Function Call
    printf("x86_64 Dot Product Function Call Trials:\n");
    for (int i = 0; i < TRIAL_NO; i++) {
        startTime = clock();
        sdot = asmDotProduct(n, vectorA, vectorB);
        startTime = clock() - startTime;
        asmTimesTaken[i] = ((double)startTime) / CLOCKS_PER_SEC;
    }
    sdotAsm = sdot;
    asmAvgTimeTaken = computeAverageTime(asmTimesTaken);
    printf("\tsdot Float Result: %f\n", sdotAsm);
    printf("\tsdot Hex Result: %x\n", *(unsigned int*)&sdotAsm);
    printf("\tExecution Times: ");
    printTimes(asmTimesTaken);
    printf("\tAverage Execution Time: %lf\n\n", asmAvgTimeTaken);

    // Results
    printf("Results:\n");
    printf("\tSimilarity: %.2f %%\n", sdotC * 100 / sdotAsm);
    if (asmAvgTimeTaken <= 0)
        printf("\tTime Difference: 0 (0 %% faster)\n");
    else {
        printf("\tTime Difference: %lf ", cAvgTimeTaken - asmAvgTimeTaken);

        if (cAvgTimeTaken > asmAvgTimeTaken)
            printf("(x86_64 is %.2lf times faster)\n", cAvgTimeTaken / asmAvgTimeTaken);
        else
            printf("(C is %.2lf times faster)\n", asmAvgTimeTaken / cAvgTimeTaken);
    }



    // Free Memory Allocation
    free(vectorA);
    free(vectorB);

    return 0;
}
