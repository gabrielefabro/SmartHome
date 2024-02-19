#!/bin/bash

# Esegue i file main nelle diverse directory

# Percorsi dei file main
CAMERA="./Camera/bin/main"
CONDITIONER="./Conditioner/bin/main"
DEVICE="./Device/bin/main"
LIGHT="./Light/bin/main"
SENSOR="./Sensor/bin/main"
SENSOR_GARDEN="./SensorGarden/bin/main"

# Esegui i file main
echo "Esecuzione del file Camera..."
$CAMERA &

echo "Esecuzione del file Conditioner..."
$CONDITIONER &

echo "Esecuzione del file Device..."
$DEVICE &

echo "Esecuzione del file Light..."
$LIGHT &

echo "Esecuzione del file Sensor..."
$SENSOR &

echo "Esecuzione del file SensorGarden..."
$SENSOR_GARDEN &

echo "Tutti i file sono stati avviati."