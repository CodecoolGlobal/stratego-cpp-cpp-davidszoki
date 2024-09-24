#pragma once

#include <SDL.h>
#include <string>
#include "Texture.h"

class UI {
public:
    UI() : window(nullptr), renderer(nullptr) {}
    ~UI();

    bool init();
    Texture loadTexture(const std::string& filename);
    // just to check SDL's bitmap loader
    Texture loadBMP(const std::string& filename);
    void getWindowSize(int& width, int& height);
    SDL_Renderer* getRenderer(){return renderer;}
    bool handleEvent();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool createWindow();
    bool createRenderer();
    bool initSDLImage();
};
