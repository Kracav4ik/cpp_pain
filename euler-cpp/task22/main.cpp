#include <stdio.h>
#include <string.h>
#include <math.h>


#include "utils.h"

void clear(){
    for (int i = 0; i < 97; i += 1) {
        printf("\n");
    }
}

bool operator<(const String& s1, const String& s2) {
    for (int i = 0; true; i += 1) {
        if (s1.str[i] == 0) {
            return true;
        } else if(s2.str[i] == 0) {
            return false;
        } else if (s1.str[i] < s2.str[i]){
            return true;
        } else if (s1.str[i] > s2.str[i]){
            return false;
        }
    }
}

int letter_sum(String& s){
    int sum = 0;
    for (int i = 0; i < s.len; i += 1) {
        sum += s.str[i] - 'A' + 1;
        printf("score is %d\n", sum);
    }
    return sum;
}



const int DATA_SIZE = 46448;
char data[DATA_SIZE];
template <typename T>
List<T> sort_list(const List<T>& list) {
    Tree<T> tree;
    // printf("AXAXAXA\n");
    for (int i = 0; i < list.size(); i += 1){
        // printf("REALY WHY?!\n");
        tree.add(list[i]);
    }
    tree.sorted_tree(*tree.root);
    return tree.list;
}

int main() {
    clear();
    // test();
    FILE* file = fopen("p022_names.txt", "r");
    if (!file) {
        return -1;
    }
    
    int size = fread(data, 1, DATA_SIZE, file);
    printf("bytes %d, read %d\n", DATA_SIZE, size);
    data[size] = 0;
    List<String> strings;
    String string("");
    bool first_bool = false;
    for (int i = 0; i < DATA_SIZE; i += 1) {
        char character_of_file = data[i];
        if (character_of_file == '"') {
            first_bool = !first_bool;
            continue;
        }
        if (first_bool) {
            string += character_of_file;
        } else {
            strings.append(string);
            string = "";
        }
    }
    printf("done!\n");
    // print(strings);
    
    
    List<int> test_list;
    test_list.append(7);
    test_list.append(6);
    test_list.append(8);
    test_list.append(10);
    test_list.append(1);
    test_list.append(15);
    test_list.append(2);
    test_list.append(8);
    test_list.append(1);
    
    printf("before:\n  %s\n", test_list.to_string().str);

    test_list = sort_list(test_list);
    int BIG_SUM = 0;
    strings = sort_list(strings);
    for (int i = 0; i < strings.size(); i += 1) {
        BIG_SUM += (i+1)*letter_sum(strings[i]);
    }
    printf("Answer is %d", BIG_SUM);

    fclose(file);
    return 0;
}
