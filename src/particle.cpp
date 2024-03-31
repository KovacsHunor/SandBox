#include "particle.h"

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

void Particle::draw(sf::RenderWindow &window)
{
    sf::RectangleShape pixel(sf::Vector2f(1, 1));
    pixel.setPosition(pos.x, window.getSize().y / 5 - 100 - pos.y);
    pixel.setFillColor(color);
    window.draw(pixel);
}