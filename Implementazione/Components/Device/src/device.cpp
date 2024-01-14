#include "device.h"

// Costruttore
Device::Device(int id, device_type state, nome_type name) : id(id), state(state), nome(name) {}

device_type Device::next()
{
    state = static_cast<device_type>((state + rand() % 2) % 4);
    return state;
}

// Funzione per programmare l'attivazione di un device in un intervallo di tempo
void Device::programmed_device(int intervalloPrimo, int intervalloSecondo)
{
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalloPrimo));
        setState();
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalloSecondo));
            
    }
}

device_type Device::getState() const
{
    return state;
}

int Device::getId() const
{
    return id;
}

nome_type Device::getNome() const
{
    return nome;
}

void Device::setState()
{
    state = ON;
}