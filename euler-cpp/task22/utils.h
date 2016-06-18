#include <stdio.h>
#include <string.h>

//
// String
//

template <typename T>
void copy_n(T* to, const T* from, int count) {
    for(int i = 0; i < count; i += 1) {
        to[i] = from[i];
    }
}

struct String {
    char* str;
    int len;
    
    String(const char* s = "") {
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
    
    String& operator+=(char c) {
        char* new_str = new char [len + 2];
        copy_n(new_str, str, len);
        new_str[len] = c;
        new_str[len + 1] = 0;
        delete[] str;
        str = new_str;
        len += 1;
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

String obj_to_string(int i) {
    char buf[30];
    sprintf(buf, "%d", i);
    return String(buf);
}

String obj_to_string(const String& s) {
    return s;
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

//
// List
//

template <typename T>
struct List {
    T* elements;
    int _size;
    
    List() {
        elements = NULL;
        _size = 0;
    }
    
    ~List() {
        delete[] elements;
    }
    
    List(const List<T>& other) {
        elements = new T[other.size()];
        copy_n(elements, other.elements, other.size());
        _size = other.size();
    }
    
    List& operator=(const List<T>& other) {
        if (this != &other) {
            delete[] elements;
            elements = new T[other.size()];
            copy_n(elements, other.elements, other.size());
            _size = other.size();
        }
        return *this;
    }
    
    void insert(int index, const T& value) {
        T* new_elements = new T[size() + 1];
        
        copy_n(new_elements, elements, index);
        copy_n(new_elements + index + 1, elements + index, size() - index);
        
        new_elements[index] = value;
        
        elements = new_elements;
        _size += 1;
    }
    
    void erase(int index) {
        T* new_elements = new T[size() - 1];
        
        copy_n(new_elements, elements, index);
        copy_n(new_elements + index, elements + index + 1, size() - (index + 1));
        
        elements = new_elements;
        _size -= 1;
        
    }
    
    void append(const T& value) {
        insert(size(), value);
    }
    
    int size() const {
        return _size;
    }
    
    const T& operator[](int index) const {
        return elements[index];
    }
    
    T& operator[](int index) {
        return elements[index];
    }
    
    String to_string() const {
        String result("[");
        for (int i = 0; i < size(); i += 1){
            T d = elements[i];
            if (i) {
                result += String(", ");
            }
            result += obj_to_string(d);
        }
        result += String("]");
        return result;
    }
    
};

template <typename T>
void print(const List<T>& list, const char* end = "") {
    printf("%s%s", list.to_string().str, end);
}

void test() {
    List<int> list;
    String s = list.to_string();
    printf("list = %s\n", s.str);
    
    list.insert(0, 3);
    s = list.to_string();
    printf("list = %s\n", s.str);
    
    list.insert(1, 1);
    s = list.to_string();
    printf("list = %s\n", s.str);
    
    list.insert(1, 2);
    s = list.to_string();
    printf("list = %s\n", s.str);
    
    list.insert(0, 4);
    s = list.to_string();
    printf("list = %s\n", s.str);
    
    list.insert(0, 5);
    s = list.to_string();
    printf("list = %s\n", s.str);
    
    list.erase(2);
    s = list.to_string();
    printf("list = %s\n", s.str);
    
    list.erase(2);
    s = list.to_string();
    printf("list = %s\n", s.str);
    
    list.erase(1);
    s = list.to_string();
    printf("list = %s\n", s.str);
    
    list.erase(1);
    s = list.to_string();
    printf("list = %s\n", s.str);
    
    list.erase(0);
    s = list.to_string();
    printf("list = %s\n", s.str);
}

//
// Node of Tree
//


template <typename T>
struct Node {
    Node<T>* _left   = NULL;
    Node<T>* _right  = NULL;
    T _us_value;
    
    Node<T>* left() const {
        return _left;
    }
    Node<T>* right() const {
        return _right;
    }
    const T& value() const {
        return _us_value;
    }
    
    Node(const T& value_input) {
        _us_value = value_input;
    }
    
    void set_right(Node<T>* node) {
        _right = node;
    }
    
    void set_left(Node<T>* node) {
        _left = node;
    }
    
};

//
// Tree
//

template <typename T>
struct Tree {
    Node<T>* root = NULL;
    List<T> list;
    
    void add_in_fking_tree(const T& value, Node<T>& node) {
        // printf("Rekursia number is <should be a number>\n");
        const T& node_value = node.value();
        if (node_value < value) {
            if (node.right() == NULL){
                node.set_right(new Node<T>(value));
            } else {
                add_in_fking_tree(value, *node.right());
            }
        } else {
            if (node.left() == NULL){
                node.set_left(new Node<T>(value));
            } else {
                add_in_fking_tree(value, *node.left());
            }
        }
    }

    void set_root(Node<T>* node) {
        root = node;
    }
        
    void add(const T& value_input) {
        // printf("TREEEE!!!\n");
        if (root == NULL){
            set_root(new Node<T>(value_input));
            return;
        }
        // printf("CONTINUE!!!\n");
        add_in_fking_tree(value_input, *root);
    }
    
    void sorted_tree(Node<T>& node) {
        if (node.left()) {
            sorted_tree(*node.left());
        }
        list.append(node.value());
        if (node.right()) {
            sorted_tree(*node.right());
        }
    }
    
};

