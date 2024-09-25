#pragma once
#include "Enum.h"

class Position {
    int x;
    int y;

public:
    Position(int x, int y) : x(x), y(y) {
    }
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void printPosition() const;
};

class Unit {
    Ranks rank;
    Players player;
    Position position;

public:
    Unit(Ranks rank, Players player, Position position) : rank(rank), player(player), position(position) {};

    Players getPlayer() const { return player; }
    Position getPosition() const {return position;}

    void setPLayer(Players newPlayer) { player = newPlayer; }
    void setPosition(const Position &newPosition) { position = newPosition; }
};