#include "particle.h"

Pos Particle::origo = Pos(0, 0);

Air::Air(Pos pos) : Particle(pos)
{
    color = sf::Color::Blue;
    material = Material();
}

bool Air::tick(std::vector<std::vector<std::unique_ptr<Particle>>> &)
{
    return false;
}

Sand::Sand(Pos pos) : Particle(pos)
{
    color = sf::Color::Yellow;
    material = Material(1, 1);
}

bool Sand::tick(std::vector<std::vector<std::unique_ptr<Particle>>> &particles)
{
    if(0 <= pos.y-1 && particles[pos.x][pos.y-1]->canSink(*this)){
        pos.y--;
        particles[pos.x][pos.y]->setPos(Pos(pos.x, pos.y + 1));

        particles[pos.x][pos.y].swap(particles[pos.x][pos.y+1]);

        return true;
    }
    return false;
}

void Particle::draw(const sf::RenderWindow &window, std::vector<sf::Vertex>& vertices)
{
    sf::Vertex vertex0(sf::Vector2f(origo.x + pos.x*11, window.getSize().y - (origo.y + pos.y*11)), color);
    sf::Vertex vertex1(sf::Vector2f(origo.x + pos.x*11+11, window.getSize().y - (origo.y + pos.y*11)), color);
    sf::Vertex vertex2(sf::Vector2f(origo.x + pos.x*11+11, window.getSize().y - (origo.y + pos.y*11+11)), color);
    sf::Vertex vertex3(sf::Vector2f(origo.x + pos.x*11, window.getSize().y - (origo.y + pos.y*11+11)), color);
    vertices.push_back(vertex0);
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
}