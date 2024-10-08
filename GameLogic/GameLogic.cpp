#include "GameLogic.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
#include "../Units/ArmyUnit.h"
#include "../Units/NonSpecailUnit.h"

using namespace std;

GameLogic::GameLogic(Players player): players(player) {
    initializedBoard();
    printboard();
}

void GameLogic::initializedBoard() {
    fields = vector(10, vector<shared_ptr<Field>>(10));
    Position position(2,3);
    ArmyUnit* colonel = new NonSpecialUnit(Ranks::Colonel, players);
    shared_ptr<Field> unit = make_shared<Field>(position);
    unit->setUnit(colonel);
    fields[2][3] = unit;
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

