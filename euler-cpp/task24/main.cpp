#include <stdio.h>
#include <string.h>
#include <math.h>


#include "utils.h"

String num_letters("0123456789");


long long fac(int n){
    long long m = 1;
    for (int x = 1; x <= n; x += 1){
        m *= x;
    }
    return m;
}

String f(int n, String letters){
    String result;
    while (letters.len() > 1) {
        long long sub_permutations_count = fac(letters.len() - 1);
        long long remainder = n % sub_permutations_count;
        long long quotient = n / sub_permutations_count;
        result += letters[quotient];
        String new_letters = letters;
        new_letters._str.erase(quotient);
        
        letters = new_letters;
        n = remainder;
    }
    result += letters[0];

    return result;
}

int main() {
    clear();
    printf("%s", f(999999, num_letters).str());
    return 0;
}
