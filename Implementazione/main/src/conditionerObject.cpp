#include "main.h"

int conditionerObject()
{
    Con2DB db1("localhost", "5432", "trafficlight3000", "47002", "logdb_trafficlight3000");

    PGresult *res;

    char buf[200];

    int pid;

    int t = 0;

    /* init random number generator  */
    srand((unsigned)time(NULL));

    pid = getpid();

    printf("Start conditioner with pid %ld, ppid %ld \n",
           (long)pid, (long)getppid());    

    /* init time */
    init_time();

    /* init traffic light state */
    Camera camera = initCamera();
    nanos = get_nanos();

    while (t <= HORIZON)
    {
        // Rimane in attesa di cambiamento

        // Salva il cambiamento nel database
        log2cameradb(db1, camera.getId(), pid, camera.getState(), camera.getRecording(), t);

        /* update time */
        t++;
        micro_sleep(500);
        update_time();

    }

    log2stdout(db1, pid);

    return 0;

} /*  main()  */