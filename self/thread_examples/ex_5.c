// p.28
// Seamphore

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// Declaration of semaphores
sem_t empty, full;

// Producer function
void *producer(void *arg) {
  char *buf = (char *)arg;
  int in = 0;
  for (;;) {
    sem_wait(&empty);
    buf[in] = getchar();
    in = (in + 1) % MAX_SIZE;
    sem_post(&full);
  }
  return NULL;
}

// Consumer function
void consumer(char *buf) {
  int out = 0;
  for (;;) {
    sem_wait(&full);
    putchar(buf[out]);
    out = (out + 1) % MAX_SIZE;
    sem_post(&empty);
  }
}

int main() {
  char buffer[MAX_SIZE];
  pthread_t producer_thread;

  sem_init(&empty, 0, MAX_SIZE);
  sem_init(&full, 0, 0);

  pthread_create(&producer_thread, NULL, producer, buffer);

  consumer(buffer);

  pthread_join(producer_thread, NULL);

  sem_destroy(&empty);
  sem_destroy(&full);

  return 0;
}
