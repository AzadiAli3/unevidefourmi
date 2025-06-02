#include "fourmiliere.h"

class Fourmiliere4 : public Fourmiliere
{
public:
    Fourmiliere4() : Fourmiliere(10)
    {
        // Build graph for fourmiliere_quatre
        add_connection("Sv", "S1");
        add_connection("S1", "S2");
        add_connection("S2", "S4");
        add_connection("S4", "S5");
        add_connection("S5", "Sd");
        add_connection("S4", "S6");
        add_connection("S6", "Sd");
        add_connection("S1", "S3");
        add_connection("S3", "S4");

        // Set capacities
        set_capacity("S1", 2);
        set_capacity("S4", 2);
    }

    void move() override
    {
        std::cout << "=== Moving ants in Fourmiliere 4 ===" << std::endl;

        // Strategy: Use capacity-aware pathfinding
        // Two main paths: Sv->S1->S2->S4->S5->Sd and Sv->S1->S2->S4->S6->Sd
        // Alternative: Sv->S1->S3->S4->...

        std::vector<int> ants_at_destination;
        int current_turn = 0;

        while (!all_ants_reached_destination() && current_turn < 20)
        {
            current_turn++;
            std::cout << "Turn " << current_turn << ":" << std::endl;

            bool any_moved = false;

            for (size_t i = 0; i < ants.size(); ++i)
            {
                if (ants[i].reached_destination)
                    continue;

                std::string current_pos = ants[i].current_position;
                std::string next_station;

                // Determine next move based on current position
                if (current_pos == "Sv")
                {
                    next_station = "S1";
                }
                else if (current_pos == "S1")
                {
                    // Choose between S2 and S3 based on capacity and strategy
                    if ((int)i % 3 == 0)
                    {
                        next_station = "S3"; // Some ants use alternative path
                    }
                    else
                    {
                        next_station = "S2";
                    }
                }
                else if (current_pos == "S2")
                {
                    next_station = "S4";
                }
                else if (current_pos == "S3")
                {
                    next_station = "S4";
                }
                else if (current_pos == "S4")
                {
                    // Choose between S5 and S6
                    if ((int)i % 2 == 0)
                    {
                        next_station = "S5";
                    }
                    else
                    {
                        next_station = "S6";
                    }
                }
                else if (current_pos == "S5")
                {
                    next_station = "Sd";
                }
                else if (current_pos == "S6")
                {
                    next_station = "Sd";
                }

                if (!next_station.empty() && can_move_to(next_station))
                {
                    update_occupancy(current_pos, next_station);
                    ants[i].move_to(next_station);
                    std::cout << "  Ant " << ants[i].id << " moved from " << current_pos
                              << " to " << next_station << std::endl;
                    any_moved = true;
                }
                else if (!next_station.empty())
                {
                    std::cout << "  Ant " << ants[i].id << " blocked at " << current_pos
                              << " (capacity full at " << next_station << ")" << std::endl;
                }
            }

            if (!any_moved)
            {
                std::cout << "No ants could move this turn." << std::endl;
                break;
            }
        }

        std::cout << "Movement completed!" << std::endl;
    }
};

int main()
{
    std::cout << "Fourmiliere 4 - Complex graph with capacity constraints" << std::endl;
    Fourmiliere4 colony;
    colony.move();
    colony.print_results();
    return 0;
}