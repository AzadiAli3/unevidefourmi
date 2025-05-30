// room.hpp
#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>

class Room {
private:
    std::string name;
    int size;  // Tu peux l'utiliser ou l’ignorer selon ton projet
    std::vector<Room*> adjacents;  // Salles reliées

public:
    Room(const std::string& name, int size);
    
    std::string getName() const;
    
    void addAdjacent(Room* room);
    
    const std::vector<Room*>& getAdjacents() const;
};

#endif
