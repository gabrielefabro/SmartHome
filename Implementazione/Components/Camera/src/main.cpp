#include "camera.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <ctime>
#include <cstdlib>

int main()
{

  int t = 0;

  // Inizializza la connessione a Redis
  redisContext *context = redisConnect("127.0.0.1", 6379);
  if (context == nullptr || context->err)
  {
    std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
    return 1;
  }

  // Inizializza un oggetto Sensor
  Camera camera = initCamera();

  while (t < HORIZON)
  {
    // Invia ID e STATE a Redis
    redisReply *reply = (redisReply *)redisCommand(context, "SET camera_id %d", camera.getId());
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(context, "SET camera_state %d", camera.getState());
    freeReplyObject(reply);

    // Aspetta una risposta dal tester
    reply = (redisReply *)redisCommand(context, "GET tester_response");
    if (reply != nullptr && reply->str != nullptr)
    {
      freeReplyObject(reply);
    }

    char state[20];
    camera_type cameraState = static_cast<camera_type>(atoi(reply->str));
    int2state(state, cameraState);
    if (strcmp(state, "WAITING") == 0)
    {
      redisReply *reply_subscribe = (redisReply *)redisCommand(context, "SUBSCRIBE channel");
      freeReplyObject(reply_subscribe);

      redisReply *reply_get = (redisReply *)redisCommand(context, "GET message");
      if (strcmp(reply_get->str, "movement detected") == 0)
      {
        camera.setRecording();
      }
      else
      {
        std::cout << "NOTHING TO REGISTER" << std::endl;
      }
      freeReplyObject(reply_get);
      redisFree(context);
    }

    // Chiudi la connessione a Redis
    redisFree(context);

    camera.next();

    t++;

    /* sleep   */
    micro_sleep(500);
  }

  return 0;
}
