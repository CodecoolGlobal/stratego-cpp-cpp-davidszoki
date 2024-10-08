#pragma once
#include "Unit.h"

class ArmyUnit : public Unit{
    Ranks rank;
    Players player;

public:
    ArmyUnit(Ranks rank, Players player) : rank(rank), player(player) {};

    Players getPlayer() const { return player; }
    Ranks getRank() const { return rank; }

    void print() const;
    void setPLayer(Players newPlayer) { player = newPlayer; }
};