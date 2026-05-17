#include <iostream>
#include "Location.h"
#include "Aphid.h"
#include "Random.h"

using std::cout;
using std::endl;

Aphid::Aphid(): Creature(nullptr, 10) {
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
	double prob = Random::Probability();

	if (prob < Aphid::probMove) {
		switch (Random::Int(0, 7)) {
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

Creature* Aphid::Combat() {
	if (location->ladybugs.size() > 0) {
		IndexCreature indexLadybugs = location->ladybugs.end() - 1; // More efficient to remove last element
		double probKill = Aphid::probKill + (location->aphids.size() * Aphid::probAccomplice);
		double prob = Random::Probability();

		if (prob < probKill) {
			Creature* killed = *indexLadybugs;
			location->ladybugs.erase(indexLadybugs);
			return killed;
		}
	}

	return nullptr;
}

std::unique_ptr<Creature> Aphid::Procreation() {
	if (location->aphids.size() > 1) {
		double prob = Random::Probability();

		if (prob < Aphid::probProcreate) {
			std::unique_ptr<Creature> aphid = std::make_unique<Aphid>(location);
			location->aphids.push_back(aphid.get());

			return aphid;
		}
	}

	return nullptr;
}

void Aphid::UpdateLocation(Location* newLocation) {
	Creature* movingAphid = this;
	
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
	Creature* movingAphid = this;

	location = newLocation;
	location->aphids.push_back(movingAphid);
}

Creature* Aphid::Starvation() {
	if (location->food > 0) {
		++life;
	}
	if (--life < 1) {
		Creature* starvedAphid = this;

		for (IndexCreature indexAphids = location->aphids.begin(); indexAphids < location->aphids.end(); indexAphids++) {
			if (starvedAphid == *indexAphids) {
				location->aphids.erase(indexAphids);
				break;
			}
		}
		return starvedAphid;
	}
	return nullptr;
}
