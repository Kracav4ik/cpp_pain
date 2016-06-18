#include <stdio.h>
#include <string.h>
#include <math.h>


#include "utils.h"

    void fib(){
        LongInt f1("1");
        LongInt f2("1");
        LongInt f3;
        for (int i = 3; f3.digits().size() < 10000 ; i += 1) {
            f3 = f1 + f2;
            f1 = f2;
            f2 = f3;
            printf("%d for %d is %s\n\n", i, f3.digits().size(), obj_to_string(f3).str);
        }
    }
    

int main() {
    clear();
    fib();

    
    return 0;
}
