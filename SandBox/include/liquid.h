#ifndef LIQUID_H
#define LIQUID_H

#include "util.h"
#include "field.h"
#include "material.h"
#include "particle.h"
#include "flammable.h"


class Liquid : virtual public Particle
{
public:
    Liquid(Vec pos) {setPos(pos);}
    bool move(Field<Particle *> &);
    virtual ~Liquid(){};
};


class Water : public Liquid
{
public:
    Water(Vec pos);
    void heat(Field<Particle *> &);
    bool tick(Field<Particle *> &);
    virtual ~Water() {}
};

class Oil : public Liquid, public Flammable
{
public:
    Oil(Vec pos, bool onFire = false);
    bool tick(Field<Particle *> &);
    virtual ~Oil() {}
};

#endif