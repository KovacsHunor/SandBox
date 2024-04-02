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
    static Vec origo;
    sf::Color color;
    Vec pos;
    Material material;

public:
    Particle(Vec pos):pos(pos){}

    void draw(const sf::RenderWindow &window, std::vector<sf::Vertex>& vertices);

    Vec getPos() const {return pos;}

    void swap(Vec delta, Field<Particle> &particles);

    void setPos(Vec p){pos = p;}
    std::string getName(){
        return material.name;
    }

    virtual bool canSink(Particle& waiter){return waiter.getDensity() > getDensity();};
    bool canSwap(Vec delta, Field<Particle> &particles);
    virtual bool tick(Field<Particle>&){return false;}
    virtual bool move(Field<Particle>&){return false;}

    void print(){
        std::cout << int(color.r) << " " << int(color.g) << " " << int(color.b) << std::endl;
    }

    int getDensity(){
        return material.density;
    }
    virtual ~Particle(){}
};

class Liquid : public Particle{
    Vec speed;
    public:
    Liquid(Vec pos):Particle(pos), speed(Vec(-1, 0)){}
    bool move(Field<Particle>&);
    virtual ~Liquid(){}
};

class Immoveable : public Particle{
    public:
    Immoveable(Vec pos):Particle(pos){}
    bool canSink(Particle&){return false;};
    virtual ~Immoveable(){}
};

class Solid : public Particle{
    public:
    Solid(Vec pos):Particle(pos){}
    bool move(Field<Particle>&);
    virtual ~Solid(){}
};



class Wood: public Immoveable
{
public:
    Wood(Vec pos);
    virtual ~Wood(){}
};

class Water: public Liquid
{
public:
    Water(Vec pos);

    bool tick(Field<Particle>&);
    virtual ~Water(){}
};

class Air: public Liquid
{
public:
    Air(Vec pos);

    bool tick(Field<Particle>&);
    virtual ~Air(){}
};

class Sand: public Solid
{
public:
    Sand(Vec pos);

    bool tick(Field<Particle>& particles);
    virtual ~Sand(){}
};

#endif