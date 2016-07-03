#include <stdio.h>

#include "utils.h"
#include "text_file.h"

template <int i>
struct Number;

template <>
struct Number<1> {
    enum {n = 0};
};

template <>
struct Number<2> {
    enum {n = 0};
};

template <int i>
struct Number {
    enum {n = Number<i-1>::n + Number<i-2>::n};
};



// template <int H, int W>
// void 

int main(){
    print(Number<150000>::n);
    return 0;
    
    
    TextFile file;
    if (!file.open("input.txt")){
        return 0;
    }
    String s = file.read_line().strip();
    
    List<String> seter = s.split(" ");
    
    LongInt a = seter[0].str();
    LongInt b = seter[1].str();
    LongInt c = seter[2].str();
    
    int h = a.as_int();
    int w = b.as_int();
    int n = c.as_int();
    
    
    char list[h][w];
    
    // 0.5 + &(list);
    
    for (int i = 0; i < h; i += 1) {
        for (int j = 0; j < w; j += 1) {
            list[i][j] = '.';
        }
    }
    
    
    for (int i = 0; i < n; i += 1) {
        String new_s = file.read_line().strip();
        
        
        List<String> seter = new_s.split(" ");

        int one = LongInt(seter[0].str()).as_int() - 1;
        int two = LongInt(seter[1].str()).as_int() - 1;
        int three = LongInt(seter[2].str()).as_int() - 1;
        int four = LongInt(seter[3].str()).as_int();
        
        for (int m = two; m < four; m += 1) {
            list[m][two] = i + 'a';
            list[m][four - 1] = i + 'a';
        }
        for (int v = one; v < three; v += 1) {
            list[one][v] = i + 'a';
            list[three][v] = i + 'a';
        }
    }
    
    for (int i = 0; i < h; i += 1) {
        for (int j = 0; j < w; j += 1) {
            printf("%c",list[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
