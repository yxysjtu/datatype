//
// Created by asus on 2022/4/30.
//

#ifndef DATATYPE_CQUEUE_H
#define DATATYPE_CQUEUE_H

#include "Iterator.h"

//circular queue
template<class T>
class CQueue : public Iterable<T>{
private:
    T* arr;
    int i0 = 0, i1 = 0, size;

    class Iter : public Iterator<T>{
    private:
        T* arr;
        int n, end, i, size;
    public:
        Iter(T* arr0, int n0, int end, int size) : size(size){
            arr = arr0;
            n = n0;
            i = n;
            this->end = end;
        }
        bool hasNext() override{
            return i != end;
        }
        T& next() override{
            T& r = arr[i];
            i = (i + 1) % size;
            return r;
        }
    };

public:
    explicit CQueue(int n);
    CQueue(const std::initializer_list<T>& sl);
    CQueue(const CQueue<T>& sl);
    CQueue(CQueue<T>&& sl) noexcept;
    CQueue(const Iterable<T>& sl, int size);
    CQueue(int n, const T& init_val);
    ~CQueue();

    inline int length() const {return (i1 - i0 + size) % size;}
    inline int capacity(){return size - 1;}

    CQueue<T>& operator=(const CQueue<T>& src);
    CQueue<T>& operator=(CQueue<T>&& src) noexcept;
    CQueue<T>& operator<<(const T& val); //append
    CQueue<T>& operator<<(T&& val); //append
    T &operator[](int index);
    T operator[] (int index) const;
    T pop();
    void clear();


    Iterator<T>* iterator() const override{
        return new Iter(arr, i0, i1, size);
    }

    std::string type() const override{return "CQueue<" + Type(T()) + ">";}
    std::string toString() const override{
        std::string output;
        output = "[";
        for(int i = 0; i < length() - 1; i++){
            output += Str(arr[i]) + ",";
        }
        if(length()> 0) output += Str(arr[length() - 1]);
        output += "]";
        return output;
    }
};

template<class T>
CQueue<T>::CQueue(int n) {
    size = n + 1;
    arr = new T[size];
}

template<class T>
CQueue<T>::CQueue(const std::initializer_list<T>& sl) {
    size = sl.size() + 1;
    arr = new T[size];
    for(const T& val : sl){
        arr[i1++] = val;
    }
}

template<class T>
CQueue<T>::CQueue(const CQueue<T> &sl) {
    size = sl.size;
    arr = new T[size];
    for(i1 = 0; i1 < sl.length(); i1++) arr[i1] = sl[i1];
}

template<class T>
CQueue<T>::CQueue(CQueue<T> &&sl) noexcept{
    size = sl.size;
    arr = sl.arr;
    sl.size = 0;
    sl.arr = nullptr;
}

template<class T>
CQueue<T>::CQueue(const Iterable<T> &sl, int size) : size(size){
    arr = new T[size];
    foreach(T& val, sl, {
        (*this) << val;
    });
}

template<class T>
CQueue<T>::CQueue(int n, const T& init_val) {
    size = n + 1;
    arr = new T[size];
    for(i1 = 0; i1 < n; i1++) arr[i1] = init_val;
}

template<class T>
CQueue<T>::~CQueue() {
    if(size > 0) delete [] arr;
}

template<class T>
CQueue<T> &CQueue<T>::operator=(const CQueue<T> &src) {
    if(this != &src){
        i0 = 0;
        for(i1 = 0; i1 < src.length(); i1++) arr[i1] = src[i1];
    }
    return (*this);
}

template<class T>
CQueue<T> &CQueue<T>::operator=(CQueue<T> &&src) noexcept{
    if(this != &src){
        i0 = src.i0;
        i1 = src.i1;
        arr = src.arr;

        src.size = 0;
        src.arr = nullptr;
    }
    return (*this);
}


template<class T>
CQueue<T> &CQueue<T>::operator<<(const T& val) {
    arr[i1] = val;
    i1 = (i1 + 1) % size;
    if(i1 == i0) i0 = (i0 + 1) % size;
    return (*this);
}

template<class T>
CQueue<T> &CQueue<T>::operator<<(T&& val) {
    arr[i1] = val;
    i1 = (i1 + 1) % size;
    if(i1 == i0) i0 = (i0 + 1) % size;
    return (*this);
}

template<class T>
T &CQueue<T>::operator[](int index) {
    if(index < 0 || index >= length()) throw err("index out of range");
    return arr[(index + i0) % size];
}

template<class T>
T CQueue<T>::operator[](int index) const {
    if(index < 0 || index >= length()) throw err("index out of range");
    return arr[(index + i0) % size];
}

template<class T>
T CQueue<T>::pop() {
    if(length() <= 0) throw err("length 0");
    T r = std::move(arr[i0]);
    i0 = (i0 + 1) % size;
    return std::move(r);
}

template<class T>
void CQueue<T>::clear() {
    /*i0 = 0;
    i1 = 0;*/
    while(length() > 0){
        pop();
    }
}

#endif //DATATYPE_CQUEUE_H
