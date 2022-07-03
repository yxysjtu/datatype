//
// Created by asus on 2022/4/9.
//

#ifndef DATATYPE_STRING_H
#define DATATYPE_STRING_H

#include "object.h"

class String : Object{
private:
    char* s;
    int len;
public:
    String();
    String(const char *c);
    String(const char *c, int len);
    String(double n);
    String(const String& s1);
    ~String();

    inline int length() const{return len;}

    friend String operator+(const String& s1, const String& s2){
        String s0(s1);
        s0 += s2;
        return s0;
    }
    String &operator+=(const String& sl);
    char &operator[](int index);
    char &operator[] (int index) const;
    bool operator==(const String &s1);

    void resize(int n);
    const String substr(int a) const;
    const String substr(int a, int b) const;

    const char* to_str() const;
    int to_hash() const;
};

#endif //DATATYPE_STRING_H
