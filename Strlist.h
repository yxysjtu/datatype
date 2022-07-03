#ifndef DATATYPE_Strlist_H
#define DATATYPE_Strlist_H

#include <utility>

#include "Iterator.h"

class Strlist : public Iterable<std::string>{
private:
    int len;

    struct node{
        std::string str;
        node *next;
        node(){next = nullptr;}
        explicit node(std::string s):str(std::move(s)){next = nullptr;}
    };

    node *head = nullptr, *tail = nullptr;

    class Iter : public Iterator<std::string>{
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
        std::string& next() override{
            n = n->next;
            return n->str;
        }
    };

public:
    Strlist();
    Strlist(const Strlist& sl);
    Strlist(Strlist&& sl) noexcept;
    Strlist(const std::initializer_list<std::string>& sl);
    ~Strlist();

    inline int length() const override{return len;}

    Strlist &operator=(const Strlist& sl);
    Strlist &operator=(Strlist&& sl) noexcept;
    Strlist &operator<<(const std::string& str); //append
    Strlist &operator<<(std::string&& str); //append
    Strlist operator+(const Strlist& sl);
    Strlist &operator+=(const Strlist& sl);
    std::string &operator[](int index);
    std::string operator[] (int index) const;
    Strlist operator[](Range r) const;

    Strlist &insert(int index, const std::string& str);
    std::string pop(int index);
    void clear();

    int find(const std::string& str) const;

    std::string join(const std::string& symbol) const;

    Iterator<std::string>* iterator() const override{
        return new Iter(head, tail);
    }

    std::string type() const override{return "Strlist";}
    std::string toString() const override{
        return "[" + join(",") + "]";
    }

};


Strlist split(const std::string& text, const Strlist& pattern);
Strlist split(const std::string& text, const std::string& pattern=" ");
Strlist split(const std::string& text, bool (*condition)(char c));
std::string replace(const std::string& text, const Strlist& pattern, const std::string& rtext);
std::string replace(const std::string& text, const std::string& pattern, const std::string& rtext);
std::string lstrip(const std::string& text, const Strlist& pattern=Strlist() << " " << "\t" << "\n" << "\r"); //space, \r,\n,\t
std::string rstrip(const std::string& text, const Strlist& pattern=Strlist() << " " << "\t" << "\n" << "\r");
std::string strip(const std::string& text, const Strlist& pattern=Strlist() << " " << "\t" << "\n" << "\r");

void to_upper(char& c);
void to_upper(std::string& s);
void to_lower(char& c);
void to_lower(std::string& s);

Strlist::Strlist() {
    head = new node;
    len = 0;
    tail = head;
}

Strlist::Strlist(const Strlist& sl){
    head = new node;
    len = 0;
    tail = head;
    foreach(const std::string& s, sl, {
        (*this) << s;
    });

}

Strlist::Strlist(Strlist&& sl) noexcept{
    head = sl.head;
    tail = sl.tail;
    len = sl.len;

    sl.len = 0;
    sl.head = nullptr;
}

Strlist::Strlist(const std::initializer_list<std::string>& sl){
    head = new node;
    len = 0;
    tail = head;
    for(const std::string& str : sl){
        (*this) << str;
    }
}

Strlist::~Strlist() {
    clear();
    delete head;
}

Strlist &Strlist::operator=(const Strlist& sl){
    if(&sl == this) return *this;
    clear();
    if(head == nullptr) head = new node;
    len = 0;
    tail = head;
    foreach(const std::string& s, sl, {
        (*this) << s;
    });
    return (*this);
}

Strlist &Strlist::operator=(Strlist&& sl) noexcept{
    if(&sl != this){
        len = sl.len;
        tail = sl.tail;
        head = sl.head;

        sl.len = 0;
        sl.head = nullptr;
    }
}

Strlist &Strlist::operator<<(const std::string& str) {
    node *n = new node(str);
    tail->next = n;
    tail = n;
    len++;
    return (*this);
}

Strlist &Strlist::operator<<(std::string&& str) {
    node *n = new node(str);
    tail->next = n;
    tail = n;
    len++;
    return (*this);
}

Strlist Strlist::operator+(const Strlist& sl) {
    Strlist sl2;
    node *n = sl2.head, *m = head;
    for(int i = 0; i < len; i++){
        m = m->next;
        n->next = new node(m->str);
        n = n->next;
    }
    m = sl.head;
    for(int i = 0; i < sl.len; i++){
        m = m->next;
        n->next = new node(m->str);
        n = n->next;
    }
    sl2.tail = n;
    sl2.len = len + sl.len;
    return std::move(sl2);
}

