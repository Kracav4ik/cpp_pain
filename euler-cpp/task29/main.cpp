#include <stdio.h>
#include <string.h>
#include <math.h>


#include "utils.h"

int main() {
    Tree<LongInt> tree;
    for (int a = 2; a < 101; a += 1){
        for (int b = 2; b < 101; b += 1){
            tree.add(pow(a,b));
            printf("a=%d b=%d a^b=%s\n",a,b,obj_to_string(pow(a,b)).str());
        }
    }
    printf("answer is\n");
    tree.sorted_tree(*tree.root);
    int result = tree.list.size();
    printf("answer is %d\n", result);
    return 0;
}
