#pragma once
#include "../Unit.h"

class Miner : public Unit {
public:
    Miner(Players player, Position position) : Unit(Ranks::Miner, player, position) {
    }
};