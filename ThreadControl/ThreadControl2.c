#include<pthread.h>

int controller = 0;

void print(char *p)
{
  printf("%s",p);
}

void * threadMethod1(void *arg)
{
  while(1)
  {
    if(controller == 3)
      break;
  }
  print("I am thread 1st\n");
  controller = 1;
  pthread_exit(NULL);
}

void * threadMethod2(void *arg)
{
  while(1)
  {
    if(controller == 1)
      break;
  }
  print("I am thread 2nd\n");
  controller = 2;
  pthread_exit(NULL);
}

void * threadMethod3(void *arg)
{
  while(1)
  {
    if(controller == 0)
      break;
  }
  print("I am thread 3rd\n");
  controller = 3;
  pthread_exit(NULL);
}

int main(void)
{
  pthread_t tid1, tid2, tid3;
  int i = 0;

  printf("Before creating the threads\n");
  if( pthread_create(&tid1, NULL, threadMethod1, NULL) != 0 )
        printf("Failed to create thread1\n");
  if( pthread_create(&tid2, NULL, threadMethod2, NULL) != 0 )
        printf("Failed to create thread2\n");
   sleep(3);
  if( pthread_create(&tid3, NULL, threadMethod3, NULL) != 0 )
        printf("Failed to create thread3\n");
 /*
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);*/
  sleep(10);
 exit(0);
}
