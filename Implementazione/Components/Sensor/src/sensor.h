#ifndef SENSR_H
#define SENSR_H

#include <cstdlib>
#include <iostream>
#include <string>

typedef enum
{
    SensorON,
    CHECKING,
    SensorOFF
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
    sensor_type next();

    // Funzione per controllare lo stato del sensore
    sensor_type getState() const;

    // Funzione per ottenere l'ID del sensore
    int getId() const;

    // Funzione per impostare il valore di movement
    void setMovement(bool value);

    // Funzione per ottenere il valore di movement
    bool getMovement() const;
};

#endif // CAMERA_H
