#include <iostream>
#include <filesystem>
#include "UI/Texture.h"
#include "UI/UI.h"
#include "./GameLogic/GameLogic.h"
using namespace std;

int main(int, char **) {

    GameLogic game_logic(Red);
    game_logic.initializedBoard();
    game_logic.printboard();

    // UI ui;
    // ui.init();
    // auto path = filesystem::current_path().parent_path();
    // path /= "Resources";
    // string pathStr = path.u8string();
    // Texture battlefield = ui.loadBMP(pathStr + "/Battlefield.bmp");
    // bool quit = false;
    // // Main loop
    // while (!quit) {
    //     quit = ui.handleEvent();
    //     SDL_RenderClear(ui.getRenderer());
    //     battlefield.render(ui.getRenderer(), nullptr);
    //     SDL_RenderPresent(ui.getRenderer());
    // }
    return 0;
}
