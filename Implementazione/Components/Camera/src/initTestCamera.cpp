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

  if (strcmp(state, "Waiting") == 0)
  {

    redisReply *reply_get = (redisReply *)redisCommand(context, "GET message");
    std::string redisValue(reply_get->str);
    if (strcmp(reply_get->str, "movement detected") == 0)
    {
      camera.setRecording(true);
    }
    else
    {
      camera.setRecording(false);
    }
    freeReplyObject(reply_get);
  }

  // Chiudi la connessione a Redis
  redisFree(context);

  return 0;
}
