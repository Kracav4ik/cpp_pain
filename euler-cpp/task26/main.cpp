#include <stdio.h>
#include <string.h>
#include <math.h>


#include "utils.h"

int main() {
    LongInt m(17000000);
    LongInt n(16);
    print(m);
    printf(" / ");
    print(n);
    m /= n;
    printf(" = ");
    print(m);
    printf("\ntrue %d\n", 17000000/16);
    return 0;
}
