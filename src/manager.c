#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager.h"

void* pool_callback(void* arg) {
  Worker* worker = (Worker*) arg;
  while(1) {
    pthread_mutex_lock(&worker->pool->mtx);
    while(worker->pool->jobQueue->count == 0) {
      pthread_cond_wait(&worker->pool->cond, &worker->pool->mtx);
    }
    pthread_mutex_unlock(&worker->pool->mtx);
    // get a job from queue:
    Job* job = job_queue_pop(worker->pool->jobQueue);
    if(job == NULL) {
      perror("Unexcepted: job is null");
    }
    job->func(job->arg);
  }
}

Pool*
pool_create(unsigned int num) {

  if(num < 1) {
    num = 1;
  }

  Pool* pool = (Pool*) malloc (sizeof(Pool));
  if(pool == NULL) {
    perror("pool malloc failed");
  }

  pool->jobQueue = job_queue_create();
  if(pool->jobQueue == NULL) {
    perror("job queue malloc failed");
  }

  pool->workerQueue = worker_queue_create();
  if(pool->workerQueue == NULL) {
    perror("worker queue malloc failed");
  }
  pthread_mutex_t blank_mtx = PTHREAD_MUTEX_INITIALIZER;
  memcpy(&pool->mtx, &blank_mtx, sizeof(pthread_mutex_t));

  pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
  memcpy(&pool->cond, &blank_cond, sizeof(pthread_cond_t));


  for(unsigned int i = 0; i < num; i++) {
    Worker* worker = (Worker*) malloc (sizeof(Worker));
    if(worker == NULL) {
      perror("worker malloc");
      return -1;
    }
    memset(worker, 0, sizeof(Worker));
    worker->worker_id = i;
    worker->pool = pool;
    int ret = pthread_create(worker->pthread_id, NULL, pool_callback, worker);
    if(ret != 0) {
      perror("pthread create failed");
    }
    worker_queue_add(pool->workerQueue, worker);
  }

  return 0;
}
