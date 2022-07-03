//
// Created by asus on 2022/4/9.
//

#ifndef DATATYPE_OBJECT_H
#define DATATYPE_OBJECT_H

#include <iostream>
#include <exception>

class err : std::exception{
public:
    explicit err(const std::string &msg){
        std::cout << "[ERR]:" << msg << std::endl;
    }
};

class Object{
public:
    //Object(){} //register
    virtual std::string toString() const{return type();}
    virtual size_t hashcode() const{return size_t(this);}
    virtual std::string type() const{return typeid((*this)).name();}
};

struct Range{
    int start, end, step;

    Range(int start=0, int end=0, int step=1) : start(start), end(end), step(step) {}
};



std::string Str(int val){return std::to_string(val);}
std::string Str(long val){return std::to_string(val);}
std::string Str(long long val){return std::to_string(val);}
std::string Str(unsigned val){return std::to_string(val);}
std::string Str(unsigned long val){return std::to_string(val);}
std::string Str(unsigned long long val){return std::to_string(val);}
std::string Str(float val){return std::to_string(val);}
std::string Str(double val){return std::to_string(val);}
std::string Str(long double val){return std::to_string(val);}
std::string Str(char val){return std::string(1, val);}
std::string Str(const char* val){return std::string(val);}
std::string Str(bool val){return (val)? "true" : "false";}
std::string Str(const std::string& val){return val;}
std::string Str(const Object& val){return val.toString();}

std::ostream &operator<<(std::ostream& output, const Object& sl){
    output << sl.toString();
    return output;
}

size_t Hash(int val){return val;}
size_t Hash(long val){return val;}
size_t Hash(long long val){return val;}
size_t Hash(unsigned val){return val;}
size_t Hash(unsigned long val){return val;}
size_t Hash(unsigned long long val){return val;}
size_t Hash(float val){
    size_t r = 0;
    memcpy(&r, &val, 4);
    return r;
}
size_t Hash(double val){
    size_t r = 0;
    memcpy(&r, &val, 8);
    return r;
}
size_t Hash(long double val){
    size_t r = 0;
    memcpy(&r, &val, 8);
    return r;
}
size_t Hash(char val){return val;}
size_t Hash(bool val){return val;}
size_t Hash(const std::string& val){
    size_t r = 0;
    for(const char& c : val){
        r *= 31;
        r += c;
    }
    return r;
}
size_t Hash(const char* val){
    return Hash(std::string(val));
}
size_t Hash(const Object& val){return val.hashcode();}

int Int(const std::string& s){
    return atoi(s.c_str());
}
double Double(const std::string& s){
    return atof(s.c_str());
}
std::string Type(int val){return "int";}
std::string Type(long val){return "long";}
std::string Type(long long val){return "long long";}
std::string Type(unsigned val){return "unsigned";}
std::string Type(unsigned long val){return "unsigned long";}
std::string Type(unsigned long long val){return "unsigned long long";}
std::string Type(float val){return "float";}
std::string Type(double val){return "double";}
std::string Type(long double val){return "long double";}
std::string Type(char val){return "char";}
std::string Type(const char* val){return "const char*";}
std::string Type(bool val){return "bool";}
std::string Type(const std::string& val){return "string";}
std::string Type(const Object& val){return val.type();}

template<class T>
int default_cmp(const T& a, const T& b){
    return Hash(a) > Hash(b);
}

#endif //DATATYPE_OBJECT_H
