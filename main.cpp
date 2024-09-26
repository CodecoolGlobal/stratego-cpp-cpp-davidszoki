#include <iostream>
#include <filesystem>
#include <vector>
#include "UI/Texture.h"
#include "UI/UI.h"

using namespace std;

static auto path = (filesystem::current_path().parent_path() /= "Resources\\").u8string();

int main(int, char **) {
    vector<string> ranks = {
        "Flag", "Spy", "Scout", "Miner", "Sergeant", "Lieutenant", "Captain", "Major", "Colonel", "General", "Marshal",
        "Bomb", "Back"
    };

    vector<string> players = {"Red", "Blue"};

    bool quit = false;
    UI ui;
    ui.init();


    // Main loop
    while (!quit) {
        quit = ui.handleEvent();
        SDL_RenderClear(ui.getRenderer());

        //ui.renderBattlefield(path);
        //ui.renderStartUnits(path, ranks, players);
        ui.renderStart(path);

        SDL_RenderPresent(ui.getRenderer());
    }
    return 0;
}
