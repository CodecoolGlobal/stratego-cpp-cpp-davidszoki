#include <iostream>
#include <SDL_image.h>
#include <filesystem>
#include "UI.h"
#include "SDL_UnitRect.h"
#include "Texture.h"
#include "../GameLogic/GameLogic.h"

class Unit;
using namespace std;

static auto path = (filesystem::current_path().parent_path() /= "Resources\\").u8string();

SDL_Rect battlefieldRect;
SDL_Rect quitButtonRect;
SDL_Rect playButtonRect;
SDL_Rect restartButtonRect;
SDL_Rect nextButtonRect;
SDL_Rect logoRect;
vector<SDL_UnitRect> unitRects;
vector<vector<SDL_UnitRect*>> units = vector(4, vector<SDL_UnitRect*>(10));

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

void UI::run(vector<Ranks> ranks, vector<Players> players) {
    pair startQuit = {false, false};
    init();

    while (!startQuit.second) {
        bool battleFieldHasChanged;
        handleStartQuitEvent(startQuit.first, startQuit.second);
        if (!startQuit.first) {
            renderStart();
        } else {
            if(!gameLogic->inGame) {
                renderBattleStart(ranks, players, startQuit.second);
            }
            SDL_RenderClear(renderer);
            renderBattlefield();
            renderBoard(gameLogic->getBoardData());
            SDL_RenderPresent(renderer);
            startQuit.second = false;
        }
    }
}

void UI::renderBattleStart(vector<Ranks> ranks, vector<Players> players, bool &quit) {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 53, 24, 6, 0);

    renderBattlefield();
    renderStartUnits(ranks, Players::Red);
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

    SDL_RenderPresent(renderer);
}

/*void UI::renderUnit(SDL_UnitRect &unitRect) {
    Texture unitImage = loadTexture(path + "Units\\" + toString(unitRect.player) + toString(unitRect.rank) + ".bmp");
    unitImage.render(renderer, &unitRect);
}*/

void UI::renderUnit(SDL_UnitRect *unitRect) {
    if (unitRect->player == gameLogic->getActualPLayer()) {
        Texture unitImage = loadTexture(path + "Units\\" + toString(unitRect->player) + toString(unitRect->rank) + ".bmp");
        unitImage.render(renderer, unitRect);
    } else {
        Texture unitImage = loadTexture(path + "Units\\" + toString(unitRect->player) + "Back.bmp");
        unitImage.render(renderer, unitRect);
    }
}

void UI::renderUnits() {
    for (auto unitRect: unitRects) {
        Texture unitImage = loadTexture(path + "Units\\" + toString(unitRect.player) + toString(unitRect.rank) + ".bmp");
        unitImage.render(renderer, &unitRect);
    }
}

void UI::renderStartUnits(vector<Ranks> ranks, Players player) {
    gameLogic->setActualPLayer(player);
    int xPos = 820;
    int yPos = 180;

    int numUnits = ranks.size();
    unitRects.resize(numUnits);

    int i = 0; // Unit counter

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

    /*for (SDL_UnitRect rect : unitRects) {
        cout << rect.getRank() << "\n";
    }*/
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
                start = true;
            }
        }
    }
}

