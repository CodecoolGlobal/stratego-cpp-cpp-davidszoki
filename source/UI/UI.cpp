#include <iostream>
#include <SDL_image.h>
#include <filesystem>
#include <functional>
#include <UI.h>
#include <SDL_UnitRect.h>
#include <Texture.h>
#include <unordered_map>

using namespace std;

static auto path = (filesystem::current_path().parent_path() / ".." / "resources/").u8string();

SDL_Rect battlefieldRect = {10, 10, 800, 800};
SDL_Rect quitButtonRect;
SDL_Rect playButtonRect;
SDL_Rect restartButtonRect;
SDL_Rect nextButtonRect;
SDL_Rect logoRect;
vector<SDL_UnitRect> unitPlacerRects;
vector<SDL_Rect> unitRects;
bool isDragging = false;
SDL_Point originalPosition;
SDL_UnitRect *selectedRect = nullptr;


UI::UI(IGame &game) : window(nullptr), renderer(nullptr), game(game) {
}

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
    window = SDL_CreateWindow("Stratego", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1220, 820,
                              SDL_WINDOW_SHOWN);
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

void UI::renderUnitPlacement(const Players &currentPlayer, const vector<Ranks> &playerUnits) {
    SDL_SetRenderDrawColor(renderer, 53, 24, 6, 0);
    SDL_RenderClear(renderer);
    drawPlayerUI();

    if (!unitPlacerRects.empty() && unitPlacerRects[0].player == currentPlayer)
        drawStartUnits();
    else
        drawStartUnits(playerUnits, currentPlayer);

    if (currentPlayer == Players::Blue)
        drawBattlefield(currentPlayer);

    drawMove(currentPlayer);

    SDL_RenderPresent(renderer);
}

void UI::drawBattlefield(const Players &currentPlayer) {
    auto battleField = game.getBattlefield();
    for (int i = 0; i < battleField.size(); i++) {
        for (int j = 0; j < battleField[i].size(); j++) {
            if (battleField[i][j]->getUnit() != nullptr && battleField[i][j]->getUnit()->getRank() != Ranks::None)
                if (battleField[i][j]->getUnit()->getPlayer() == currentPlayer)
                    drawUnit(battleField[i][j]->getUnit()->getRank(), battleField[i][j]->getUnit()->getPlayer(), j, i);
                else
                    drawUnit(Ranks::None, battleField[i][j]->getUnit()->getPlayer(), j, i);
        }
    }
}

void UI::renderBattlefield(const Players &currentPlayer) {
    SDL_SetRenderDrawColor(renderer, 53, 24, 6, 0); // Background color
    SDL_RenderClear(renderer);

    drawPlayerUI();
    drawBattlefield(currentPlayer);
    drawMove(currentPlayer);

    SDL_RenderPresent(renderer);
}

void UI::drawPlayerUI() {
    Texture battlefieldImg = loadTexture(path + "Battlefield.bmp");
    drawTexture(battlefieldImg, battlefieldRect, 800, 800, 10, 10);

    Texture logoImg = loadTexture(path + "StrategoLogo.png");
    drawTexture(logoImg, logoRect, 250, 80, 820, 5);

    Texture restartImg = loadTexture(path + "RestartButton.png");
    drawTexture(restartImg, restartButtonRect, 150, 80, 820, 90);

    if (!game.getUnitPlacement()) {
        if (game.getCurrentPlayer() == Players::Red) {
            Texture nextImg = loadTexture(path + "NextButton.png");
            drawTexture(nextImg, nextButtonRect, 150, 80, 980, 90);
        } else {
            Texture playImg = loadTexture(path + "PlayButton.png");
            drawTexture(playImg, playButtonRect, 150, 80, 980, 90);
        }
    }
}

void UI::renderMenuUI() {
    SDL_RenderClear(renderer);

    Texture strategoCover = loadTexture(path + "StrategoCover.png");
    SDL_Rect strategoRect;
    drawTexture(strategoCover, strategoRect, 1220, 820, 0, 0);

    Texture playButton = loadTexture(path + "PlayButton.png");
    drawTexture(playButton, playButtonRect, 200, 80, 530, 360);

    Texture quitButton = loadTexture(path + "QuitButton.png");
    drawTexture(quitButton, quitButtonRect, 200, 80, 530, 470);

    SDL_RenderPresent(renderer);
}

