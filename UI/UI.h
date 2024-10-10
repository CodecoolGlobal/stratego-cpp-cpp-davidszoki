#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "SDL_UnitRect.h"
#include "Texture.h"
#include "../GameLogic/GameLogic.h"

using namespace std;

class GameLogic;

class UI {
public:
    UI(GameLogic* gameLogic) : window(nullptr), renderer(nullptr), gameLogic(gameLogic) {
    };

    ~UI();

    bool init();

    Texture loadTexture(const std::string &filename);

    void getWindowSize(int &width, int &height);

    SDL_Renderer *getRenderer() { return renderer; }

    void run(std::vector<Ranks> ranks, std::vector<Players> players);

    void renderStart();

    void renderUnit(SDL_UnitRect *unitRect);

    void renderUnit(SDL_UnitRect &unitRect);

    void renderUnits();

    void renderBattleStart(std::vector<Ranks> ranks, std::vector<Players> players, bool &quit);

    void renderBattlefield();

    void renderStartUnits(std::vector<Ranks> ranks, Players player);

    void renderTexture(Texture &texture, SDL_Rect &rect, int width, int height, int x, int y);

    void handleStartQuitEvent(bool &start, bool &quit);

    void handleUnitStartPlace(bool &quit);

    void renderBoard(vector<vector<SDL_UnitRect*>> unitRects);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    GameLogic *gameLogic;

    bool createWindow();

    bool createRenderer();

    bool initSDLImage();

    void printRectVector();

};
