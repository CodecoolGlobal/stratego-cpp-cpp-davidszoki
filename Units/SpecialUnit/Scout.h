#pragma once
#include "../ArmyUnit.h"

class Scout : public ArmyUnit {
public:
    Scout(Players player) : ArmyUnit(Ranks::Scout, player) {
    }
};