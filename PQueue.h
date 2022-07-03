//
// Created by asus on 2022/4/9.
//

#ifndef DATATYPE_PQUEUE_H
#define DATATYPE_PQUEUE_H

#include "Iterator.h"

//priority queue
template<class T>
class PQueue : public Object{
private:
    T* arr = nullptr;
    int size = 0;
    int len = 0;
    int (*cmp)(const T&, const T&);

    void deepcopy(const PQueue<T> & src);
    void float_elem(int n);
    void sink_elem(int n);

public:
    explicit PQueue(int (*cmp)(const T&, const T&)=default_cmp<T>);
    explicit PQueue(int n, int (*cmp)(const T&, const T&)=default_cmp<T>); //size
    PQueue(const std::initializer_list<T>& q, int (*cmp)(const T&, const T&)=default_cmp<T>);
    PQueue(const Iterable<T>& q, int (*cmp)(const T&, const T&)=default_cmp<T>);
    PQueue(const PQueue<T>& q);
    PQueue(PQueue<T>&& array) noexcept;
    ~PQueue();
    
    inline int length() const{return len;}
    void resize(int n);
    void set_cmp(int (*cmp)(const T&, const T&)){this->cmp = cmp;}

    PQueue<T>& operator=(const PQueue<T>& src);
    PQueue<T>& operator=(PQueue<T>&& array) noexcept;
    PQueue<T> operator+(const PQueue<T>& src); //concat
    PQueue<T>& operator+=(const PQueue<T>& src);
    PQueue<T>& operator<<(const T& val); //append
    PQueue<T>& operator<<(T&& val); //append

    T pop();
    void clear();


    std::string type() const override{return "PQueue<" + Type(T()) + ">";}
    std::string toString() const override{
        std::string output;
        output = "[";
        for(int i = 1; i <= len - 1; i++){
            output += Str(arr[i]) + ",";
        }
        if(len > 0) output += Str(arr[len]);
        output += "]";
        return output;
    }
};

template<class T>
void PQueue<T>::deepcopy(const PQueue<T> &src) {
    if(size < src.len + 1) resize(src.len + 1);
    for(int i = 1; i <= src.len; i++) arr[i] = src.arr[i];
    len = src.len;
    cmp = src.cmp;
}

template<class T>
void PQueue<T>::resize(int n) {
    T* arr0 = arr;
    arr = new T[n];
    size = n;
    for(int i = 0; i < len; i++) arr[i] = std::move(arr0[i]);
    if(arr0 != nullptr) delete [] arr0;
}


template<class T>
PQueue<T>::PQueue(int (*cmp)(const T&, const T&)) : cmp(cmp){

}

template<class T>
PQueue<T>::PQueue(int n, int (*cmp)(const T&, const T&)) : cmp(cmp) {
    arr = new T[n];
    size = n;
}

template<class T>
PQueue<T>::PQueue(const std::initializer_list<T>& q, int (*cmp)(const T&, const T&)) : cmp(cmp) {
    resize(q.size());
    for(const T& val : q){
        (*this) << val;
    }
}

template<class T>
PQueue<T>::PQueue(const Iterable<T>& q, int (*cmp)(const T&, const T&)) : cmp(cmp) {
    resize(q.length());
    for(const T& val : q){
        (*this) << val;
    }
}

template<class T>
PQueue<T>::PQueue(const PQueue<T> &q) {
    deepcopy(q);
}

template<class T>
PQueue<T>::~PQueue() {
    for(int i = 0; i < len; i++) arr[i].~T();
    if(size > 0) delete [] arr;
    len = 0;
    size = 0;
    arr = nullptr;
}

template<class T>
PQueue<T> &PQueue<T>::operator=(const PQueue<T> &src) {
    if(this != &src) deepcopy(src);
    return (*this);
}

template<class T>
PQueue<T> PQueue<T>::operator+(const PQueue<T> &src) {
    PQueue<T> pq((*this));
    for(int i = 1; i <= src.len; i++) pq << src.arr[i];
    return std::move(pq);
}

template<class T>
PQueue<T> &PQueue<T>::operator+=(const PQueue<T> &src) {
    for(int i = 1; i <= src.len; i++) (*this) << src.arr[i];
    return (*this);
}

template<class T>
PQueue<T> &PQueue<T>::operator<<(const T& val) {
    len++;
    if(len >= size) resize(len * 2);
    arr[len] = val;
    float_elem(len);
    return (*this);
}

template<class T>
PQueue<T> &PQueue<T>::operator<<(T &&val) {
    len++;
    if(len >= size) resize(len * 2);
    arr[len] = val;
    float_elem(len);
    return (*this);
}

template<class T>
T PQueue<T>::pop() {
    if(len <= 0) throw err("length 0");
    T elem = std::move(arr[1]);
    arr[1] = std::move(arr[len]);
    len--;
    sink_elem(1);
    return std::move(elem);
}

template<class T>
void PQueue<T>::clear() {
    len = 0;
}

template<class T>
void PQueue<T>::float_elem(int n) {
    int i;
    T temp = std::move(arr[n]);
    for(i = n; i > 1; i /= 2){
        if(cmp(arr[i / 2], temp) > 0) break;
        arr[i] = std::move(arr[i / 2]);
    }
    arr[i] = std::move(temp);
}

template<class T>
void PQueue<T>::sink_elem(int n) {
    int i;
    T temp = std::move(arr[n]);
    for(i = n; i * 2 <= len; ){
        int index = i * 2;
        if(index + 1 < len && cmp(arr[index + 1], arr[index]) > 0) index++;
        if(cmp(temp, arr[index]) > 0) break;
        arr[i] = std::move(arr[index]);
        i = index;
    }
    arr[i] = std::move(temp);
}

template<class T>
PQueue<T>::PQueue(PQueue<T> &&array) noexcept{
    if(&array != this){
        len = array.len;
        size = array.size;
        arr = array.arr;

        array.arr = nullptr;
        array.len = 0;
        array.size = 0;
    }
}

template<class T>
PQueue<T> &PQueue<T>::operator=(PQueue<T> &&array) noexcept{
    if(&array != this){
        len = array.len;
        size = array.size;
        arr = array.arr;

        array.arr = nullptr;
        array.len = 0;
        array.size = 0;
    }
    return *this;
}



#endif //DATATYPE_PQUEUE_H
