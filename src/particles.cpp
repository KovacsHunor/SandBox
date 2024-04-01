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
    window.clear();
    std::vector<sf::Vertex> vertices;
    for (int i = 0; i < size.x; i++)
    {
        for (int j = 0; j < size.y; j++)
        {
            particles[i][j]->draw(window, vertices);
        }
    }
    window.draw(&vertices[0], vertices.size(), sf::Quads);
    window.display();
}

void Particles::tick()
{
    std::vector<Pos> temp;
    while (!active.empty())
    {
        if ((*this)[active.back()]->tick(particles))
        {
            for (int i = active.back().x - 1; i <= active.back().x + 1; i++)
            {
                for (int j = active.back().y - 1; j <= active.back().y + 1; j++)
                {
                    Pos pos = Pos(i, j);
                    if (Pos(0, 0) <= pos && pos < getSize() && std::find(temp.begin(), temp.end(), pos) == temp.end())
                        temp.push_back(pos);
                }
            }
        }
        active.pop_back();
    }
    active = temp;
}

Particles::~Particles()
{
    particles.clear();
}
