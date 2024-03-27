#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define TWO_THIRTY 1073741824
#define MAX_FLOAT 1000.0



// Generate Random Values into Vector
void generateRandomVector(int vectorSize, float* vector) {

    for (int i = 0; i < vectorSize; i++)
        vector[i] = (float)rand() / (float)(RAND_MAX / MAX_FLOAT);
}



// Display Vector for Debugging
void printVector(int vectorSize, float* vector) {

    printf("[ ");

    for (int i = 0; i < vectorSize - 1; i++)
        printf("%f, ", vector[i]);

    printf("%f ]\n", vector[vectorSize - 1]);
}



// Print Vector to File
void printVectorToFile(int vectorSize, float* vector, char* filename) {

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file");
        return 1;
    }

    fprintf(fp, "{ ");
    for (int i = 0; i < vectorSize - 1; i++)
        fprintf(fp, "%f, ", vector[i]);
    fprintf(fp, "%f }\n", vector[vectorSize - 1]);

    fclose(fp);
}



int main() {
    // Initialize Variables
    char vectorAFilename[] = "vector_A.txt";
    char vectorBFilename[] = "vector_B.txt";
    float* vector = (float*)malloc(TWO_THIRTY * sizeof(float));

    // Randomize Vectors
    srand((unsigned int)time(NULL));

    printf("Generating Vector A...\n");
    generateRandomVector(TWO_THIRTY, vector);
    printVectorToFile(TWO_THIRTY, vector, vectorAFilename);

    printf("Generating Vector B...\n");
    generateRandomVector(TWO_THIRTY, vector);
    printVectorToFile(TWO_THIRTY, vector, vectorBFilename);
    

    // Clean up: free allocated memory
    free(vector);

    return 0;
}
