/*
Skeleton code for solving the readers-writers problem using a monitor.
Complete the solution by adding any necessary global variables,
and implement the functions read_lock, write_lock, etc.
Carefully examine the output generated to be sure that you are only
admitting multiple readers at once or a single writer at once.
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int nthreads = 100;
int sleeptime = 10000; /* microseconds */
int value = 0;

void read_lock()
{
	/* put your code here */
}

void read_unlock()
{	
	/* put your code here */
}

void write_lock()
{
	/* put your code here */
}

void write_unlock()
{
	/* put your code here */
}

void * reader_writer_thread( void * arg )
{
  while(1) {
    if(rand()%10 < 8) {
      printf("thread %d wants to read\n",(int)pthread_self());
      read_lock();
      printf("thread %d reading\n",(int)pthread_self());
      int v = value;
      usleep(rand()%sleeptime);
      printf("thread %d done reading value %d\n",(int)pthread_self(),v);
      read_unlock();
    } else {
      int v = rand()%100;
      printf("thread %d wants to write\n",(int)pthread_self());
      write_lock();
      printf("thread %d writing value %d\n",(int)pthread_self(),v);
      value = v;
      usleep(rand()%sleeptime);
      printf("thread %d done writing value %d\n",(int)pthread_self(),v);
      write_unlock();
    }
  }
}

int main( int argc, char *argv[] )
{
  pthread_t tid[nthreads];
  int i;

  srand(time(0));

  for(i=0;i<nthreads;i++) {
    pthread_create(&tid[i],0,reader_writer_thread,0);
  }

  for(i=0;i<nthreads;i++) {
    void *result;
    pthread_join(tid[i],&result);
  }

  printf("main: all threads done.\n");

  return 0;
}
