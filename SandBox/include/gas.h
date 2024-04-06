#ifndef GAS_H
#define GAS_H

#include "util.h"
#include "field.h"
#include "material.h"
#include "particle.h"
#include "liquid.h"

class Gas : public Particle
{
public:
    Gas(Vec pos) : Particle(pos) {}
    bool isGas(){return true;}
    virtual bool canSwap(Vec delta, Field<Particle *> &particles);
	virtual bool move(Field<Particle *> &);
	virtual ~Gas(){};
};


class Air : public Gas
{
public:
    Air(Vec pos = Vec(0, 0));
    bool move(Field<Particle *> &){return false;};
    bool tick(Field<Particle *> &);
    virtual ~Air() {}
};

class Steam : public Gas
{
    int lifeTime;
public:
    Steam(Vec pos = Vec(0, 0));

    bool tick(Field<Particle *> &);
    virtual ~Steam() {}
};

#endif