#include <iostream>
#include <string>
#include <cstdlib>
#include "main.h"
#include "device.h"
#include <chrono>
#include <thread>

class Device
{
private:
    device_type state;
    int id;
    nome_type nome;

public:
    // Costruttore
    Device(int id, device_type state, nome_type name) : id(id), state(state), nome(name) {}

    device_type next(Device device)
    {
        device.state = static_cast<device_type>((state + rand() % 2) % 4);
        return state;
    }

    // Funzione per cambiare colore delle luci
    void programmed_device(Device device, int intervalloPrimo, int intervalloSecondo)
    {
        if (getState() == OFF)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(intervalloPrimo));
            device.setState();
            std::this_thread::sleep_for(std::chrono::milliseconds(intervalloSecondo));

            
        }
    }

    device_type getState() const
    {
        return state;
    }

    int getId() const
    {
        return id;
    }

    nome_type getNome() const
    {
        return nome;
    }

    void setState()
    {
        state = ON;
    }
};