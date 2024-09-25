#pragma once
#include "../Unit.h"

class Spy : public Unit {
public:
    Spy(Players player, Position position) : Unit(Ranks::Spy, player, position) {
    }
};