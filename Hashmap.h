//
// Created by asus on 2022/5/1.
//

#ifndef DATATYPE_HASHMAP_H
#define DATATYPE_HASHMAP_H

template<class K, class V>
class Hashmap{
private:
    int len = 0;
    int size = 16;

    struct node{
        K key;
        V val;
        node* next;
        node(K key, V val) : key(key), val(val) { next = nullptr;}
    };

    node* arr;

public:

};

#endif //DATATYPE_HASHMAP_H
