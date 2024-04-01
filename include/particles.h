#ifndef PARTICLES_H
#define PARTICLES_H

#include "particle.h"
#include "iostream"
#include "field.h"


#include <vector>
#include <algorithm>

class Particles
{
    Field<Particle> particles;
    std::vector<Vec> active;

public:
    Particles(Vec size);
    void draw(sf::RenderWindow &window);
    void DEBUG()
    {
        std::cout << active.size() << std::endl;
    }
    void wake(Vec p);
    void tick();
    Vec getSize() { return particles.getSize(); }
    std::vector<Particle*> &operator[](int i)
    {
        return particles[i];
    }
    Particle* &operator[](Vec p)
    {
        return particles[p];
    }
    virtual ~Particles();
};

#endif