// p.28
// Seamphore

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// Delcaration of semaphore
sem_t empty, full;

// producer function
void producer(char *buf) {
  int in = 0;
  for (;;) {
    sem_wait(&empty);
    buf[in] = getchar();
    in = (in + 1) % MAX_SIZE;
    sem_post(&full);
  }
}

// consumer function
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
  pthread_t producer_thread, consumer_thread;

  // Initialize Semaphore
  sem_init(&empty, 0, MAX_SIZE);
  sem_init(&full, 0, 0);

  pthread_create(&producer_thread, NULL, (void *)producer, &buffer);
  pthread_create(&consumer_thread, NULL, (void *)consumer, &buffer);

  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  sem_destroy(&empty);
  sem_destroy(&full);

  return 0;
}
