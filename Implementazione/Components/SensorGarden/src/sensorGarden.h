#ifndef SENSOR_GARDEN_H
#define SENSOR_GARDEN_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include "../../../con2db/src/pgsql.h"

// Enumerazione dei possibili stati del sensore da giardino
typedef enum
{
    SensorGardenON,
    SensorGardenOFF
} sensorGarden_type;

class SensorGarden
{
private:

    // Stato attuale del sensore da giardino
    sensorGarden_type state;

    // ID univoco del sensore da giardino
    int id;

    // Livello di umidità rilevato dal sensore da giardino
    int humidity;
    
    // Temperatura rilevata dal sensore da giardino
    int temperature;

public:
    // Costruttore del sensore da giardino
    SensorGarden(int id, sensorGarden_type state, int humidity, int temperature);

    // Funzione per ottenere lo stato attuale del sensore da giardino
    sensorGarden_type getState() const;

    // Funzione per ottenere l'ID del sensore da giardino
    int getId() const;

    // Funzione per ottenere il livello di umidità rilevato dal sensore da giardino
    int getHumidity() const;

    // Funzione per ottenere la temperatura rilevata dal sensore da giardino
    int getTemperature() const;

    // Funzione per impostare lo stato del sensore da giardino
    void setState(sensorGarden_type newState);

    // Funzione per impostare la temperatura rilevata dal sensore da giardino
    void setTemperature(int newTemperature);

    // Funzione per impostare il livello di umidità rilevato dal sensore da giardino
    void setHumidity(int newHumidity);
};

SensorGarden initSensorGarden();
void log2sensorGardendb(Con2DB db1, int id, int pid, sensorGarden_type state, int humidity, int temperature, int64_t tempo_trascorso);
void int2stateSensorGarden(char *cstate, sensorGarden_type state);
void timeFlies(char *buf);

#endif
