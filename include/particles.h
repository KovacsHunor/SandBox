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
    void DEBUG(){
        std::cout << active.size() << std::endl;
    }
    void wake(Pos p)
    {
        active.push_back(p);
    }
    void tick()
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