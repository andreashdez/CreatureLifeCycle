#include <iostream>
#include <fstream>
#include "Aphid.h"
#include "Ladybug.h"
#include "Builder.h"

using std::ifstream;
using std::shared_ptr;
using std::cerr;
using std::endl;

double Aphid::probMove = 0.7;
double Aphid::probKill = 0.2;
double Aphid::probAccomplice = 0.1;
double Aphid::probProcreate = 0.4;

double Ladybug::probMove = 0.7;
double Ladybug::probKill = 0.2;
double Ladybug::probDirection = 0.4;
double Ladybug::probProcreate = 0.2;

void Builder::ReadBoard(Board* &board) {
	ifstream in;
	in.open("board.conf");
	if (!in.fail()) {
		unsigned m, n;
		unsigned creatures;
		unsigned x, y;

		// Read Board dimentions
		in >> m >> n;
		board->SetM(m);
		board->SetN(n);
		board->CreateField();

		// Read Aphids
		in >> creatures;
		for (size_t i=0; i<creatures; i++) {
			in >> x >> y;
			shared_ptr<Creature> aphid = std::make_shared<Aphid>();
			board->AddCreature(aphid, x, y);
		}

		// Read Ladybugs
		in >> creatures;
		for (size_t i = 0; i < creatures; i++) {
			in >> x >> y;
			shared_ptr<Creature> ladybug = std::make_shared<Ladybug>();
			board->AddCreature(ladybug, x, y);
		}
	}
	else {
		cerr << "File \"board.conf\" not found, using standard data." << endl;
		LoadStandardDate(board);
	}
	in.close();
}

void Builder::ReadAphids() {
	ifstream in;
	in.open("aphid.conf");
	if (!in.fail()) {
		double probMove, probKill, probAccomplice, probProcreate;
		in >> probMove >> probKill >> probAccomplice >> probProcreate;
		Aphid::SetProbMove(probMove);
		Aphid::SetProbKill(probKill);
		Aphid::SetProbAccomplice(probAccomplice);
		Aphid::SetProbProcreate(probProcreate);
	}
	else {
		cerr << "File \"aphid.conf\" not found, using standard data." << endl;
	}
	in.close();
}

void Builder::ReadLadybugs() {
	ifstream in;
	in.open("ladybug.conf");
	if (!in.fail()) {
		double probMove, probKill, probDirection, probProcreate;
		in >> probMove >> probKill >> probDirection >> probProcreate;
		Ladybug::SetProbMove(probMove);
		Ladybug::SetProbKill(probKill);
		Ladybug::SetProbDirection(probDirection);
		Ladybug::SetProbProcreate(probProcreate);
	}
	else {
		cerr << "File \"ladybug.conf\" not found, using standard data." << endl;
	}
	in.close();
}

void Builder::LoadStandardDate(Board* &board) {
	board->SetM(10);
	board->SetN(10);
	board->CreateField();

	shared_ptr<Creature> aphid = std::make_shared<Aphid>();
	board->AddCreature(aphid, 3, 5);
	aphid = std::make_shared<Aphid>();
	board->AddCreature(aphid, 4, 8);
	aphid = std::make_shared<Aphid>();
	board->AddCreature(aphid, 2, 9);
	aphid = std::make_shared<Aphid>();
	board->AddCreature(aphid, 1, 6);
	aphid = std::make_shared<Aphid>();
	board->AddCreature(aphid, 1, 9);

	shared_ptr<Creature> ladybug = std::make_shared<Ladybug>();
	board->AddCreature(ladybug, 5, 9);
	ladybug = std::make_shared<Ladybug>();
	board->AddCreature(ladybug, 1, 1);
	ladybug = std::make_shared<Ladybug>();
	board->AddCreature(ladybug, 3, 8);
	ladybug = std::make_shared<Ladybug>();
	board->AddCreature(ladybug, 9, 2);
}