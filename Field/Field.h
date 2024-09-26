#pragma once
#include "Obstacle.h"

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