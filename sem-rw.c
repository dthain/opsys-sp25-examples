/*
A complete example of using semaphores to solve the readers-writers problem.
Each thread either calls read_lock/unlock or write_lock/unlock prior
to reading or writing the global variable "value".  Carefully examine
the output to be satisfied that the solution is doing the right thing.
Can you modify the code to eliminate starvation of writer threads?
*/


#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

sem_t mutex;
sem_t writelock;
int   readcount=0;
int   value = 0;

int nthreads = 100;
int sleeptime = 10000; /* microseconds */

void read_lock()
{
  sem_wait(&mutex);
  readcount++;
  if(readcount==1) sem_wait(&writelock);
  sem_post(&mutex);
}

void read_unlock()
{	
  sem_wait(&mutex);
  readcount--;
  if(readcount==0) sem_post(&writelock);
  sem_post(&mutex);
}

void write_lock()
{
  sem_wait(&writelock);
}

void write_unlock()
{
  sem_post(&writelock);
}

void * reader_writer_thread( void * arg )
{
  while(1) {
    if(rand()%10 < 8) {
      printf("thread %d wants to read\n",(int)pthread_self());
      read_lock();
      printf("thread %d reading (%d readers)\n",(int)pthread_self(),readcount);
      int v = value;
      usleep(rand()%sleeptime);
      printf("thread %d read value %d\n",(int)pthread_self(),v);
      read_unlock();
    } else {
      int v = rand()%100;
      printf("thread %d wants to write\n",(int)pthread_self());
      write_lock();
      printf("thread %d writing value %d\n",(int)pthread_self(),v);
      value = v;
      usleep(rand()%sleeptime);
      printf("threed %d done writing\n",(int)pthread_self());
      write_unlock();
    }
  }
}

int main( int argc, char *argv[] )
{
  pthread_t tid[nthreads];
  int i;

  srand(time(0));

  sem_init(&mutex,0,1);
  sem_init(&writelock,0,1);

  readcount = 0;
  value = 0;

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
