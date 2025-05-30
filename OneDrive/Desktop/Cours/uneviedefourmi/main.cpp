#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>  
#include "ants.hpp"
#include "room.hpp"

std::unordered_map<Room*, Room*> bfs_with_parent(Room* start) {
    std::queue<Room*> q;
    std::unordered_set<Room*> visited;
    std::unordered_map<Room*, Room*> parent;

    q.push(start);
    visited.insert(start);
    parent[start] = nullptr;

    while (!q.empty()) {
        Room* cur = q.front(); q.pop();
        for (Room* nei : cur->getAdjacents()) {
            if (!visited.count(nei)) {
                visited.insert(nei);
                parent[nei] = cur;
                q.push(nei);
            }
        }
    }
    return parent;
}

std::vector<Room*> reconstruct_path(Room* end,
    const std::unordered_map<Room*, Room*>& parent) {
    std::vector<Room*> path;
    for (Room* cur = end; cur != nullptr; cur = parent.at(cur)) {
        path.push_back(cur);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    // 1) Paramètres donnés
    int f = 2;             // nombre de fourmis
    // on crée toutes les salles
    Room* Sv = new Room("Sv", 0);
    Room* S1 = new Room("S1", 0);
    Room* S2 = new Room("S2", 0);
    Room* Sd = new Room("Sd", 0);

    // 2) On connecte selon ta spécification
    Sv->addAdjacent(S1);
    Sv->addAdjacent(S2);
    S1->addAdjacent(Sd);
    S2->addAdjacent(Sd);

    // 3) On lance un BFS depuis Sv
    auto parent = bfs_with_parent(Sv);

    // 4) On reconstruit le chemin jusqu'à Sd
    auto path = reconstruct_path(Sd, parent);

    // 5) On affiche le chemin
    std::cout << "Shortest path from Sv to Sd: ";
    for (Room* r : path) {
        std::cout << r->getName() << " ";
    }
    std::cout << "\n\n";

    // 6) On crée les fourmis et on leur fait suivre ce chemin
    for (int id = 1; id <= f; ++id) {
        Ant ant(id, Sv);
        std::cout << "Ant #" << ant.getId() << " starts in " 
                  << ant.getPosition()->getName() << "\n";
        // saute la première salle (Sv) qui est déjà leur position
        for (size_t i = 1; i < path.size(); ++i) {
            ant.moveTo(path[i]);
        }
        std::cout << "\n";
    }

    // Clean up
    delete Sv;
    delete S1;
    delete S2;
    delete Sd;

    return 0;
}
