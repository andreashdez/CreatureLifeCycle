#include <iostream>
#include <math.h>
#include "Location.h"
#include "Aphid.h"

using std::cout;
using std::endl;
using std::shared_ptr;

Aphid::Aphid(): Creature(NULL, 10) {
	//cout << "   [+] Constructing Aphid" << endl;
}
Aphid::Aphid(Location *location): Creature(location, 2) {
	//cout << "   [+] Constructing Aphid" << endl;
}
Aphid::~Aphid() {
	//cout << "   [-] Deconstructing Aphid" << endl;
}

void Aphid::SetProbMove(double probMove) { Aphid::probMove = probMove; }
void Aphid::SetProbKill(double probKill) { Aphid::probKill = probKill; }
void Aphid::SetProbAccomplice(double probAccomplice) { Aphid::probAccomplice = probAccomplice; }
void Aphid::SetProbProcreate(double probProcreate) { Aphid::probProcreate = probProcreate; }

Direction Aphid::Movement() {
	double prob = static_cast <double> (rand()) / RAND_MAX;

	if (prob < Aphid::probMove) {
		switch ((int)round(prob*8)) {
		case 0:
			return Direction::NW;
		case 1:
			return Direction::N;
		case 2:
			return Direction::NE;
		case 3:
			return Direction::W;
		case 4:
			return Direction::E;
		case 5:
			return Direction::SW;
		case 6:
			return Direction::S;
		case 7:
			return Direction::SE;
		default:
			break;
		};
	}

	return Direction::SAME;
}

shared_ptr<Creature> Aphid::Combat() {
	if (location->ladybugs.size() > 0) {
		IndexCreature indexLadybugs = location->ladybugs.end() - 1; // More efficient to remove last element
		double probKill = Aphid::probKill + (location->aphids.size() * Aphid::probAccomplice);
		double prob = static_cast <double> (rand()) / RAND_MAX;

		if (prob < probKill) {
			shared_ptr<Creature> killed = *indexLadybugs;
			location->ladybugs.erase(indexLadybugs);
			return killed;
		}
	}

	return NULL;
}

shared_ptr<Creature> Aphid::Procreation() {
	if (location->aphids.size() > 1) {
		double prob = static_cast <double> (rand()) / RAND_MAX;

		if (prob < Aphid::probProcreate) {
			std::shared_ptr<Creature> aphid = std::make_shared<Aphid>(location);
			location->aphids.push_back(aphid);

			return aphid;
		}
	}

	return NULL;
}

void Aphid::UpdateLocation(Location* newLocation) {
	shared_ptr<Creature> movingAphid = shared_from_this();
	
	for (IndexCreature indexAphids = location->aphids.begin(); indexAphids < location->aphids.end(); indexAphids++) {
		if (movingAphid == *indexAphids) {
			location->aphids.erase(indexAphids);
			break;
		}
	}

	location = newLocation;
	location->aphids.push_back(movingAphid);
}

void Aphid::AddToLocation(Location* newLocation) {
	shared_ptr<Creature> movingLadybug = shared_from_this();

	location = newLocation;
	location->aphids.push_back(movingLadybug);
}

std::shared_ptr<Creature> Aphid::Starvation() {
	if (location->food > 0) {
		++life;
	}
	if (--life < 1) {
		shared_ptr<Creature> starvedAphid = shared_from_this();

		for (IndexCreature indexAphids = location->aphids.begin(); indexAphids < location->aphids.end(); indexAphids++) {
			if (starvedAphid == *indexAphids) {
				location->aphids.erase(indexAphids);
				break;
			}
		}
		return starvedAphid;
	}
	return NULL;
}
