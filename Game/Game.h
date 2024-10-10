#pragma once
#include <memory>
#include <vector>
#include "Field.h"
#include "UI.h"

class Game {
    static std::vector<std::string> players;
    static std::vector<std::string> playerUnits;
    static std::vector<std::pair<int, int> > obstacleLocations;
    std::vector<std::vector<std::unique_ptr<Field> > > battleField;
    bool gameEnded;
    UI ui;

public:
    Game() : gameEnded(false) {
    }

    void run();

    void initializeBoard();

    void printBoard() const;

    bool checkTargetFieldHasEnemyUnit(const std::pair<int, int> &to, Players player) const;

    bool checkMoveValidation(const std::pair<int, int> &from, const std::pair<int, int> &to,
                             Players currentPlayer) const;
};