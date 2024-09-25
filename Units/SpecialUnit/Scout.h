#pragma once
#include "../Unit.h"

class Scout : public Unit {
public:
    Scout(Players player, Position position) : Unit(Ranks::Scout, player, position) {
    }
};