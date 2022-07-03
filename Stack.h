//
// Created by asus on 2022/4/9.
//

#ifndef DATATYPE_STACK_H
#define DATATYPE_STACK_H

#include "Array.h"

template<class T>
class Stack : public Object{
private:
    Array<T> arr;

public:
    Stack();
    Stack(const Stack& stack);
    Stack(Stack&& stack) noexcept;
    Stack(const std::initializer_list<T>& stack);
    Stack(const Iterable<T>& src);

    inline int length() const{return arr.length();}

    Stack& operator=(const Stack<T>& src);
    Stack& operator=(Stack<T>&& src) noexcept;
    Stack& operator=(const Iterable<T>& src);
    Stack& operator<<(const T& val);
    Stack& operator<<(T&& val);
    T& top();
    T pop();

    std::string type() const override{return "Stack<" + Type(T()) + ">";}
    std::string toString() const override{
        return arr.toString();
    }

};

template<class T>
Stack<T>::Stack() {

}

template<class T>
Stack<T>::Stack(const Stack &stack) {
    arr = stack.arr;
}

template<class T>
Stack<T>::Stack(Stack &&stack) noexcept{
    arr = std::move(stack.arr);
}

template<class T>
Stack<T>::Stack(const std::initializer_list<T>& stack) {
    for(const T& val : stack){
        arr << val;
    }
}

template<class T>
Stack<T> &Stack<T>::operator<<(const T& val) {
    arr << val;
    return (*this);
}

template<class T>
Stack<T> &Stack<T>::operator<<(T&& val) {
    arr << val;
    return (*this);
}

template<class T>
T& Stack<T>::top(){
    return arr[length() - 1];
}

template<class T>
T Stack<T>::pop() {
    return arr.pop();
}

template<class T>
Stack<T>::Stack(const Iterable<T> &src) {
    arr = src;
}

template<class T>
Stack<T> &Stack<T>::operator=(const Iterable<T> &src) {
    arr = src;
    return (*this);
}

template<class T>
Stack<T> &Stack<T>::operator=(const Stack<T> &src) {
    arr = src.arr;
    return (*this);
}

template<class T>
Stack<T> &Stack<T>::operator=(Stack<T> &&src) noexcept{
    arr = std::move(src.arr);
    return (*this);
}

#endif //DATATYPE_STACK_H
