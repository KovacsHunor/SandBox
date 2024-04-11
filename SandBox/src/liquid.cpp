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

void Water::tick(Field<Particle *> &particles) {
	move(particles);
	setKeep(true);
	if (rand() % 3000 == 0) {
		heat(particles);  // transmutation !!!
	}
}

void Liquid::move(Field<Particle *> &particles) {
	setChanged(true);
	if (trySwap(Vec(0, -1), particles)) {
		speed = Vec(0, 0);
	} else if (canSwap(Vec(-1, 0), particles) && trySwap(Vec(-1, -1), particles)) {
		speed = Vec(0, 0);
	} else if (canSwap(Vec(1, 0), particles) && trySwap(Vec(1, -1), particles)) {
		speed = Vec(0, 0);
	} else if (trySwap(speed, particles))
		;
	else if (canSwap(Vec(-1, 0), particles) && canSwap(Vec(1, 0), particles)) {
		if (rand() % 2 == 0)
			speed = Vec(1, 0);
		else
			speed = Vec(-1, 0);
	} else if (canSwap(Vec(-1, 0), particles)) {
		speed = Vec(-1, 0);
	} else if (canSwap(Vec(1, 0), particles)) {
		speed = Vec(1, 0);
	} else {
		setChanged(false);
	}
}
Oil::Oil(Vec pos, bool onFire) : Liquid(pos), Flammable(onFire) {
	updated.push_back(pos);
	material = Material("oil", sf::Color(55, 58, 54), 2);
	if (!onFire) color = material.color;
}

void Oil::tick(Field<Particle *> &particles) {
	move(particles);
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
		lifeTime -= rand() % 50;
		if (lifeTime < 0) {
			if (rand() % 10 == 0) {
				particles.transmutate(pos, new Air(pos));
				return;
			}
		}

		if (!getAir(particles) && rand() % 24 < 7) {
			extinguish();
		}
		setKeep(true);
	}
}

Acid::Acid(Vec pos) : Liquid(pos) {
	updated.push_back(pos);
	material = Material("acid", sf::Color(143, 254, 9), 1);
	color = material.color;
}

void Acid::tick(Field<Particle *> &particles) {
	move(particles);
	Vec corrodex = Vec(pos.x + 1 - 2 * (rand() % 2), pos.y);
	Vec corrodey = Vec(pos.x, pos.y + 1 - 2 * (rand() % 2));

	if ((rand() % 15 == 0) && (corrodey >= 0 && corrodey < particles.getSize()) && particles[corrodey]->canCorrode()) {
		particles.transmutate(corrodey, new Air(corrodey));
		if (rand() % 3 == 0) particles.transmutate(pos, new Air(pos));
	} else if ((rand() % 60 == 0) && (corrodex >= 0 && corrodex < particles.getSize()) && particles[corrodex]->canCorrode()) {
		particles.transmutate(corrodex, new Air(corrodex));
		if (rand() % 3 == 0) particles.transmutate(pos, new Air(pos));
	}
	keep = !all("acid", particles);
}
