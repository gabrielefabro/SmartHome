#include "camera.h"
#include "main.h"
#include <iostream>
#include <hiredis/hiredis.h>
#include <ctime>
#include <cstdlib>
#include "global.h"

int main()
{

  int t = 0;
  int pid;
  char buf[200];

  // Inizializza database
  Con2DB db1("localhost", "5432", "smarthome", "12345", "logdb_smarthome");

  pid = getpid();

    /* init time */
  init_time();

  // Inizializza la connessione a Redis
  redisContext *context = redisConnect("127.0.0.1", 6379);
  if (context == nullptr || context->err)
  {
    std::cerr << "Errore nella connessione a Redis: " << context->errstr << std::endl;
    return 1;
  }

  // Inizializza un oggetto Sensor
  Camera camera = initCamera();

  init_logdb(db1, pid, camera.getId(), camera.getState());

  while (t < HORIZON)
  {

    nanos_day = nanos2day(buf, nanos);

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
      log2db(db1, pid, nanos, camera.getState(), camera.getRecording());
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
  log2stdout(db1, pid);
  return 0;
}
