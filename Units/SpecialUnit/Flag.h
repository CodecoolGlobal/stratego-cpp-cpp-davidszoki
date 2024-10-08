#pragma once
#include "../ArmyUnit.h"

class Flag : public ArmyUnit {
    public:
    Flag(Players player) : ArmyUnit(Ranks::Flag, player) {
    }
};