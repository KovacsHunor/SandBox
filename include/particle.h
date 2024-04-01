#include <SFML/Graphics.hpp>
#include <iostream>
#include "util.h"
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

    void swap(Vec delta, std::vector<std::vector<std::unique_ptr<Particle>>> &particles);

    void setPos(Vec p){pos = p;}

    bool canSink(Particle& waiter){return waiter.getDensity() > getDensity();};
    bool canSwap(Vec delta, std::vector<std::vector<std::unique_ptr<Particle>>> &particles);
    virtual bool tick(std::vector<std::vector<std::unique_ptr<Particle>>>&){return false;}
    virtual bool move(std::vector<std::vector<std::unique_ptr<Particle>>>&){return false;}

    void print(){
        std::cout << int(color.r) << " " << int(color.g) << " " << int(color.b) << std::endl;
    }

    int getDensity(){
        return material.density;
    }
};

class Liquid : public Particle{
    Vec speed;
    public:
    Liquid(Vec pos):Particle(pos), speed(Vec(-1, 0)){}
    bool move(std::vector<std::vector<std::unique_ptr<Particle>>>&);
};

class Solid : public Particle{
    public:
    Solid(Vec pos):Particle(pos){}
    bool move(std::vector<std::vector<std::unique_ptr<Particle>>>&);
};  

class Water: public Liquid
{
public:
    Water(Vec pos);

    bool tick(std::vector<std::vector<std::unique_ptr<Particle>>>&);
};

class Air: public Liquid
{
public:
    Air(Vec pos);

    bool tick(std::vector<std::vector<std::unique_ptr<Particle>>>&);
};

class Sand: public Solid
{
public:
    Sand(Vec pos);

    bool tick(std::vector<std::vector<std::unique_ptr<Particle>>>& particles);
};