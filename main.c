#include <stdio.h>
#include <stdlib.h>
#include "calculateC.h"
#include "calculateCL.h"

int main(int argc, char** args) {
    srand(123);
    const int NUMOFPEOPLE = 40000;
    float* vectorData = malloc(NUMOFPEOPLE * 3 * sizeof(float));
    for(int i = 0; i < NUMOFPEOPLE; i++) {
        vectorData[i * 3] = rand() % 50;
        vectorData[i * 3 + 1] = rand() % 50;
        vectorData[i * 3 + 2] = rand() % 3 + 0.5f;
    }

    unsigned long startTime = time(NULL);
 
    int* result = calculateC(vectorData, NUMOFPEOPLE);
    unsigned long afterC = time(NULL);
    int* result2 = calculateCL(vectorData, NUMOFPEOPLE);
    //Test doing it via OpenCL CPU
    unsigned long afterCPU = time(NULL);
    //Test doing it via OpenGL GPU
    unsigned long afterGPU = time(NULL);
    //Test doing it via OpenGL CPU+GPU
    unsigned long afterCPUGPU = time(NULL);
    printf("%lu %lu\n", startTime, afterC);
    printf("C Timer: %lu\n", afterC - startTime); 
    printf("GL CPU Timer: %lu\n", afterCPU - afterC); 
    printf("GL GPU Timer: %lu\n", afterGPU - afterCPU); 
    printf("GL CPU+GPU Timer: %lu\n", afterCPUGPU - afterGPU);

    printf("%d", result2[1]);

    free(vectorData);
    free(result);
    free(result2);
}
