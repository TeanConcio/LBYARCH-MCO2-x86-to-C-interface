// Dot Product Function in C
float cDotProduct(int vectorSize, float* vectorA, float* vectorB) {

    float sdot = 0.0f;

    // For vectorSize, total the product of elements in Vector A and B
    for (int i = 0; i < vectorSize; i++) {
        
        //printf("(%lf * %lf) + ", vectorA[i], vectorB[i]);
        //printf("%lf + ", vectorA[i] * vectorB[i]);

        sdot += vectorA[i] * vectorB[i];
    }

    //printf(" = %lf", sdot);

    //printf("\n");

    return sdot;
}