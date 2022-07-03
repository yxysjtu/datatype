//
// Created by asus on 2022/4/9.
//

#ifndef DATATYPE_LIST_H
#define DATATYPE_LIST_H

#include "Iterator.h"

template<class T>
class List : public Iterable<T>{
private:
    int len;

    void deepcopy(const List<T>& src);
    void init();

    struct node{
        T val;
        node *next;
        node(){next = nullptr;}
        explicit node(const T &v):val(v){next = nullptr;}
        explicit node(T &&v):val(v){next = nullptr;}
    };
    node *head = nullptr, *tail = nullptr;

    class Iter : public Iterator<T>{
    private:
        node *n, *end;
    public:
        Iter(node *nd, node* end){
            n = nd;
            this->end = end;
        }
        bool hasNext() override{
            return n != end;
        }
        T& next() override{
            n = n->next;
            return n->val;
        }
    };

public:
    List();
    List(T* src, int n);
    List(const std::initializer_list<T>& sl);
    List(const List<T>& sl);
    List(List<T>&& sl) noexcept;
    List(int n, const T& init_val);
    List(const Iterable<T>& src);

    ~List();

    inline int length() const override{return len;}

    List<T>& operator=(const List<T>& src);
    List<T>& operator=(List<T>&& sl) noexcept;
    List<T>& operator=(const Iterable<T>& src);
    List<T> operator+(const List<T>& src); //concat
    List<T>& operator+=(const List<T>& src);
    T &operator[](int index);
    T operator[] (int index) const;
    List<T> operator[](Range r) const;
    List<T>& operator<<(const T& val); //append
    List<T>& operator<<(T&& val); //append
    bool operator==(const List<T> &src);
    bool operator!=(const List<T> &src);


    List<T>& insert(int index, const T& val);
    T pop(int index=-1);
    void clear();

    int find(T val);

    Iterator<T>* iterator() const override{
        return new Iter(head, tail);
    }

    std::string type() const override{return "List<" + Type(T()) + ">";}
    std::string toString() const override{
        std::string output;
        node* n = head->next;
        output = "[";
        for(int i = 0; i < len - 1; i++){
            output += Str(n->val) + ",";
            n = n->next;
        }
        if(len > 0) output += Str(n->val) + "]";
        return std::move(output);
    }

};

template<class T>
void List<T>::deepcopy(const List<T> &src) {
    clear();
    //foreach(src, T val) (*this) << val;
    foreach(T& val, src, {
        (*this) << val;
    });
}

template<class T>
void List<T>::init() {
    head = new node;
    len = 0;
    tail = head;
}

template<class T>
List<T>::List() {
    init();
}

template<class T>
List<T>::List(T *src, int n){
    init();
    for(int i = 0; i < n; i++) (*this) << src[i];
}

template<class T>
List<T>::List(const std::initializer_list<T>& sl){
    init();
    for(const T &val : sl) (*this) << val;
}

template<class T>
List<T>::List(const List<T> &sl){
    init();
    deepcopy(sl);
}

template<class T>
List<T>::List(int n, const T& init_val){
    init();
    for(int i = 0; i < n; i++) (*this) << init_val;
}

template<class T>
List<T>::~List() {
    clear();
    if(head != nullptr){
        delete head;
        head = nullptr;
    }
}


template<class T>
List<T> List<T>::operator+(const List<T> &src) {
    List<T> sl2(*this);
    foreach(T& val, src, {
        sl2 << val;
    });
    return std::move(sl2);
}

template<class T>
List<T> &List<T>::operator+=(const List<T> &src) {
    foreach(T& val, src, {
        (*this) << val;
    })
    return (*this);
}

template<class T>
T &List<T>::operator[](int index) {
    if(index >= len || index < 0) throw err("index out of range");

    node *n = head->next;
    for(int i = 0; i < index; i++){
        n = n->next;
    }
    return n->val;
}

