#pragma once
#include <iostream>

enum class Ranks { Flag, Spy, Scout, Miner, Sergeant, Lieutenant, Captain, Major, Colonel, General, Marshal, Bomb };
enum class Players { Red, Blue, none };

inline std::ostream& operator<<(std::ostream& os, const Ranks& rank) {
    switch(rank) {
        case Ranks::Flag: os << "Flag"; break;
        case Ranks::Spy: os << "Spy"; break;
        case Ranks::Scout: os << "Scout"; break;
        case Ranks::Miner: os << "Miner"; break;
        case Ranks::Sergeant: os << "Sergeant"; break;
        case Ranks::Lieutenant: os << "Lieutenant"; break;
        case Ranks::Captain: os << "Captain"; break;
        case Ranks::Major: os << "Major"; break;
        case Ranks::Colonel: os << "Colonel"; break;
        case Ranks::General: os << "General"; break;
        case Ranks::Marshal: os << "Marshal"; break;
        case Ranks::Bomb: os << "Bomb"; break;
        default: os.setstate(std::ios_base::failbit);
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Players& player) {
    switch(player) {
        case Players::Red: os << "Red"; break;
        case Players::Blue: os << "Blue"; break;
        default: os.setstate(std::ios_base::failbit);
    }
    return os;
}
