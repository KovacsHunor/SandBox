#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "util.h"
#include <memory>

template<typename T>
class Field{
    Vec size;
    std::vector<std::vector<T*>> field;
public:
    void setSize(Vec v){
        size = v;
    }
    void addCol(){
        field.push_back(std::vector<T*>());
    }
    void clear(){
        field.clear();
    }
    Vec getSize(){
        return size;
    }
    T* &operator[](Vec p)
    {
        return field[p.x][p.y];
    }
    std::vector<T*> &operator[](int i)
    {
        return field[i];
    }
    virtual ~Field(){}
};

#endif