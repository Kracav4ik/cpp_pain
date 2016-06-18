#include <stdio.h>
#include <string.h>

//
// common stuff
//

int max(int x1, int x2) {
    if (x1 > x2) {
        return x1;
    }
    return x2;
}

template <typename T>
void copy_n(T* to, const T* from, int count) {
    if (to < from) {
        for (int i = 0; i < count; i += 1) {
            to[i] = from[i];
        }
    } else {
        for (int i = count - 1; i >= 0; i -= 1) {
            to[i] = from[i];
        }
    }
}

//
// List
//

template <typename T>
struct List {
    T* elements;
    int _size;
    int _capacity;
    
    List() {
        elements = NULL;
        _size = 0;
        _capacity = 0;
    }
    
    ~List() {
        delete[] elements;
    }
    
    List(const List<T>& other) {
        elements = new T[other.capacity()];
        copy_n(elements, other.elements, other.size());
        _size = other.size();
        _capacity = other.capacity();
    }
    
    List& operator=(const List<T>& other) {
        if (this != &other) {
            delete[] elements;
            elements = new T[other.capacity()];
            copy_n(elements, other.elements, other.size());
            _size = other.size();
            _capacity = other.capacity();
        }
        return *this;
    }
    
    void insert(int index, const T& value) {
        ensure_capacity(size() + 1);

        copy_n(elements + index + 1, elements + index, size() - index);
        
        elements[index] = value;

        _size += 1;
    }
    
    void erase(int index) {
        copy_n(elements + index, elements + index + 1, size() - (index + 1));
        _size -= 1;
    }
    
    void append(const T& value) {
        insert(size(), value);
    }
    
    int size() const {
        return _size;
    }
    
    int capacity() const {
        return _capacity;
    }
    
    void ensure_capacity(int required_capacity) {
        if (capacity() >= required_capacity) {
            return;
        }
        T* new_elements = new T[required_capacity];
        copy_n(new_elements, elements, size());
        delete [] elements;
        elements = new_elements;
        _capacity = required_capacity;
    }
    
    const T& operator[](int index) const {
        return elements[index];
    }
    
    const T& get(int index, const T& def = T()) const {
        if (index >= size()) {
            return def;
        }
        return (*this)[index];
    }
    
    T& operator[](int index) {
        return elements[index];
    }
    
    T& set_and_fill(int index, const T& value, const T& fill_value = T()) {
        ensure_capacity(index + 1);
        for (int i = size(); i < index; i += 1) {
            (*this)[i] = fill_value;
        }
        (*this)[index] = value;
        _size = max(size(), index + 1);
        return (*this)[index];
    }
};

//
// String
//

struct String {
    char* str;
    int len;
    
    String(const char* s = "");
    String(const String& other);

    String& operator=(const String& other);
    
    ~String();
    
    String& operator+=(const String& other);
    
    String& operator+=(char c);
    
    void print() const;
};

String::String(const char* s) {
    len = strlen(s);
    str = new char [len + 1];
    copy_n(str, s, len + 1);
    // printf("  constructor: string at [%p] for str %p '%s'\n", this, str, str);
}

String::String(const String& other) {
    len = strlen(other.str);
    str = new char [len + 1];
    copy_n(str, other.str, len + 1);
    // printf("  copy CTOR from [%p] str %p '%s'\n", &other, other.str, other.str);
}

String& String::operator=(const String& other) {
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

String::~String() {
    // printf("  destructor:  string at [%p] for str %p '%s'\n", this, str, str);
    delete[] str;
}

String& String::operator+=(const String& other) {
    char* new_str = new char [len + other.len + 1];
    copy_n(new_str, str, len);
    copy_n(new_str + len, other.str, other.len + 1);
    delete[] str;
    str = new_str;
    len += other.len;
    return *this;
}

String& String::operator+=(char c) {
    char* new_str = new char [len + 2];
    copy_n(new_str, str, len);
    new_str[len] = c;
    new_str[len + 1] = 0;
    delete[] str;
    str = new_str;
    len += 1;
    return *this;
}

void String::print() const {
    printf("{String [%p] '%s' len %d}\n", this, str, len);
}

String operator+(const String& s1, const String& s2) {
    String result = s1;
    result += s2;
    return result;
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

//
// LongInt
//

int char_to_digit(char c) {
    return c - '0';
}

char digit_to_char(int c) {
    return c + '0';
}

void add_arrays(List<int>& target, const List<int>& source) {
    int carry = 0;
    int max_size = max(target.size(), source.size());
    for (int i = 0; i < max_size; i +=1) {
        int sum = target.get(i) + source.get(i) + carry;
        target.set_and_fill(i, sum % 10);
        carry = sum / 10;
    }
    if (carry != 0) {
        target.set_and_fill(max_size, carry);
    }
}

struct LongInt {
    List<int> _digits;
    
    LongInt() {
        _digits.append(0);
    }

    LongInt(const char* s) {
        int len_s = strlen(s);
        for (int i = 0; i < len_s; i += 1) {
            _digits.append(char_to_digit(s[len_s - (i+1)]));
        }
    }
    
    const List<int>& digits() const {
        return _digits;
    }
    
    LongInt& operator +=(const LongInt& other) {
        add_arrays(_digits, other._digits);
        return *this;
    }
    
    LongInt& operator*=(const LongInt& other) {
        LongInt result;
        
        int subresult_offset = 0;
        for (int i = 0; i < _digits.size(); i += 1) {
            LongInt subresult;
            int subresult_carry = 0;
            for (int j = 0; j < other._digits.size(); j += 1) {
                int product = _digits[i] * other._digits[j] + subresult_carry;
                subresult._digits.set_and_fill(j + subresult_offset, product % 10);
                subresult_carry = product / 10;
            }
            if (subresult_carry != 0) {
                subresult._digits.set_and_fill(other._digits.size() + subresult_offset, subresult_carry);
            }
            
            result += subresult;
            subresult_offset += 1;
        }
        (*this) = result;
        return *this;
    }
    
};

LongInt operator*(const LongInt& i1, const LongInt& i2) {
    LongInt result = i1;
    result *= i2;
    return result;
}

LongInt operator+(const LongInt& i1, const LongInt& i2) {
    LongInt result = i1;
    result += i2;
    return result;
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

//
// utils
//

String obj_to_string(int i) {
    char buf[30];
    sprintf(buf, "%d", i);
    return String(buf);
}

String obj_to_string(const String& s) {
    return s;
}

template <typename T>
String obj_to_string(const List<T>& list) {
    String result("[");
    for (int i = 0; i < list.size(); i += 1){
        T d = list.elements[i];
        if (i) {
            result += String(", ");
        }
        result += obj_to_string(d);
    }
    result += String("]");
    return result;
}

String obj_to_string(const LongInt& number) {
    String result("");
    bool nonzero_found = false;
    for (int i = number.digits().size() - 1; i > -1; i -= 1){
        int d = number.digits()[i];
        if (d != 0 || nonzero_found) {
            result += digit_to_char(d);
            nonzero_found = true;
        }
    }
    if (!nonzero_found){
        result += '0';
    }
    return result;
}

template <typename T>
void print(const List<T>& list, const char* end = "") {
    printf("%s%s", list.to_string().str, end);
}

void clear(){
    for (int i = 0; i < 97; i += 1) {
        printf("\n");
    }
}

template <typename T>
List<T> sort_list(const List<T>& list) {
    Tree<T> tree;
    for (int i = 0; i < list.size(); i += 1){
        tree.add(list[i]);
    }
    tree.sorted_tree(*tree.root);
    return tree.list;
}
