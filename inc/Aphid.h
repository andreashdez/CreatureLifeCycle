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
	Creature* Combat();
	std::unique_ptr<Creature> Procreation();
	virtual Creature* Starvation();

	void UpdateLocation(Location*);
	void AddToLocation(Location*);
};

#endif
