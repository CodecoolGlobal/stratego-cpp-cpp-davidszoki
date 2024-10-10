#pragma once
#include <memory>
#include "Unit.h"

class Field {
    std::unique_ptr<Unit> unit = nullptr;

public:
    Field() = default;

    void setUnit(std::unique_ptr<Unit> unit);

    std::unique_ptr<Unit> getUnit() {
        return std::move(unit);
    }

    Unit* getUnitPtr() {
        return unit.get();
    }

    void printField() const;
};
