#include "particle.h"

Vec Particle::origo = Vec(0, 0);

Air::Air(Vec pos) : Liquid(pos)
{
    color = sf::Color(20, 20, 20);
    material = Material(0);
}

bool Air::tick(std::vector<std::vector<std::unique_ptr<Particle>>> &)
{
    return false;
}

Sand::Sand(Vec pos) : Solid(pos)
{
    color = sf::Color::Yellow;
    material = Material(2);
}

bool Sand::tick(std::vector<std::vector<std::unique_ptr<Particle>>> &particles)
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

void Particle::swap(Vec delta, std::vector<std::vector<std::unique_ptr<Particle>>> &particles)
{
    pos += delta;
    particles[pos.x][pos.y]->setPos(pos - delta);
    particles[pos.x][pos.y].swap(particles[pos.x - delta.x][pos.y - delta.y]);
}

bool Particle::canSwap(Vec delta, std::vector<std::vector<std::unique_ptr<Particle>>> &particles)
{
    return pos + delta >= 0 && (pos + delta).x < static_cast<int>(particles.size()) && particles[pos.x + delta.x][pos.y + delta.y]->canSink(*this);
}

bool Solid::move(std::vector<std::vector<std::unique_ptr<Particle>>> &particles)
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

bool Water::tick(std::vector<std::vector<std::unique_ptr<Particle>>> &particles)
{
    return move(particles);
}

bool Liquid::move(std::vector<std::vector<std::unique_ptr<Particle>>> &particles)
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
