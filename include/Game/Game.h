#pragma once
#include <IGame.h>
#include <Field.h>
#include <UI.h>

class Game : public IGame {
    UI ui;

public:
    Game();

    ~Game() = default;

    void run();

    void initializeBoard();

    bool checkGameOver(Players currentPlayer);

    bool canPlayerMove(Players player);

    void printBoard() const;

    void placeUnit(const std::pair<int, int> &to, const Players &player, const Ranks &rank);
    
    bool checkUnitPlaceInBounds(const std::pair<int, int> &to) override;

    void removeUnit(const std::pair<int, int> &field) override;

    void removeUnit(const SDL_Point &field) override;

    void changePlayer(Players &currentPlayer) override;

    void resetGame() override;

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