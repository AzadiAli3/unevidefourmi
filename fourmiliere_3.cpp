#include "fourmiliere.h"

class Fourmiliere3 : public Fourmiliere
{
public:
    Fourmiliere3() : Fourmiliere(5)
    {
        // Build graph for fourmiliere_trois
        add_connection("Sv", "S1");
        add_connection("S1", "S2");
        add_connection("S4", "Sd");
        add_connection("S1", "S4");
        add_connection("S2", "S3");
    }

    void move() override
    {
        std::cout << "=== Moving ants in Fourmiliere 3 ===" << std::endl;

        // Strategy: Use shortest path Sv -> S1 -> S4 -> Sd (3 steps)
        // Alternative longer path: Sv -> S1 -> S2 -> S3 (but S3 has no exit to Sd)

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
                    next_station = "S4"; // Choose S4 over S2 (shortest path)
                }
                else if (step == 3 && ants[i].current_position == "S4")
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

        std::cout << "All ants moved through optimal path!" << std::endl;
    }
};

int main()
{
    std::cout << "Fourmiliere 3 - Branching paths with optimal choice" << std::endl;
    Fourmiliere3 colony;
    colony.move();
    colony.print_results();
    return 0;
}