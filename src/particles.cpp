#include "particles.h"

Particles::Particles(Pos size) : size(size)
{
    for (int i = 0; i < size.x; i++)
    {
        particles.push_back(std::vector<std::unique_ptr<Particle>>());
        for (int j = 0; j < size.y; j++)
        {
            particles[i].push_back(std::unique_ptr<Air>(new Air(Pos(i, j))));
        }
    }
}

void Particles::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < size.x; i++)
    {
        for (int j = 0; j < size.y; j++)
        {
            particles[i][j]->draw(window);
        }
    }
}

Particles::~Particles()
{
    particles.clear();
}
