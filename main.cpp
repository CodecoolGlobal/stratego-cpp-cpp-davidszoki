#include <iostream>
#include <filesystem>
#include <vector>
#include "UI/Texture.h"
#include "UI/UI.h"

using namespace std;

static auto path = (filesystem::current_path().parent_path() /= "Resources\\").u8string();

int main(int, char **) {
    vector<string> ranks = {
        "Flag", "Spy", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Scout", "Miner", "Miner",
        "Miner", "Miner", "Miner", "Sergeant", "Sergeant", "Sergeant", "Sergeant", "Lieutenant", "Lieutenant",
        "Lieutenant", "Lieutenant", "Captain", "Captain", "Captain", "Captain", "Major", "Major", "Major", "Colonel",
        "Colonel", "General", "Marshal",
        "Bomb", "Bomb", "Bomb", "Bomb", "Bomb", "Bomb"
    };

    vector<string> players = {"Red"};

    bool quit = false;
    UI ui;
    ui.init();


    // Main loop
    while (!quit) {
        quit = ui.handleEvent();
        SDL_RenderClear(ui.getRenderer());
        SDL_SetRenderDrawColor(ui.getRenderer(), 53, 24, 6, 0);
        ui.renderBattlefield(path);
        ui.renderStartUnits(path, ranks, players);
        //ui.renderStart(path);

        SDL_RenderPresent(ui.getRenderer());
    }
    return 0;
}
