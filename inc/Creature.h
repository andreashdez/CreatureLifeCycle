#ifndef CREATURE_H
#define CREATURE_H

#include <memory>
#include <vector>
#include "Location.h"
#include "Direction.h"

using IndexCreature = std::vector<Creature*>::iterator;

class Creature {

protected:
	Location* location;
	int life;

public:
	Creature();
	Creature(Location*, int);
	virtual ~Creature();

	//void SetLocation(Location*);
	Location* GetLocation();

	virtual Direction Movement();
	virtual Creature* Combat();
	virtual std::unique_ptr<Creature> Procreation();
	virtual Creature* Starvation();

	virtual void UpdateLocation(Location*);
	virtual void AddToLocation(Location*);
};

#endif
