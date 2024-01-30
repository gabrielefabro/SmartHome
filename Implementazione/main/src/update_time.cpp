#include "main.h"

// Funzione che aggiorna le variabili di tempo
void update_time()
{
  
   nanos = get_nanos();

   timeadvance = ((double) (nanos - last_nanos))/((double) (1000000000L));
   global_time_sec = global_time_sec + timeadvance; 
   last_nanos = nanos;
} 