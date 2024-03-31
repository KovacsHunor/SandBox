#include <SFML/Graphics.hpp>
#include <iostream>
#include "util.h"
#include "material.h"

class Particle
{
protected:
    sf::Color color;
    Pos pos;
    Material material;
public:
    Particle(Pos pos):pos(pos){}
    void draw(sf::RenderWindow &window);
    Pos getPos() const {return pos;}
    void setPos(Pos p){pos = p;}
    virtual bool canSink(Particle& waiter){return waiter.getDensity() > getDensity();};
    virtual bool tick(std::vector<std::vector<std::unique_ptr<Particle>>>&){return false;}
    void print(){
        std::cout << int(color.r) << " " << int(color.g) << " " << int(color.b) << std::endl;
    }
    int getDensity(){
        return material.density;
    }
};
class Air: public Particle
{
public:
    Air(Pos pos);
    bool tick(std::vector<std::vector<std::unique_ptr<Particle>>>&);
};
class Sand: public Particle
{
public:
    Sand(Pos pos);
    bool tick(std::vector<std::vector<std::unique_ptr<Particle>>>& particles);
};