void UI::handleUnitStartPlace(bool &quit) {
    SDL_Event e;
    bool isDragging = false;
    SDL_UnitRect *selectedRect = nullptr; // Pointer to the currently dragged rectangle
    SDL_Point originalPosition; // Original position of the rectangle
    int originX = -1;
    int originY = -1;
    gameLogic->inGame = false;

    while (!quit) {
        // Main event loop for the placement phase
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = e.button.x;
                int mouseY = e.button.y;

                // Check if a rectangle is selected for dragging
                for (auto &unitRect: unitRects) {
                    if (isMouseInsideRect(mouseX, mouseY, unitRect)) {
                        isDragging = true;
                        selectedRect = &unitRect;
                        originalPosition = {unitRect.x, unitRect.y}; // Store original position
                        std::cout << "Selected unit for dragging at (" << unitRect.x << ", " << unitRect.y << ")" <<
                                std::endl;
                        if(mouseY > 480 && mouseX > 0 && mouseX < 800) {
                            originY = (mouseY - 480) / 80;
                            originX = mouseX / 80;
                            units[originY][originX] = nullptr;
                        }
                        break;
                    }
                }
                if(isMouseInsideRect(mouseX, mouseY, nextButtonRect)) {
                    bool isFull = true;
                    for (vector<SDL_UnitRect*> rects : units) {
                        for(SDL_UnitRect* rect : rects) {
                            if(rect == nullptr) {
                                isFull = false;
                            }
                        }
                    }
                    if(isFull) {
                        gameLogic->copyArmyToBoard(units);
                        //clear red units
                        unitRects.clear();
                        for (vector<SDL_UnitRect*>& rects : units) {
                            for(SDL_UnitRect*& rect : rects) {
                               rect = nullptr;
                            }
                        }
                        if(gameLogic->getActualPLayer() == Players::Red) {
                            gameLogic->setActualPLayer(Players::Blue);
                            renderStartUnits(gameLogic->getRanks(), Players::Blue);
                        } else {
                            gameLogic->setActualPLayer(Players::Red);
                            SDL_RenderClear(renderer);
                            renderBoard(gameLogic->getBoardData());
                            gameLogic->inGame = true;
                            quit = true;
                        }
                    }
                }
            } else if (e.type == SDL_MOUSEMOTION && isDragging && selectedRect != nullptr) {
                // Update the position of the selected rectangle to follow the mouse
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;

                selectedRect->x = mouseX - selectedRect->w / 2;
                selectedRect->y = mouseY - selectedRect->h / 2;
                //std::cout << "Dragging unit to (" << selectedRect->x << ", " << selectedRect->y << ")" << std::endl;
            } else if (e.type == SDL_MOUSEBUTTONUP && isDragging) {
                int mouseX = e.button.x;
                int mouseY = e.button.y;
                // Check if the selected rectangle is within the battlefield and not overlapping with other units
                if (selectedRect != nullptr) {
                    int snapX = mouseX / (battlefieldRect.w / 10) * (battlefieldRect.w / 10) + 16;
                    //int snapX = selectedRect->x - (selectedRect->x % 80) +16;
                    int snapY = mouseY / (battlefieldRect.h / 10) * (battlefieldRect.h / 10) + 16;
                    //int snapY = selectedRect->y - (selectedRect->y % 80) +16;

                    bool isOutOfBounds = (selectedRect->x < 10 || selectedRect->x + selectedRect->w / 2 >
                                          battlefieldRect.w ||
                                          selectedRect->y < 490 || selectedRect->y + selectedRect->h / 2 >
                                          battlefieldRect.h);

                    if (isOutOfBounds) {
                        std::cout << "Out of bounds: Attempted position (" << snapX << ", " << snapY << ")" <<
                                std::endl;
                    } else {
                        std::cout << "In bounds: Attempted position (" << snapX << ", " << snapY << ")" << std::endl;
                    }

                    // Check for overlap with other unit rectangles
                    /*bool isOverlapping = false;
                    for (const auto &unitRect: unitRects) {
                        if (&unitRect != selectedRect && SDL_HasIntersection(selectedRect, &unitRect)) {
                            isOverlapping = true;
                            std::cout << "Overlap detected with unit at (" << unitRect.x << ", " << unitRect.y << ")" <<
                                    std::endl;
                            break;
                        }
                    }*/

                    if (!isOutOfBounds) {
                        int flooredY = static_cast<int>(std::floor((snapY - 480) / 80));
                        int flooredX = static_cast<int>(std::floor(snapX / 80));
                        cout << units[1][1];
                        if(units[(snapY - 480) / 80][snapX / 80] == nullptr) {
                            // No issues, snapping to calculated position
                            units[flooredY][flooredX] = selectedRect;
                            selectedRect->x = snapX;
                            selectedRect->y = snapY;
                            std::cout << "Unit snapped to (" << snapX << ", " << snapY << ")" << std::endl;
                            cout << "X: " << snapX / 80 << "Y: " << snapY / 80 << " Player: " << selectedRect->player <<
                                    " Unit: " << selectedRect->rank << endl;
                            printRectVector();


                        } else {
                            // Snap back to original position if out of bounds or overlapping
                            selectedRect->x = originalPosition.x;
                            selectedRect->y = originalPosition.y;
                            if(originY != -1) {
                                units[originY][originX] = selectedRect;
                            }
                            std::cout << "Unit returned to original position (" << originalPosition.x << ", " <<
                                    originalPosition.y << ")" << std::endl;
                        }
                    } else {
                        // Snap back to original position if out of bounds or overlapping
                        selectedRect->x = originalPosition.x;
                        selectedRect->y = originalPosition.y;
                        if(originY != -1) {
                            units[originY][originX] = selectedRect;
                        }
                        std::cout << "Unit returned to original position (" << originalPosition.x << ", " <<
                                originalPosition.y << ")" << std::endl;
                    }
                }
                isDragging = false;
                selectedRect = nullptr;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 53, 24, 6, 0); // Background color
        SDL_RenderClear(renderer);
        renderBattlefield();
        renderUnits();


        // Draw the selected rectangle last to ensure it’s on top
        if (selectedRect != nullptr) {
            // Load the image for the selected rectangle
            renderUnit(selectedRect);

            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow outline for the selected rectangle
            for (int offset = 0; offset < 4; offset++) {
                // Adjust "4" for thickness
                SDL_Rect highlightRect = {
                    selectedRect->x - offset,
                    selectedRect->y - offset,
                    selectedRect->w + 2 * offset,
                    selectedRect->h + 2 * offset
                };
                SDL_RenderDrawRect(renderer, &highlightRect);
            }
        }
        // Present the updated renderer
        SDL_RenderPresent(renderer);

        // Delay for smoother rendering (adjust as necessary)
        SDL_Delay(16); // Roughly 60 frames per second
    }
}

void UI::printRectVector() {
    for (size_t row = 0; row < units.size(); ++row) {
        for (size_t col = 0; col < units[row].size(); ++col) {
            if(units[row][col]) {
                cout << toString(units[row][col]->player) + toString(units[row][col]->rank);
            } else {
                cout << "[Empty]";
            }
            cout << " ";
        }
        cout << endl;
    }

}

void UI::renderBoard(vector<vector<SDL_UnitRect*>> unitRects) {
    for(size_t row = 0; row < unitRects.size(); row++) {
        for (size_t column = 0; column < unitRects[row].size(); column++) {
            if(unitRects[row][column] != nullptr) {
                renderUnit(unitRects[row][column]);
                cout << unitRects[row][column]->getRank() << unitRects[row][column]->getPlayer();
            }
            else cout << "empty";
        }
        cout << "\n";
    }
}


