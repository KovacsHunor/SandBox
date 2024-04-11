#include "particle.h"

std::deque<Vec> Particle::updated = std::deque<Vec>();
std::deque<Vec> Particle::active = std::deque<Vec>();

bool Particle::getAir(Field<Particle *> &particles) {
	for (int i = pos.x - 1; i <= pos.x + 1; i++) {
		for (int j = pos.y - 1; j <= pos.y + 1; j++) {
			Vec p = Vec(i, j);
			if (Vec(0, 0) <= p && p < particles.getSize())
				if (particles[p]->getName() == "air") return true;
		}
	}
	return false;
}

bool Particle::all(const char *str, Field<Particle *> &particles) {
	for (int i = pos.x - 1; i <= pos.x + 1; i++) {
		for (int j = pos.y - 1; j <= pos.y + 1; j++) {
			Vec p = Vec(i, j);
			if (Vec(0, 0) <= p && p < particles.getSize())
				if (particles[p]->getName() != str) return false;
		}
	}
	return true;
}

void Particle::draw(const sf::RenderWindow &window, std::vector<sf::Vertex> &vertices) {
	vertices.push_back(sf::Vertex(sf::Vector2f(pos.x * Global::TILESIZE, window.getSize().y - pos.y * Global::TILESIZE), color));
	vertices.push_back(
		sf::Vertex(sf::Vector2f((pos.x + 1) * Global::TILESIZE, window.getSize().y - pos.y * Global::TILESIZE), color));
	vertices.push_back(
		sf::Vertex(sf::Vector2f((pos.x + 1) * Global::TILESIZE, window.getSize().y - (pos.y + 1) * Global::TILESIZE), color));
	vertices.push_back(
		sf::Vertex(sf::Vector2f(pos.x * Global::TILESIZE, window.getSize().y - (pos.y + 1) * Global::TILESIZE), color));
}

bool Particle::trySwap(Vec delta, Field<Particle *> &particles) {
	if (canSwap(delta, particles)) {
		swap(delta, particles);
		return true;
	}
	return false;
}

void Particle::swap(Vec delta, Field<Particle *> &particles) {
	active.push_back(pos);
	updated.push_back(pos);
	updated.push_back(pos + delta);

	pos += delta;
	particles[pos]->setPos(pos - delta);
	Particle *temp = particles[pos];
	particles[pos] = particles[pos - delta];
	particles[pos - delta] = temp;
}

bool Particle::canSwap(Vec delta, Field<Particle *> &particles) {
	if (pos + delta >= 0 && pos + delta < particles.getSize()) {
		bool stable = particles[pos + delta]->denser(*this);
		// if (delta.y > 0)
		//   stable = !stable;
		return stable;
	}
	return false;
}
