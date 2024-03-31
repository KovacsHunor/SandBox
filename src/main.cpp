#include <SFML/Graphics.hpp>
#include "particles.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Hello World");
    sf::Clock clock;
    Particles p(Pos(window.getSize().x / 5, window.getSize().y / 5 - 100));

    p.draw(window);
    window.display();
    while (window.isOpen())
    {
        if (clock.getElapsedTime().asSeconds() > (1 / 60))
        {
            p.DEBUG();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i position = sf::Mouse::getPosition(window);
                        Pos click = Pos(position.x, p.getSize().y - position.y);

                        if (Pos(0, 0) <= click && click < p.getSize())
                        {
                            p[click] = std::unique_ptr<Sand>(new Sand(click));
                            p.wake(click);
                        }
                    }
                }
                if (event.type == sf::Event::Closed)
                    window.close();
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