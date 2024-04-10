#include <time.h>

#include <SFML/Graphics.hpp>

#include "flammable.h"
#include "gas.h"
#include "immoveable.h"
#include "liquid.h"
#include "particle.h"
#include "particles.h"
#include "solid.h"

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,
										  sf::VideoMode::getDesktopMode().height),
							"SandBox");
	sf::Clock clock1;
	sf::Clock clock2;
	sf::Clock clock3;
	Particles p(Vec(window.getSize().x / (2 * (Global::TILESIZE)),
					window.getSize().y / (1 * (Global::TILESIZE))));

	bool pour = false;
	int which = 0;
	Vec click;
	window.clear(sf::Color(10, 10, 10));
	while (window.isOpen()) {
		if (clock2.getElapsedTime().asMilliseconds() >  Global::TILESIZE / 1.2) {
			click =
				Vec(sf::Mouse::getPosition(window).x / (Global::TILESIZE),
					(window.getSize().y - sf::Mouse::getPosition(window).y) / (Global::TILESIZE));

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::MouseButtonPressed && click < p.getSize()) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						pour = true;
					}
					if (event.mouseButton.button == sf::Mouse::Right) {
						if (p[click]->getName() == "air") which = 0;
						if (p[click]->getName() == "water") which = 1;
						if (p[click]->getName() == "sand") which = 2;
						if (p[click]->getName() == "wood") which = 3;
						if (p[click]->getName() == "oil") which = 5;
						if (p[click]->getName() == "stone") which = 6;
						if (p[click]->getName() == "acid") which = 6;
					}
				} else if (event.type == sf::Event::MouseButtonReleased) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						pour = false;
					}
				} else if (event.type == sf::Event::KeyPressed) {
					int code = event.key.code;

					if (26 <= code && code < 36) {
						which = code - 26;
					} else if (code == sf::Keyboard::Escape) {
						p.clear();
					}
				} else if (event.type == sf::Event::Closed)
					window.close();
			}

			if (pour) {
				for (int i = click.x - 1; i <= click.x; i++) {
					for (int j = click.y - 1; j <= click.y; j++) {
						Vec pos = Vec(i, j);

						if (p.validPos(pos)) {
							delete p[pos];
							switch (which) {
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
								case 6:
									p[pos] = new Stone(pos);
									break;
								case 7:
									p[pos] = new Acid(pos);
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
			clock2.restart();
		}

		if (clock1.getElapsedTime().asSeconds() > 1 / 60.0) {
			p.draw(window);
			if (clock3.getElapsedTime().asSeconds() > 1) {
				clock3.restart();

				std::cout << "fps:" << 1 / clock1.getElapsedTime().asSeconds() << std::endl;
			}
			clock1.restart();
		}
	}
	return 0;
}