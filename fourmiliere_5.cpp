#include "fourmiliere.h"

class Fourmiliere5 : public Fourmiliere
{
public:
    Fourmiliere5() : Fourmiliere(50)
    {
        // Build complex graph for fourmiliere_cinq
        add_connection("Sv", "S1");
        add_connection("S1", "S2");
        add_connection("S2", "S3");
        add_connection("S3", "S4");
        add_connection("S4", "Sd");
        add_connection("S2", "S5");
        add_connection("S5", "S4");
        add_connection("S13", "Sd");
        add_connection("S8", "S12");
        add_connection("S12", "S13");
        add_connection("S6", "S7");
        add_connection("S7", "S9");
        add_connection("S9", "S14");
        add_connection("S14", "Sd");
        add_connection("S7", "S10");
        add_connection("S10", "S14");
        add_connection("S1", "S6");
        add_connection("S6", "S8");
        add_connection("S8", "S11");
        add_connection("S11", "S13");

        // Set capacities
        set_capacity("S1", 8);
        set_capacity("S2", 4);
        set_capacity("S3", 2);
        set_capacity("S4", 4);
        set_capacity("S5", 2);
        set_capacity("S6", 4);
        set_capacity("S7", 2);
        set_capacity("S8", 5);
        set_capacity("S13", 4);
        set_capacity("S14", 2);
    }

    void move() override
    {
        std::cout << "=== Moving ants in Fourmiliere 5 ===" << std::endl;
        std::cout << "Complex colony with " << total_ants << " ants and capacity constraints" << std::endl;

        // Strategy: Use multiple paths with capacity management
        // Path 1: Sv->S1->S2->S3->S4->Sd
        // Path 2: Sv->S1->S2->S5->S4->Sd
        // Path 3: Sv->S1->S6->S8->S11->S13->Sd
        // Path 4: Sv->S1->S6->S7->S9->S14->Sd
        // Path 5: Sv->S1->S6->S7->S10->S14->Sd
        // Path 6: Sv->S1->S6->S8->S12->S13->Sd

        int current_turn = 0;
        const int max_turns = 100;

        while (!all_ants_reached_destination() && current_turn < max_turns)
        {
            current_turn++;
            if (current_turn % 10 == 1)
            {
                std::cout << "Turn " << current_turn << "..." << std::endl;
            }

            bool any_moved = false;

            for (size_t i = 0; i < ants.size(); ++i)
            {
                if (ants[i].reached_destination)
                    continue;

                std::string current_pos = ants[i].current_position;
                std::string next_station;

                // Route ants based on their ID to distribute load
                int route = (int)i % 6;

                // Determine next move based on current position and assigned route
                if (current_pos == "Sv")
                {
                    next_station = "S1";
                }
                else if (current_pos == "S1")
                {
                    if (route <= 1)
                    {
                        next_station = "S2";
                    }
                    else
                    {
                        next_station = "S6";
                    }
                }
                else if (current_pos == "S2")
                {
                    if (route == 0)
                    {
                        next_station = "S3";
                    }
                    else
                    {
                        next_station = "S5";
                    }
                }
                else if (current_pos == "S3")
                {
                    next_station = "S4";
                }
                else if (current_pos == "S5")
                {
                    next_station = "S4";
                }
                else if (current_pos == "S4")
                {
                    next_station = "Sd";
                }
                else if (current_pos == "S6")
                {
                    if (route == 2 || route == 5)
                    {
                        next_station = "S8";
                    }
                    else
                    {
                        next_station = "S7";
                    }
                }
                else if (current_pos == "S7")
                {
                    if (route == 3)
                    {
                        next_station = "S9";
                    }
                    else
                    {
                        next_station = "S10";
                    }
                }
                else if (current_pos == "S8")
                {
                    if (route == 2)
                    {
                        next_station = "S11";
                    }
                    else
                    {
                        next_station = "S12";
                    }
                }
                else if (current_pos == "S9")
                {
                    next_station = "S14";
                }
                else if (current_pos == "S10")
                {
                    next_station = "S14";
                }
                else if (current_pos == "S11")
                {
                    next_station = "S13";
                }
                else if (current_pos == "S12")
                {
                    next_station = "S13";
                }
                else if (current_pos == "S13")
                {
                    next_station = "Sd";
                }
                else if (current_pos == "S14")
                {
                    next_station = "Sd";
                }

                if (!next_station.empty() && can_move_to(next_station))
                {
                    update_occupancy(current_pos, next_station);
                    ants[i].move_to(next_station);
                    any_moved = true;
                }
            }

            if (!any_moved)
            {
                std::cout << "Deadlock detected at turn " << current_turn << std::endl;
                break;
            }
        }

        std::cout << "Movement completed after " << current_turn << " turns!" << std::endl;
    }
};

int main()
{
    std::cout << "Fourmiliere 5 - Large complex colony with 50 ants" << std::endl;
    Fourmiliere5 colony;
    colony.move();
    colony.print_results();
    return 0;
}