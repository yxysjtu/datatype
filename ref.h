//
// Created by asus on 2022/5/8.
//

#ifndef DATATYPE_REF_H
#define DATATYPE_REF_H

template<class T>
class ref{
private:
    T* val = nullptr;
    int* cnt = nullptr;
public:
    ref(T* val) : val(val) {cnt = new int();}
    ref(ref& r){
        val = r.val;
        r->cnt++;
        cnt = r.cnt;
    }
    ~ref(){
        (*cnt)--;
        if((*cnt) == 0){
            val->~T();
            delete val;
            delete cnt;
        }
    }

    ref<T>& operator=(const ref<T>& r){
        if(r.val != val){
            (*cnt)--;
            if((*cnt) == 0){
                val->~T();
                delete val;
                delete cnt;
            }
            val = r.val;
            cnt = r.cnt;
            (*cnt)++;
        }
        return (*this);
    }

};

#endif //DATATYPE_REF_H
