#include "particle.h"
#include "iostream"
#include <vector>
#include <algorithm>
class Particles
{
    Vec size;
    std::vector<std::vector<std::unique_ptr<Particle>>> particles;
    std::vector<Vec> active;

public:
    Particles(Vec size);
    void draw(sf::RenderWindow &window);
    void DEBUG()
    {
        std::cout << active.size() << std::endl;
    }
    void wake(Vec p);
    void tick();
    Vec getSize() { return size; }
    std::vector<std::unique_ptr<Particle>> &operator[](int i)
    {
        return particles[i];
    }
    std::unique_ptr<Particle> &operator[](Vec p)
    {
        return particles[p.x][p.y];
    }
    ~Particles();
};