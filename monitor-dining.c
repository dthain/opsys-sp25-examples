/*
A skeleton for solving the dining philosophers problem with a monitor.
Add whatever global variables are needed, and implement pickup() and putdown()
to synchronize the diners so that deadlock is impossible.
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NFORKS 5

int sleeptime = 1000000; /* microseconds */

void pickup( int id )
{
	/* put your code here */
}

void putdown( int id )
{
	/* put your code here */
}

void * philosopher_thread( void * arg )
{
  int *id_pointer = (int*) arg;
  int id = *id_pointer;

  while(1) {
    printf("thread %d sleeping\n",id);
     usleep(rand()%sleeptime);
     printf("thread %d hungry\n",id);
     pickup(id);
     printf("thread %d eating\n",id);
     usleep(rand()%sleeptime);
     putdown(id);
  }
}

int main( int argc, char *argv[] )
{
  pthread_t threadid[NFORKS];
  int id[NFORKS];
  int i;

  srand(time(0));

  for(i=0;i<NFORKS;i++) {
    id[i] = i;
    pthread_create(&threadid[i],0,philosopher_thread,&id[i]);
  }

  for(i=0;i<NFORKS;i++) {
    void *result;
    pthread_join(threadid[i],&result);
  }

  printf("main: all threads done.\n");

  return 0;
}

