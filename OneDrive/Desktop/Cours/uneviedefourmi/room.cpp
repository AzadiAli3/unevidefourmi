#include "room.hpp"

Room::Room(const std::string& name, int size) : name(name), size(size) {}

std::string Room::getName() const {
    return name;
}

void Room::addAdjacent(Room* room) {
    adjacents.push_back(room);
}

const std::vector<Room*>& Room::getAdjacents() const {
    return adjacents;
}
