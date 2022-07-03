//
// Created by asus on 2022/5/7.
//

#ifndef DATATYPE_ITERATOR_H
#define DATATYPE_ITERATOR_H

#ifndef foreach
#define foreach(i, collection, func)    {auto iter = collection.iterator();\
                                        while(iter->hasNext()){\
                                            i = iter->next();\
                                            func\
                                        }\
                                        delete iter;}
#endif

#include "object.h"

template <class T>
class Iterator : public Object{
public:
    virtual bool hasNext(){return false;}
    virtual T& next(){}
    std::string type() const override{return "Iterator";}
};

template <class T>
class Iterable : public Object{
public:
    virtual Iterator<T>* iterator() const{return nullptr;}
    virtual inline int length() const {return 0;}
};

#endif //DATATYPE_ITERATOR_H
