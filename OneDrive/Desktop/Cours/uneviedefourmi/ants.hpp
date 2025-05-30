
#ifndef ANTS_HPP
#define ANTS_HPP

#include "room.hpp"  
#include <string>

class Ant {
private:
    int id;
    Room* position;

public:
    Ant(int id, Room* startPos);

    int getId() const;
    Room* getPosition() const;

    void moveTo(Room* newPos);
};

#endif
