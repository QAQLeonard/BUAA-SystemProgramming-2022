#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <semaphore.h>

typedef struct
{
    volatile int oc;
    volatile int hc;
    sem_t os;
    sem_t hs;
    sem_t rs;
} H2O;

H2O *h2oCreate()
{
    H2O *obj = (H2O *)malloc(sizeof(H2O));

    obj->oc = 0;
    obj->hc = 0;

    sem_init(&obj->os, 0, 1);
    sem_init(&obj->hs, 0, 2);
    sem_init(&obj->rs, 0, 1);

    return obj;
}

bool reset(H2O *obj)
{
    return obj->oc == 1 && obj->hc == 2;
}
void check_reset(H2O *obj)
{
    sem_wait(&obj->rs);
    if (reset(obj))
    {
        obj->hc = 0;
        obj->oc = 0;
        sem_post(&obj->os);
        sem_post(&obj->hs);
        sem_post(&obj->hs);
    }
    sem_post(&obj->rs);
}
void hydrogen(H2O *obj)
{
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    check_reset(obj);
    while (0 != sem_trywait(&obj->hs))
    {
        usleep(300);
    }
    releaseHydrogen();
    obj->hc += 1;
    check_reset(obj);
}

void oxygen(H2O *obj)
{
    check_reset(obj);
    while (0 != sem_trywait(&obj->os))
    {
        usleep(300);
    }
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
    obj->oc += 1;
    check_reset(obj);
}

void h2oFree(H2O *obj)
{
    // User defined data may be cleaned up here.
    sem_destroy(&obj->rs);
    sem_destroy(&obj->hs);
    sem_destroy(&obj->os);
    free(obj);
}
