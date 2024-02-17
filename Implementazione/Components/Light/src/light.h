#ifndef LIGHT_H
#define LIGHT_H
#include <cstdlib>

// Dichiarazione di un tipo di enumerazione per rappresentare lo stato di una luce.
typedef enum
{
    LightON,
    LightOFF,
    change_intensity,
    change_color,
} light_type;

// Dichiarazione di un tipo di enumerazione per rappresentare il colore di una luce.
typedef enum
{
    RED,
    BLUE,
    YELLOW,
    PINK,
    ORANGE,
    WHITE,
    PURPLE,
} light_color;

// Dichiarazione della classe Light, che rappresenta una luce con un ID, uno stato, un colore e un'intensità.
class Light
{
private:
    // Variabile di stato della luce (accesa, spenta, ecc.).
    light_type state;

    // Colore della luce.
    light_color color;

    // Intensità della luce.
    int intensity;

    // ID univoco della luce.
    int id;

public:
    // Costruttore della classe Light.
    Light(int id, light_type state, light_color color, int intensity);

    // Funzione per ottenere il prossimo stato casuale della luce.
    light_type next();

    // Funzione per cambiare il colore delle luci.
    void setColor(light_color newColor);

    // Funzione per ottenere lo stato attuale della luce.
    light_type getState() const;

    // Funzione per cambiare l'intensità delle luci.
    void setIntensity(int newIntensity);

    // Funzione per ottenere l'ID della luce.
    int getId() const;

    // Funzione per ottenere il colore attuale della luce.
    light_color getColor() const;

    // Funzione per ottenere l'intensità attuale della luce.
    int getIntensity() const;

    // Funzione per impostare lo stato della luce.
    void setState(light_type newState);
};

Light initLight();
void log2lightdb(Con2DB db1, int id, int pid, light_type state, light_color color, int intensity);


#endif
