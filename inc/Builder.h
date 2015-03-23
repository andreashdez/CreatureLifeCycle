#ifndef PARSER_H
#define PARSER_H

#include "Board.h"

class Builder {

public:
	void ReadBoard(Board*&);
	void ReadAphids();
	void ReadLadybugs();
	void LoadStandardDate(Board*&);

};

#endif
