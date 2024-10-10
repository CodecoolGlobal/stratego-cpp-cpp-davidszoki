#pragma once
#include "../Field/Field.h"
#include <memory>
#include <vector>

class GameLogic {
    Players players;
    Ranks ranks;
    Position positions;
    std::vector<std::vector<std::shared_ptr<Field>>> fields;
    public:
    GameLogic(Players player, Ranks ranks, Position positions);
    void initializedBoard();
    void fillUpBoard(Players player, Ranks rank, Position position);
    void printboard();
};