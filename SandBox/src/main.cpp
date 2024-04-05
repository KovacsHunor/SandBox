#include <SFML/Graphics.hpp>

#include "solid.h"
#include "liquid.h"
#include "gas.h"
#include "flammable.h"
#include "immoveable.h"

#include "particle.h"
#include "particles.h"
#include <time.h>

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Hello World");
    sf::Clock clock1;
    sf::Clock clock2;
    Particles p(Vec(window.getSize().x / (2 * (Global::TILESIZE)), window.getSize().y / (1 * (Global::TILESIZE))));

    bool pour = false;
    int which = 0;
    Vec click;
    window.clear(sf::Color(10, 10, 10));
    while (window.isOpen())
    {
        if (clock1.getElapsedTime().asMilliseconds() > 15.0)
        {
            p.draw(window);
            clock1.restart();

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
                        if (p[click]->getName() == "wood")
                            which = 5;
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
                for (int i = click.x - 1; i <= click.x; i++)
                {
                    for (int j = click.y - 1; j <= click.y; j++)
                    {
                        Vec pos = Vec(i, j);

                        if (p.validPos(pos))
                        {
                            delete p[pos];
                            switch (which)
                            {
                            case 1:
                                p[pos] = new Water(pos);
                                break;
                            case 2:
                                p[pos] = new Sand(pos);
                                break;
                            case 3:
                                p[pos] = new Wood(pos);
                                break;
                            case 4:
                                p[pos] = new Wood(pos, true);
                                break;
                            case 5:
                                p[pos] = new Oil(pos);
                                break;
                            default:
                                p[pos] = new Air(pos);
                            }
                            p.wake(pos);
                        }
                    }
                }
            }

            p.tick();
        }
        if (clock1.getElapsedTime().asSeconds() > (1/20.0))
        {
            p.draw(window);
            clock1.restart();
        }
    }
    return 0;
}