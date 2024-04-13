#ifndef IMMOVEABLE_H
#define IMMOVEABLE_H

#include "field.h"
#include "flammable.h"
#include "material.h"
#include "particle.h"
#include "util.h"

class Immoveable : virtual public Particle {
   public:
	Immoveable(Vec pos) { setPos(pos); }
	bool denser(Particle &) { return false; };
	bool moveable() { return false; }
	virtual ~Immoveable(){};
};

class Stone : public Immoveable {
   public:
	Stone(Vec pos);
	virtual ~Stone() {}
};

class Wood : public Immoveable, public Flammable {
   public:
	Wood(Vec pos, bool onFire = false);
	bool tick(Field<Particle *> &);

	virtual ~Wood() {}
};
#endif