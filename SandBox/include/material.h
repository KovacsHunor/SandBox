#ifndef MATERIAL_H
#define MATERIAL_H

#include <SFML/Graphics.hpp>

struct Material{
    std::string name;
    sf::Color color;
    int density;
    Material(const char* name = "", sf::Color c = sf::Color::Transparent, int d = 0):name(name), color(c), density(d){}
};

#endif