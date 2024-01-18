#include "../../../main/main.h"

int initTestCamera(Camera camera)
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
  if (strcmp(state, "WAITING") == 0)
  {
    redisReply *reply_subscribe = (redisReply *)redisCommand(context, "SUBSCRIBE channel");
    freeReplyObject(reply_subscribe);

    redisReply *reply_get = (redisReply *)redisCommand(context, "GET message");
    if (strcmp(reply_get->str, "movement detected") == 0)
    {
      camera.setRecording();
    }
    freeReplyObject(reply_get);
  }

  // Chiudi la connessione a Redis
  redisFree(context);

  return 0;
}
