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

    void renderBattlefield(SDL_Rect &rect, std::string path);

    void renderStartUnits(std::vector<SDL_Rect> &rects, std::string path, std::vector<std::string> ranks,
                          std::vector<std::string> players);

    bool handleEvent();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool createWindow();

    bool createRenderer();

    bool initSDLImage();
};
