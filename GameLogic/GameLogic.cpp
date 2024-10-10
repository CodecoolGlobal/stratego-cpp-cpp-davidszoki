#include "GameLogic.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>
#include <vector>
#include "./Units/ArmyUnit.h"
#include "./Units/NonSpecialUnit.h"
#include "Units/SpecialUnit/Bomb.h"
#include "Units/SpecialUnit/Flag.h"
#include "Units/SpecialUnit/Marshal.h"
#include "Units/SpecialUnit/Miner.h"
#include "Units/SpecialUnit/Scout.h"
#include "Units/SpecialUnit/Spy.h"

using namespace std;

vector ranks = {
    Ranks::Flag, Ranks::Spy, Ranks::Scout, Ranks::Scout, Ranks::Scout, Ranks::Scout, Ranks::Scout, Ranks::Scout,
    Ranks::Scout, Ranks::Scout, Ranks::Miner, Ranks::Miner,
    Ranks::Miner, Ranks::Miner, Ranks::Miner, Ranks::Sergeant, Ranks::Sergeant, Ranks::Sergeant, Ranks::Sergeant,
    Ranks::Sergeant, Ranks::Sergeant,
    Ranks::Lieutenant, Ranks::Lieutenant, Ranks::Captain, Ranks::Captain, Ranks::Captain, Ranks::Captain, Ranks::Major,
    Ranks::Major, Ranks::Major, Ranks::Colonel,
    Ranks::Colonel, Ranks::General, Ranks::Marshal,
    Ranks::Bomb, Ranks::Bomb, Ranks::Bomb, Ranks::Bomb, Ranks::Bomb, Ranks::Bomb
};

vector players = {Players::Red, Players::Blue};

GameLogic::GameLogic() {
    ui = new UI(this);
}

GameLogic::~GameLogic() {
    delete ui;
}

void GameLogic::run() {
    initializeBoard();
    ui->run(ranks, players);
}

void GameLogic::initializeBoard() {
    fields.resize(10);
    for (int i = 0; i < 10; ++i) {
        fields[i].resize(10);
        for (int j = 0; j < 10; ++j) {
            fields[i][j] = std::make_shared<Field>(i * 10 + j); // Assign shared_ptr to each Field
        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << fields[i][j]->getId() << " "; // Assign shared_ptr to each Field
        }
        cout << "\n";
    }
}

void GameLogic::printBoard() {
    for (size_t row = 0; row < fields.size(); ++row) {
        for (size_t col = 0; col < fields[row].size(); ++col) {
            if (fields[row][col]->getUnit()) {
                fields[row][col]->printField();
            } else {
                cout << "[Empty]";
            }
            cout << " ";
        }
        cout << endl;
    }
}

void GameLogic::copyArmyToBoard(vector<vector<SDL_UnitRect *> > rects) {
    cout << "In game logic: \n";
    for (size_t row = 0; row < rects.size(); ++row) {
        for (size_t col = 0; col < rects[row].size(); ++col) {
            if (rects[row][col]) {
                cout << toString(rects[row][col]->player) + toString(rects[row][col]->rank);
            } else {
                cout << "[Empty]";
            }
            cout << " ";
        }
        cout << endl;
    }
    for (size_t row = 0; row < rects.size(); ++row) {
        Players players = rects[0][0]->player;
        for (size_t col = 0; col < rects[row].size(); ++col) {
            Unit *unit = nullptr;
            switch (rects[row][col]->rank) {
                case Ranks::Bomb: {
                    unit = new Bomb(players);
                } break;
                case Ranks::Flag: {
                    unit = new Flag(players);
                } break;
                case Ranks::Marshal: {
                    unit = new Marshal(players);
                } break;
                case Ranks::Miner: {
                    unit = new Miner(players);
                } break;
                case Ranks::Scout: {
                    unit = new Scout(players);
                } break;
                case Ranks::Spy: {
                    unit = new Spy(players);
                } break;
                case Ranks::Sergeant: {
                    unit = new NonSpecialUnit(Ranks::Sergeant, players);
                } break;
                case Ranks::Colonel: {
                    unit = new NonSpecialUnit(Ranks::Colonel, players);
                } break;
                case Ranks::Captain: {
                    unit = new NonSpecialUnit(Ranks::Captain, players);
                } break;
                case Ranks::Lieutenant: {
                    unit = new NonSpecialUnit(Ranks::Lieutenant, players);
                } break;
                case Ranks::Major: {
                    unit = new NonSpecialUnit(Ranks::Major, players);
                } break;
                case Ranks::General: {
                    unit = new NonSpecialUnit(Ranks::General, players);
                }
            }
            if (rects[0][0]->player == Players::Red) {
                fields[row + 6][col]->setUnit(unit);
            } else {
                fields[9 - row][9 - col]->setUnit(unit);
            }
        }
    }
    printBoard();
}
