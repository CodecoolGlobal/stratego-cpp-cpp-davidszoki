#include <iostream>
#include <vector>

#include "GameLogic/GameLogic.h"
#include "UI/Texture.h"
#include "UI/UI.h"


using namespace std;

int main(int, char **) {
    vector<string> players = {"Red", "Blue"};
    GameLogic* gameLogic = new GameLogic();
    (*gameLogic).run();
    return 0;
}
