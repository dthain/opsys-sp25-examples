/*
A skeleton for solving the GPU Dataset problem.
Ensure that (up to) four threads may use the GPU at once,
but only if they are operating on the same dataset.
Add whatever global variables are needed, and then implement
gpu_enter() and gpu_exit().
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int nthreads = 100;
int sleeptime = 1000000;

void gpu_enter( int dataset )
{
	/* put your code here */
}

void gpu_exit()
{
	/* put your code here */
}

void * user_thread( void * arg )
{
  while(1) {
   int d = rand() % 10;
   printf("thread %d wants to use gpu with dataset %d\n",(int)pthread_self(),d);
   gpu_enter(d);
   printf("thread %d using gpu with dataset %d\n",(int)pthread_self(),d);
   usleep(500000);
   printf("thread %d done using gpu with dataset %d\n",(int)pthread_self(),d);
   gpu_exit(d);
  }
}

int main( int argc, char *argv[] )
{
  pthread_t tid[nthreads];
  int i;

  srand(time(0));

  for(i=0;i<nthreads;i++) {
    pthread_create(&tid[i],0,user_thread,0);
  }

  for(i=0;i<nthreads;i++) {
    void *result;
    pthread_join(tid[i],&result);
  }

  printf("main: all threads done.\n");

  return 0;
}

