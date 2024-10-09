#pragma once
#include "./Units/Unit.h"

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

class Field {
    Unit* unit = nullptr;
    Position position;
public:
    Field(Position position) : position(position) {}
    bool setUnit(Unit* unit);
    Unit* getUnit() {
        return unit;
    }
    void printField() const;
};
