#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"


int d(int x){
    int sum = 1;
    double x_2 = sqrt(x);
    for(int i = 2; i < x_2 + 1; i += 1) {
        if (x % i == 0) {
            sum += i;
            if (i * i != x) {
                sum += x/i;
            }
        }
    }
    return sum;
}

int main() {
    printf("%d\n",d(220));
    int sum = 0;
    for(int i = 2; i < 10000; i += 1) {
        printf("%5d -> %d\r", i, sum);
        int d_i = d(i);
        if(d_i != i && i == d(d_i)) {
            sum += i;
        }
    }
    printf("\n%d\n",sum);
    return 0;
}
