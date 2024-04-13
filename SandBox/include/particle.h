#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>

#include "field.h"
#include "material.h"
#include "util.h"

class Particle {
   protected:
	bool change;
	bool keep;

	sf::Color color;
	Vec pos;
	Material material;
	Field<Particle **> neighbours;

   public:
	static std::deque<Vec> updated;
	static std::deque<Vec> active;

	Particle() {}
	Particle(Vec pos) : pos(pos) { updated.push_back(pos); }
	static void DEBUG() { std::cout << active.size() << std::endl; }
	virtual bool canCorrode() { return true; }
	virtual bool isGas() { return false; }
	bool getAir(Field<Particle *> &particles);
	bool Keep() { return keep; }
	void setKeep(bool b) { keep = b; }
	bool all(std::string str, Field<Particle *> &particles);

	void draw(const sf::RenderWindow &window, std::vector<sf::Vertex> &vertices);

	bool trySwap(Vec delta, Field<Particle *> &particles);

	Vec getPos() const { return pos; }

	void swap(Vec delta, Field<Particle *> &particles);

	void setPos(Vec p) { pos = p; }
	std::string getName() { return material.name; }

	virtual bool denserThan(Particle &waiter) { return waiter.getDensity() < getDensity(); };
	virtual bool lighterThan(Particle &waiter) { return waiter.getDensity() > getDensity(); };
	virtual bool canSwap(Vec delta, Field<Particle *> &particles);
	virtual bool tick(Field<Particle *> &) { return false; }
	virtual bool move(Field<Particle *> &) { return false; }
	virtual bool moveable() { return true; }
	virtual void heat(Field<Particle *> &) {}

	void print() { std::cout << int(color.r) << " " << int(color.g) << " " << int(color.b) << std::endl; }

	int getDensity() { return material.density; }
	sf::Color getColor() { return material.color; }
	virtual ~Particle() {}
};

#endif