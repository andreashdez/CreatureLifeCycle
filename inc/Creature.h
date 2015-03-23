#ifndef CREATURE_H
#define CREATURE_H

#include <memory>
#include <vector>
#include "Location.h"
#include "Direction.h"

typedef std::vector<std::shared_ptr<Creature>>::iterator IndexCreature;

class Creature: public std::enable_shared_from_this<Creature> {

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
	virtual std::shared_ptr<Creature> Combat();
	virtual std::shared_ptr<Creature> Procreation();
	virtual std::shared_ptr<Creature> Starvation();

	virtual void UpdateLocation(Location*);
	virtual void AddToLocation(Location*);
};

#endif
