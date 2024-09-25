#pragma once
#include "Unit.h"

class NonSpecialUnit : public Unit {
public:
    NonSpecialUnit(Ranks rank, Players player, Position position) : Unit(rank, player, position) {
    }
};