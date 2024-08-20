// p.17
// Mutex

#include <pthread.h>
#include <stdio.h>

#define MAX_SIZE 5

pthread_mutex_t bufLock;
int count;

void producer(char *buf) {
  for (;;) {
    while (count == MAX_SIZE)
      ;
    pthread_mutex_lock(&bufLock);
    buf[count] = getchar();
    count++;
    pthread_mutex_unlock(&bufLock);
  }
}

void consumer(char *buf) {
  for (;;) {
    while (count == 0)
      ;
    pthread_mutex_lock(&bufLock);
    putchar(buf[count - 1]);
    count--;
    pthread_mutex_unlock(&bufLock);
  }
}

int main() {
  char buffer[MAX_SIZE];
  pthread_t p;

  count = 0;

  pthread_mutex_init(&bufLock, NULL);
  pthread_create(&p, NULL, (void *)producer, &buffer);
  consumer(&buffer);

  return 0;
}
