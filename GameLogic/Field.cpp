#include "Field.h"
#include <iostream>
#include "./Units/ArmyUnit.h"
using namespace std;

void Position::printPosition() const {
    cout << "X:" << getX() << " Y:" << getY() << endl;
}
void Field::printField() const {
    auto* armyUnit = dynamic_cast<ArmyUnit*>(unit);
    cout << "[";
    armyUnit->print();
    cout << "]";
}

bool Field::setUnit(Unit* unit) {
    this->unit = unit;
    return true;
}

int Field::getId() {
    return this->id;
}
