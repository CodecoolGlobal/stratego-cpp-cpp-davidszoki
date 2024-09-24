#ifndef MARSHALL_H
#define MARSHALL_H
#include "Unit.h"

class Marshal : public Unit {
    int move = 1;

public:
    Marshal(): Unit(Ranks::Marshal, none, Position(0, 0)) {
    }
};
#endif //MARSHALL_H
