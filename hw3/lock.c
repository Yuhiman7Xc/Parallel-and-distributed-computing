#include <pthread.h>
#include <stdio.h>
pthread_mutex_t mutex;
int Global;
void *Thread1(void *x) {
  pthread_mutex_lock(&mutex);
  Global = 42;
  printf("%d\n",Global);
  pthread_mutex_unlock(&mutex);
  return x;
}
void *Thread2(void *x) {
  pthread_mutex_lock(&mutex);
  Global = 43;
  printf("%d\n",Global);
  return x;
  pthread_mutex_unlock(&mutex);
}

int main() {
  pthread_t t1,t2;
  pthread_mutex_init(&mutex,NULL);
  pthread_create(&t1, NULL, Thread1, NULL);
  pthread_create(&t2, NULL, Thread2, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return Global;
}
