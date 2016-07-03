#include <stdio.h>


#include "utils.h"
#include "text_file.h"


int main() {
    TextFile file;
    String s;
    if (file.open("birthday.in")) {
        while (true) {
            String f = file.read_line();
            if (f.is_empty()) {
                break;
            }
            s += f;
        }
    }
    
    for (int i = 0; i < s.len(); i += 1) {
        
    }
    

    return 0;
}
