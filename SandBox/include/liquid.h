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
	bool move(Field<Particle *> &);
	virtual ~Liquid(){};
};

class Acid : public Liquid {
   public:
	Acid(Vec pos);
	bool allAcid(Field<Particle *> &particles);
	bool canCorrode(){return false;}
	bool tick(Field<Particle *> &);
	virtual ~Acid() {}
};

class Water : public Liquid {
   public:
	Water(Vec pos);
	void heat(Field<Particle *> &);
	bool tick(Field<Particle *> &);
	virtual ~Water() {}
};

class Oil : public Liquid, public Flammable {
   public:
	Oil(Vec pos, bool onFire = false);
	bool tick(Field<Particle *> &);
	virtual ~Oil() {}
};

#endif