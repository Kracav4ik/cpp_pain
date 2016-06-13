#include <stdio.h>
#include <string.h>

//
// String
//

void copy_n(char* to, const char* from, int count) {
    for(int i = 0; i < count; i += 1) {
        to[i] = from[i];
    }
}

struct String {
    char* str;
    int len;
    
    String(const char* s) {
        len = strlen(s);
        str = new char [len + 1];
        copy_n(str, s, len + 1);
        // printf("  constructor: string at [%p] for str %p '%s'\n", this, str, str);
    }
    
    String(const String& other) {
        len = strlen(other.str);
        str = new char [len + 1];
        copy_n(str, other.str, len + 1);
        // printf("  copy CTOR from [%p] str %p '%s'\n", &other, other.str, other.str);
    }
    
    String& operator=(const String& other) {
        if (this != &other) {
            // printf("  copy OPER from [%p] str %p '%s' to [%p] str %p '%s'\n", &other, other.str, other.str, this, str, str);
            delete[] str;
            len = strlen(other.str);
            str = new char [len + 1];
            copy_n(str, other.str, len + 1);
        } else {
            // printf("  copy OPER from [%p] str %p '%s' to ITSELF FUCK YOU\n", &other, other.str, other.str);
        }
        return *this;
    }
    
    ~String() {
        // printf("  destructor:  string at [%p] for str %p '%s'\n", this, str, str);
        delete[] str;
    }
    
    String& operator+=(const String& other) {
        char* new_str = new char [len + other.len + 1];
        copy_n(new_str, str, len);
        copy_n(new_str + len, other.str, other.len + 1);
        delete[] str;
        str = new_str;
        len += other.len;
        return *this;
    }
    
    void print() const {
        printf("{String [%p] '%s' len %d}\n", this, str, len);
    }
};

String operator+(const String& s1, const String& s2) {
    String result = s1;
    result += s2;
    return result;
}

//
// LongInt100
//

int max(int x1, int x2) {
    if (x1 > x2) {
        return x1;
    }
    return x2;
}


int convert(char c) {
    return c - '0';
}

char convert_to_str(int c) {
    return c + '0';
}

const int LEN = 400;

void add_arrays(int *m, int *n, int size) {
    int carry = 0;
    for(int i = 0; i < size; i +=1) {
        int product = m[i] + n[i] + carry;
        m[i] = product % 10;
        carry = product / 10;
    }
}

struct LongInt100 {
    int digits[LEN];
    
    LongInt100(const char* s) {
        int len_s = strlen(s);
        for (int i = 0; i < LEN; i += 1) {
            if (i < len_s){
                digits[i] = convert(s[len_s - (i+1)]);
            } else {
                digits[i] = 0;
            }
        }
    }
    
    void add(LongInt100 x) {
        add_arrays(digits, x.digits, LEN);
    }
    
    String to_string() {
        String result("");
        char buf[2] = {0, 0};
        bool b = false;
        for (int i = LEN - 1; i > -1; i -= 1){
            char d = digits[i];
            if (d != 0 || b) {
                buf[0] = convert_to_str(d);
                result += String(buf);
                b = true;
            }
        }
        if (!b){
            buf[0] = convert_to_str(0);
            result += String(buf);
        }
        return result;
    }

    void mul(LongInt100 x) {
        int result_offset = 0;
        int result [LEN];
        int subresult [LEN];
        for (int i = 0; i < LEN; i += 1) {
            result[i] = 0;
            subresult[i] = 0;
        }
        for (int i = 0; i < LEN; i += 1) {
            int subresult_carry = 0;
            for (int j = 0; j < LEN; j += 1) {
                int product = digits[i] * x.digits[j] + subresult_carry;
                subresult[j] += product % 10;
                subresult_carry = product / 10;
                // printf("digits[%2d] * x.digits[%2d] = %d * %d = product = %2d; carry = %d; add[%d] = %d \n", i, j, 
                // digits[i], x.digits[j], product, subresult_carry, j, subresult[j]);
            }
            // printf(" result\n") ;
            add_arrays(result + result_offset, subresult, LEN);
            for (int j = 0; j < LEN; j += 1) {
                subresult[j] = 0;
                // printf("add[%d] = %d \n",j, result[j]);
            }
            result_offset += 1;
        }
        for (int i = 0; i < LEN; i += 1) {
            digits[i] = result[i];
        }
        
    }
    
};
