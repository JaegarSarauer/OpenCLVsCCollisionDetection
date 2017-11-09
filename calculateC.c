#include "calculateC.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

//x1,y1,r1,x2,y2,r2

//p1p1,p1p2,p2p1,p2p2

int* calculateC(float* vectorData, int vectorCount) {

    int* result = malloc(vectorCount * sizeof(int));
    for(int me = 0; me < vectorCount; me++) {

        float myX = vectorData[me * 4];
        float myY = vectorData[me * 4 + 1];
        float myRadius = vectorData[me * 4 + 2];
        int collidedIndex = 0;

        for(int you = 0; you < vectorCount; you++) {
            if (me != you) {
                float yourX = vectorData[you * 4];
                float yourY = vectorData[you * 4 + 1];
                float yourRadius = vectorData[you * 4 + 2];

                if (sqrtf((yourX - myX) * (yourX - myX) + (yourY - myY) * (yourY - myY)) <= (yourRadius + myRadius)) {
                    result[me] = you;
                }
            }
        }

        result[me] = collidedIndex;
    }

    return result;
}