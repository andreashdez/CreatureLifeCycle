#ifndef LOCATION_H
#define LOCATION_H

#include <vector>
#include <memory>
#include "Coordinates.h"

class Creature;

struct Location {
	std::vector<std::shared_ptr<Creature>> aphids;
	std::vector<std::shared_ptr<Creature>> ladybugs;
	Coordinates coordinates;
	int food;
};


#endif
