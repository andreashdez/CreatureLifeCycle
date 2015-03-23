#ifndef LADYBUG_H
#define LADYBUG_H

#include "Creature.h"

class Ladybug: public Creature {

private:
	static double probMove;
	static double probKill;
	static double probDirection;
	static double probProcreate;
	Direction preferedDirection[3];

public:
	Ladybug();
	Ladybug(Location*);
	~Ladybug();

	static void SetProbMove(double);
	static void SetProbKill(double);
	static void SetProbDirection(double);
	static void SetProbProcreate(double);

	void ChangeDirection();
	Direction Movement();
	std::shared_ptr<Creature> Combat();
	std::shared_ptr<Creature> Procreation();
	virtual std::shared_ptr<Creature> Starvation();

	void UpdateLocation(Location*);
	void AddToLocation(Location*);
};

#endif
