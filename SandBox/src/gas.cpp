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
	bool action = move(particles);
	lifeTime -= rand() % 10;
	if (lifeTime < 0 && rand() % 400 == 0) {
		particles.transmutate(pos, new Water(pos));
		return true;
	}
	keep = !all(getName(), particles);
	return action;
}

bool Air::tick(Field<Particle *> &particles) { return move(particles); }

bool Gas::canSwap(Vec delta, Field<Particle *> &particles) {
	if (particles.validPos(pos + delta) && particles[pos + delta]->moveable()) {
		return lighterThan(*particles[pos + delta]);
	}
	return false;
}

bool Gas::move(Field<Particle *> &particles) {
	if (!all(getName(), particles)) keep = true;

	if (trySwap(Vec(0, 1), particles)) {
	} else if (trySwap(speed, particles)) {
	} else if (canSwap(Vec(-1, 0), particles) && canSwap(Vec(1, 0), particles)) {
		if (rand() % 2 == 0)
			speed = Vec(1, 0);
		else
			speed = Vec(-1, 0);
	} else if (canSwap(Vec(-1, 0), particles)) {
		speed = Vec(-1, 0);
	} else if (canSwap(Vec(1, 0), particles)) {
		speed = Vec(1, 0);
	} else {
		return false;
		speed = Vec(0, 0);
	}
	return true;
}