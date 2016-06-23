#include <stdio.h>
#include <string.h>
#include <math.h>

#pragma once

#include "utils.h"

int hash(int i){
    return i;
}

int hash(const char* s){
    return 0;
}

template < typename T > 
struct Bucket {
    List<T> buck;
    
    Bucket(){
    }
    
    void add(T i){
        buck.append(i);
    }
    
    bool contains(T i) {
        for (int j = 0; j < buck.size(); j += 1) {
            if (i == buck[j]) {
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
        Bucket<T> b1;
        Bucket<T> b2;
        buckets.append(b1);
        buckets.append(b2);
    }
    
    void add(T i){
        if (contains(i)) {
            return;
        }
        _size += 1;
        int h = hash(i);
        h = h % buckets.size();
        buckets[h].add(i);
        if (size() * 0.75 > buckets.size()){
            rehash();
        }
    }
    
    bool contains(T i){
        int h = hash(i);
        h = h % buckets.size();
        return buckets[h].contains(i);
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

/* template < typename T > 
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
}
