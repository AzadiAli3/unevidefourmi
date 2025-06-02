#include "fourmiliere.h"

class Fourmiliere1 : public Fourmiliere
{
public:
    Fourmiliere1() : Fourmiliere(5)
    {
        // Build graph for fourmiliere_un
        add_connection("Sv", "S1");
        add_connection("S1", "S2");
        add_connection("S2", "Sd");
    }

    void move() override
    {
        std::cout << "=== Moving ants in Fourmiliere 1 ===" << std::endl;

        // Sequential movement through single path: Sv -> S1 -> S2 -> Sd
        // All ants follow the same path one after another

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

        std::cout << "All ants moved through the linear path!" << std::endl;
    }
};

int main()
{
    std::cout << "Fourmiliere 1 - Single linear path" << std::endl;
    Fourmiliere1 colony;
    colony.move();
    colony.print_results();
    return 0;
}