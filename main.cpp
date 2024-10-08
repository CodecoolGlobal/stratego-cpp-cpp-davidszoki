#include <iostream>
#include <vector>
#include "UI/Texture.h"
#include "UI/UI.h"

using namespace std;

int main(int, char **) {
    vector<string> ranks = {
        "Flag", "Spy", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Miner", "Miner",
        "Miner", "Miner", "Miner", "Sergeant", "Sergeant", "Sergeant", "Sergeant", "Lieutenant", "Lieutenant",
        "Lieutenant", "Lieutenant", "Captain", "Captain", "Captain", "Captain", "Major", "Major", "Major", "Colonel",
        "Colonel", "General", "Marshal",
        "Bomb", "Bomb", "Bomb", "Bomb", "Bomb", "Bomb"
    };

    vector<string> players = {"Red"};

    UI ui;
    ui.run(ranks, players);
    return 0;
}
