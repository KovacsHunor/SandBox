#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "util.h"
#include "field.h"
#include "material.h"

class Particle
{
protected:
    sf::Color color;
    Vec pos;
    Material material;

public:
    Particle() {}
    Particle(Vec pos) : pos(pos) {}

    void draw(const sf::RenderWindow &window, std::vector<sf::Vertex> &vertices);

    Vec getPos() const { return pos; }

    void swap(Vec delta, Field<Particle> &particles);

    void setPos(Vec p) { pos = p; }
    std::string getName()
    {
        return material.name;
    }

    virtual bool canSink(Particle &waiter) { return waiter.getDensity() > getDensity(); };
    bool canSwap(Vec delta, Field<Particle> &particles);
    virtual bool tick(Field<Particle> &) { return false; }
    virtual bool move(Field<Particle> &) { return false; }

    virtual void heat(Field<Particle> &) {}

    void print()
    {
        std::cout << int(color.r) << " " << int(color.g) << " " << int(color.b) << std::endl;
    }

    int getDensity()
    {
        return material.density;
    }

    virtual ~Particle() {}
};

class Liquid : public Particle
{
protected:
    Vec speed;

public:
    Liquid(Vec pos) : Particle(pos), speed(Vec(-1, 0)) {}
    bool move(Field<Particle> &);
    virtual ~Liquid(){};
};

class Flammable : virtual public Particle
{
protected:
    bool onFire;

public:
    Flammable(bool onFire = false) : onFire(onFire) {}
    void ignite()
    {
        onFire = true;
        color = sf::Color::Red;
    }
    virtual void heat(Field<Particle> &particles)
    {
        if (getAir(particles))
        {
            ignite();
        }
    }
    void extinguish()
    {
        color = material.color;
        onFire = false;
    }
    bool getAir(Field<Particle> &particles);
    virtual ~Flammable() {}
};

class Immoveable : virtual public Particle
{
public:
    Immoveable(Vec pos)
    {
        setPos(pos);
    }
    bool canSink(Particle &) { return false; };
    virtual ~Immoveable(){};
};

class Solid : public Particle
{
public:
    Solid(Vec pos) : Particle(pos) {}
    bool move(Field<Particle> &);
    virtual ~Solid(){};
};

class Wood : public Immoveable, public Flammable
{
public:
    Wood(Vec pos, bool onFire = false);
    bool tick(Field<Particle> &);
    virtual ~Wood() {}
};

class Water : public Liquid
{
public:
    Water(Vec pos);

    bool tick(Field<Particle> &);
    virtual ~Water() {}
};

class Air : public Liquid
{
public:
    Air(Vec pos);

    bool tick(Field<Particle> &);
    virtual ~Air() {}
};

class Sand : public Solid
{
public:
    Sand(Vec pos);

    bool tick(Field<Particle> &particles);
    virtual ~Sand() {}
};

#endif