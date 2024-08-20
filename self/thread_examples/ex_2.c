// p.12
// Thread (2)

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *printMsg(void *msg) {
  int *status = (int *)malloc(sizeof(int));

  if (status == NULL) {
    perror("Failed to allocate memory");
    pthread_exit(NULL);
  }

  *status = 0;

  printf("%s\n", (char *)msg);
  pthread_exit(status);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <message>\n", argv[0]);
    return 1;
  }

  pthread_t thrdID;
  int *status = NULL;

  printf("creating a new thread\n");

  if (pthread_create(&thrdID, NULL, printMsg, (void *)argv[1]) != 0) {
    perror("Failed to create thread");
    return 1;
  }

  printf("created thread %p\n", (void *)thrdID);

  if (pthread_join(thrdID, (void **)&status) != 0) {
    perror("Failed to join thread");
    return 1;
  }

  printf("Thread %p exited with status %d\n", (void *)thrdID, *status);
  free(status);
  return 0;
}
