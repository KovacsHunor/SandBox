#ifndef MATERIAL_H
#define MATERIAL_H

struct Material{
    std::string name;
    int density;
    bool flammable;
    Material(const char* name = "", int d = 0, bool f = false):name(name), density(d), flammable(f){}
};

#endif