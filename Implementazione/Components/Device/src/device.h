#ifndef DEVICE_H
#define DEVICE_H
#include <cstdlib>

typedef enum
{
    ON,
    OFF,
    programmed,
} device_type;

typedef enum
{
    TV,
    DISHWASHER,
    WASHING_MACHINE,
    COFFEE_MAKER,
    MICROWAVE,
    HEATED_BLANKETS,
    SPEAKERS,
    LAWN_MOWER,
} nome_type;

class Device
{
private:
    device_type state;
    nome_type nome;
    int id;

public:
    // Costruttore
    Device(int id, device_type state, nome_type nome);

    // Funzione per ottenere lo stato successivo
    device_type next();

    // Funzione per programmare il device
    void programmed_device(int intervalloPrimo, int intervalloSecondo);

    // Funzione per controllare lo stato del device
    device_type getState() const;

    // Funzione per ottenere il nome del device
    nome_type getNome() const;

    // Funzione per ottenere l'ID del device
    int getId() const;

    void setState();
};

#endif // DEVICE_H