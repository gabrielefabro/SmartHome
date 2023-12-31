#include "main.h"
#include "camera.h"
#include "hiredis/hiredis.h"

#define READ_STREAM "stream1"
#define WRITE_STREAM "stream2"

int main()
{
  Con2DB db1("localhost", "5432", "user_Smarthome", "47002", "SmartHome");

  PGresult *res;
  redisContext *c2r;
  char buf[200];
  redisReply *reply;
  int pid;
  char id[20];
  char state[20];
  char id2send[20];
  char state2send[30];
  int block = 1000000000;
  char username[100];

#if (DEBUG > 0)
  setvbuf(stdout, (char *)NULL, _IONBF, 0);
  setvbuf(stderr, (char *)NULL, _IONBF, 0);
#endif

  int t = 0;
  sprintf(username, "%u", rand());

  /* init random number generator  */
  srand((unsigned)time(NULL));

  pid = getpid();

  printf("Start main with pid %ld, ppid %ld \n",
         (long)pid, (long)getppid());
  printf("main(): pid %d: connecting to redis ...\n", pid);

  printf(
      "Format: time step, global time in second, elapsed time in sec, present time in nanoseconds, variable, value\n");

  init_logdb(db1, pid);

  /* init time */
  init_time();

  Camera camera = initCamera();

  c2r = redisConnect("localhost", 6379);

  // delete stream if it exists
  reply = RedisCommand(c2r, "DEL %s", READ_STREAM);
  assertReply(c2r, reply);
  dumpReply(reply, 0);
  reply = RedisCommand(c2r, "DEL %s", WRITE_STREAM);
  assertReply(c2r, reply);
  dumpReply(reply, 0);

  /* Create streams/groups */
  initStreams(c2r, READ_STREAM);
  initStreams(c2r, WRITE_STREAM);

  while (t <= HORIZON)
  {
    /* output */
    int2state(state, camera.getState());

    sprintf(id2send, "my ID: %d", camera.getId());
    sprintf(state2send, "my state: %s", state);

    // sender
    reply = RedisCommand(c2r, "XADD %s * %s %s", WRITE_STREAM, id2send, state2send);
    assertReplyType(c2r, reply, REDIS_REPLY_STRING);
    printf("main(): pid =%d: stream %s: camera %s, changed state to %s (id: %s)\n", pid, WRITE_STREAM, id2send, state2send, reply->str);
    freeReplyObject(reply);

    nanos_day = nanos2day(buf, nanos);

    printf("%d, %lf, %lf, %ld, %s, %s, %ld\n", t, global_time_sec, timeadvance, nanos, state, buf, nanos_day);

    log2db(db1, pid, nanos, camera.getState());
    reply = RedisCommand(c2r, "XREADGROUP GROUP diameter %s BLOCK %d COUNT 1 NOACK STREAMS %s >", username, block, READ_STREAM);

    assertReply(c2r, reply);
    dumpReply(reply, 0);
    freeReplyObject(reply);
    /* update state */
    camera.next();

    /* update time */
    t++;

    /* sleep   */
    micro_sleep(500);

    update_time(); // update nanos, global_time_sec, timeadvance,

  } /* while */

  log2stdout(db1, pid);

} /*  main()  */
