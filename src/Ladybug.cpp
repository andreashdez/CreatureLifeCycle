#include <iostream>
#include <math.h>
#include "Location.h"
#include "Ladybug.h"

using std::cout;
using std::endl;
using std::shared_ptr;

Ladybug::Ladybug(): Creature(NULL, 15) {
//	cout << "   [+] Constructing Ladybug" << endl;
}
Ladybug::Ladybug(Location *location): Creature(location, 5) {
	//cout << "   [+] Constructing Ladybug" << endl;
	ChangeDirection();
}
Ladybug::~Ladybug() {
	//cout << "   [-] Deconstructing Ladybug" << endl;
}

void Ladybug::SetProbMove(double probMove) { Ladybug::probMove = probMove; }
void Ladybug::SetProbKill(double probKill) { Ladybug::probKill = probKill; }
void Ladybug::SetProbDirection(double probDirection) { Ladybug::probDirection = probDirection; }
void Ladybug::SetProbProcreate(double probProcreate) { Ladybug::probProcreate = probProcreate; }

void Ladybug::ChangeDirection() {
	switch (rand() % 4) {
	case 0:
		this->preferedDirection[0] = Direction::NW;
		this->preferedDirection[1] = Direction::N;
		this->preferedDirection[2] = Direction::NE;
		break;
	case 1:
		this->preferedDirection[0] = Direction::SW;
		this->preferedDirection[1] = Direction::W;
		this->preferedDirection[2] = Direction::NW;
		break;
	case 2:
		this->preferedDirection[0] = Direction::NE;
		this->preferedDirection[1] = Direction::E;
		this->preferedDirection[2] = Direction::SE;
		break;
	case 3:
		this->preferedDirection[0] = Direction::SE;
		this->preferedDirection[1] = Direction::S;
		this->preferedDirection[2] = Direction::SW;
		break;
	default:
		break;
	};
}

Direction Ladybug::Movement() {
	double prob = static_cast <double> (rand()) / RAND_MAX;
	
	if (prob < Ladybug::probDirection)
		ChangeDirection();

	if (prob < Ladybug::probMove) {
		switch ((int)round(prob*3)) {
		case 0:
			return preferedDirection[0];
		case 1:
			return preferedDirection[1];
		case 2:
			return preferedDirection[2];
		default:
			break;
		};
	}

	return Direction::SAME;
}

shared_ptr<Creature> Ladybug::Combat() {
	if (location->aphids.size() > 0) {
		IndexCreature indexAphids = location->aphids.end() - 1; // More efficient to remove last element
		double prob = static_cast <double> (rand()) / RAND_MAX;

		if (prob < Ladybug::probKill) {
			shared_ptr<Creature> killed = *indexAphids;
			location->aphids.erase(indexAphids);
			return killed;
		}
	}

	return NULL;
}

shared_ptr<Creature> Ladybug::Procreation() {
	if (location->ladybugs.size() > 1) {
		double prob = static_cast <double> (rand()) / RAND_MAX;

		if (prob < Ladybug::probProcreate) {
			shared_ptr<Creature> ladybug = std::make_shared<Ladybug>(location);
			location->ladybugs.push_back(ladybug);

			return ladybug;
		}
	}

	return NULL;
}

void Ladybug::UpdateLocation(Location* newLocation) {
	shared_ptr<Creature> movingLadybug = shared_from_this();

	for (IndexCreature indexLadybugs = location->ladybugs.begin(); indexLadybugs < location->ladybugs.end(); indexLadybugs++) {
		if (movingLadybug == *indexLadybugs) {
			location->ladybugs.erase(indexLadybugs);
			break;
		}
	}

	location = newLocation;
	location->ladybugs.push_back(movingLadybug);
}

void Ladybug::AddToLocation(Location* newLocation) {
	shared_ptr<Creature> movingLadybug = shared_from_this();

	location = newLocation;
	location->ladybugs.push_back(movingLadybug);
}

std::shared_ptr<Creature> Ladybug::Starvation() {
	if (location->food > 0) {
		++life;
	}
	if (--life < 1) {
		shared_ptr<Creature> starvedLadybug = shared_from_this();

		for (IndexCreature indexLadybugs = location->ladybugs.begin(); indexLadybugs < location->ladybugs.end(); indexLadybugs++) {
			if (starvedLadybug == *indexLadybugs) {
				location->ladybugs.erase(indexLadybugs);
				break;
			}
		}
		return starvedLadybug;
	}
	return NULL;
}
