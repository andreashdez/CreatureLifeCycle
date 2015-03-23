#ifndef BOARD_H
#define BOARD_H

#include "Location.h"
#include "Direction.h"

class Board {

private:
	unsigned m;
	unsigned n;
	Location **field;
	std::vector<std::shared_ptr<Creature>> creatures;

public:
	Board();
	~Board();

	void SetM(unsigned);
	void SetN(unsigned);

	void CreateField();
	void AddCreature(std::shared_ptr<Creature>, unsigned, unsigned);

	void DirectionToLocation(Direction, Coordinates&);
	void InBoundaries(int&, int&);
	void CreatureMovement(std::shared_ptr<Creature>&);
	void CreatureCombat(std::shared_ptr<Creature>&);
	void CreatureProcreation(std::shared_ptr<Creature>&);
	void CreatureStarvation(std::shared_ptr<Creature>&);
	bool Refresh();
	void Print() const;

};

#endif
