#include "../../../main/src/main.h"

// Funzione per testare una telecamera e generare un qualsiasi scenario possibile
int initTestCamera(Camera &camera)
{
  camera_type cameraState;
  char state[20];

  // Inizializzazione della connessione a Redis
  redisContext *context = redisConnect("127.0.0.1", 6379);

  // Verifica se la connessione è avvenuta correttamente.
  if (context == nullptr || context->err)
  {
    std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
    return 1;
  }

  cameraState = camera.getState();

  // Converti lo stato della telecamera in formato stringa.
  int2stateCamera(state, cameraState);

  if (strcmp(state, "CameraOFF") == 0)
  {
    camera.setRecording(false);
  }

  // Verifica se lo stato è "Waiting" e in caso legge un messaggio da redis per verificare un movimento, messaggio generato dai test del sensore.
  if (strcmp(state, "Waiting") == 0)
  {
    // Esegui una richiesta Redis
    redisReply *reply_get = (redisReply *)redisCommand(context, "GET message");
    std::string redisValue(reply_get->str);

    // Verifica se il valore ottenuto è "movement detected", in caso positivo significa che cè stato del movimento la telecamera deve iniziare a registrare.
    if (strcmp(reply_get->str, "movement detected") == 0)
    {
      camera.setRecording(true);
    }
    else
    {
      // Altrimenti, imposta la registrazione su false.
      camera.setRecording(false);
    }

    freeReplyObject(reply_get);
  }

  // Chiudi la connessione a Redis.
  redisFree(context);

  return 0;
}
