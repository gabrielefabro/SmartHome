#ifndef DEVICE_H
#define DEVICE_H

#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>
#include <hiredis/hiredis.h>
#include <string>
#include <tuple>
#include "../../../con2db/src/pgsql.h"

// Enumerazione che rappresenta i possibili stati del dispositivo.
typedef enum
{
    DeviceON,
    DeviceOFF,
    programmed,
} device_type;

// Enumerazione che rappresenta i possibili tipi di dispositivi.
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

// Dichiarazione della classe Device.
class Device
{
private:
    // Variabile che rappresenta l'identificatore del dispositivo.
    int id;
    
    // Variabile di stato del dispositivo.
    device_type state;

    // Variabile che rappresenta il tipo di dispositivo.
    nome_type nome;

    // Variabili per memorizzare gli intervalli di tempo programmati per l'attivazione del dispositivo.
    int inizio;
    int fine;

public:
    // Costruttore della classe Device.
    Device(int id, device_type state, nome_type nome);

    // Funzione per programmare l'attivazione del dispositivo in un intervallo di tempo.
    void programmed_device(int intervalloPrimo, int intervalloSecondo);

    // Funzione per ottenere lo stato corrente del dispositivo.
    device_type getState() const;

    // Funzione per ottenere il tipo di dispositivo.
    nome_type getNome() const;

    // Funzione per ottenere l'ID del dispositivo.
    int getId() const;

    // Funzione per impostare manualmente lo stato del dispositivo a DeviceON.
    void setState();

    // Funzione per impostare manualmente lo stato del dispositivo con il valore passato come argomento.
    void setState(device_type newState);

    void setName(nome_type newName);

    // Funzione per ottenere gli intervalli di tempo programmato per l'attivazione del dispositivo.
    std::tuple<int, int> getProgrammed();
};

Device initDevice();
void log2devicedb(Con2DB db1, int id, int pid, device_type state, nome_type nome, int inizio, int fine, int64_t tempo_trascorso);
void int2stateDevice(char *cstate, device_type);
const char *nomeToString(nome_type nomeDev);
void timeFlies(char *buf);
int changeInt();
#endif
