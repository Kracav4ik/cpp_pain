#include <stdio.h>
#include <string.h>
#include <math.h>


#include "utils.h"

bool is_abundant(int number) {
    if (number < divisor_sum(number)) {
        return true;
    }
    return false;
}

bool is_abundant_sum(int numder) {
    for (int i = 1; i < numder; i += 1) {
        if (is_abundant(numder - i) && is_abundant(i)) {
            return true;
        }
    }
    return false;
}



int main() {
    // clear();
    int result = 0;
    for (int i = 1; i < 28124; i += 1) {
        if (!is_abundant_sum(i)) {
            result += i;
            printf("found %d sum %d\r", i, result);
        }
    }
    printf("\nresult %d\n", result);
    return 0;
}
