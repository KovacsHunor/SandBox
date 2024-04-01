#include <SFML/Graphics.hpp>
#include <iostream>
#include "util.h"
#include "material.h"

class Particle
{
protected:
    static Pos origo;
    sf::Color color;
    Pos pos;
    Material material;

public:
    Particle(Pos pos):pos(pos){}

    void draw(const sf::RenderWindow &window, std::vector<sf::Vertex>& vertices);

    Pos getPos() const {return pos;}

    void setPos(Pos p){pos = p;}

    virtual bool canSink(Particle& waiter){return waiter.getDensity() > getDensity();};

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
    public:
    Liquid(Pos pos):Particle(pos){}
    bool move(std::vector<std::vector<std::unique_ptr<Particle>>>&);
};

class Solid : public Particle{
    public:
    Solid(Pos pos):Particle(pos){}
    bool move(std::vector<std::vector<std::unique_ptr<Particle>>>&);
};  

class Water: public Liquid
{
public:
    Water(Pos pos);

    bool tick(std::vector<std::vector<std::unique_ptr<Particle>>>&);
};

class Air: public Liquid
{
public:
    Air(Pos pos);

    bool tick(std::vector<std::vector<std::unique_ptr<Particle>>>&);
};

class Sand: public Solid
{
public:
    Sand(Pos pos);

    bool tick(std::vector<std::vector<std::unique_ptr<Particle>>>& particles);
};