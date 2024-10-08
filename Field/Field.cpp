#include "Field.h"
#include <iostream>

#include "../Units/ArmyUnit.h"
using namespace std;

void Position::printPosition() const {
    cout << "X:" << getX() << " Y:" << getY() << endl;
}
void Field::printField() const {
    std::cout << "Unit: ";
    auto* armyUnit = dynamic_cast<ArmyUnit*>(unit);
    armyUnit->print();
    std::cout << " at ";
    position.printPosition();
}

bool Field::setUnit(Unit* unit) {
    this->unit = unit;
    return true;
}
