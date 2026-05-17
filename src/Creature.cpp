#include <iostream>
#include "Creature.h"

using std::cout;
using std::endl;

Creature::Creature(): location(nullptr), life(0) {}
Creature::Creature(Location *location, int life) : location(location), life(life) {}
Creature::~Creature() {}

Location* Creature::GetLocation() { return location; }

void Creature::UpdateLocation(Location *newLocation) {
	location = newLocation;
}

void Creature::AddToLocation(Location* newLocation) {
	location = newLocation;
}

Creature* Creature::Starvation() {
	return nullptr;
}

Direction Creature::Movement() {
	return Direction::SAME;
}

Creature* Creature::Combat() {
	return nullptr;
}

std::unique_ptr<Creature> Creature::Procreation() {
	return nullptr;
}
