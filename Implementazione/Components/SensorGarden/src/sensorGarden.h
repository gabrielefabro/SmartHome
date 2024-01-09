#ifndef SENSOR_GARDEN_H
#define SENSOR_GARDEN_H

#include <cstdlib>

typedef enum
{
    ON,
    change_light,
    set_sprinklers,
    OFF
} sensorGarden_type;

class SensorGarden
{
private:
    sensorGarden_type state;
    int id;
    int humidity;
    int temperature;

public:
    // Costruttore
    SensorGarden(int id, sensorGarden_type state, int humidity, int temperature);

    // Funzione per ottenere lo stato successivo
    sensorGarden_type next();

    // Funzione per controllare lo stato del sensorGarden
    sensorGarden_type getState() const;

    // Funzione per ottenere l'ID del sensorGarden
    int getId() const;
};

#endif // SENSOR_GARDEN_H
