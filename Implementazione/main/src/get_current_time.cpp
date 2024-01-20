#include "main.h"

// Funzione che restituisce il tempo corrente in nanosecondi
long long get_current_time_ns() {
    // Ottieni il tempo corrente
    auto current_time = std::chrono::high_resolution_clock::now();

    // Converti il tempo corrente in nanosecondi
    auto nanoseconds = std::chrono::time_point_cast<std::chrono::nanoseconds>(current_time);
    return nanoseconds.time_since_epoch().count();
}