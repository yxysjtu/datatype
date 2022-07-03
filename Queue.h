//
// Created by asus on 2022/4/9.
//

#ifndef DATATYPE_QUEUE_H
#define DATATYPE_QUEUE_H

#include "List.h"

template<class T>
class Queue : public Object{
private:
    List<T> arr;

public:
    Queue();
    Queue(const Queue& Queue);
    Queue(Queue&& Queue) noexcept;
    Queue(const std::initializer_list<T>& Queue);
    Queue(const Iterable<T>& src);

    inline int length() const{return arr.length();}

    Queue& operator=(const Queue<T>& src);
    Queue& operator=(Queue<T>&& src) noexcept;
    Queue& operator=(const Iterable<T>& src);
    Queue& operator<<(const T& val);
    Queue& operator<<(T&& val);
    T& top();
    T pop();

    std::string type() const override{return "Queue<" + Type(T()) + ">";}
    std::string toString() const override{
        return arr.toString();
    }

};

template<class T>
Queue<T>::Queue() {

}

template<class T>
Queue<T>::Queue(const Queue &Queue) {
    arr = Queue.arr;
}

template<class T>
Queue<T>::Queue(Queue &&Queue) noexcept{
    arr = std::move(Queue.arr);
}
template<class T>
Queue<T>::Queue(const std::initializer_list<T>& Queue) {
    for(const T& val : Queue){
        arr << val;
    }
}

template<class T>
Queue<T> &Queue<T>::operator<<(const T& val) {
    arr << val;
    return (*this);
}

template<class T>
Queue<T> &Queue<T>::operator<<(T&& val) {
    arr << val;
    return (*this);
}

template<class T>
T& Queue<T>::top(){
    return arr[0];
}

template<class T>
T Queue<T>::pop() {
    return arr.pop(0);
}

template<class T>
Queue<T>::Queue(const Iterable<T> &src) {
    arr = src;
}

template<class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &src) {
    arr = src.arr;
    return (*this);
}

template<class T>
Queue<T> &Queue<T>::operator=(Queue<T> &&src) noexcept{
    arr = std::move(src.arr);
    return (*this);
}

template<class T>
Queue<T> &Queue<T>::operator=(const Iterable<T> &src) {
    arr = src;
    return (*this);
}

#endif //DATATYPE_QUEUE_H
