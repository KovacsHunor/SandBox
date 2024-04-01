#include "particles.h"

Particles::Particles(Vec size)
{
    particles.setSize(size);
    for (int i = 0; i < size.x; i++)
    {
        particles.addCol();
        for (int j = 0; j < size.y; j++)
        {
            particles[i].push_back(new Air(Vec(i, j)));
        }
    }
}

void Particles::draw(sf::RenderWindow &window)
{
    window.clear();
    std::vector<sf::Vertex> vertices;
    for (int i = 0; i < getSize().x; i++)
    {
        for (int j = 0; j < getSize().y; j++)
        {
            particles[i][j]->draw(window, vertices);
        }
    }
    window.draw(&vertices[0], vertices.size(), sf::Quads);
    window.display();
}

void Particles::wake(Vec p)
{
    for (int i = p.x - 1; i <= p.x + 1; i++)
    {
        for (int j = p.y - 1; j <= p.y + 1; j++)
        {
            Vec pos = Vec(i, j);
            if (Vec(0, 0) <= pos && pos < getSize() && std::find(active.begin(), active.end(), pos) == active.end())
                active.push_back(pos);
        }
    }
}

void Particles::tick()
{
    std::vector<Vec> temp;
    while (!active.empty())
    {
        if ((*this)[active.back()]->tick(particles))
        {
            for (int i = active.back().x - 1; i <= active.back().x + 1; i++)
            {
                for (int j = active.back().y - 1; j <= active.back().y + 1; j++)
                {
                    Vec pos = Vec(i, j);
                    if (Vec(0, 0) <= pos && pos < getSize() && std::find(temp.begin(), temp.end(), pos) == temp.end())
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
    for (int i = 0; i < particles.getSize().x; i++)
    {
        for (int j = 0; j < particles.getSize().y; j++)
        {
            delete particles[Vec(i, j)];
        }
        
    }
    particles.clear();
}
