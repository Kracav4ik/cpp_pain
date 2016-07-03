#include <stdio.h>

#include "utils.h"
#include "text_file.h"

int main(){
    TextFile file;
    if (!file.open("input.txt")){
        return 0;
    }
    String s = file.read_line().strip();    

    List <String> new_s = s.split(" ");
    
    LongInt res1 = new_s[0].str();
    LongInt res1_1 = new_s[1].str();
    LongInt res2 = new_s[2].str();
    LongInt res2_2 = new_s[3].str();
    

    res1 *= res1_1;
    res2 *= res2_2;
    

    if (res1 < res2){
        printf("P\n");
    } else if (res2 < res1) {
        printf("M\n");       
    } else {     
        printf("E\n");
    }
    
    return 0;
}
