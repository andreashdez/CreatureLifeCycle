#ifndef LOCATION_H
#define LOCATION_H

#include <vector>
#include "Coordinates.h"

class Creature;

struct Location {
	std::vector<Creature*> aphids;
	std::vector<Creature*> ladybugs;
	Coordinates coordinates;
	int food;
};


#endif
