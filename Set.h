//
// Created by asus on 2022/5/1.
//

#ifndef DATATYPE_SET_H
#define DATATYPE_SET_H

#include "Iterator.h"

//TODO:Iterator

template<class T>
class Set : public Iterable<T>{
private:
    struct node{
        bool color;
        node* left;
        node* right;
        T val;
        node() {color = false; left = nullptr; right = nullptr;}
        explicit node(bool color, const T& val) : val(val), color(color) {left = nullptr; right = nullptr;}
    };
    
    node* root = nullptr;
    int len = 0;

    int (*cmp)(const T&, const T&);

    void remove_tree(node* n);
    node* rotate_left(node *n);
    node* rotate_right(node *n);
    void flip_colors(node *n);
    node* put(node *n, const T& val);
    bool equal_tree(node *n, node *m);

    node* del(node *n, const T& val);
    node* delMin(node *n, node *min); //return root
    node* move_left(node *n);
    node* move_right(node *n);
    bool isRed(node *n);

public:
    explicit Set(int (*cmp)(const T&, const T&)=default_cmp<T>);
    Set(const std::initializer_list<T>& set, int (*cmp)(const T&, const T&)=default_cmp<T>);
    Set(const Set<T>& set);
    Set(const Iterable<T>& src, int (*cmp)(const T&, const T&)=default_cmp<T>);
    Set(Set<T>&& set) noexcept;
    ~Set();

    inline int length() const override{return len;}
    void set_cmp(int (*cmp)(const T&, const T&)){this->cmp = cmp;}

    Set<T>& operator=(const Set<T>& src);
    Set<T>& operator=(const Iterable<T>& src);
    Set<T>& operator=(Set<T>&& set) noexcept;
    Set<T> operator&(const Set<T>& src) const;
    Set<T>& operator&=(const Set<T>& src);
    Set<T> operator|(const Set<T>& src) const;
    Set<T>& operator|=(const Set<T>& src);
    Set<T> operator-(const Set<T>& src) const;
    Set<T>& operator-=(const Set<T>& src);
    Set<T>& operator<<(const T& val); //append
    bool operator==(const Set<T> &src);
    bool operator!=(const Set<T> &src);

    bool find(const T& val) const;
    bool remove(const T& val);
    void clear();


    std::string type() const override{return "Set<" + Type(T()) + ">";}
    std::string toString() const override{
        std::string output;
        output = "[";
        foreach(T& val, (*this), {
            output += Str(val) + ",";
        });
        if(len > 0) output = output.substr(0, output.length() - 1);
        output += "]";
        return output;
    }
};
template<class T>
Set<T>::Set(int (*cmp)(const T &, const T &)) {
    this->cmp = cmp;
}

template<class T>
Set<T>::Set(const std::initializer_list<T>& set, int (*cmp)(const T&, const T&)) : cmp(cmp){
    for(T& val : set){
        (*this) << val;
    }
}

template<class T>
Set<T>::Set(const Set<T> &set){
    cmp = set.cmp;
    foreach(T& val, set, {
        (*this) << val;
    });
}

template<class T>
Set<T>::Set(Set<T> &&set) noexcept{
    cmp = set.cmp;
    len = set.len;
    root = set.root;

    set.root = nullptr;
    set.len = 0;
}

template<class T>
Set<T>::Set(const Iterable<T> &src, int (*cmp)(const T &, const T &)) : cmp(cmp){
    foreach(T& val, src, {
        (*this) << val;
    });
}

template<class T>
Set<T>::~Set() {
    clear();
}

template<class T>
Set<T> &Set<T>::operator=(const Set<T> &src) {
    if(&src == this) return *this;
    clear();
    foreach(const T& val, src, {
        (*this) << val;
    });
    return (*this);
}

template<class T>
Set<T> &Set<T>::operator=(const Iterable<T> &src) {
    clear();
    foreach(const T& val, src, {
        (*this) << val;
    });
    return *this;
}

template<class T>
Set<T> &Set<T>::operator=(Set<T> &&set) noexcept{
    clear();

    cmp = set.cmp;
    len = set.len;
    root = set.root;

    set.root = nullptr;
    set.len = 0;
    return *this;
}

template<class T>
Set<T> Set<T>::operator&(const Set<T> &src) const {
    Set<T> set;
    foreach(const T& val, (*this), {
        if(src.find(val)) set << val;
    });
    return std::move(set);
}

template<class T>
Set<T> &Set<T>::operator&=(const Set<T> &src) {
    (*this) = (*this) & src;
    return (*this);
}

template<class T>
Set<T> Set<T>::operator|(const Set<T> &src) const {
    Set<T> s = (*this);
    foreach(const T& val, src, {
        s << val;
    })
    return std::move(s);
}

template<class T>
Set<T> &Set<T>::operator|=(const Set<T> &src) {
    foreach(const T& val, src, {
        (*this) << val;
    })
    return (*this);
}

template<class T>
Set<T> Set<T>::operator-(const Set<T> &src) const {
    Set<T> s = (*this);
    foreach(const T& val, src, {
        s.remove(val);
    });
    return std::move(s);
}

template<class T>
Set<T> &Set<T>::operator-=(const Set<T> &src) {
    foreach(const T& val, src, {
        remove(val);
    });
    return (*this);
}

template<class T>
bool Set<T>::operator==(const Set<T> &src) {
    return equal_tree(root, src.root);
}

template<class T>
bool Set<T>::operator!=(const Set<T> &src) {
    return !equal_tree(root, src.root);
}

