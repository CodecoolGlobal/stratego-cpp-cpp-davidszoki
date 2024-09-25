#include <iostream>
#include "Unit.h"
using namespace std;

void Position::printPosition() const {
    cout << "X:" << getX() << " Y:" << getY() << endl;
}
