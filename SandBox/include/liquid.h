#ifndef LIQUID_H
#define LIQUID_H

#include "field.h"
#include "flammable.h"
#include "material.h"
#include "particle.h"
#include "util.h"

class Liquid : virtual public Particle {
	Vec speed;

   public:
	Liquid(Vec pos) {
		setPos(pos);
		speed = Vec(0, 0);
	}
	void move(Field<Particle *> &);
	virtual ~Liquid(){};
};

class Acid : public Liquid {
   public:
	Acid(Vec pos);
	bool canCorrode() { return false; }
	void tick(Field<Particle *> &);
	virtual ~Acid() {}
};

class Water : public Liquid {
   public:
	Water(Vec pos);
	void heat(Field<Particle *> &);
	void tick(Field<Particle *> &);
	virtual ~Water() {}
};

class Oil : public Liquid, public Flammable {
   public:
	Oil(Vec pos, bool onFire = false);
	void tick(Field<Particle *> &);
	virtual ~Oil() {}
};

#endif