#include "qmaster.h"

#include <fstream>
#include <iostream>

void Qmaster::write(Node* c, std::ofstream& file) {
	file << c->getName() << std::endl;
	file << c->isLeaf() << std::endl;
	if (!c->isLeaf()) {
		write(c->getYes(), file);
		write(c->getNo(), file);
	}
}
void Qmaster::build(Node*& c, std::ifstream& file) {
	std::string str;
	getline(file, str);
	c = new Node(str);
	getline(file, str);
	if (str == "1") return;
	build(c->getYes(), file);
	build(c->getNo(), file);
}
void Qmaster::save() {
	std::ofstream file("tree.txt");
	if (!file.good()) {
		std::cout << "file not open";
	}
	write(start, file);
	file.close();
}

void Qmaster::load() {
	std::ifstream file("tree.txt");
	if (!file.good()) {
		std::cout << "file not open";
	} else {
		build(start, file);
		file.close();
	}
}
