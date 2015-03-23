#include <iostream>
#include "Board.h"
#include "Creature.h"

using std::cout;
using std::endl;
using std::shared_ptr;

Board::Board(): m(0), n(0), field(NULL) {}
Board::~Board() {
	for (size_t i=0; i<m*n; i++)
		delete field[i];
}

void Board::SetM(unsigned m) { this->m = m; }
void Board::SetN(unsigned n) { this->n = n; }

void Board::CreateField() {
	field = new Location*[m*n];

	for (size_t i=0; i<m; i++) {
		for (size_t j=0; j<n; j++) {
			field[i*m+j] = new Location;
			field[i*m+j]->coordinates.x = i;
			field[i*m+j]->coordinates.y = j;
			field[i*m+j]->food = rand()%10;
		}
	}
}

void Board::AddCreature(shared_ptr<Creature> creature, unsigned x, unsigned y) {
	creature->AddToLocation(field[x*m+y]);
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
		creature->UpdateLocation(field[coordinates.x*m+coordinates.y]);
	}
}

void Board::CreatureCombat(shared_ptr<Creature> &creature) {
	Coordinates coordinates;

	coordinates = creature->GetLocation()->coordinates;
	shared_ptr<Creature> killed = creature->Combat();
	if (killed) {
		for (size_t i = 0; i<creatures.size(); i++) {
			if (creatures[i] == killed) {
				creatures.erase(creatures.begin() + i);
				killed.reset();
				break;
			}
		}
	}
}

void Board::CreatureProcreation(shared_ptr<Creature> &parentCreature) {
	shared_ptr<Creature> childCreature = parentCreature->Procreation();

	if (childCreature) {
		creatures.push_back(childCreature);
	}
}

void Board::CreatureStarvation(shared_ptr<Creature> &creature) {
	Coordinates coordinates;

	coordinates = creature->GetLocation()->coordinates;
	field[coordinates.x*m+coordinates.y]->food--;
	shared_ptr<Creature> starved = creature->Starvation();
	if (starved) {
		for (size_t i = 0; i<creatures.size(); i++) {
			if (creatures[i] == starved) {
				creatures.erase(creatures.begin() + i);
				starved.reset();
				break;
			}
		}
	}
}

bool Board::Refresh() {
	for (size_t i = 0; i<creatures.size(); i++) {
		shared_ptr<Creature> creature = creatures[i];
		CreatureMovement(creature);
		CreatureCombat(creature);
		CreatureProcreation(creature);
		CreatureStarvation(creature);
	}

	return creatures.empty();
}

void Board::Print() const {
	cout << endl;
	for (size_t i=0; i<m; i++) {
		for (size_t j=0; j<n; j++) {
			cout << " ";
			if (field[i*m+j]->aphids.size() == 0)
				cout << "_";
			else if (field[i*m+j]->aphids.size() > 9)
				cout << "~";
			else
				cout << field[i*m+j]->aphids.size();

			if (field[i*m+j]->ladybugs.size() == 0)
				cout << "_";
			else if (field[i*m+j]->ladybugs.size() > 9)
				cout << "~";
			else
				cout << field[i*m+j]->ladybugs.size();
		}
		cout << endl;
	}
}
