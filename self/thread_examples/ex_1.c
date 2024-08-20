// p.9
// Thread (1)

#include <pthread.h>
#include <stdio.h>

void *printMsg(char *msg) {
  printf("%s\n", msg);
  return NULL;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <message>\n", argv[0]);
    return 1;
  }

  pthread_t thrdID;

  printf("creating a new thread\n");
  pthread_create(&thrdID, NULL, (void *)printMsg, (void *)argv[1]);
  printf("created thread %p\n", thrdID);
  pthread_join(thrdID, NULL);

  return 0;
}
