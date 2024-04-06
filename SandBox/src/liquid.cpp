#include "liquid.h"

#include "gas.h"

Water::Water(Vec pos) : Liquid(pos) {
	updated.push_back(pos);
	color = sf::Color::Blue;
	material = Material("water", color, 4);
}

void Water::heat(Field<Particle *> &particles) {
	if (rand() % 2 == 0)
		particles.transmutate(pos, new Steam(pos));
	else
		particles.transmutate(pos, new Air(pos));
}

bool Water::tick(Field<Particle *> &particles) {
	if (rand() % 3000 == 0) {
		heat(particles);
		return true;
	}
	return move(particles);
}

bool Liquid::move(Field<Particle *> &particles) {
	if (trySwap(Vec(0, -1), particles)) {
		speed = Vec(0, 0);
		return true;
	}
	if (canSwap(Vec(-1, 0), particles) && trySwap(Vec(-1, -1), particles)) {
		speed = Vec(0, 0);
		return true;
	}
	if (canSwap(Vec(1, 0), particles) && trySwap(Vec(1, -1), particles)) {
		speed = Vec(0, 0);
		return true;
	}
	if (trySwap(speed, particles)) return true;
	if (canSwap(Vec(-1, 0), particles) && canSwap(Vec(1, 0), particles)) {
		if (rand() % 2 == 0)
			speed = Vec(1, 0);
		else
			speed = Vec(-1, 0);
		return true;
	}
	if (canSwap(Vec(-1, 0), particles)) {
		speed = Vec(-1, 0);
		return true;
	}
	if (canSwap(Vec(1, 0), particles)) {
		speed = Vec(1, 0);
		return true;
	}
	return false;
}
Oil::Oil(Vec pos, bool onFire) : Liquid(pos), Flammable(onFire) {
	updated.push_back(pos);
	material = Material("oil", sf::Color(55, 58, 54), 2);
	if (!onFire) color = material.color;
}

bool Oil::tick(Field<Particle *> &particles) {
	bool event = move(particles);
	if (onFire) {
		for (int i = pos.x - 1; i <= pos.x + 1; i++) {
			for (int j = pos.y - 1; j <= pos.y + 1; j++) {
				Vec p = Vec(i, j);

				if (Vec(0, 0) <= p && p < particles.getSize()) {
					if (rand() % 20 != 0) continue;
					particles[p]->heat(particles);
				}
			}
		}
		lifeTime -= rand() % 20;
		if (lifeTime < 0) {
			if (rand() % 15 == 0) {
				particles.transmutate(pos, new Air(pos));
				return true;
			}
		}

		if (!getAir(particles) && rand() % 24 < 7) {
			extinguish();
		}
		event = true;
	}
	return event;
}