#include "GameLogic.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

#include "../Units/ArmyUnit.h"

using namespace std;

GameLogic::GameLogic(Players player, Ranks rank, Position position): players(player), ranks(rank), positions(position) {
    initializedBoard();
    fillUpBoard(player, rank, position);
    printboard();
}

void GameLogic::initializedBoard() {
    fields = vector(10, vector<shared_ptr<Field>>(10));
}

void GameLogic::fillUpBoard(Players player, Ranks rank, Position position) {
    shared_ptr<ArmyUnit> armyUnit = make_shared<ArmyUnit>(rank, player);
    shared_ptr<Field> unit = make_shared<Field>(position);
    unit->setUnit(armyUnit);
}


void GameLogic::printboard() {
    for (size_t row = 0; row < fields.size(); ++row) {
        for (size_t col = 0; col < fields[row].size(); ++col) {
            if(fields[row][col]) {
                fields[row][col]->printField();
            } else {
                cout << "[Empty]";
            }
            cout << " ";
        }
        cout << endl;
    }
}

