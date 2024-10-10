#pragma once
#include <memory>
#include <vector>
#include <string>
#include "./Field.h"
#include "../UI/UI.h"
#include "Units/Enum.h"

using namespace std;

class UI;

class GameLogic {
    int row = 10;
    std::vector<std::vector<std::shared_ptr<Field>>> fields;
    UI* ui;
public:
    GameLogic();

    ~GameLogic();

    void initializeBoard();
    void printBoard();
    void run();
    void copyArmyToBoard(vector<vector<SDL_UnitRect*>>);
};
