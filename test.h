//
// Created by asus on 2022/5/7.
//

#ifndef DATATYPE_TEST_H
#define DATATYPE_TEST_H
#include <iostream>
#include "Iterator.h"
class Test : public Iterable<int>{
public:
    class Iter : public Iterator<int>{
    public:
        int *arr;
        int n = 0, nmax;
        Iter(int *arr, int nmax){
            this->arr = arr;
            this->nmax = nmax;
        }
        bool hasNext() override{
            return n < nmax;
        }
        int& next() override{
            return arr[n++];
        }
    };
    int* arr = new int[10]();

    Iterator<int>* iterator() const override{
        return new Iter(arr, 10);
    }
};
#endif //DATATYPE_TEST_H
