#include "particle.h"

Pos Particle::origo = Pos(0, 0);

Air::Air(Pos pos) : Liquid(pos)
{
    color = sf::Color::Black;
    material = Material(0);
}

bool Air::tick(std::vector<std::vector<std::unique_ptr<Particle>>> &)
{
    return false;
}

Sand::Sand(Pos pos) : Solid(pos)
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
    sf::Vertex vertex0(sf::Vector2f(origo.x + pos.x * Global::TILESIZE, window.getSize().y - (origo.y + pos.y * Global::TILESIZE)), color);
    sf::Vertex vertex1(sf::Vector2f(origo.x + pos.x * Global::TILESIZE + Global::TILESIZE, window.getSize().y - (origo.y + pos.y * Global::TILESIZE)), color);
    sf::Vertex vertex2(sf::Vector2f(origo.x + pos.x * Global::TILESIZE + Global::TILESIZE, window.getSize().y - (origo.y + pos.y * Global::TILESIZE + Global::TILESIZE)), color);
    sf::Vertex vertex3(sf::Vector2f(origo.x + pos.x * Global::TILESIZE, window.getSize().y - (origo.y + pos.y * Global::TILESIZE + Global::TILESIZE)), color);
    vertices.push_back(vertex0);
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
}

bool Solid::move(std::vector<std::vector<std::unique_ptr<Particle>>> &particles)
{
    if (0 <= pos.y - 1)
    {
        if (particles[pos.x][pos.y - 1]->canSink(*this))
        {
            pos.y--;
            particles[pos.x][pos.y]->setPos(Pos(pos.x, pos.y + 1));
            particles[pos.x][pos.y].swap(particles[pos.x][pos.y + 1]);
            return true;
        }
        else if (0 <= pos.x - 1 && particles[pos.x - 1][pos.y - 1]->canSink(*this))
        {
            pos.y--;
            pos.x--;
            particles[pos.x][pos.y]->setPos(Pos(pos.x + 1, pos.y + 1));
            particles[pos.x][pos.y].swap(particles[pos.x + 1][pos.y + 1]);
            return true;
        }
        else if (static_cast<int>(particles.size()) > pos.x + 1 && particles[pos.x + 1][pos.y - 1]->canSink(*this))
        {
            pos.y--;
            pos.x++;
            particles[pos.x][pos.y]->setPos(Pos(pos.x - 1, pos.y + 1));
            particles[pos.x][pos.y].swap(particles[pos.x - 1][pos.y + 1]);
            return true;
        }
    }

    return false;
}

Water::Water(Pos pos) : Liquid(pos)
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
    if (0 <= pos.y - 1 && particles[pos.x][pos.y - 1]->canSink(*this))
    {
        pos.y--;
        particles[pos.x][pos.y]->setPos(Pos(pos.x, pos.y + 1));
        particles[pos.x][pos.y].swap(particles[pos.x][pos.y + 1]);
        return true;
    }
    else if (0 <= pos.x - 1 && particles[pos.x - 1][pos.y]->canSink(*this))
    {
        pos.x--;
        particles[pos.x][pos.y]->setPos(Pos(pos.x + 1, pos.y));
        particles[pos.x][pos.y].swap(particles[pos.x + 1][pos.y]);
        return true;
    }
    else if (0 <= pos.x - 1 && static_cast<int>(particles.size()) > pos.x + 1 && particles[pos.x + 1][pos.y]->canSink(*this))
    {
        pos.x++;
        particles[pos.x][pos.y]->setPos(Pos(pos.x - 1, pos.y));
        particles[pos.x][pos.y].swap(particles[pos.x - 1][pos.y]);
        return true;
    }

    return false;
}
