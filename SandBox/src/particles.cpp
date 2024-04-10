#include "particles.h"

#include "gas.h"

Particles::Particles(Vec size) {
	particles.setSize(size);
	for (int i = 0; i < size.x; i++) {
		particles.addCol();
		for (int j = 0; j < size.y; j++) {
			particles[i].push_back(new Air(Vec(i, j)));
		}
	}
}

void Particles::draw(sf::RenderWindow &window) {
	std::vector<sf::Vertex> vertices;
	while (!Particle::updated.empty()) {
		particles[Particle::updated.back()]->draw(window, vertices);
		Particle::updated.pop_back();
	}

	window.draw(&vertices[0], vertices.size(), sf::Quads);
	window.display();
}

void Particles::clear() {
	for (int i = 0; i < getSize().x; i++) {
		for (int j = 0; j < getSize().y; j++) {
			delete particles[i][j];
			particles[i][j] = new Air(Vec(i, j));
		}
	}
}

void Particles::wake(Vec p) {
	Particle::active.push_back(p);
	for (int i = p.x - 1; i <= p.x + 1; i++) {
		for (int j = p.y - 1; j <= p.y + 1; j++) {
			Vec pos = Vec(i, j);
			if (Vec(0, 0) <= pos && pos < getSize()) Particle::active.push_back(pos);
		}
	}
}

void Particles::tick() {
	std::deque<Vec> temp;
	Field<int> intemp;
	for (int i = 0; i < getSize().x; i++) {
		intemp.addCol();
		for (int j = 0; j < getSize().y; j++) {
			intemp[i].push_back(0);
		}
	}

	while (!Particle::active.empty()) {
		if ((*this)[Particle::active.back()]->tick(particles)) {
			for (int i = Particle::active.back().x - 1; i <= Particle::active.back().x + 1; i++) {
				for (int j = Particle::active.back().y - 1; j <= Particle::active.back().y + 1;
					 j++) {
					Vec pos = Vec(i, j);
					if (validPos(pos) && !intemp[pos]) {
						temp.push_back(pos);
						intemp[pos] = true;
					}
				}
			}
		}
		Particle::active.pop_back();
	}
	Particle::active = temp;
}

Particles::~Particles() {
	for (int i = 0; i < particles.getSize().x; i++) {
		for (int j = 0; j < particles.getSize().y; j++) {
			delete particles[Vec(i, j)];
		}
	}
	particles.clear();
}
