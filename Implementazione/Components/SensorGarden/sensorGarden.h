#ifndef SENSOR_GARDEN_H
#define SENSOR_GARDEN_H

#include <cstdlib>

typedef enum
{
    ON,
    change_light,
    set_sprinklers,
    OFF
} sensor_Garden_type;

class SensorGarden
{
private:
    sensor_Garden_type state;
    int id;
    int humidity;
    int temperature;

public:
    // Costruttore
    SensorGarden(int id, sensor_Garden_type state, int humidity, int temperature);

    // Funzione per ottenere lo stato successivo
    sensor_Garden_type next(SensorGarden sensor);

    // Funzione per controllare lo stato di registrazione
    sensor_Garden_type getState() const;

    // Funzione per ottenere l'ID della fotocamera
    int getId() const;
};

#endif // SENSOR_GARDEN_H
