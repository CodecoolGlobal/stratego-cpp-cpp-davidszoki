#include "UI.h"
#include <iostream>
#include <SDL_image.h>
#include "Texture.h"

using namespace std;

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

void UI::renderBattlefield(string path) {
    Texture battlefieldImg = loadTexture(path + "Battlefield.bmp");
    SDL_Rect battlefieldRect;

    Texture logoImg = loadTexture(path + "StrategoLogo.png");
    SDL_Rect logoRect;

    Texture restartImg = loadTexture(path + "RestartButton.png");
    SDL_Rect restartRect;

    Texture nextImg = loadTexture(path + "NextButton.png");
    SDL_Rect nextRect;

    renderTexture(battlefieldImg, battlefieldRect, 800, 800, 10, 10);
    renderTexture(logoImg, logoRect, 250, 80, 820, 5);
    renderTexture(restartImg, restartRect, 150,80,820,90);
    renderTexture(nextImg, nextRect, 150,80,980,90);
}

void UI::renderStart(std::string path) {
    // Load and render the Stratego cover
    Texture strategoCover = loadTexture(path + "StrategoCover.png");
    SDL_Rect strategoRect;
    renderTexture(strategoCover, strategoRect, 1220, 820, 0, 0);

    // Load and render the Play button
    Texture playButton = loadTexture(path + "PlayButton.png");
    SDL_Rect playButtonRect;
    renderTexture(playButton, playButtonRect, 200, 80, 510, 360);

    // Load and render the Quit button
    Texture quitButton = loadTexture(path + "QuitButton.png");
    SDL_Rect quitButtonRect;
    renderTexture(quitButton, quitButtonRect, 200, 80, 510, 470);
}

void UI::renderStartUnits(string path, vector<string> ranks, vector<string> players) {
    vector<SDL_Rect> unitRects;
    int xPos = 820;
    int yPos = 180;

    // Define the number of units (ranks.size() * players.size())
    int numUnits = ranks.size() * players.size();
    unitRects.resize(numUnits); // Resize the vector to the number of units

    int i = 0; // Unit counter

    // Loop through all combinations of ranks and players
    for (const auto &player: players) {
        for (const auto &rank: ranks) {
            // Load the texture for the current unit
            Texture unitImage = loadTexture(path + "Units\\" + player + rank + ".bmp"); // Assuming file format

            // Set up the SDL_Rect for the current unit
            SDL_Rect rect;
            rect.h = 70;
            rect.w = 70;
            rect.x = xPos;
            rect.y = yPos;

            // Save the current rect to the rects vector
            unitRects[i] = rect;

            // Render the current unit immediately after loading the texture
            unitImage.render(renderer, &rect);

            // Update position for the next unit
            xPos += 80;

            // Move to the next row after every 5 units
            if ((i + 1) % 5 == 0) {
                xPos = 820;
                yPos += 80;
            }

            i++; // Increment the unit counter
        }
    }
}

void UI::renderTexture(Texture &texture, SDL_Rect &rect, int width, int height, int x, int y) {
    rect.h = height; // Set height
    rect.w = width; // Set width
    rect.x = x; // Set x position
    rect.y = y; // Set y position
    texture.render(renderer, &rect); // Render the texture
}

bool UI::handleEvent() {
    bool quit = false;
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
            break;
        }
    }
    return quit;
}
