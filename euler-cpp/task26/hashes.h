#pragma once

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"

int hash(int i){
    return i;
}

int hash(const char* s){
    int x = 31;
    int size_s = strlen(s);
    int result = 0;
    for (int i = 0; i < size_s; i += 1) {
        int p = size_s - i;
        char c = s[i];
        result += pow(x, p) * c;
    }
    return result;    
}

template < typename T > 
struct Bucket {
    List<T> buck;
    
    Bucket(){
    }
    
    void add(T t){
        buck.append(t);
    }
    
    bool contains(T t) {
        for (int j = 0; j < buck.size(); j += 1) {
            if (t == buck[j]) {
                return true;
            }
        }
        return false;
    }
    
    
};

template < typename T > 
struct HashSet {
    int _size;
    List<Bucket<T> > buckets;
    
    HashSet() {
        _size = 0;
        buckets.append(Bucket<T>());
        buckets.append(Bucket<T>());
    }
    
    void add(T t){
        if (contains(t)) {
            return;
        }
        _size += 1;
        int h = hash(t);
        h = h % buckets.size();
        buckets[h].add(t);
        if (size() * 0.75 > buckets.size()){
            rehash();
        }
    }
    
    bool contains(T t){
        int h = hash(t);
        h = h % buckets.size();
        return buckets[h].contains(t);
    }
    
    int size(){
        return _size;
    }
    
    void rehash() {
        List<Bucket<T> > new_buckets;
        new_buckets.set_and_fill(buckets.size() * 2, Bucket<T>());
        for (int i = 0; i < buckets.size(); i += 1) {
            for (int j = 0; j < buckets[i].buck.size(); j += 1) {
                T d = buckets[i].buck[j];
                int h = hash(d);
                h = h % new_buckets.size();
                new_buckets[h].add(d);
            }
        }
        buckets = new_buckets;
    }
};

/*
template < typename T > 
String obj_to_string(const HashSet<T>& set) {
    String result("{");
    
    bool write_comma = false;
    
    for (int i = 0; i < set.buckets.size(); i += 1) {
        for (int j = 0; j < set.buckets[i].buck.size(); j += 1) {
            T d = set.buckets[i].buck[j];
            if (write_comma) {
                result += String(", ");
            } else {
                write_comma = true;
            }
            result += obj_to_string(d);
        }
    }
        
    result += String("}");
    return result;
}

 */
template < typename T > 
String obj_to_string(const HashSet<T>& set) {
    String result("{");
    int set_size = set.buckets.size();
    for (int i = 0; i < set_size; i += 1) {
        result += obj_to_string(set.buckets[i].buck);
        if (i < set_size - 1){
            result += String("; ");
        }
    }

    result += String("}");
    return result;
}

void test(){
    HashSet<int> h;
    printf("begin\nsize is %d\nhash is %s\n", h.size(), obj_to_string(h).str());
    h.add(1);
    h.add(3);
    h.add(5);
    printf("\nafter\nsize is %d\nhash is %s\n", h.size(), obj_to_string(h).str());
    printf("7 is ");
    if (h.contains(7)){
        printf("contain\n");
    } else {         
        printf("not contain\n");
    }
    h.add(3);
    h.add(5);
    h.add(7);
    printf("\nend\nsize is %d\nhash is %s\n", h.size(), obj_to_string(h).str());
    printf("after add 7 is ");
    if (h.contains(7)){
        printf("contain\n");
    } else {        
        printf("not contain\n");
    }
    
    printf("\ndebug\nfor \"abc\" Hash = %d\n", hash("abc"));
    printf("for \"cba\" Hash = %d\n", hash("cba"));
    printf("for \"abcdef\" Hash = %d\n", hash("abcdef"));
    printf("for \"000\" Hash = %d\n", hash("000"));
}
