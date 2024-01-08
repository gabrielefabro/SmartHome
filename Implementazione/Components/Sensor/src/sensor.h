#ifndef SENSR_H
#define SENSR_H

#include <cstdlib>

typedef enum
{
    ON,
    CHECKING,
    OFF
} sensor_type;

class Sensor
{
private:
    sensor_type state;
    int id;
    bool movement;

public:
    // Costruttore
    Sensor(int id, sensor_type state);

    // Funzione per ottenere lo stato successivo
    sensor_type next(Sensor sensor);

    // Funzione per controllare lo stato di registrazione
    sensor_type getState() const;

    // Funzione per ottenere l'ID della fotocamera
    int getId() const;
};

#endif // CAMERA_H
