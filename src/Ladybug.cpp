#include <iostream>
#include "Location.h"
#include "Ladybug.h"
#include "Random.h"

using std::cout;
using std::endl;

Ladybug::Ladybug(): Creature(nullptr, 15) {
//	cout << "   [+] Constructing Ladybug" << endl;
	ChangeDirection();
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
	switch (Random::Int(0, 3)) {
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
	double probDirection = Random::Probability();
	
	if (probDirection < Ladybug::probDirection)
		ChangeDirection();

	double probMove = Random::Probability();

	if (probMove < Ladybug::probMove) {
		switch (Random::Int(0, 2)) {
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

Creature* Ladybug::Combat() {
	if (location->aphids.size() > 0) {
		IndexCreature indexAphids = location->aphids.end() - 1; // More efficient to remove last element
		double prob = Random::Probability();

		if (prob < Ladybug::probKill) {
			Creature* killed = *indexAphids;
			location->aphids.erase(indexAphids);
			return killed;
		}
	}

	return nullptr;
}

std::unique_ptr<Creature> Ladybug::Procreation() {
	if (location->ladybugs.size() > 1) {
		double prob = Random::Probability();

		if (prob < Ladybug::probProcreate) {
			std::unique_ptr<Creature> ladybug = std::make_unique<Ladybug>(location);
			location->ladybugs.push_back(ladybug.get());

			return ladybug;
		}
	}

	return nullptr;
}

void Ladybug::UpdateLocation(Location* newLocation) {
	Creature* movingLadybug = this;

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
	Creature* movingLadybug = this;

	location = newLocation;
	location->ladybugs.push_back(movingLadybug);
}

Creature* Ladybug::Starvation() {
	if (location->food > 0) {
		++life;
	}
	if (--life < 1) {
		Creature* starvedLadybug = this;

		for (IndexCreature indexLadybugs = location->ladybugs.begin(); indexLadybugs < location->ladybugs.end(); indexLadybugs++) {
			if (starvedLadybug == *indexLadybugs) {
				location->ladybugs.erase(indexLadybugs);
				break;
			}
		}
		return starvedLadybug;
	}
	return nullptr;
}
