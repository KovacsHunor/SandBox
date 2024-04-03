#include <SFML/Graphics.hpp>
#include "particles.h"
#include <time.h>
int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Hello World");
    sf::Clock clock;
    Particles p(Vec(window.getSize().x / (2 * (Global::TILESIZE)), window.getSize().y / (1 * (Global::TILESIZE))));

    bool pour = false;
    int which = 0;
    Vec click;
    while (window.isOpen())
    {
        if (clock.getElapsedTime().asMilliseconds() > 0.0)
        {
            click = Vec(sf::Mouse::getPosition(window).x / (Global::TILESIZE), (window.getSize().y - sf::Mouse::getPosition(window).y) / (Global::TILESIZE));

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::MouseButtonPressed && click < p.getSize())
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        pour = true;
                    }
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        if (p[click]->getName() == "air")
                            which = 0;
                        if (p[click]->getName() == "water")
                            which = 1;
                        if (p[click]->getName() == "sand")
                            which = 2;
                        if (p[click]->getName() == "wood")
                            which = 3;
                    }
                }
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        pour = false;
                    }
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                    int code = event.key.code;

                    if (26 <= code && code < 36)
                    {
                        which = code - 26;
                    }
                    else if (code == sf::Keyboard::Escape)
                    {
                        p.clear();
                    }
                }
                else if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (pour)
            {
                if (Vec(0, 0) <= click && click < p.getSize())
                {
                    delete p[click];
                    switch (which)
                    {
                    case 1:
                        p[click] = new Water(click);
                        break;
                    case 2:
                        p[click] = new Sand(click);
                        break;
                    case 3:
                        p[click] = new Wood(click);
                        break;
                    case 4:
                        p[click] = new Wood(click, true);
                        break;
                    default:
                        p[click] = new Air(click);
                    }
                    p.wake(click);
                }
            }

            p.tick();
            p.draw(window);
            clock.restart();
        }
    }
    return 0;
}