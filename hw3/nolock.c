#include <pthread.h>
#include <stdio.h>
int Global;
void *Thread1(void *x) {
  Global = 42;
  printf("%d\n",Global);
  return x;
}
void *Thread2(void *x) {
  Global = 43;
  printf("%d\n",Global);
  return x;
}

int main() {
  pthread_t t1,t2;
  pthread_create(&t1, NULL, Thread1, NULL);
  pthread_create(&t2, NULL, Thread2, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return Global;
}
