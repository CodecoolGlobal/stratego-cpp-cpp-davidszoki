#include "UI.h"
#include <iostream>
#include <SDL_image.h>
#include <filesystem>
#include "UI.h"
#include "SDL_UnitRect.h"
#include "Texture.h"

using namespace std;

static auto path = (filesystem::current_path().parent_path() /= "Resources\\").u8string();

SDL_Rect battlefieldRect;
SDL_Rect quitButtonRect;
SDL_Rect playButtonRect;
SDL_Rect restartButtonRect;
SDL_Rect nextButtonRect;
SDL_Rect logoRect;
vector<SDL_UnitRect> unitRects;

UI::~UI() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

bool UI::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return false;
    }
    if (!createWindow()) return false;
    if (!createRenderer()) return false;
    if (!initSDLImage()) return false;
    return true;
}

Texture UI::loadTexture(const string &filename) {
    SDL_Texture *imgTexture = IMG_LoadTexture(renderer, filename.c_str());
    if (nullptr == imgTexture) {
        printf("File not found: %s SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
    }

    return Texture(imgTexture);
}

void UI::getWindowSize(int &width, int &height) {
    SDL_GetWindowSize(window, &width, &height);
}

bool UI::createWindow() {
    window = SDL_CreateWindow("Stratego", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1220, 820, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

bool UI::createRenderer() {
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

bool UI::initSDLImage() {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    return true;
}

void UI::run(vector<string> ranks, vector<string> players) {
    pair startQuit = {false, false};
    init();

    while (!startQuit.second) {
        handleStartQuitEvent(startQuit.first, startQuit.second);
        if (!startQuit.first) {
            renderStart();
        } else {
            renderBattleStart(ranks, players, startQuit.second);
        }
    }
}

void UI::renderBattleStart(vector<string> ranks, vector<string> players, bool &quit) {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 53, 24, 6, 0);

    renderBattlefield();
    renderStartUnits(ranks, players);
    handleUnitStartPlace(quit);
    SDL_RenderPresent(renderer);
}

void UI::renderBattlefield() {
    Texture battlefieldImg = loadTexture(path + "Battlefield.bmp");
    Texture logoImg = loadTexture(path + "StrategoLogo.png");
    Texture restartImg = loadTexture(path + "RestartButton.png");
    Texture nextImg = loadTexture(path + "NextButton.png");

    renderTexture(battlefieldImg, battlefieldRect, 800, 800, 10, 10);
    renderTexture(logoImg, logoRect, 250, 80, 820, 5);
    renderTexture(restartImg, restartButtonRect, 150, 80, 820, 90);
    renderTexture(nextImg, nextButtonRect, 150, 80, 980, 90);
}

void UI::renderStart() {
    SDL_RenderClear(renderer);

    Texture strategoCover = loadTexture(path + "StrategoCover.png");
    SDL_Rect strategoRect;
    renderTexture(strategoCover, strategoRect, 1220, 820, 0, 0);

    Texture playButton = loadTexture(path + "PlayButton.png");
    renderTexture(playButton, playButtonRect, 200, 80, 530, 360);

    Texture quitButton = loadTexture(path + "QuitButton.png");
    renderTexture(quitButton, quitButtonRect, 200, 80, 530, 470);
}

void UI::renderStartUnits(vector<string> ranks, vector<string> players) {
    int xPos = 820;
    int yPos = 180;

    int numUnits = ranks.size() * players.size();
    unitRects.resize(numUnits);

    int i = 0; // Unit counter

    for (const auto &player: players) {
        for (const auto &rank: ranks) {
            //Texture unitImage = loadTexture(path + "Units\\" + player + rank + ".bmp"); // Assuming file format

            SDL_UnitRect rect(rank, player);
            rect.h = 70;
            rect.w = 70;
            rect.x = xPos;
            rect.y = yPos;

            unitRects[i] = rect;

            //unitImage.render(renderer, &rect);

            xPos += 80;

            if ((i + 1) % 5 == 0) {
                xPos = 820;
                yPos += 80;
            }

            i++;
        }
    }
}

void UI::renderTexture(Texture &texture, SDL_Rect &rect, int width, int height, int x, int y) {
    rect.h = height;
    rect.w = width;
    rect.x = x;
    rect.y = y;
    texture.render(renderer, &rect);
}

bool isMouseInsideRect(int mouseX, int mouseY, SDL_Rect &rect) {
    return (mouseX > rect.x &&
            mouseX < rect.x + rect.w &&
            mouseY > rect.y &&
            mouseY < rect.y + rect.h);
}

void UI::handleStartQuitEvent(bool &start, bool &quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
            break;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;

            if (isMouseInsideRect(mouseX, mouseY, quitButtonRect)) {
                quit = true;
            } else if (isMouseInsideRect(mouseX, mouseY, playButtonRect)) {
                started = true;
            }
        }
    }
    return quit;
                start = true;
            }
        }
    }
}
}