Strlist &Strlist::operator+=(const Strlist& sl) {
    node *n = tail, *m = sl.head;
    for(int i = 0; i < sl.length(); i++){
        m = m->next;
        n->next = new node(m->str);
        n = n->next;
    }
    len += sl.len;
    return (*this);
}

std::string &Strlist::operator[](int index) {
    if(index >= len || index < 0) throw err("index out of range");

    node *n = head->next;
    for(int i = 0; i < index; i++){
        n = n->next;
    }
    return n->str;
}

std::string Strlist::operator[](int index) const{
    if(index >= len || index < 0) throw err("index out of range");

    node *n = head->next;
    for(int i = 0; i < index; i++){
        n = n->next;
    }
    return n->str;
}

Strlist &Strlist::insert(int index, const std::string& str) {
    if(index > len || index < 0) throw err("index out of range");
    if(index == len) return ((*this) << str);

    node *n = head;
    for(int i = 0; i < index; i++) n = n->next;
    node *m = new node(str);
    m->next = n->next;
    n->next = m;
    len++;
    return (*this);
}

std::string Strlist::pop(int index) {
    if(index < 0) index += len;
    if(index >= len || index < 0) throw err("index out of range");

    node *n = head;
    std::string result;
    for(int i = 0; i < index; i++) n = n->next;
    node *t = n->next;
    n->next = t->next;
    result = std::move(t->str);
    delete t;
    if(index == len - 1) tail = n;
    len--;
    return std::move(result);
}

int Strlist::find(const std::string& str) const{
    node *n = head;
    for(int i = 0; i < len; i++){
        n = n->next;
        if(n->str == str) return i;
    }
    return -1;
}

std::string Strlist::join(const std::string& symbol) const{ //test speed
    std::string str;
    node *n = head;
    while(n != tail){
        n = n->next;
        str += n->str + symbol;
    }
    //str += n->str;
    return str;
}

void Strlist::clear(){
    if(len == 0) return;
    node *n = head->next, *t;
    for(int i = 0; i < len; i++) {
        t = n->next;
        delete n;
        n = t;
    }
    len = 0;
    tail = head;
}

Strlist Strlist::operator[](Range r) const {
    Strlist result;
    node* n = head->next;
    if(r.end < 0) r.end += len;
    if(r.end < r.start) throw err("index out of range");
    if(r.end > len) r.end = len;

    for(int i = 0; i < r.start; i++) n = n->next;
    for(int i = r.start; i < r.end; i += r.step){
        result << n->str;
        for(int j = 0; j < r.step && n != nullptr; j++)
            n = n->next;
    }
    return std::move(result);
}

Strlist split(const std::string& text, const Strlist& pattern){
    //build next array and lookup table
    int** table = new int*[pattern.length()];
    int*** next = new int**[pattern.length()];
    int *char_n = new int[pattern.length()]();
    size_t n = text.length(), p = 0, m;
    int x;
    char c;
    Strlist result;
    for(int k = 0; k < pattern.length(); k++){
        next[k] = new int*[256]; //[char][state]
        table[k] = new int[256]();
        m = pattern[k].length();
        x = 0;
        next[k][0] = new int[m + 1]();
        for(int i = 1; i < m; i++){
            c = pattern[k][i - 1];
            if(table[k][c] == 0){
                table[k][c] = ++char_n[k];
                next[k][char_n[k]] = new int[m + 1]();
            }
            next[k][table[k][c]][i - 1] = i;
            for(int j = 1; j <= char_n[k]; j++) next[k][j][i] = next[k][j][x];
            x = next[k][table[k][pattern[k][i]]][x];
        }
        c = pattern[k][m - 1];
        if(table[k][c] == 0){
            table[k][c] = ++char_n[k];
            next[k][char_n[k]] = new int[m + 1]();
        }
        next[k][table[k][c]][m - 1] = m;
    }


    //iterate through text
    int* xi = new int[pattern.length()]();
    for(int i = 0; i < n; i++){
        c = text[i];
        for(int k = 0; k < pattern.length(); k++){
            xi[k] = next[k][table[k][c]][xi[k]];
            m = pattern[k].length();
            if(xi[k] == m){
                for(int j = 0; j < pattern.length(); j++) xi[j] = 0;
                if(i - p - m + 1 > 0)
                    result << text.substr(p, i - p - m + 1);
                p = i + 1;
                break;
            }
        }

    }
    if(text.length() - p > 0) result << text.substr(p, text.length() - p);

    for(int k = 0; k < pattern.length(); k++){
        for(int i = 0; i <= char_n[k]; i++) delete [] next[k][i];
        delete [] table[k];
    }

    delete [] next;
    delete [] table;
    delete [] char_n;

    return std::move(result);
}

