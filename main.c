#include <stdio.h>
#include <stdlib.h>
#include "calculateC.h"
#include "calculateCL.h"
#include <sys/time.h>

#ifdef MAC
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif


float timedifference_msec(struct timeval t0, struct timeval t1)
{
    return (t0.tv_sec - t1.tv_sec) * 1000.0f + (t0.tv_usec - t1.tv_usec) / 1000.0f;
}

int main(int argc, char** args) {
    srand(123);
    const int NUMOFPEOPLE = 65536;
    const int DATA_SIZE = 4;
    float* vectorData = malloc(NUMOFPEOPLE * DATA_SIZE * sizeof(float));
    for(int i = 0; i < NUMOFPEOPLE; i++) {
        vectorData[(i * DATA_SIZE)] = rand() % 500;
        vectorData[(i * DATA_SIZE) + 1] = rand() % 500;
        vectorData[(i * DATA_SIZE) + 2] = rand() % 3 + 0.5f;
        vectorData[(i * DATA_SIZE) + 3] = 0;
    }

    struct timeval startTime;
    struct timeval afterC;
    struct timeval afterCPU;
    struct timeval afterGPU;
    struct timeval afterCPUGPU;
    gettimeofday(&startTime, 0);
 
    int* result = calculateC(vectorData, NUMOFPEOPLE);
    gettimeofday(&afterC, 0);

    //Test doing it via OpenCL CPU
    int* result2 = calculateCL(vectorData, NUMOFPEOPLE, CL_DEVICE_TYPE_CPU);
    gettimeofday(&afterCPU, 0);

    //Test doing it via OpenGL GPU
    int* result3 = calculateCL(vectorData, NUMOFPEOPLE, CL_DEVICE_TYPE_GPU);
    gettimeofday(&afterGPU, 0);

    //Test doing it via OpenGL CPU+GPU
    int* result4 = calculateCL(vectorData, NUMOFPEOPLE, CL_DEVICE_TYPE_ALL);
    gettimeofday(&afterCPUGPU, 0);

    //printf("%lu %lu\n", startTime, afterC);
    printf("C Timer: %fms\n", timedifference_msec(afterC, startTime)); 
    printf("GL CPU Timer: %fms\n", timedifference_msec(afterCPU, afterC)); 
    printf("GL GPU Timer: %fms\n", timedifference_msec(afterGPU, afterCPU)); 
    printf("GL CPU+GPU Timer: %fms\n", timedifference_msec(afterCPUGPU, afterGPU));

    free(vectorData);
    free(result);
    free(result2);
    free(result3);
    free(result4);
}