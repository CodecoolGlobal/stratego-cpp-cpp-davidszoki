#include "Field.h"
#include <iostream>
using namespace std;

void Position::printPosition() const {
    cout << "X:" << getX() << " Y:" << getY() << endl;
}