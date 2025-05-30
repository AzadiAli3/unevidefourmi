#include "ants.hpp"
#include <iostream>

Ant::Ant(int id, Room* startPos) : id(id), position(startPos) {}

int Ant::getId() const {
    return id;
}

Room* Ant::getPosition() const {
    return position;
}

void Ant::moveTo(Room* newPos) {
    position = newPos;
    std::cout << "Ant " << id << " moves to " << position->getName() << std::endl;
}
