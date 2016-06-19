#include <stdio.h>
#include <string.h>
#include <math.h>


#include "utils.h"

int main() {
    long long sum = 1;
    long long number = 1;
    long long step = 2;
    for (int i = 0; i < 500; i += 1) {
        for (int j = 0; j < 4; j += 1){
            number += step;
            sum += number;
        }
        step += 2;
    }
    printf("result is %lld", sum);
    return 0;
}
