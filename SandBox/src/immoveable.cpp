#include "immoveable.h"

#include "gas.h"

Wood::Wood(Vec pos, bool onFire) : Immoveable(pos), Flammable(onFire) {
	updated.push_back(pos);
	material = Material("wood", sf::Color(200, 150, 100), INT32_MAX);
	if (!onFire) color = material.color;
}

void Wood::tick(Field<Particle *> &particles) {
	if (onFire) {
		for (int i = pos.x - 1; i <= pos.x + 1; i++) {
			for (int j = pos.y - 1; j <= pos.y + 1; j++) {
				Vec p = Vec(i, j);
				if (p != pos && j == pos.y - 1) {
					if (rand() % 2 != 0) continue;
				}

				if (Vec(0, 0) <= p && p < particles.getSize()) {
					if (rand() % 20 != 0) continue;
					particles[p]->heat(particles);
				}
			}
		}
		lifeTime -= rand() % 20;
		if (lifeTime < 0) {
			if (rand() % 20 == 0) {
				particles.transmutate(pos, new Air(pos));
				return;
			}
		}

		if (!getAir(particles)) {
			extinguish();
		} else if (rand() % 100 == 0) {
			trySwap(Vec(0, 1), particles);
		}

		setKeep(true);
	}
}

Stone::Stone(Vec pos) : Immoveable(pos) {
	updated.push_back(pos);
	material = Material("stone", sf::Color(136, 140, 141), INT32_MAX);
	color = material.color;
}
