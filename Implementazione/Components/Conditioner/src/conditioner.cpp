#include <iostream>
#include <string>
#include <cstdlib>
#include "main.h"
#include "conditioner.h"


class Conditioner
{
private:
    conditioner_type state;
    int level;
    int id;

public:
    // Costruttore
    Conditioner(int id, int level, conditioner_type state) : id(id), level(level), state(state) {}
    
    conditioner_type next(Conditioner conditioner)
    {
        conditioner.state = static_cast<conditioner_type>((state + rand() % 2) % 2);
        return state;
    }

    // Funzione per controllare lo stato della temperatura
    conditioner_type getState() const
    {
        return state;
    }

    // Modificare la temperatura
    void modifyTheLevel(int newLevel)
    {
        if (getState() == ON)
        {
            level = newLevel;
            std::cout << " power level modified to " << level << std::endl;
        }
        else
        {
            std::cout << "Error: turned off. Turn it on first." << std::endl;
        }
    }

     int getId() const
    {
        return id;
    }