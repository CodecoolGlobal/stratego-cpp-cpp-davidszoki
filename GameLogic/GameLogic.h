#pragma once
#include "./Field.h"
#include <memory>
#include <vector>
#include "../UI/UI.h"

#include "Units/Enum.h"

class GameLogic {
    Players players;
    std::vector<std::vector<std::shared_ptr<Field>>> fields;
    UI ui;
public:
    GameLogic();
    void initializeBoard();
    void printBoard();
    void run(std::vector<std::string> players);
};
