#include "particle.h"

Air::Air(Vec pos) : Liquid(pos)
{
    color = sf::Color(20, 20, 20);
    material = Material("air", sf::Color(20, 20, 20), 0);
}

bool Air::tick(Field<Particle> &)
{
    return false;
}

Sand::Sand(Vec pos) : Solid(pos)
{
    color = sf::Color::Yellow;
    material = Material("sand", sf::Color::Yellow, 2);
}

bool Sand::tick(Field<Particle> &particles)
{
    return move(particles);
}

void Particle::draw(const sf::RenderWindow &window, std::vector<sf::Vertex> &vertices)
{
    vertices.push_back(sf::Vertex(sf::Vector2f(pos.x * Global::TILESIZE, window.getSize().y - pos.y * Global::TILESIZE), color));
    vertices.push_back(sf::Vertex(sf::Vector2f((pos.x + 1) * Global::TILESIZE, window.getSize().y - pos.y * Global::TILESIZE), color));
    vertices.push_back(sf::Vertex(sf::Vector2f((pos.x + 1) * Global::TILESIZE, window.getSize().y - (pos.y + 1) * Global::TILESIZE), color));
    vertices.push_back(sf::Vertex(sf::Vector2f(pos.x * Global::TILESIZE, window.getSize().y - (pos.y + 1) * Global::TILESIZE), color));
}

void Particle::swap(Vec delta, Field<Particle> &particles)
{
    pos += delta;
    particles[pos]->setPos(pos - delta);
    Particle *temp = particles[pos];
    particles[pos] = particles[pos - delta];
    particles[pos - delta] = temp;
}

bool Particle::canSwap(Vec delta, Field<Particle> &particles)
{
    return pos + delta >= 0 && pos + delta < particles.getSize() && particles[pos + delta]->canSink(*this);
}

bool Solid::move(Field<Particle> &particles)
{
    if (canSwap(Vec(0, -1), particles))
        swap(Vec(0, -1), particles);
    else if (canSwap(Vec(-1, 0), particles) && canSwap(Vec(-1, -1), particles))
        swap(Vec(-1, -1), particles);
    else if (canSwap(Vec(1, 0), particles) && canSwap(Vec(1, -1), particles))
        swap(Vec(1, -1), particles);
    else
        return false;
    return true;
}

Water::Water(Vec pos) : Liquid(pos)
{
    color = sf::Color::Blue;
    material = Material("water", sf::Color::Blue, 1);
}

bool Water::tick(Field<Particle> &particles)
{
    return move(particles);
}

bool Liquid::move(Field<Particle> &particles)
{
    if (canSwap(Vec(0, -1), particles))
        swap(Vec(0, -1), particles);
    else if (canSwap(Vec(-1, 0), particles) && canSwap(Vec(-1, -1), particles))
        swap(Vec(-1, -1), particles);
    else if (canSwap(Vec(1, 0), particles) && canSwap(Vec(1, -1), particles))
        swap(Vec(1, -1), particles);
    else if (canSwap(Vec(-1, 0), particles))
        swap(Vec(-1, 0), particles);
    else if (canSwap(Vec(1, 0), particles))
        swap(Vec(1, 0), particles);
    else
        return false;
    return true;
}

Wood::Wood(Vec pos, bool onFire) : Immoveable(pos), Flammable(onFire)
{
    color = sf::Color(200, 150, 100);
    material = Material("wood", sf::Color(200, 150, 100), 10);
}

bool Wood::tick(Field<Particle> &particles)
{
    if (onFire)
    {
        for (int i = pos.x - 1; i <= pos.x + 1; i++)
        {
            for (int j = pos.y - 1; j <= pos.y + 1; j++)
            {
                Vec p = Vec(i, j);
                if (Vec(0, 0) <= p && p < particles.getSize())
                    particles[p]->heat(particles);
            }
        }

        if(rand() % 200 == 0){
            particles.transmutate(pos, new Air(pos));
            return true;
        }
        

        if (!getAir(particles))
        {
            extinguish();
        }

        return true;
    }
    return false;
}

bool Flammable::getAir(Field<Particle> &particles)
{
    for (int i = pos.x - 1; i <= pos.x + 1; i++)
    {
        for (int j = pos.y - 1; j <= pos.y + 1; j++)
        {
            Vec p = Vec(i, j);
            if (Vec(0, 0) <= p && p < particles.getSize())
                if (particles[p]->getName() == "air")
                    return true;
        }
    }
    return false;
}
