#pragma once
#include "Enum.h"
#include "../Field/Field.h"

class Unit {
    Ranks rank;
    Players player;
    Position position;

public:
    Unit(Ranks rank, Players player, Position position) : rank(rank), player(player), position(position) {};

    Players getPlayer() const { return player; }
    Position getPosition() const {return position;}

    void printPlayer() const;
    void setPLayer(Players newPlayer) { player = newPlayer; }
    void setPosition(const Position &newPosition) { position = newPosition; }
};