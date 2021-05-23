#ifndef __JOB
#define __JOB

#ifndef NULL
#define NULL ((void*)0)
#endif

struct __job {
  void (*func)(void* arg);
  void* arg;

  struct __job* next;
  struct __job* prev;
};

typedef struct __job Job;

struct __job_queue {
  Job* head;
  Job* tail;
  unsigned int count;
};

typedef struct __job_queue JobQueue;


/**
 * Create a new job queue without any job.
 * Return NULL(0) if error.
 */
JobQueue*
job_queue_create();

/**
 *  Add a new job into a queue.
 *  If the queue is NULL, do nothing.
 *  If the job is NULL, do nothing.
 *  Insert the new job at the front of the queue.
 */
void
job_queue_add(JobQueue*, Job*);

/**
 * Remove a job from a queue and return.
 * If there's no job, return NULL;
 */
Job*
job_queue_pop(JobQueue*);

#endif
