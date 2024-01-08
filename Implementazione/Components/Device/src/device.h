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
    //
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
    device_type next(Device device);

    // Funzione per controllare lo stato delle luci
    device_type getState() const;

    // Funzione per ottenere l'ID del device
    int getId() const;

    void setState();
};

#endif // LIGHT_H