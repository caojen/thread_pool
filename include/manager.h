#ifndef __MANAGER
#define __MANAGER

#include <pthread.h>

#include "job.h"
#include "worker.h"

struct __worker_queue;
typedef struct __worker_queue WorkerQueue;

struct __manager {
  JobQueue* jobQueue;
  WorkerQueue* workerQueue;

  pthread_mutex_t mtx;
  pthread_cond_t cond;
};

typedef struct __manager Manager;
typedef struct __manager Pool;

// api:

/**
 * Create a new pool.
 * @param{num} the number of worker (init)
 * @return{Pool*} the ptr to pool. If NULL, something error.
 */
Pool*
pool_create(unsigned int num);

/**
 * Destory this pool.
 * Return 0 if success.
 */
int
pool_destory(Pool*);

/**
 * Push a new job into the pool.
 */
int
pool_push_job(Pool*, Job*);


#endif
