#include "Game.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>
#include <vector>
#include "ArmyUnit.h"
#include "Obstacle.h"
#include "Bomb.h"
#include "Marshal.h"
#include "Miner.h"
#include "Spy.h"
#include "Flag.h"

using namespace std;

vector<string> Game::playerUnits = {
    "Flag", "Spy", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Miner", "Miner",
    "Miner", "Miner", "Miner", "Sergeant", "Sergeant", "Sergeant", "Sergeant", "Lieutenant", "Lieutenant",
    "Lieutenant", "Lieutenant", "Captain", "Captain", "Captain", "Captain", "Major", "Major", "Major", "Colonel",
    "Colonel", "General", "Marshal",
    "Bomb", "Bomb", "Bomb", "Bomb", "Bomb", "Bomb"
};

vector<string> Game::players = {"Red", "Blue"};

vector<pair<int, int> > Game::obstacleLocations = {
    pair(4, 2), pair(4, 3), pair(4, 6), pair(4, 7), pair(5, 2), pair(5, 3), pair(5, 6), pair(5, 7)
};

void Game::printBoard() const {
    for (size_t row = 0; row < battleField.size(); ++row) {
        for (size_t col = 0; col < battleField[row].size(); ++col) {
            battleField[row][col]->printField();
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool Game::checkSpecialCaptureRules(Unit *fromUnit, Unit *toUnit, const std::pair<int, int> &from,
                                    const std::pair<int, int> &to) {
    if (!fromUnit || !toUnit) {
        cout << "Invalid capture attempt." << endl;
        return false;
    }

    Ranks fromRank = fromUnit->getRank();
    Ranks toRank = toUnit->getRank();

    if ((fromRank == Ranks::Spy && toRank == Ranks::Marshal) ||
        (fromRank == Ranks::Miner && toRank == Ranks::Bomb)) {
        transferUnit(from, to);
        cout << (fromRank == Ranks::Spy ? "Spy captures Marshal!" : "Miner disarms Bomb!") << endl;
        return true;
    }
    return false;
}

void Game::executeStandardCapture(Unit *fromUnit, Unit *toUnit, const std::pair<int, int> &from,
                                  const std::pair<int, int> &to) {
    if (!fromUnit || !toUnit) {
        cout << "Invalid capture logic." << endl;
        return;
    }

    Ranks fromRank = fromUnit->getRank();
    Ranks toRank = toUnit->getRank();

    if (fromRank == toRank) {
        removeUnit(from);
        removeUnit(to);
        cout << "Both units are defeated!" << endl;
    } else if (toRank > fromRank) {
        removeUnit(from);
        cout << "Attacking unit was defeated!" << endl;
    } else {
        transferUnit(from, to);
        cout << "Capture successful!" << endl;
    }
}

Ranks Game::checkFieldUnitRank(const std::pair<int, int> &field) const {
    if (const auto unit = getFieldPtr(field)->getUnitPtr()) {
        return unit->getRank();
    }
    return Ranks::None;
}

bool Game::checkMoveInBounds(const std::pair<int, int> &to) const {
    int boardSize = battleField.size();
    return (to.first >= 0 && to.first < boardSize) &&
           (to.second >= 0 && to.second < boardSize);
}

bool Game::checkUnitMoveable(Unit *unit) const {
    return unit->getMoveable();
}

bool Game::checkIsOwnUnit(const std::pair<int, int> &from, Players currentPlayer) const {
    return getFieldPtr(from)->getUnitPtr() && getFieldPtr(from)->getUnitPtr()->getPlayer() == currentPlayer;
}

bool Game::checkDistanceValidation(const std::pair<int, int> &from, const std::pair<int, int> &to) const {
    if ((abs(from.first - to.first) == 1 && from.second == to.second) ||
        (abs(from.second - to.second) == 1 && from.first == to.first))
        return true;
    return false;
}

bool Game::checkTargetFieldEmpty(const std::pair<int, int> &to) const {
    return getFieldPtr(to)->getUnitPtr() == nullptr;
}

bool Game::checkTargetFieldHasEnemyUnit(const std::pair<int, int> &to, Players player) const {
    auto targetUnit = getFieldPtr(to)->getUnitPtr();
    return targetUnit && (targetUnit->getPlayer() != player);
}

bool Game::checkMoveValidation(const std::pair<int, int> &from, const std::pair<int, int> &to,
                               Players currentPlayer) const {
    auto unit = getFieldPtr(from)->getUnitPtr();
    return unit && checkMoveInBounds(to) && checkUnitMoveable(unit) && checkDistanceValidation(from, to) &&
           checkIsOwnUnit(from, currentPlayer);
}
