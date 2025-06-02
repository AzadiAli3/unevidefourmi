//bfs
#include "fourmiliere.h"

class Fourmiliere0 : public Fourmiliere
{
public:
    Fourmiliere0() : Fourmiliere(2)
    {
        // Build graph for fourmiliere_zero
        add_connection("Sv", "S1");
        add_connection("Sv", "S2");
        add_connection("S1", "Sd");
        add_connection("S2", "Sd");
    }

    void move() override
    {
        std::cout << "=== Moving ants in Fourmiliere 0 ===" << std::endl;

        // Simple strategy: first ant goes Sv->S1->Sd, second ant goes Sv->S2->Sd
        if (ants.size() >= 1)
        {
            ants[0].move_to("S1");
            ants[0].move_to("Sd");
        }

        if (ants.size() >= 2)
        {
            ants[1].move_to("S2");
            ants[1].move_to("Sd");
        }

        std::cout << "All ants moved successfully!" << std::endl;
    }
};

int main()
{
    std::cout << "Fourmiliere 0 - Simple parallel paths" << std::endl;
    Fourmiliere0 colony;
    colony.move();
    colony.print_results();
    return 0;
}