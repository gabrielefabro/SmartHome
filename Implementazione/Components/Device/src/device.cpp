#include "device.h"

// Costruttore della classe Device.
Device::Device(int id, device_type state, nome_type name) : id(id), state(state), nome(name) {}

// Funzione per generare casualmente uno stato successivo per il dispositivo.
device_type Device::next()
{
    state = static_cast<device_type>(rand() % 3);
    return state;
}

// Funzione per programmare l'attivazione di un dispositivo in un intervallo di tempo.
void Device::programmed_device(int intervalloPrimo, int intervalloSecondo)
{
    {
        inizio = intervalloPrimo;
        fine = intervalloSecondo;
    }
}

// Funzione per ottenere lo stato corrente del dispositivo.
device_type Device::getState() const
{
    return state;
}

// Funzione per ottenere l'ID del dispositivo.
int Device::getId() const
{
    return id;
}

// Funzione per ottenere il nome del dispositivo.
nome_type Device::getNome() const
{
    return nome;
}

// Funzione per impostare manualmente lo stato del dispositivo a DeviceON.
void Device::setState()
{
    state = DeviceON;
}

// Funzione per impostare manualmente lo stato del dispositivo con il valore passato come argomento.
void Device::setState(device_type newState)
{
    state = newState;
}

// Funzione per ottenere gli intervalli di tempo programmato per l'attivazione del dispositivo.
std::tuple<int, int> Device::getProgrammed()
{
    return std::make_tuple(inizio, fine);
}
