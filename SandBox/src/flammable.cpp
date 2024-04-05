#include "flammable.h"

void Flammable::ignite()
{
    updated.push_back(pos);
    onFire = true;

    int rnd = rand() % 3; // better name?
    if (rnd == 0)
        color = sf::Color::Red;
    else if (rnd == 1)
        color = sf::Color(255, 90, 0);
    else if (rnd == 2)
        color = sf::Color(255, 154, 0);
}