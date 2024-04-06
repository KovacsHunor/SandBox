#include "gas.h"

Air::Air(Vec pos) : Gas(pos) {
	color = sf::Color(20, 20, 20);
	material = Material("air", color, 0);
}

Steam::Steam(Vec pos) : Gas(pos) {
	lifeTime = 1000;
	color = sf::Color(150, 150, 150);
	material = Material("steam", color, -1);
}

bool Steam::tick(Field<Particle *> &particles) {
	move(particles);
	lifeTime -= rand() % 6;
	if (lifeTime < 0) {
		particles.transmutate(pos, new Water(pos));
		return true;
	}
	if (getAir(particles) || rand() % 7 == 0) {
		return true;
	}
	return false;
}

bool Air::tick(Field<Particle *> &particles) { return move(particles); }

bool Gas::canSwap(Vec delta, Field<Particle *> &particles) {
	if (pos + delta >= 0 && pos + delta < particles.getSize()) {
        if(!particles[pos + delta]->isGas()) return false;
		bool stable = particles[pos + delta]->lighter(*this);
		return stable;
	}
	return false;
}

bool Gas::move(Field<Particle *> &particles) {
	if (trySwap(Vec(0, 1), particles)) return true;
	if (canSwap(Vec(-1, 0), particles) && trySwap(Vec(-1, 1), particles)) return true;
	if (canSwap(Vec(1, 0), particles) && trySwap(Vec(1, 1), particles)) return true;
	if (trySwap(Vec(-1, 0), particles)) return true;
	if (trySwap(Vec(1, 0), particles)) return true;
	return false;
}