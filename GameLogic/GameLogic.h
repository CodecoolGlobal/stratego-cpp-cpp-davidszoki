#pragma once
#include "../Field/Field.h"
#include <memory>
#include <vector>

class GameLogic {
    Players players;
    std::vector<std::vector<std::shared_ptr<Field>>> fields;
    public:
    GameLogic(Players player);
    void initializedBoard();
    void printboard();
};