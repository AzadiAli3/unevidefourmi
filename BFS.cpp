#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Fourmiliere {
private:
    unordered_map<string, vector<string>> graphe;

public:
    void ajouter_chemin(const string& depart, const string& arrivee) {
        graphe[depart].push_back(arrivee);
    }

    void bfs(const string& depart) {
        queue<string> queue;
        unordered_map<string, bool> visite;

        queue.push(depart);
        visite[depart] = true;

        while (!queue.empty()) {
            string noeud = queue.front();
            queue.pop();
            cout << "Exploration : " << noeud << endl;

            for (const string& voisin : graphe[noeud]) {
                if (!visite[voisin]) {
                    queue.push(voisin);
                    visite[voisin] = true;
                }
            }
        }
    }
};

int main() {
    Fourmiliere fourmiliere;

    fourmiliere.ajouter_chemin("Entrée", "Salle 1");
    fourmiliere.ajouter_chemin("Salle 1", "Salle 2");
    fourmiliere.ajouter_chemin("Salle 2", "Sortie");

    cout << "Début de l'exploration BFS depuis l'entrée de la fourmilière..." << endl;
    fourmiliere.bfs("Entrée");

    return 0;
}
