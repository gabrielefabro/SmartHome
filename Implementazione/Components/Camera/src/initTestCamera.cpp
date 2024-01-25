#include "../../../main/src/main.h"

int initTestCamera(Camera &camera)
{
  camera_type cameraState;
  char state[20];
  // Inizializza la connessione a Redis
  redisContext *context = redisConnect("127.0.0.1", 6379);
  if (context == nullptr || context->err)
  {
    std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
    return 1;
  }

  cameraState = camera.getState();
  int2stateCamera(state, cameraState);

  if (strcmp(state, "CameraOFF") == 0)
  {
    camera.setRecording(false);
  }

  else if (strcmp(state, "Waiting") == 0)
  {
    std::cout << "Sono in waiting" << std::endl;

    redisReply *reply_get = (redisReply *)redisCommand(context, "GET message");
    std::string redisValue(reply_get->str);
    std::cout << "Valore ottenuto da Redis: " << redisValue << std::endl;
    if (strcmp(reply_get->str, "movement detected") == 0)
    {
      std::cout << "camera accenditi" << std::endl;
      camera.setRecording(true);
      std::cout << "lo stato della camera è " << camera.getRecording() << std::endl;
    }
    else
    {
      camera.setRecording(false);
      std::cout << "lo stato della camera è " << camera.getRecording() << std::endl;
    }
    freeReplyObject(reply_get);
  }
  
  // Chiudi la connessione a Redis
  redisFree(context);

  return 0;
}
