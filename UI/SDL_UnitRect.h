#pragma once
#include <SDL_rect.h>
#include <string>
#include <utility>

class SDL_UnitRect : public SDL_Rect {
public:
    SDL_UnitRect() = default; // Default constructor
    SDL_UnitRect(std::string rank, std::string player) : SDL_Rect(), rank(std::move(rank)), player(std::move(player)) {
    }

    std::string rank;
    std::string player;
};
