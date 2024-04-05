#ifndef IMMOVEABLE_H
#define IMMOVEABLE_H

#include "util.h"
#include "field.h"
#include "material.h"
#include "particle.h"
#include "flammable.h"

class Immoveable : virtual public Particle
{
public:
    Immoveable(Vec pos)
    {
        setPos(pos);
    }
    bool denser(Particle &) { return false; };
    virtual ~Immoveable(){};
};



class Wood : public Immoveable, public Flammable
{
public:
    Wood(Vec pos, bool onFire = false);
    bool tick(Field<Particle *> &);
    virtual ~Wood() {}
};
#endif