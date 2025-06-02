#include "fourmiliere.h"

class Fourmiliere2 : public Fourmiliere
{
public:
    Fourmiliere2() : Fourmiliere(5)
    {
        // Build graph for fourmiliere_deux (has cycle)
        add_connection("Sv", "S1");
        add_connection("S1", "S2");
        add_connection("S2", "Sd");
        add_connection("Sd", "Sv"); // Creates a cycle
    }

    void move() override
    {
        std::cout << "=== Moving ants in Fourmiliere 2 ===" << std::endl;

        // Strategy: Use shortest path avoiding cycles
        // Path: Sv -> S1 -> S2 -> Sd

        for (int step = 1; step <= 3; ++step)
        {
            std::cout << "Step " << step << ":" << std::endl;

            for (size_t i = 0; i < ants.size(); ++i)
            {
                if (ants[i].reached_destination)
                    continue;

                std::string next_station;
                if (step == 1 && ants[i].current_position == "Sv")
                {
                    next_station = "S1";
                }
                else if (step == 2 && ants[i].current_position == "S1")
                {
                    next_station = "S2";
                }
                else if (step == 3 && ants[i].current_position == "S2")
                {
                    next_station = "Sd";
                }
                else
                {
                    continue;
                }

                ants[i].move_to(next_station);
                std::cout << "  Ant " << ants[i].id << " moved to " << next_station << std::endl;
            }
        }

        std::cout << "All ants moved avoiding the cycle!" << std::endl;
    }
};

int main()
{
    std::cout << "Fourmiliere 2 - Path with cycle (avoiding cycle)" << std::endl;
    Fourmiliere2 colony;
    colony.move();
    colony.print_results();
    return 0;
}