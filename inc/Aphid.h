#ifndef APHID_H
#define APHID_H

#include "Creature.h"

class Aphid: public Creature {

private:
	static double probMove;
	static double probKill;
	static double probAccomplice;
	static double probProcreate;

public:
	Aphid();
	Aphid(Location*);
	~Aphid();

	static void SetProbMove(double);
	static void SetProbKill(double);
	static void SetProbAccomplice(double);
	static void SetProbProcreate(double);

	Direction Movement();
	std::shared_ptr<Creature> Combat();
	std::shared_ptr<Creature> Procreation();
	virtual std::shared_ptr<Creature> Starvation();

	void UpdateLocation(Location*);
	void AddToLocation(Location*);
};

#endif
