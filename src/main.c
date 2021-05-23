#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "manager.h"

#define POOL_NUM 4
#define JOB_NUM 100

typedef struct Config {
  int id;
  int time;
  int display;
} Config;

void function(void* arg) {
  Config* config = (Config*) arg;
  // printf("\n======================%d start, will wait %d\n", config->id, config->time);
  // sleep(config->time); // should not use sleep. sleep will stop the whole process.
  int begin = 100;
  int end = 10000 + rand();
  int sum = 1;
  for(int i = begin; i <= end; i++) {
    sum += begin * end;
  }
  printf("\n%d => %d\n", config->id, config->display);
}

int main() {
  srand(time(NULL));
  // create pool:
  Pool* pool = pool_create(POOL_NUM);
  
  for(int i = 0; i < JOB_NUM; i++) {
    printf("input time and display\n");
    int time, display;
    scanf("%d%d", &time, &display);
    // time = 1;
    // display = 2;

    Job* job = (Job*) malloc (sizeof(Job));
    if(job == NULL) {
      perror("job malloc");
    }

    job->func = function;
    
    Config* config = (Config*) malloc (sizeof(Config));
    config->id = i + 1;
    config->time = time;
    config->display = display;

    job->arg = (void*)config;
    
    // job_queue_add(pool->jobQueue, job);
    pool_push_job(pool, job);
  }

  getchar();
}