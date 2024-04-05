#ifndef FLAMMABLE_H
#define FLAMMABLE_H

#include "util.h"
#include "field.h"
#include "material.h"
#include "particle.h"

class Flammable : virtual public Particle
{
protected:
    bool onFire;
    int lifeTime;

public:
    Flammable(bool setFire = false) : lifeTime(1000)
    {
        if (setFire)
            ignite();
        else
            onFire = false;
    }
    void ignite();
    virtual void heat(Field<Particle *> &)
    {
        ignite();
    }
    void extinguish()
    {
        updated.push_back(pos);
        color = material.color;
        onFire = false;
    }
    virtual ~Flammable() {}
};

#endif