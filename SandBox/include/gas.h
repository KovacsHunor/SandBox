#ifndef GAS_H
#define GAS_H

#include "util.h"
#include "field.h"
#include "material.h"
#include "particle.h"
#include "liquid.h"

class Gas : public Particle
{
    Vec speed;
public:
    Gas(Vec pos) : Particle(pos) {speed = Vec(0, 0);}

    bool isGas(){return true;}
    virtual bool canSwap(Vec delta, Field<Particle *> &particles);
	virtual void move(Field<Particle *> &);
    bool canCorrode(){return false;}
	virtual ~Gas(){};
};


class Air : public Gas
{
public:
    Air(Vec pos = Vec(0, 0));
    void move(Field<Particle *> &){};
    void tick(Field<Particle *> &);
    virtual ~Air() {}
};

class Steam : public Gas
{
    int lifeTime;
public:
    Steam(Vec pos = Vec(0, 0));

    void tick(Field<Particle *> &);
    virtual ~Steam() {}
};

#endif