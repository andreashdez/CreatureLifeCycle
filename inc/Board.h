#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>
#include "Location.h"
#include "Direction.h"

class Board {

private:
	unsigned m;
	unsigned n;
	std::vector<Location> field;
	std::vector<std::unique_ptr<Creature>> creatures;

public:
	Board();
	~Board();

	void SetM(unsigned);
	void SetN(unsigned);

	void CreateField();
	void AddCreature(std::unique_ptr<Creature>, unsigned, unsigned);

	void DirectionToLocation(Direction, Coordinates&);
	void InBoundaries(int&, int&);
	void CreatureMovement(Creature*);
	void CreatureCombat(Creature*, std::vector<Creature*>&);
	void CreatureProcreation(Creature*, std::vector<std::unique_ptr<Creature>>&);
	void CreatureStarvation(Creature*, std::vector<Creature*>&);
	bool Refresh();
	void Print() const;

};

#endif
