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
    
    List(const T* array, int array_size) {
        elements = NULL;
        _size = 0;
        _capacity = 0;

        ensure_capacity(array_size);
        copy_n(elements, array, array_size);
        _size = array_size;
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
        required_capacity = max(required_capacity, 2*capacity());
        required_capacity = max(required_capacity, 16);
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
    
    List<T>& operator+=(const List<T>& other) {
       ensure_capacity(size() + other.size());
       copy_n(elements + size(), other.elements, other.size());
       _size += other.size();
       return *this;
    }
};

template <typename T>
List<T> operator+(const List<T>& list1, const List<T>& list2) {
    List<T> result = list1;
    result += list2;
    return result;
}

//
// String
//

struct String {
    List<char> _str;
    
    String(const char* s = "");
    
    String& operator+=(const String& other);
    
    String& operator+=(char c);
    
    const char* str() const;
    int len() const;
    
    void print() const;
    
    char operator[](int index) const;
     
    char& operator[](int index);
    
};

String::String(const char* s)
    : _str(s, strlen(s) + 1)
{
}

char String::operator[](int index) const {
    return _str[index];    
}


char& String::operator[](int index) {
    return _str[index];
}

String& String::operator+=(const String& other) {
    _str.erase(len());
    _str += other._str;
    return *this;
}

String& String::operator+=(char c) {
    _str.insert(len(), c);
    return *this;
}

const char* String::str() const {
    return _str.elements;
}

int String::len() const {
    return _str.size() - 1;
}

void String::print() const {
    printf("{String [%p] '%s' len %d}\n", this, str(), len());
}

String operator+(const String& s1, const String& s2) {
    String result = s1;
    result += s2;
    return result;
}

bool operator<(const String& s1, const String& s2) {
    for (int i = 0; true; i += 1) {
        if (s1.str()[i] == 0) {
            return true;
        } else if(s2.str()[i] == 0) {
            return false;
        } else if (s1.str()[i] < s2.str()[i]){
            return true;
        } else if (s1.str()[i] > s2.str()[i]){
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
    
    LongInt(int ix) {
        _digits.append(ix);
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


bool operator<(const LongInt& l1, const LongInt& l2) {
    if (l1.digits().size() < l2.digits().size()) {
        return true;
    } else { 
        for (int i = 0;i < max(l1.digits().size(),l2.digits().size()); i += 1) {
            // printf("len is %d i=%d\n",l1.digits().size(),i);
            if (l1.digits().get(i) < l2.digits().get(i)){
                return true;
            } else if (l1.digits().get(i) > l2.digits().get(i)){
                return false;
            }
        }
    }
    return false;
}

LongInt fastpow(const LongInt& a, int b) {
    if (b <= 3) {
        LongInt num(1);
        for (int i = 1; i <= b; i += 1){
            num *= a;
        }
        return num;
    }
    LongInt result = fastpow(a, b/2);
    if (b % 2 == 1) {
        return result * result * a;
    } else {
        return result * result;
    }
}

LongInt pow(int a, int b) {
    return fastpow(a, b);
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
        } else if (value < node_value) {
                if (node.left() == NULL){
                    node.set_left(new Node<T>(value));
                } else {
                    add_in_fking_tree(value, *node.left());
            }
        } else {
            return;
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

// Fiba 
void num_fib() {
    LongInt f1("1");
    LongInt f2("1");
    LongInt f3;
    for (int i = 3; f3.digits().size() < 10000 ; i += 1) {
        f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
        printf("%d for %d is %s\n\n", i, f3.digits().size(), obj_to_string(f3).str());
    }
}

//Revisor of divisor =)
int divisor_sum(int x){
    int sum = 1;
    for(int i = 2; i*i <= x; i += 1) {
        if (x % i == 0) {
            sum += i;
            if (i * i != x) {
                sum += x/i;
            }
        }
    }
    return sum;
}

    



