#include <iostream>
#include "Unit.h"
using namespace std;

Unit::Unit(Ranks rank, Players player, Position pos) : rank(rank), player(player), position(pos) {}

void Position::printPosition() const {
    cout << "X:" << getX() << " Y:" << getY() << endl;
}
