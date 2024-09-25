#include <iostream>
#include <filesystem>
#include "UI/Texture.h"
#include "UI/UI.h"
#include "Units/Marshal.h"
using namespace std;

int main(int, char **) {
    Position position = Position(10, 12);

    Unit marshal(Ranks::Colonel,none,position);

    marshal.setPLayer(Red);

    cout << "Player: " << marshal.getPlayer() << endl;

    marshal.getPosition().printPosition();

    auto secondMarshal = Marshal(Blue, Position(0, 0));

    secondMarshal.setPosition(Position(8, 8));

    secondMarshal.getPosition().printPosition();

    cout << "Player: " << secondMarshal.getPlayer() << endl;

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
