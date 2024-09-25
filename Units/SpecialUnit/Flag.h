#pragma once
#include "../Unit.h"

class Flag : public Unit {
    public:
    Flag(Players player, Position position) : Unit(Ranks::Flag, player, position) {
    }
};