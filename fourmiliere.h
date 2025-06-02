#ifndef FOURMILIERE_H
#define FOURMILIERE_H

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <iostream>
#include <algorithm>

class Fourmi
{
public:
    int id;
    std::string current_position;
    std::vector<std::string> path;
    bool reached_destination;

    Fourmi(int ant_id) : id(ant_id), current_position("Sv"), reached_destination(false)
    {
        path.push_back("Sv");
    }

    void move_to(const std::string &station)
    {
        current_position = station;
        path.push_back(station);
        if (station == "Sd")
        {
            reached_destination = true;
        }
    }

    void print_path() const
    {
        std::cout << "Ant " << id << " path: ";
        for (size_t i = 0; i < path.size(); ++i)
        {
            std::cout << path[i];
            if (i < path.size() - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
};

class Fourmiliere
{
protected:
    int total_ants;
    std::vector<Fourmi> ants;
    std::map<std::string, std::vector<std::string>> graph;
    std::map<std::string, int> station_capacity;
    std::map<std::string, int> current_occupancy;

public:
    Fourmiliere(int num_ants) : total_ants(num_ants)
    {
        for (int i = 0; i < num_ants; ++i)
        {
            ants.emplace_back(i + 1);
        }
    }

    virtual ~Fourmiliere() = default;

    void add_connection(const std::string &from, const std::string &to)
    {
        graph[from].push_back(to);
    }

    void set_capacity(const std::string &station, int capacity)
    {
        station_capacity[station] = capacity;
        current_occupancy[station] = 0;
    }

    bool can_move_to(const std::string &station) const
    {
        if (station == "Sv" || station == "Sd")
            return true;

        auto it = station_capacity.find(station);
        if (it == station_capacity.end())
            return true; // No capacity limit

        auto occ_it = current_occupancy.find(station);
        int current_occ = (occ_it != current_occupancy.end()) ? occ_it->second : 0;

        return current_occ < it->second;
    }

    void update_occupancy(const std::string &from, const std::string &to)
    {
        if (from != "Sv" && from != "Sd")
        {
            current_occupancy[from]--;
        }
        if (to != "Sv" && to != "Sd")
        {
            current_occupancy[to]++;
        }
    }

    std::vector<std::string> find_shortest_path(const std::string &start, const std::string &end)
    {
        std::queue<std::string> q;
        std::map<std::string, std::string> parent;
        std::set<std::string> visited;

        q.push(start);
        visited.insert(start);
        parent[start] = "";

        while (!q.empty())
        {
            std::string current = q.front();
            q.pop();

            if (current == end)
            {
                std::vector<std::string> path;
                std::string node = end;
                while (node != "")
                {
                    path.push_back(node);
                    node = parent[node];
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            if (graph.find(current) != graph.end())
            {
                for (const std::string &neighbor : graph[current])
                {
                    if (visited.find(neighbor) == visited.end())
                    {
                        visited.insert(neighbor);
                        parent[neighbor] = current;
                        q.push(neighbor);
                    }
                }
            }
        }

        return {}; // No path found
    }

    virtual void move() = 0;

    void print_results() const
    {
        std::cout << "\n=== Final Results ===" << std::endl;
        int successful_ants = 0;
        for (const auto &ant : ants)
        {
            ant.print_path();
            if (ant.reached_destination)
                successful_ants++;
        }
        std::cout << "Successfully moved " << successful_ants << " out of " << total_ants << " ants." << std::endl;
    }

    bool all_ants_reached_destination() const
    {
        for (const auto &ant : ants)
        {
            if (!ant.reached_destination)
                return false;
        }
        return true;
    }
};

#endif // FOURMILIERE_H