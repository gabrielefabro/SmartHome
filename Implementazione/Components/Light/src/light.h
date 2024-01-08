#ifndef LIGHT_H
#define LIGHT_H
#include <cstdlib>

typedef enum
{
    ON,
    OFF,
} light_type;

typedef enum
{
    RED,
    BLUE,
    YELLOW,
    PINK
} light_color;



class Light
{
private:
    light_type state;
    light_color color;
    int intensity;
    int id;

public:
    // Costruttore
    Light(int id, light_type state, light_color color, int intensity);

    // Funzione per ottenere lo stato successivo
    light_type next(Light light);

    // Funzione per cambiare colore delle luci
    light_color changeColor(Light light);

    // Funzione per controllare lo stato delle luci
    light_type getState() const;

    // Funzione per cambiare l'intesità delle luci
    void changeIntensity(int newIntensity);

    // Funzione per ottenere l'ID della fotocamera
    int getId() const;
};

#endif // LIGHT_H