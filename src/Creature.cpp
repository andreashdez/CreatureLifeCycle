#include <iostream>
#include "Creature.h"

using std::cout;
using std::endl;

Creature::Creature(): location(NULL), life(0) {}
Creature::Creature(Location *location, int life) : location(location), life(life) {}
Creature::~Creature() {}

Location* Creature::GetLocation() { return location; }

void Creature::UpdateLocation(Location *newLocation) {
	location = newLocation;
}

void Creature::AddToLocation(Location* newLocation) {
	location = newLocation;
}

std::shared_ptr<Creature> Creature::Starvation() {
	return NULL;
}

Direction Creature::Movement() {
	return Direction::SAME;
}

std::shared_ptr<Creature> Creature::Combat() {
	return NULL;
}

std::shared_ptr<Creature> Creature::Procreation() {
	return NULL;
}
