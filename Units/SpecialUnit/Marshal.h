#pragma once
#include "../ArmyUnit.h"

class Marshal : public ArmyUnit {
public:
    Marshal(Players player) : ArmyUnit(Ranks::Marshal, player) {
    }
};
