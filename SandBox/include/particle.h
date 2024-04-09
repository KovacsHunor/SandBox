#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "field.h"
#include "material.h"
#include "util.h"

class Particle {
   protected:
	sf::Color color;
	Vec pos;
	Material material;

   public:
	static std::vector<Vec> updated;
	static std::vector<Vec> active;

	Particle() {}
	Particle(Vec pos) : pos(pos) { updated.push_back(pos); }
	static size_t updateSize() { return updated.size(); }
	static Vec updateBack() { return updated.back(); }
	static void updatePop() { return updated.pop_back(); }
	static void DEBUG() { std::cout << active.size() << std::endl; }
	virtual bool canCorrode(){return true;}
	virtual bool isGas() { return false; }
	bool getAir(Field<Particle *> &particles);

	void draw(const sf::RenderWindow &window, std::vector<sf::Vertex> &vertices);

	bool trySwap(Vec delta, Field<Particle *> &particles);

	Vec getPos() const { return pos; }

	void swap(Vec delta, Field<Particle *> &particles);

	void setPos(Vec p) { pos = p; }
	std::string getName() { return material.name; }

	virtual bool denser(Particle &waiter) { return waiter.getDensity() > getDensity(); };
	virtual bool lighter(Particle &waiter) { return waiter.getDensity() < getDensity(); };
	virtual bool canSwap(Vec delta, Field<Particle *> &particles);
	virtual bool tick(Field<Particle *> &) { return false; }
	virtual bool move(Field<Particle *> &) { return false; }

	virtual void heat(Field<Particle *> &) {}

	void print() {
		std::cout << int(color.r) << " " << int(color.g) << " " << int(color.b) << std::endl;
	}

	int getDensity() { return material.density; }
	sf::Color getColor() { return material.color; }
	virtual ~Particle() {}
};

#endif