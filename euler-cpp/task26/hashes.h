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

int hash(const String& s) {
    return hash(s.str());
}

template < typename T > 
struct HashSet {
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
    
    
    int _size;
    List<Bucket> buckets;
    
    HashSet() {
        _size = 0;
        buckets.append(Bucket());
        buckets.append(Bucket());
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
        List<Bucket> new_buckets;
        new_buckets.set_and_fill(buckets.size() * 2, Bucket());
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
/*
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

 */
template <typename K, typename V>
struct Item {
	K key;
	V value;
	
	Item(){
	}
	
	Item(const Item& other){
		key = other.key;
		value = other.value;
	}
	
	~Item(){
	}
	
	Item(const K& k, const V& v)
		: key(k), value(v)
	{
	}
	
	
};

template <typename K, typename V>
struct Bucket {
	List< Item<K, V> > list_of_items;
	
	Bucket(){
	}
	
	int size(){return list_of_items.size();}
	
	void add(K k, V v){
		Item<K, V> t(k, v);
		list_of_items.append(t);
	}
	
	void add(Item<K, V> t) {
		add(t.key, t.value);
	}
	
	bool contains(K k) {
		for (int j = 0; j < list_of_items.size(); j += 1) {
			if (k == list_of_items[j].key) {
				return true;
			}
		}
		return false;
	}
	
	Item<K, V>& operator[](K k) {
		int index=0;
		for(int i = 0; i < size(); i += 1){
			if (k == list_of_items[i].key) {
				index = i;
			}
		}
		return list_of_items[index];
	}
	
};

template <typename K, typename V>
struct HashMap {
    int _size;
    List< Bucket<K, V> >  buckets;
    
    HashMap() {
        _size=0; 
        buckets.append(Bucket<K, V>());
    }
    
    V get(K key, V def_value=V());
    
    void add(K key, V value);    
    
    V operator[](K key);
    
    void rehash();
    
    bool contains(K k);
    
    int size(){return _size;}
};
template < typename K, typename V > String obj_to_string(const Item<K, V>& item) {
	return obj_to_string(item.key) + " -> " + obj_to_string(item.value);
}

template < typename K, typename V > String obj_to_string(const Bucket<K, V>& bucket) {
	return obj_to_string(bucket.list_of_items);
}


template < typename K, typename V > 
String obj_to_string(const HashMap<K, V>& set) {
    String result("{");
    
    bool write_comma = false;
    
    for (int i = 0; i < set.buckets.size(); i += 1) {
        for (int j = 0; j < set.buckets[i].list_of_items.size(); j += 1) {
            Item<K, V> d = set.buckets[i].list_of_items[j];
            if (write_comma) {
                result += String(", ");
            } else {
                write_comma = true;
            }
            result += obj_to_string(d.key) + ": " + obj_to_string(d.value);
        }
    }
        
    result += String("}");
    return result;
}



template<typename K, typename V> 
int hash(const typename HashMap<K, V>::Item& i){
     return hash(i.key);
}

template<typename K, typename V> 
void HashMap<K, V>::add(K key, V value){
    int h = hash(key);
    h = h % buckets.size();
    if (contains(key)) {
        buckets[h][key] = Item<K, V>(key, value);
    } else {
        _size += 1;
        buckets[h].add(key, value);
        if (size() * 0.75 > buckets.size()){
            rehash();
        }
    }
}

template<typename K, typename V>
void HashMap<K, V>::rehash() {
    List< Bucket<K, V> > new_buckets;
    new_buckets.set_and_fill(buckets.size() * 2, Bucket<K, V>());
    for (int i = 0; i < buckets.size(); i += 1) {
        for (int j = 0; j < buckets[i].list_of_items.size(); j += 1) {
            K d = buckets[i].list_of_items[j].key;
            int h = hash(d);
            h = h % new_buckets.size();
            new_buckets[h].add(buckets[i].list_of_items[j]);
        }
    }
    buckets = new_buckets;
}

template<typename K, typename V>
bool HashMap<K, V>::contains(K k){
    int h = hash(k);
    h = h % buckets.size();
    return buckets[h].contains(k);
}


void test(){
    HashMap<String, int> m;
    m.add("hhh", 8);
    printf("\n=====================\nmap is %s\n=====================\n", obj_to_string(m).str());
    m.add("hh", 88);
    printf("\n=====================\nmap is %s\n=====================\n", obj_to_string(m).str());
    m.add("hhh", 9);
    printf("\n=====================\nmap is %s\n=====================\n", obj_to_string(m).str());
    return;
/*     HashSet<int> h;
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
 */}
