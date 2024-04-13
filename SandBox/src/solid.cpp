#include "solid.h"

Sand::Sand(Vec pos) : Solid(pos) {
	color = sf::Color::Yellow;
	material = Material("sand", color, 10);
}

bool Sand::tick(Field<Particle *> &particles) { return move(particles); }

bool Solid::move(Field<Particle *> &particles) {
	if (trySwap(Vec(0, -1), particles)) {
	} else if (canSwap(Vec(-1, 0), particles) && trySwap(Vec(-1, -1), particles)) {
	} else if (canSwap(Vec(1, 0), particles) && trySwap(Vec(1, -1), particles)) {
	} else {
		return false;
	}
	return true;
}