template<class T>
bool Set<T>::find(const T &val) const {
    node *n = root;
    while(n != nullptr){
        int c = cmp(val, n->val);
        if(c == 0) return true;
        else if(c < 0) n = n->left;
        else n = n->right;
    }
    return false;
}

template<class T>
void Set<T>::remove_tree(Set::node *n) {
    if(n == nullptr) return;
    remove_tree(n->left);
    remove_tree(n->right);
    n->val.~T();
    delete n;
    n = nullptr;
}
template<class T>
void Set<T>::clear() {
    remove_tree(root);
    len = 0;
}

template<class T>
typename Set<T>::node *Set<T>::rotate_left(Set::node *n) {
    if(!isRed(n->right)) throw err("rotate_left:right node not red");
    node *r = n->right;
    n->right = r->left;
    r->left = n;
    r->color = n->color;
    n->color = true;
    return r;
}

template<class T>
typename Set<T>::node *Set<T>::rotate_right(Set::node *n) {
    if(!isRed(n->left)) throw err("rotate_right:left node not red");
    node *r = n->left;
    n->left = r->right;
    r->right = n;
    r->color = n->color;
    n->color = true;
    return r;
}

template<class T>
void Set<T>::flip_colors(Set::node *n) {
    /*if(n->left != true) throw err("flip_colors:left node not red");
    if(n->right != true) throw err("flip_colors:right node not red");
    if(n->color == true) throw err("flip_colors:node color not black");*/

    n->color = !n->color;
    n->left->color = !n->left->color;
    n->right->color = !n->right->color;
}

template<class T>
Set<T> &Set<T>::operator<<(const T& val) {
    root = put(root, val);
    root->color = false;
    len++;
    return (*this);
}

template<class T>
typename Set<T>::node *Set<T>::put(Set::node *n, const T &val) {
    if(n == nullptr) return new node(true, val);
    int c = cmp(val, n->val);
    if(c > 0) n->right = put(n->right, val);
    else if(c < 0) n->left = put(n->left, val);

    if(isRed(n->right) && !isRed(n->left)) n = rotate_left(n);
    if(isRed(n->left) && isRed(n->left->left)) n = rotate_right(n);
    if(isRed(n->left) && isRed(n->right)) flip_colors(n);
    return n;
}

template<class T>
typename Set<T>::node *Set<T>::move_left(Set::node *n) {
    node *c = n->right->left;
    node *d = n->right;

    d->left = c->right;
    n->right = c->left;
    c->left = n;
    c->right = d;

    //c->color = n->color; //red
    n->color = false;
    n->left->color = true;

    return c;
}

template<class T>
typename Set<T>::node *Set<T>::move_right(Set::node *n) {
    node *b = n->left;
    node *d = n->right;

    n->right = d->left;
    n->left = b->right;
    d->left = n;
    b->right = d;

    b->color = n->color; //red
    b->left->color = false;
    //n->color = true;
    return b;
}

template<class T>
bool Set<T>::remove(const T &val){
    int len0 = len;
    root = del(root, val);
    if(root != nullptr) root->color = false;
    if(len0 > len)  return true;
    return false;
}

template<class T>
typename Set<T>::node *Set<T>::del(Set::node *n, const T &val) {
    //adjust child trees
    int c = cmp(val, n->val);
    if(c > 0){
        if(n->right == nullptr) return nullptr;
        if(!isRed(n->right) && !isRed(n->right->left)) {
            if(!isRed(n)) n = rotate_right(n); //assert n->left = red
            else{
                if(!isRed(n->left->left)) flip_colors(n);
                else n = move_right(n);
            }
        }
        n->right = del(n->right, val);
    }else if(c < 0){
        if(n->left == nullptr) return nullptr;
        if(!isRed(n->left) && !isRed(n->left->left)){
            if(!isRed(n->right->left)) flip_colors(n);
            else n = move_left(n);
        }
        n->left = del(n->left, val);
    }else{ //replace
        //TODO:I have doubt there, that is, if n is a black node, then how to delete it
        if(!isRed(n)){
            n = rotate_right(n); //assert n->left = red
            n->right = del(n->right, val);
        }else n->right = delMin(n->right, n);
    }

    //break node
    if(isRed(n->right) && !isRed(n->left)) n = rotate_left(n);
    if(isRed(n->left) && isRed(n->left->left)) n = rotate_right(n);
    if(isRed(n->left) && isRed(n->right)) flip_colors(n);

    return n;
}

template<class T>
typename Set<T>::node *Set<T>::delMin(Set::node *n, Set::node *min) {
    if(n->left == nullptr){ //assert n->right == nullptr
        n->left = min->left;
        n->right = min->right;
        n->color = min->color;
        delete min;
        min = n;
        len--;
        return nullptr;
    }
    //adjust tree
    if(!isRed(n->left) && !isRed(n->left->left)){
        if(!isRed(n->right->left)) flip_colors(n);
        else n = move_left(n);
    }
    n->left = delMin(n->left, min);

    if(isRed(n->right) && !isRed(n->left)) n = rotate_left(n);
    if(isRed(n->left) && isRed(n->left->left)) n = rotate_right(n);
    if(isRed(n->left) && isRed(n->right)) flip_colors(n);

    return n;
}

template<class T>
bool Set<T>::equal_tree(Set::node *n, Set::node *m) {
    if(n == nullptr || m == nullptr){
        if(n == nullptr && m == nullptr) return true;
        else return false;
    }
    if(n->val == m->val) return equal_tree(n->left, m->left) && equal_tree(n->right, m->right);
    return false;
}

template<class T>
bool Set<T>::isRed(Set::node *n) {
    return n != nullptr && n->color;
}


#endif //DATATYPE_SET_H
