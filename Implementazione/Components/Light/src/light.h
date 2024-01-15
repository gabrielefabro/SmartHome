#ifndef lightli_h
#define lightli_h
#include <cstdlib>

typedef enum
{
    ON,
    OFF,
    change_intensity,
    change_color,
} light_type;

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
    light_type next();

    // Funzione per cambiare colore delle luci
    void setColor(light_color newColor);

    // Funzione per controllare lo stato delle luci
    light_type getState() const;

    // Funzione per cambiare l'intesità delle luci
    void setIntensity(int newIntensity);

    // Funzione per ottenere l'ID della luce
    int getId() const;

    light_color getColor() const;

    int getIntensity() const;
};

#endif // LIGHT_H