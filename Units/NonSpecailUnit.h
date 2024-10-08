#pragma once
#include "ArmyUnit.h"

class NonSpecialUnit : public ArmyUnit {
public:
    NonSpecialUnit(Ranks rank, Players player) : ArmyUnit(rank, player) {
    }
};