#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "job.h"

JobQueue*
job_queue_create() {
  JobQueue* jq = (JobQueue*) malloc (sizeof(JobQueue));
  if(jq == NULL) {
    perror("malloc");
  }

  memset(jq, 0, sizeof(JobQueue));

  return jq;
}

void
job_queue_add(JobQueue* jobQueue, Job* job) {
  if(jobQueue == NULL || job == NULL) {
    return;
  }
  if(jobQueue->head == NULL) {
    jobQueue->head = jobQueue->tail = job;
  } else {
    job->next = jobQueue->head;
    jobQueue->head->prev = job;
    jobQueue->head = job;
  }
  jobQueue->count++;
  return;
}

Job*
job_queue_pop(JobQueue* jobQueue) {
  if(jobQueue == NULL) {
    return NULL;
  }

  if(jobQueue->count == 0) {
    return NULL;
  }

  Job* ret = jobQueue->tail;
  Job* prev = ret->prev;
  ret->prev = NULL;
  if(prev != NULL) {
    prev->next = NULL;
  }
  return ret;
}
