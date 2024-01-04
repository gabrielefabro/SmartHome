#include "main.h"

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

#if (DEBUG > 0)
  setvbuf(stdout, (char *)NULL, _IONBF, 0);
  setvbuf(stderr, (char *)NULL, _IONBF, 0);
#endif

  camera_type x, y;
  int t = 0;

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

  /* init camera state */
  int value = rand();
  x = init();
  nanos = get_nanos();

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

  sprintf(key, "mykey:%d", send_counter);
  sprintf(value, "myvalue:%d", send_counter);

  while (t <= HORIZON)
  {
    /* output */

    //   nanos_day = get_day_nanos(buf);

    nanos_day = nanos2day(buf, nanos);

    printf("%d, %lf, %lf, %ld, %d, %s, %ld\n", t, global_time_sec, timeadvance, nanos, x, buf, nanos_day);

    log2db(db1, pid, nanos, x);

    /* update state */
    y = next(x);

    assert((y == x) || (y == (x + 1) % 3));

    x = y;

    /* update time */
    t++;

    /* sleep   */
    micro_sleep(500);

    update_time(); // update nanos, global_time_sec, timeadvance,

  } /* while */

  log2stdout(db1, pid);

} /*  main()  */
