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

    bool canPlayerMove(Players player);

    void printBoard() const;

    Field *getFieldPtr(const std::pair<int, int> &field) const;

    bool handleAction(const std::pair<int, int> &from, const std::pair<int, int> &to, Players currentPlayer);

    void transferUnit(const std::pair<int, int> &from, const std::pair<int, int> &to);

    void removeUnit(const std::pair<int, int> &field);

    void handleCapture(const std::pair<int, int> &from, const std::pair<int, int> &to);

    void executeStandardCapture(Unit *fromUnit, Unit *toUnit, const std::pair<int, int> &from,
                                const std::pair<int, int> &to);

    bool checkSpecialCaptureRules(Unit *fromUnit, Unit *toUnit, const std::pair<int, int> &from,
                                  const std::pair<int, int> &to);

    Ranks checkFieldUnitRank(const std::pair<int, int> &field) const;

    bool checkMoveInBounds(const std::pair<int, int> &to) const;

    bool checkUnitMoveable(Unit *unit) const;

    bool checkIsOwnUnit(const std::pair<int, int> &from, Players currentPlayer) const;

    bool checkDistanceValidation(const std::pair<int, int> &from, const std::pair<int, int> &to) const;

    bool checkTargetFieldEmpty(const std::pair<int, int> &to) const;

    bool checkTargetFieldHasEnemyUnit(const std::pair<int, int> &to, Players player) const;

    bool checkMoveValidation(const std::pair<int, int> &from, const std::pair<int, int> &to,
                             Players currentPlayer) const;
};