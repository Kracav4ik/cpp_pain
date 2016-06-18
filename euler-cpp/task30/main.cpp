#include <stdio.h>
#include <string.h>
#include <math.h>


#include "utils.h"

bool lol(int num){
    int sum = 0;
    int new_num = num;
    while (true){
        if (new_num != 0) {
            int www = new_num % 10;
            // printf("www is %d\n",www);
            sum += (www) * (www) * (www) * (www) * (www);
        } else {
            break;
        }
        new_num /= 10;
    }
    // printf(" Sum is%d\n",sum);
    if (num == sum) {
        return true;
    }
    return false;
}

int main() {
    // printf("result is %d\n", lol(5));
    int sum = 0;
    for (int i = 10; i < 500000; i += 1) {
        if (lol(i)){
            printf("result is %d\n", i);
            sum += i;
        }
    }
    printf("Sum is %d\n", sum);
    return 0;
}
