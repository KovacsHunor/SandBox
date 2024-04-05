#include "gas.h"

Air::Air(Vec pos) : Gas(pos)
{
    color = sf::Color(20, 20, 20);
    material = Material("air", color, 0);
}

Steam::Steam(Vec pos) : Gas(pos)
{
    lifeTime = 1000;
    color = sf::Color(150, 150, 150);
    material = Material("steam", color, -1);
}

bool Steam::tick(Field<Particle *> &particles)
{
    move(particles);
    lifeTime -= rand()%3 + 1;
    if(lifeTime < 0){
       particles.transmutate(pos, new Water(pos));
       return true;
    }
    if(getAir(particles)){
        return true;
    }
    return false;
}

bool Air::tick(Field<Particle *> &particles)
{
    return move(particles);
}


bool Gas::move(Field<Particle *> &particles)
{
    if (trySwap(Vec(0, -1), particles))
        return true;
    if (canSwap(Vec(-1, 0), particles) && trySwap(Vec(-1, -1), particles))
        return true;
    if (canSwap(Vec(1, 0), particles) && trySwap(Vec(1, -1), particles))
        return true;
    if (canSwap(Vec(-1, 1), particles) && trySwap(Vec(-1, 0), particles))
        return true;
    if (canSwap(Vec(1, 1), particles) && trySwap(Vec(1, 0), particles))
        return true;
    return false;
}