//
// Created by asus on 2022/4/8.
//

#ifndef DATATYPE_ARRAY_H
#define DATATYPE_ARRAY_H

#include "Iterator.h"

/*
 * there's a common problem among collections, that is, if you throw new instance() into the container, the memory will not be recycled
 * unless I implement smart ptr or garbage recycling*/

template<class T>
class Array : public Iterable<T>{
private:
    T* arr = nullptr;
    int size = 0;
    int len = 0;

    void deepcopy(const Array<T>& src);

    class Iter : public Iterator<T>{
    private:
        T* arr;
        int n = 0, nmax;
    public:
        Iter(T* arr0, int n0){
            arr = arr0;
            nmax = n0;
        }
        bool hasNext() override{
            return n < nmax;
        }
        T& next() override{
            return arr[n++];
        }
    };

public:
    Array();
    explicit Array(int n);
    Array(T* array, int n);
    Array(const std::initializer_list<T>& array);
    Array(const Array<T>& array);
    Array(Array<T>&& array) noexcept;
    Array(int n, const T& init_val);
    Array(const Iterable<T>& array);
    ~Array();

    inline int length() const override{return len;}

    Array<T>& operator=(const Array<T>& src);
    Array<T>& operator=(Array<T>&& array) noexcept;
    Array<T>& operator=(const Iterable<T>& src);
    Array<T> operator+(const Array<T>& src); //concat
    Array<T>& operator+=(const Array<T>& src);
    T &operator[](int index);
    T operator[](int index) const;
    Array<T> operator[](Range r) const;
    Array<T>& operator<<(const T& val); //append
    Array<T>& operator<<(T&& val); //append
    bool operator==(const Array<T> &src);
    bool operator!=(const Array<T> &src);

    Array<T>& insert(int index, const T& val);
    Array<T>& insert(int index, T&& val);
    T pop(int index=-1);
    void clear();
    void resize(int n);

    int find(T val);

    Iterator<T>* iterator() const override{
        return new Iter(arr, len);
    }

    std::string type() const override{return "Array<" + Type(T()) + ">";}
    std::string toString() const override{
        std::string output;
        output = "[";
        for(int i = 0; i < len - 1; i++){
            output += Str(arr[i]) + ",";
        }
        if(len > 0) output += Str(arr[len - 1]);
        output += "]";
        return std::move(output);
    }

};



template<class T>
Array<T>::Array() {
    len = 0;
    size = 0;
    arr = nullptr;
}

template<class T>
Array<T>::Array(int n) {
    len = n;
    size = n;
    arr = new T[n]();
}
template<class T>
void Array<T>::deepcopy(const Array<T> & src){
    T* arr0 = arr;
    arr = new T[src.len];
    len = src.len;
    size = len;
    for(int i = 0; i < src.len; i++) arr[i] = src[i];
    if(arr0 != nullptr){
        for(int i = 0; i < len; i++){
            arr0[i].~T();
        }
        delete [] arr0;
    }
}

template<class T>
void Array<T>::resize(int n){
    T* arr0 = arr;
    arr = new T[n];
    size = n;

    if(len > 0){
        for(int i = 0; i < len; i++){
            arr[i] = std::move(arr0[i]);
            //arr0[i].~T();
        }
        delete [] arr0;
    }
}

template<class T>
Array<T>::Array(const Array<T> &array) { //deepcopy
    deepcopy(array);
}

template<class T>
Array<T>::Array(const std::initializer_list<T>& array) { //deepcopy
    len = array.size();
    size = array.size();
    arr = new T[size];
    int i = 0;
    for(const T& val : array){
        arr[i++] = val;
    }
}

template<class T>
Array<T>::Array(T* array, int n){
    arr = new T[n];
    size = n;
    len = n;
    for(int i = 0; i < n; i++) arr[i] = array[i];
}

template<class T>
Array<T>::Array(int n, const T& init_val) {
    len = n;
    size = n;
    arr = new T[n];
    for(int i = 0; i < n; i++) arr[i] = init_val;
}

template<class T>
Array<T>::~Array() {
    clear();
}


template<class T>
Array<T> Array<T>::operator+(const Array<T> &src) {
    Array<T> arr1;
    arr1.resize(len + src.len);
    for(int i = 0; i < len; i++) arr1[i] = arr[i];
    for(int i = len; i < len + src.len; i++) arr1[i] = src[i];
    arr1.len = len + src.len;
    return std::move(arr1);
}

