#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "Texture.h"

class UI {
public:
    UI() : window(nullptr), renderer(nullptr) {
    }

    ~UI();

    bool init();

    Texture loadTexture(const std::string &filename);

    void getWindowSize(int &width, int &height);

    SDL_Renderer *getRenderer() { return renderer; }

    void renderStart(std::string path);

    void renderBattlefield(std::string path);

    void renderStartUnits(std::string path, std::vector<std::string> ranks,
                          std::vector<std::string> players);

    void renderTexture(Texture &texture, SDL_Rect &rect, int width, int height, int x, int y);

    bool handleEvent(bool& started);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool createWindow();

    bool createRenderer();

    bool initSDLImage();
};
