#pragma once
#include "../ArmyUnit.h"

class Bomb : public ArmyUnit {
public:
    Bomb(Players player) : ArmyUnit(Ranks::Bomb, player) {
    }
};