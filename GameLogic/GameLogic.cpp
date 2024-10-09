#include "GameLogic.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>
#include <vector>
#include "./Units/ArmyUnit.h"
#include "./Units/NonSpecialUnit.h"

using namespace std;

vector<string> ranks = {
    "Flag", "Spy", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Miner", "Miner",
    "Miner", "Miner", "Miner", "Sergeant", "Sergeant", "Sergeant", "Sergeant", "Lieutenant", "Lieutenant",
    "Lieutenant", "Lieutenant", "Captain", "Captain", "Captain", "Captain", "Major", "Major", "Major", "Colonel",
    "Colonel", "General", "Marshal",
    "Bomb", "Bomb", "Bomb", "Bomb", "Bomb", "Bomb"
};

GameLogic::GameLogic() {
}

void GameLogic::run(vector<string> players) {
    initializeBoard();
    ui.run(ranks, std::move(players));
}

void GameLogic::initializeBoard() {
    fields = vector(10, vector<shared_ptr<Field>>(10));

}

void GameLogic::printBoard() {
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