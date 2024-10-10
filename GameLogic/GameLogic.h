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
    std::vector<std::vector<std::shared_ptr<Field>>> fields;
    vector<vector<SDL_UnitRect*>> actualRects;
    std::vector<Ranks> ranks = {
        Ranks::Flag, Ranks::Spy, Ranks::Scout, Ranks::Scout, Ranks::Scout, Ranks::Scout, Ranks::Scout, Ranks::Scout,
        Ranks::Scout, Ranks::Scout, Ranks::Miner, Ranks::Miner,
        Ranks::Miner, Ranks::Miner, Ranks::Miner, Ranks::Sergeant, Ranks::Sergeant, Ranks::Sergeant, Ranks::Sergeant,
        Ranks::Sergeant, Ranks::Sergeant,
        Ranks::Lieutenant, Ranks::Lieutenant, Ranks::Captain, Ranks::Captain, Ranks::Captain, Ranks::Captain, Ranks::Major,
        Ranks::Major, Ranks::Major, Ranks::Colonel,
        Ranks::Colonel, Ranks::General, Ranks::Marshal,
        Ranks::Bomb, Ranks::Bomb, Ranks::Bomb, Ranks::Bomb, Ranks::Bomb, Ranks::Bomb
    };
    UI* ui;
    Players actualPlayer;

public:
    GameLogic();

    ~GameLogic();

    void initializeBoard();
    void printBoard();
    void run();
    void copyArmyToBoard(vector<vector<SDL_UnitRect*>>);
    std::vector<Ranks> getRanks();
    void setActualPLayer(Players player);
    Players getActualPLayer();
    vector<vector<SDL_UnitRect*>> getBoardData();
    bool inGame;
};
