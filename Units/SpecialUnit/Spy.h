#pragma once
#include "../ArmyUnit.h"

class Spy : public ArmyUnit {
public:
    Spy(Players player) : ArmyUnit(Ranks::Spy, player) {
    }
};