#pragma once
#include "../ArmyUnit.h"

class Miner : public ArmyUnit {
public:
    Miner(Players player) : ArmyUnit(Ranks::Miner, player) {
    }
};