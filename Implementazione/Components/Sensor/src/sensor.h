#ifndef SENSR_H
#define SENSR_H

#include <cstdlib>
#include <iostream>
#include <string>

// Enumerazione che rappresenta gli stati possibili del sensore
typedef enum
{
    SensorON, 
    SensorOFF 
} sensor_type;

// Classe che rappresenta un sensore
class Sensor
{
private:
    // Enumerazione che rappresenta gli stati possibili del Sensore
    sensor_type state;

    // Identificatore univoco del Sensore.
    int id;

    // Flag per indicare se è stato rilevato un movimento
    bool check;

public:
    // Costruttore della classe Sensor
    Sensor(int id, sensor_type state);

    // Funzione per controllare lo stato attuale del sensore
    sensor_type getState() const;

    // Funzione per ottenere l'identificatore del sensore
    int getId() const;

    // Funzione per impostare manualmente il valore di movement
    void setCheck(bool value);

    // Funzione per ottenere il valore di movement
    bool getCheck() const;

    // Funzione per impostare manualmente lo stato del sensore
    void setState(sensor_type newState);
};

Sensor initSensor();
void log2sensordb(Con2DB db1, int id, int pid, sensor_type state, bool check);


#endif