template<class T>
T List<T>::operator[](int index) const {
    if(index >= len || index < 0) throw err("index out of range");

    node *n = head->next;
    for(int i = 0; i < index; i++){
        n = n->next;
    }
    return n->val;
}

template<class T>
List<T> List<T>::operator[](Range r) const {
    List<T> result;
    node* n = head->next;
    if(r.end < 0) r.end += len;
    if(r.end < r.start) throw err("index out of range");
    if(r.end > len) r.end = len;

    for(int i = 0; i < r.start; i++) n = n->next;
    for(int i = r.start; i < r.end; i += r.step){
        result << n->val;
        for(int j = 0; j < r.step && n != nullptr; j++)
            n = n->next;
    }
    return std::move(result);
}
template<class T>
List<T> &List<T>::operator<<(const T& val) {
    node *n = new node(val);
    tail->next = n;
    tail = n;
    len++;
    return (*this);
}

template<class T>
List<T> &List<T>::operator<<(T&& val) {
    node *n = new node(val);
    tail->next = n;
    tail = n;
    len++;
    return (*this);
}

template<class T>
bool List<T>::operator==(const List<T> &src) {
    if(src.len != len) return false;
    if(this == &src) return true;
    node *n = head, *n1 = src.head;
    for(int i = 0; i < len; i++){
        n = n->next;
        n1 = n1->next;
        if(n->val != n1->val) return false;
    }
    return true;
}

template<class T>
bool List<T>::operator!=(const List<T> &src) {
    return !((*this) == src);
}

template<class T>
List<T> &List<T>::insert(int index, const T& val) {
    if(index < 0) index += len;
    if(index > len || index < 0) throw err("index out of range");
    if(index == len) return ((*this) << val);

    node *n = head;
    for(int i = 0; i < index; i++) n = n->next;
    node *m = new node(val);
    m->next = n->next;
    n->next = m;
    len++;
    return (*this);
}

template<class T>
T List<T>::pop(int index) {
    if(index < 0) index += len;
    if(index >= len || index < 0) throw err("index out of range");

    node *n = head;
    T result;
    for(int i = 0; i < index; i++) n = n->next;
    node *t = n->next;
    n->next = t->next;
    result = std::move(t->val);
    //t->val.~T();
    delete t;
    if(index == len - 1) tail = n;
    len--;
    return std::move(result);
}

template<class T>
void List<T>::clear() {
    if(len == 0) return;
    node *n = head->next, *t;
    for(int i = 0; i < len; i++) {
        t = n->next;
        n->val.~T();
        delete n;
        n = t;
    }
    len = 0;
    tail = head;
    tail->next = nullptr;
}

template<class T>
int List<T>::find(T val) {
    node *n = head;
    for(int i = 0; i < len; i++){
        n = n->next;
        if(n->val == val) return i;
    }
    return -1;
}

template<class T>
List<T>::List(const Iterable<T>& src) {
    init();
    foreach(T& i, src, {
        (*this) << i;
    });
}

template<class T>
List<T> &List<T>::operator=(const Iterable<T> &src) {
    if(len > 0) clear();
    foreach(T& i, src, {
        (*this) << i;
    });
    return (*this);
}

template<class T>
List<T> &List<T>::operator=(const List<T> &src) {
    if(&src == this) return *this;
    if(len > 0) clear();
    foreach(T& i, src, {
        (*this) << i;
    });
    return (*this);
}

template<class T>
List<T>::List(List<T> &&sl) noexcept{
    if(&sl != this){
        head = sl.head;
        tail = sl.tail;
        len = sl.len;

        sl.len = 0;
        sl.head = sl.tail = nullptr;
    }
}

template<class T>
List<T> &List<T>::operator=(List<T> &&sl) noexcept{
    if(&sl != this){
        head = sl.head;
        tail = sl.tail;
        len = sl.len;

        sl.len = 0;
        sl.head = sl.tail = nullptr;
    }
    return *this;
}


#endif //DATATYPE_LIST_H
