#include <stdio.h>

#include "utils.h"
#include "text_file.h"

int main(){
    TextFile file;
    if (!file.open("input.txt")){
        return 0;
    }
    String s = file.read_line().strip();
    
    List<String> seter = s.split(" ");
    
    LongInt a = seter[0].str();
    LongInt b = seter[1].str();
    LongInt c = seter[2].str();
    
    int w = a.as_int();
    int h = b.as_int();
    int n = c.as_int();
    
    
    char list[w][h];
        
    for (int i = 0; i < w; i += 1) {
        for (int j = 0; j < h; j += 1) {
            list[i][j] = '.';
        }
    }
    
    
    for (int i = 0; i < n; i += 1) {
        String new_s = file.read_line().strip();
        
        
        List<String> seter = new_s.split(" ");

        int one = LongInt(seter[0].str()).as_int() - 1;
        int two = LongInt(seter[1].str()).as_int() - 1;
        int three = LongInt(seter[2].str()).as_int() - 1;
        int four = LongInt(seter[3].str()).as_int() - 1;
        
        for (int m = two; m <= four; m += 1) {
            list[one][m] = i + 'a';
            list[three][m] = i + 'a';
        }
        for (int v = one; v <= three; v += 1) {
            list[v][two] = i + 'a';
            list[v][four] = i + 'a';
        }
    }
    
    for (int i = 0; i < w; i += 1) {
        for (int j = 0; j < h; j += 1) {
            printf("%c",list[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
