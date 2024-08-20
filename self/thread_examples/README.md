# Multithreading and Synchronization Examples

pthreads, mutex, condition variables, semaphores를 사용한 멀티스레딩 및 동기화 예제들이 포함되어 있습니다. 
각 파일에 대한 간략한 설명은 아래와 같습니다.

## ex_1. Thread Example 1

기본적인 thread 생성과 join을 다루는 예제입니다.

```c
pthread_create(&thrdID, NULL, printMsg, argv[1]);
pthread_join(thrdID, NULL);
```

## ex_2. Thread Example 2

thread가 종료 시 상태값을 반환하는 방법을 보여줍니다.

```c
pthread_join(thrdID, (void **)&status);
printf("Thread exited with status %d\n", *status);
```

## ex_3. Mutex Example

shared buffer에 대한 접근을 mutex로 보호하여 producer와 consumer 간의 race condition을 방지합니다.

```c
pthread_mutex_lock(&bufLock);
buf[in] = getchar();
pthread_mutex_unlock(&bufLock);
```

## ex_4. Condition Variable Example

condition variable을 사용하여 buffer가 가득 찼거나 비어있을 때 thread가 대기하도록 합니다.

```c
pthread_cond_wait(&notFull, &bufLock);
pthread_cond_signal(&notEmpty);
```
## ex_5. Semaphore Example with Main Thread Consumer

consumer가 main thread에서 실행되고, producer는 별도 thread에서 실행됩니다.

```c
pthread_create(&producer_thread, NULL, producer, buffer);
consumer(buffer);
```

## ex_5_2. Semaphore Example

semaphore를 사용해 producer-consumer 문제를 해결합니다.

```c
sem_wait(&empty);
buf[in] = getchar();
sem_post(&full);
```
