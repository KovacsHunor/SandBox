#ifndef SOLID_H
#define SOLID_H

#include "util.h"
#include "field.h"
#include "material.h"
#include "particle.h"

class Solid : public Particle
{
public:
    Solid(Vec pos) : Particle(pos) {}
    bool move(Field<Particle *> &);
    virtual ~Solid(){};
};

class Sand : public Solid
{
public:
    Sand(Vec pos);

    bool tick(Field<Particle *> &particles);
    virtual ~Sand() {}
};

#endif