#include <SFML/Graphics.hpp>
#include "particles.h"
#include <time.h>
int main()
{
    srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Hello World");
    sf::Clock clock;
    Particles p(Vec(window.getSize().x / (2 * (Global::TILESIZE)), window.getSize().y / (1 * (Global::TILESIZE))));

    bool pour = false;
    int which = 0;
    while (window.isOpen())
    {
        if (clock.getElapsedTime().asMilliseconds() > (5.0))
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        pour = true;
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
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Num0:
                        which = 0;
                        break;
                    case sf::Keyboard::Num1:
                        which = 1;
                        break;
                    case sf::Keyboard::Num2:
                        which = 2;
                        break;
                    
                    default:
                        break;
                    }
                }
                else if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (pour)
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                Vec click = Vec(position.x / (Global::TILESIZE), (window.getSize().y - position.y) / (Global::TILESIZE));

                if (Vec(0, 0) <= click && click < p.getSize())
                {
                    switch (which)
                    {
                    case 0:
                        p[click] = std::unique_ptr<Air>(new Air(click));
                        break;
                    case 1:
                        p[click] = std::unique_ptr<Water>(new Water(click));
                        break;
                    case 2:
                        p[click] = std::unique_ptr<Sand>(new Sand(click));
                        break;
                    
                    default:
                        break;
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