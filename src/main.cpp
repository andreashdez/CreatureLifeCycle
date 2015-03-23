#include <iostream>
#include <thread>
#include <chrono>
#include "Board.h"
#include "Builder.h"

using namespace std;

void ReadFiles(Board* &board) {
	Builder p;
	p.ReadBoard(board);
	p.ReadAphids();
	p.ReadLadybugs();
}

int main() {
	Board *board = new Board();
	ReadFiles(board);
	bool extintion = false;
	size_t i = 0;

	board->Print();

	while (!extintion && i<60) {
		extintion = board->Refresh();
		board->Print();
		cout << "Turn: " << ++i << endl;
		this_thread::sleep_for(chrono::milliseconds(400));
	}
	
	delete board;

	return 0;
}