template<class T>
Array<T> &Array<T>::operator+=(const Array<T> &src) {
    if(size < len + src.len) resize(len + src.len);
    for(int i = len; i < len + src.len; i++) arr[i] = src[i];
    len += src.len;
    return (*this);
}

template<class T>
T &Array<T>::operator[](int index) {
    if(index < 0 || index >= len) throw err("index out of range");
    return arr[index];
}

template<class T>
T Array<T>::operator[](int index) const {
    if(index < 0 || index >= len) throw err("index out of range");
    return arr[index];
}

template<class T>
Array<T> &Array<T>::operator<<(const T& val) {
    if(len + 1 > size){
        if(len == 0) resize(1);
        else resize(len * 2); //to minimize copy
    }
    arr[len] = val;
    len++;
    return (*this);
}

template<class T>
Array<T> &Array<T>::operator<<(T&& val) {
    if(len + 1 > size){
        if(len == 0) resize(1);
        else resize(len * 2); //to minimize copy
    }

    arr[len] = val;
    len++;
    return (*this);
}

template<class T>
bool Array<T>::operator==(const Array<T> &src){
    if(src.len != len) return false;
    if(this == &src) return true;
    for(int i = 0; i < len; i++){
        if(src[i] != arr[i]) return false;
    }
    return true;
}

template<class T>
bool Array<T>::operator!=(const Array<T> &src){
    return !((*this) == src);
}

template<class T>
Array<T> &Array<T>::insert(int index, const T& val) {
    if(index < 0) index += len;
    if(index < 0 || index > len) throw err("index out of range");
    if(len + 1 > size){
        if(len == 0) resize(1);
        else resize(len * 2); //to minimize copy
    }
    for(int i = len; i > index; i--) arr[i] = std::move(arr[i - 1]);
    arr[index] = val;
    len++;
    return (*this);
}

template<class T>
Array<T> &Array<T>::insert(int index, T&& val) {
    if(index < 0) index += len;
    if(index < 0 || index > len) throw err("index out of range");
    if(len + 1 > size){
        if(len == 0) resize(1);
        else resize(len * 2); //to minimize copy
    }
    for(int i = len; i > index; i--) arr[i] = std::move(arr[i - 1]);
    arr[index] = val;
    len++;
    return (*this);
}

template<class T>
T Array<T>::pop(int index) {
    if(index < 0) index += len;
    if(index < 0 || index >= len) throw err("index out of range");
    T result = std::move(arr[index]);
    for(int i = index; i < len - 1; i++) arr[i] = std::move(arr[i + 1]);
    len--;
    //arr[len].~T();
    return std::move(result);
}

template<class T>
void Array<T>::clear() {
    for(int i = 0; i < len; i++) arr[i].~T();
    if(size > 0) delete [] arr;
    len = 0;
    size = 0;
    arr = nullptr;
}

template<class T>
int Array<T>::find(const T val) {
    for(int i = 0; i < len; i++){
        if(arr[i] == val) return i;
    }
    return -1;
}

template<class T>
Array<T>::Array(const Iterable<T>& array) {
    len = array.length();
    size = len;
    arr = new T[array.length()]();
    foreach(T& i, array, {
        (*this) << i;
    });
}

template<class T>
Array<T> &Array<T>::operator=(const Iterable<T> &src) {
    clear();
    len = src.length();
    size = len;
    arr = new T[src.length()]();
    int n = 0;
    foreach(T& i, src, {
        arr[n++] = i;
    });

    return (*this);
}

template<class T>
Array<T> &Array<T>::operator=(const Array<T> &src) {
    if(&src == this) return *this;
    clear();
    len = src.length();
    size = len;
    arr = new T[src.length()]();
    int n = 0;
    foreach(T& i, src, {
        arr[n++] = i;
    });
    return (*this);
}

template<class T>
Array<T>::Array(Array<T> &&array) noexcept{
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
Array<T> &Array<T>::operator=(Array<T> &&array) noexcept{
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

template<class T>
Array<T> Array<T>::operator[](Range r) const{
    if(r.end < 0) r.end += len;
    if(r.end < r.start) throw err("index out of range");
    if(r.end > len) r.end = len;
    Array<T> result((r.end - r.start) / r.step);
    for(int i = r.start; i < r.end; i += r.step){
        result[(i - r.start) / r.step] = arr[i];
    }
    return std::move(result);
}


#endif //DATATYPE_ARRAY_H
