#ifndef UNIT_H
#define UNIT_H

//Move to Game logic
enum Ranks { Flag, Spy, Scout, Miner, Sergeant, Lieutenant, Captain, Major, Colonel, General, Marshal, Bomb };

enum Players { Red, Blue, none };

//End in here

class Position {
    int x;
    int y;

public:
    Position(int x, int y) : x(x), y(y) {
    }
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void printPosition() const;
};

class Unit {
    Ranks rank;
    Players player;
    Position position;

public:
    Unit(Ranks rank, Players player, Position position);

    Players getPlayer() const { return player; }
    Position getPosition() const {return position;}
    void setPLayer(Players newPlayer) { player = newPlayer; }
    void setPosition(const Position &newPosition) { position = newPosition; }
};

#endif
