#include <iostream>
#include <algorithm>
#include "Board.h"
#include "Creature.h"

using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;

namespace {
	bool ContainsCreature(const vector<shared_ptr<Creature>> &creatures, const shared_ptr<Creature> &creature) {
		return std::find(creatures.begin(), creatures.end(), creature) != creatures.end();
	}
}

Board::Board(): m(0), n(0) {}
Board::~Board() {}

void Board::SetM(unsigned m) { this->m = m; }
void Board::SetN(unsigned n) { this->n = n; }

void Board::CreateField() {
	field.clear();
	field.resize(m*n);

	for (size_t i=0; i<m; i++) {
		for (size_t j=0; j<n; j++) {
			field[i*n+j].coordinates.x = i;
			field[i*n+j].coordinates.y = j;
			field[i*n+j].food = rand()%10;
		}
	}
}

void Board::AddCreature(shared_ptr<Creature> creature, unsigned x, unsigned y) {
	creature->AddToLocation(&field[x*n+y]);
	creatures.push_back(creature);
}

void Board::DirectionToLocation(Direction direction, Coordinates &coordinates) {
	int i = coordinates.x;
	int j = coordinates.y;

	switch (direction) {
	case Direction::NW:
		i--; j--; break;
	case Direction::N:
		i--; break;
	case Direction::NE:
		i--; j++; break;
	case Direction::W:
		j--; break;
	case Direction::E:
		j++; break;
	case Direction::SW:
		i++; j--; break;
	case Direction::S:
		i++; break;
	case Direction::SE:
		i++; j++; break;
	default:
		break;
	}

	InBoundaries(i, j);

	coordinates.x = (unsigned) i;
	coordinates.y = (unsigned) j;
}

void Board::InBoundaries(int &x, int &y) {
	int maxX = this->m - 1;
	int maxY = this->n - 1;

	if (x < 0)
		x += 2;
	else if (x > maxX)
		x -= 2;

	if (y < 0)
		y += 2;
	else if (y > maxY)
		y -= 2;
}

void Board::CreatureMovement(shared_ptr<Creature> &creature) {
	Coordinates coordinates;
	Direction direction;

	coordinates = creature->GetLocation()->coordinates;
	direction = creature->Movement();
	if (direction != Direction::SAME) {
		DirectionToLocation(direction, coordinates);
		creature->UpdateLocation(&field[coordinates.x*n+coordinates.y]);
	}
}

void Board::CreatureCombat(shared_ptr<Creature> &creature, vector<shared_ptr<Creature>> &deadCreatures) {
	shared_ptr<Creature> killed = creature->Combat();
	if (killed) {
		deadCreatures.push_back(killed);
	}
}

void Board::CreatureProcreation(shared_ptr<Creature> &parentCreature, vector<shared_ptr<Creature>> &bornCreatures) {
	shared_ptr<Creature> childCreature = parentCreature->Procreation();

	if (childCreature) {
		bornCreatures.push_back(childCreature);
	}
}

void Board::CreatureStarvation(shared_ptr<Creature> &creature, vector<shared_ptr<Creature>> &deadCreatures) {
	Coordinates coordinates;

	coordinates = creature->GetLocation()->coordinates;
	field[coordinates.x*n+coordinates.y].food--;
	shared_ptr<Creature> starved = creature->Starvation();
	if (starved) {
		deadCreatures.push_back(starved);
	}
}

bool Board::Refresh() {
	vector<shared_ptr<Creature>> turnCreatures = creatures;
	vector<shared_ptr<Creature>> bornCreatures;
	vector<shared_ptr<Creature>> deadCreatures;

	for (size_t i = 0; i<turnCreatures.size(); i++) {
		shared_ptr<Creature> creature = turnCreatures[i];
		if (ContainsCreature(deadCreatures, creature))
			continue;

		CreatureMovement(creature);
		CreatureCombat(creature, deadCreatures);
		CreatureProcreation(creature, bornCreatures);
		CreatureStarvation(creature, deadCreatures);
	}

	for (size_t i = 0; i<bornCreatures.size(); i++) {
		if (!ContainsCreature(deadCreatures, bornCreatures[i]))
			creatures.push_back(bornCreatures[i]);
	}

	for (size_t i = 0; i<deadCreatures.size(); i++) {
		creatures.erase(std::remove(creatures.begin(), creatures.end(), deadCreatures[i]), creatures.end());
	}

	return creatures.empty();
}

void Board::Print() const {
	cout << endl;
	for (size_t i=0; i<m; i++) {
		for (size_t j=0; j<n; j++) {
			const Location &location = field[i*n+j];

			cout << " ";
			if (location.aphids.size() == 0)
				cout << "_";
			else if (location.aphids.size() > 9)
				cout << "~";
			else
				cout << location.aphids.size();

			if (location.ladybugs.size() == 0)
				cout << "_";
			else if (location.ladybugs.size() > 9)
				cout << "~";
			else
				cout << location.ladybugs.size();
		}
		cout << endl;
	}
}
