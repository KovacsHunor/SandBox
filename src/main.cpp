#include <SFML/Graphics.hpp>
#include "particles.h"
int main()
{
    const int size = 10;
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Hello World");
    sf::Clock clock;
    Particles p(Pos(window.getSize().x/(2*(size+1)), window.getSize().y/(1*(size+1))));

    p.draw(window);
    window.display();
    while (window.isOpen())
    {
        if (clock.getElapsedTime().asSeconds() > 0)
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
                        Pos click = Pos(position.x/(size+1), (window.getSize().y - position.y)/(size+1));

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