void UI::drawUnit(const SDL_UnitRect &unitRect) {
    Texture unitImage = loadTexture(path + "Units/" + toString(unitRect.player) + toString(unitRect.rank) + ".bmp");
    unitImage.render(renderer, &unitRect);
}

void UI::drawUnit(const SDL_UnitRect *unitRect) {
    Texture unitImage = loadTexture(path + "Units/" + toString(unitRect->player) + toString(unitRect->rank) + ".bmp");
    unitImage.render(renderer, unitRect);
}

void UI::drawStartUnits() {
    for (auto &unitRect: unitPlacerRects) {
        Texture unitImage = loadTexture(
            path + "Units/" + toString(unitRect.player) + toString(unitRect.rank) + ".bmp");
        unitImage.render(renderer, &unitRect);
    }
}

/*void UI::drawUnits() {
    for (auto &field: game.getBattlefield()) {
        for (auto &cell: field) {
            Texture unitImage = loadTexture(
                path + "Units/" + toString(cell->getUnit()->getPlayer()) + toString(cell->getUnit()->getRank()) +
                ".bmp");
            unitImage.render(renderer, &unitRect);
        }
    }
}*/

void UI::drawStartUnits(const vector<Ranks> &playerUnits, const Players &player) {
    int xPos = 820;
    int yPos = 180;

    int numUnits = playerUnits.size();
    unitPlacerRects.resize(numUnits);
    int i = 0; // Unit counter

    for (const auto &rank: playerUnits) {
        Texture unitImage = loadTexture(path + "Units/" + toString(player) + toString(rank) + ".bmp");
        // Assuming file format

        SDL_UnitRect rect(rank, player);
        rect.h = 70;
        rect.w = 70;
        rect.x = xPos;
        rect.y = yPos;

        unitPlacerRects[i] = rect;
        unitImage.render(renderer, &rect);

        xPos += 80;

        if ((i + 1) % 5 == 0) {
            xPos = 820;
            yPos += 80;
        }

        i++;
    }
}

void UI::drawUnit(Ranks rank, Players player, int &x, int &y) {
    Texture unitImage = loadTexture(path + "Units/" + toString(player) + toString(rank) + ".bmp");

    SDL_Rect rect;
    rect.h = 70;
    rect.w = 70;
    rect.x = x * 80 + 16;
    rect.y = y * 80 + 16;

    unitImage.render(renderer, &rect);
}

void UI::drawTexture(Texture &texture, SDL_Rect &rect, int width, int height, int x, int y) {
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

void UI::handleEvents(bool &gameEnded, bool &gameStart, bool &unitPlacement, Players &currentPlayer,
                      const vector<Ranks> &playerUnits) {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            gameEnded = true;
            break;
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            handleMouseDownEvent(e, gameEnded, gameStart, unitPlacement, currentPlayer,
                                 playerUnits, isDragging, originalPosition);
            break;
        }

        if (e.type == SDL_MOUSEMOTION) {
            handleMouseMotionEvent(e, isDragging);
            break;
        }

        if (e.type == SDL_MOUSEBUTTONUP) {
            handleMouseUpEvent(e, originalPosition, currentPlayer);
            break;
        }
    }
}


void UI::handleMouseDownEvent(const SDL_Event &e, bool &gameEnded, bool &gameStart, bool &unitPlacement,
                              Players &currentPlayer, const vector<Ranks> &playerUnits, bool &isDragging,
                              SDL_Point &originalPosition) {
    int mouseX = e.button.x;
    int mouseY = e.button.y;

    if (isMouseInsideRect(mouseX, mouseY, quitButtonRect) && !gameStart) {
        gameEnded = true;
        return;
    }

    if (isMouseInsideRect(mouseX, mouseY, playButtonRect) && !unitPlacement && !gameStart) {
        gameStart = true;
        return;
    }

    if (isMouseInsideRect(mouseX, mouseY, playButtonRect) && !unitPlacement && gameStart && currentPlayer ==
        Players::Blue) {
        game.changePlayer(currentPlayer);
        game.middleMirrorBattlefield();
        unitPlacement = true;
        return;
    }

    if (isMouseInsideRect(mouseX, mouseY, nextButtonRect) && currentPlayer == Players::Red && !unitPlacement) {
        game.changePlayer(currentPlayer);
        return;
    }

    if (isMouseInsideRect(mouseX, mouseY, restartButtonRect)) {
        game.resetGame();
        drawStartUnits(playerUnits, currentPlayer);
        return;
    }

    for (auto &unitRect: unitPlacerRects) {
        if (isMouseInsideRect(mouseX, mouseY, unitRect)) {
            isDragging = true;
            selectedRect = &unitRect;
            originalPosition = {selectedRect->x, selectedRect->y};
            break;
        }
    }
}

