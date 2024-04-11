#include "solid.h"

Sand::Sand(Vec pos) : Solid(pos) {
	color = sf::Color::Yellow;
	material = Material("sand", color, 10);
}

void Sand::tick(Field<Particle *> &particles) { move(particles); }

void Solid::move(Field<Particle *> &particles) {
	setChanged(true);
	if (trySwap(Vec(0, -1), particles)) {
	} else if (canSwap(Vec(-1, 0), particles) && trySwap(Vec(-1, -1), particles)) {
	} else if (canSwap(Vec(1, 0), particles) && trySwap(Vec(1, -1), particles)) {
	} else {
		setChanged(false);
	}
}