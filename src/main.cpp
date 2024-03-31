#include <SFML/Graphics.hpp>
#include "particles.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Hello World");
    sf::Clock clock;
    Particles p(Pos(window.getSize().x / (2 * (Global::TILESIZE)), window.getSize().y / (1 * (Global::TILESIZE))));

    bool pour = false;
    while (window.isOpen())
    {
        if (clock.getElapsedTime().asMilliseconds() > (3.0))
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
                else if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (pour)
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                Pos click = Pos(position.x / (Global::TILESIZE), (window.getSize().y - position.y) / (Global::TILESIZE));

                if (Pos(0, 0) <= click && click < p.getSize())
                {
                    p[click] = std::unique_ptr<Sand>(new Sand(click));
                    p.wake(click);
                }
            }

            p.tick();

            window.clear();
            p.draw(window);
            window.display();

            clock.restart();
        }
    }
    return 0;
}