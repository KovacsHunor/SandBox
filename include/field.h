#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "util.h"
#include <memory>

template<typename T>
class Field{
    Vec size;
    std::vector<std::vector<T*>> particles;
public:
    void setSize(Vec v){
        size = v;
    }
    void addCol(){
        particles.push_back(std::vector<T*>());
    }
    void clear(){
        particles.clear();
    }
    Vec getSize(){
        return size;
    }
    T* &operator[](Vec p)
    {
        return particles[p.x][p.y];
    }
    std::vector<T*> &operator[](int i)
    {
        return particles[i];
    }
    virtual ~Field(){}
};

#endif