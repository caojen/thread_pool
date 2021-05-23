#ifndef __WORKER
#define __WORKER

#include <pthread.h>

#include "manager.h"

struct __manager;
typedef struct __manager Pool;

struct __worker {
  int worker_id;
  pthread_t pthread_id;
  int terminate;

  Pool* pool;

  struct __worker* next;
  struct __worker* prev;
};

typedef struct __worker Worker;

struct __worker_queue {
  Worker* head;
  Worker* tail;
  unsigned int count;
};

typedef struct __worker_queue WorkerQueue;

/**
 * Create an empty queue without any worker
 * Return NULL if error.
 * Return the queue if success.
 */
WorkerQueue*
worker_queue_create();

/**
 * Add a pthread_t into worker.
 * Return 0 if success.
 * Return other if failed.
 */
int
worker_queue_add(WorkerQueue* wq, Worker* worker);
#endif
