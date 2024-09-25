#pragma once
#include "../Unit.h"

class Bomb : public Unit {
public:
    Bomb(Players player, Position position) : Unit(Ranks::Bomb, player, position) {
    }
};