void UI::handleMouseMotionEvent(const SDL_Event &e, const bool &isDragging) {
    int mouseX = e.motion.x;
    int mouseY = e.motion.y;

    if (isDragging && selectedRect != nullptr) {
        selectedRect->x = mouseX - selectedRect->w / 2;
        selectedRect->y = mouseY - selectedRect->h / 2;
    }
}

void UI::handleMouseUpEvent(const SDL_Event &e, SDL_Point &originalPosition, const Players &currentPlayer) {
    int mouseX = e.button.x;
    int mouseY = e.button.y;
    int flooredX = 0;
    int flooredY = 0;

    auto snappedPosition = snapToGrid(mouseX, mouseY);

    if (currentPlayer == Players::Blue) {
        flooredX = (snappedPosition.x + 10) / 80;
        flooredY = snappedPosition.y - 490 < 0 ? -1 : (snappedPosition.y + 10) / 80;
    } else {
        flooredX = battlefieldRect.w / 80 - 1 - (snappedPosition.x + 10) / 80;
        flooredY = snappedPosition.y - 490 < 0 ? -1 : battlefieldRect.h / 80 - 1 - (snappedPosition.y + 10) / 80;
    }

    if (selectedRect != nullptr) {
        //cout << game.checkUnitPlaceInBounds({flooredX, flooredY}) << endl;
        if (game.checkMoveInBounds({flooredX, flooredY}) && game.checkTargetFieldEmpty({flooredX, flooredY})) {
            selectedRect->x = snappedPosition.x;
            selectedRect->y = snappedPosition.y;
            auto pos = calculateGridPosition(originalPosition, currentPlayer);
            if (game.checkMoveInBounds({pos.x, pos.y}) && !game.checkTargetFieldEmpty({pos.x, pos.y})) {
                game.removeUnit(pos);
            }
            game.placeUnit({flooredX, flooredY}, selectedRect->player, selectedRect->rank);
        } else {
            selectedRect->x = originalPosition.x;
            selectedRect->y = originalPosition.y;
        }
        isDragging = false;
        selectedRect = nullptr;
        originalPosition = {0, 0};
    }
}

SDL_Point UI::calculateGridPosition(const SDL_Point &position, const Players &currentPlayer) const {
    if (currentPlayer == Players::Blue)
        return {
            (position.x / (battlefieldRect.w / 10) * (battlefieldRect.w / 10) + 16) / 80,
            (position.y / (battlefieldRect.h / 10) * (battlefieldRect.h / 10) + 16) / 80
        };

    return {
        battlefieldRect.w / 80 - 1 - (originalPosition.x + 10) / 80,
        originalPosition.y - 490 < 0 ? -1 : battlefieldRect.h / 80 - 1 - (originalPosition.y + 10) / 80
    };
}

SDL_Point UI::snapToGrid(const int mouseX, const int mouseY) const {
    const int snapX = mouseX / (battlefieldRect.w / game.getGridSize()) * (battlefieldRect.w / game.getGridSize()) + 16;
    const int snapY = mouseY / (battlefieldRect.h / game.getGridSize()) * (battlefieldRect.h / game.getGridSize()) + 16;
    return {snapX, snapY};
}

void UI::drawMove(const Players &currentPlayer) {
    if (isDragging && selectedRect != nullptr) {
        drawUnit(selectedRect);
        drawHighlight(*selectedRect);
    }
}

void UI::drawHighlight(const SDL_Rect &rect, const int thickness) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (int offset = 0; offset < thickness; offset++) {
        SDL_Rect highlightRect = {rect.x - offset, rect.y - offset, rect.w + 2 * offset, rect.h + 2 * offset};
        SDL_RenderDrawRect(renderer, &highlightRect);
    }
}
