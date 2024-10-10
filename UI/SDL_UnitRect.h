#pragma once
#include <SDL_rect.h>
#include <string>
#include <utility>
#include "../GameLogic/Units/Enum.h"

class SDL_UnitRect : public SDL_Rect {

public:
    SDL_UnitRect() = default; // Default constructor
    SDL_UnitRect(Ranks rank, Players player) : SDL_Rect(), rank(rank), player(player) {
    }
    Ranks getRank() const {
        return rank;
    }

    Players getPlayer() {
        return player;
    }

    Ranks rank;
    Players player;
};
