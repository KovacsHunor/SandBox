#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "util.h"
#include <memory>

template <typename T>
class Field
{
    Vec size;
    std::vector<std::vector<T *>> field;

public:
    void setSize(Vec v)
    {
        size = v;
    }
    void transmutate(Vec pos, T *into)
    {
        delete (*this)[pos];
        (*this)[pos] = into;
    }
    void addCol()
    {
        field.push_back(std::vector<T *>());
    }
    bool validPos(Vec p){
        return Vec(0, 0) <= p && p < getSize();
    }
    void clear()
    {
        field.clear();
    }
    Vec getSize()
    {
        return size;
    }
    T *&operator[](Vec p)
    {
        return field[p.x][p.y];
    }
    std::vector<T *> &operator[](int i)
    {
        return field[i];
    }
    virtual ~Field() {}
};

#endif