Strlist split(const std::string& text, const std::string& pattern) {
    //build next array and lookup table
    int* table = new int[256]();
    int** next = new int*[256]; //[char][state]
    int char_n = 0;
    size_t m = pattern.length(), n = text.length(), p = 0;
    int x = 0;
    char c;
    Strlist result;
    next[0] = new int[m + 1]();
    for(int i = 1; i < m; i++){
        c = pattern[i - 1];
        if(table[c] == 0){
            table[c] = ++char_n;
            next[char_n] = new int[m + 1]();
        }
        next[table[c]][i - 1] = i;
        for(int j = 1; j <= char_n; j++) next[j][i] = next[j][x];
        x = next[table[pattern[i]]][x];
    }
    c = pattern[m - 1];
    if(table[c] == 0){
        table[c] = ++char_n;
        next[char_n] = new int[m + 1]();
    }
    next[table[c]][m - 1] = m;

    //iterate through text
    x = 0;
    for(int i = 0; i < n; i++){
        c = text[i];
        x = next[table[c]][x];
        if(x == m){
            x = 0;
            if(i - p - m + 1 > 0) result << text.substr(p, i - p - m + 1);
            p = i + 1;
        }
    }
    if(text.length() - p > 0) result << text.substr(p, text.length() - p);

    for(int i = 0; i <= char_n; i++) delete [] next[i];
    delete [] next;
    delete [] table;

    return std::move(result);
}

std::string lstrip(const std::string& text, const Strlist& pattern) { //just 1 character pattern
    int i, j;
    for(i = 0; i < text.length(); i++){
        for(j = 0; j < pattern.length(); j++){
            if(text[i] == pattern[j][0]) break;
        }
        if(j == pattern.length()) break;
    }
    return text.substr(i, text.length() - i);
}

std::string rstrip(const std::string& text, const Strlist& pattern) {
    int i, j;
    for(i = text.length() - 1; i >= 0; i--){
        for(j = 0; j < pattern.length(); j++){
            if(text[i] == pattern[j][0]) break;
        }
        if(j == pattern.length()) break;
    }
    return text.substr(0, i + 1);
}

std::string strip(const std::string& text, const Strlist& pattern) {
    int i, j;
    for(i = 0; i < text.length(); i++){
        for(j = 0; j < pattern.length(); j++){
            if(text[i] == pattern[j][0]) break;
        }
        if(j == pattern.length()) break;
    }
    int i1;
    for(i1 = text.length() - 1; i1 >= 0; i1--){
        for(j = 0; j < pattern.length(); j++){
            if(text[i1] == pattern[j][0]) break;
        }
        if(j == pattern.length()) break;
    }
    return text.substr(i, i1 - i + 1);
}

std::string replace(const std::string& text, const Strlist& pattern, const std::string& rtext){
    return split(text, pattern).join(rtext);
}

std::string replace(const std::string& text, const std::string& pattern, const std::string& rtext){ //kmp
    return split(text, pattern).join(rtext);
}

Strlist split(const std::string& text, bool (*condition)(char c)){
    Strlist sl;
    int i0 = 0;
    bool wordflag = false;
    for(int i = 0; i < text.length(); i++){
        char c = text[i];
        if(condition(c)){
            if(!wordflag){
                wordflag = true;
                i0 = i;
            }
        }else{
            if(wordflag){
                wordflag = false;
                sl << text.substr(i0, i - i0);
            }
        }
    }
    if(wordflag){
        sl << text.substr(i0);
    }
    return std::move(sl);
}

void to_upper(char& c){
    if(c >= 'a' && c <= 'z') c += 'A' - 'a';
}
void to_upper(std::string& s){
    for(char& c : s)
        if(c >= 'a' && c <= 'z') c += 'A' - 'a';
}
void to_lower(char& c){
    if(c >= 'A' && c <= 'Z') c -= 'A' - 'a';
}
void to_lower(std::string& s){
    for(char& c : s)
        if(c >= 'A' && c <= 'Z') c -= 'A' - 'a';
}

#endif //DATATYPE_Strlist_H
