#include <stdio.h>


#include "utils.h"
#include "text_file.h"


int main() {
    // TextFile file;
    // if (file.open("birthday.in")) {
        // while (true) {
            // String s = file.read_line();
            // if (s.is_empty()) {
                // break;
            // }
            // printf("%s",s.str());
        // }
    // }

    String s("aaabbbccc");
    printf("strip >>>%s<<<\n", obj_to_string(s.strip("ab","bc")).str());

    return 0;
}
