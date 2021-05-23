#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "worker.h"

WorkerQueue*
worker_queue_create() {
  WorkerQueue* wq = (WorkerQueue*) malloc (sizeof(WorkerQueue));
  if(wq == NULL) {
    perror("malloc");
    return NULL;
  }

  memset(wq, 0, sizeof(WorkerQueue));

  return wq;
}

int
worker_queue_add(WorkerQueue* wq, Worker* worker) {

  if(wq == NULL) {
    return -1;
  }

  if(wq->count == 0) {
    wq->head = wq->tail = worker;
  } else {
    worker->next = wq->head;
    wq->head->prev = worker;
    wq->head = worker;
  }
  wq->count++;
  return 0;
}
