#pragma once
#include "Unit.h"

class Marshal : public Unit {
public:
    Marshal(Players player, Position position) : Unit(Ranks::Marshal, player, position) {
    }
};
