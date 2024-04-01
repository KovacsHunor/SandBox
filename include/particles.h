#include "particle.h"
#include "iostream"
#include <vector>
#include <algorithm>
class Particles
{
    Pos size;
    std::vector<std::vector<std::unique_ptr<Particle>>> particles;
    std::vector<Pos> active;

public:
    Particles(Pos size);
    void draw(sf::RenderWindow &window);
    void DEBUG()
    {
        std::cout << active.size() << std::endl;
    }
    void wake(Pos p)
    {
        for (int i = p.x - 1; i <= p.x + 1; i++)
        {
            for (int j = p.y - 1; j <= p.y + 1; j++)
            {
                Pos pos = Pos(i, j);
                if (Pos(0, 0) <= pos && pos < getSize() && std::find(active.begin(), active.end(), pos) == active.end())
                    active.push_back(pos);
            }
        }
    }
    void tick();
    Pos getSize() { return size; }
    std::vector<std::unique_ptr<Particle>> &operator[](int i)
    {
        return particles[i];
    }
    std::unique_ptr<Particle> &operator[](Pos p)
    {
        return particles[p.x][p.y];
    }
    ~Particles();
};