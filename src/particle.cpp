#include "particle.h"

Air::Air(Vec pos) : Liquid(pos)
{
    color = sf::Color(20, 20, 20);
    material = Material(0);
}

bool Air::tick(Field<Particle> &)
{
    return false;
}

Sand::Sand(Vec pos) : Solid(pos)
{
    color = sf::Color::Yellow;
    material = Material(2);
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
    particles[pos].swap(particles[pos - delta]);
}

bool Particle::canSwap(Vec delta, Field<Particle> &particles)
{
    return pos + delta >= 0 && pos + delta < particles.getSize() && particles[pos + delta]->canSink(*this);
}

bool Solid::move(Field<Particle> &particles)
{
    if (canSwap(Vec(0, -1), particles))
        swap(Vec(0, -1), particles);
    else if (canSwap(Vec(-1, -1), particles))
        swap(Vec(-1, -1), particles);
    else if (canSwap(Vec(1, -1), particles))
        swap(Vec(1, -1), particles);
    else
        return false;
    return true;
}

Water::Water(Vec pos) : Liquid(pos)
{
    color = sf::Color::Blue;
    material = Material(1);
}

bool Water::tick(Field<Particle> &particles)
{
    return move(particles);
}

bool Liquid::move(Field<Particle> &particles)
{
    if (canSwap(Vec(0, -1), particles))
        swap(Vec(0, -1), particles);
    else if (canSwap(Vec(-1, -1), particles))
        swap(Vec(-1, -1), particles);
    else if (canSwap(Vec(1, -1), particles))
        swap(Vec(1, -1), particles);
    else if (canSwap(Vec(-1, 0), particles))
        swap(Vec(-1, 0), particles);
    else if (canSwap(Vec(1, 0), particles))
        swap(Vec(1, 0), particles);
    else
        return false;
    return true;
}
