#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num+4)%N
#define RIGHT (ph_num+1)%N

pthread_t pid[N];
sem_t s[N];
int state[N];
sem_t mutex;
int phil[]={0,1,2,3,4};

void test(int ph_num)
{
/*	sem_wait(&mutex);*/
	if(state[ph_num]==HUNGRY && LEFT!=EATING && RIGHT!=EATING)
	{
		state[ph_num]=EATING;
		printf("\nPhilosopher is Eating %d",ph_num+1);
		sem_post(&s[ph_num]);
	}
/*	sem_post(&mutex);*/
}

void take_fork(int ph_num)
{
	sem_wait(&mutex);
	state[ph_num]=HUNGRY;
	printf("\nPhilosopher %d is HUNGRY",ph_num+1);	
	test(ph_num);

	sem_post(&mutex);
	sem_wait(&s[ph_num]);
}

void put_fork(int ph_num)
{
	sem_wait(&mutex);
	state[ph_num]=THINKING;
	printf("\nPhilosopher %d has put down forks %d and %d",ph_num+1,ph_num+1,(ph_num+2)%N);
	printf("\nPhilosopher %d is THINKING",ph_num+1);
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}


void *philosopher(void *arg)
{
	int num=*((int *)arg);
	while(1)
	{
		sleep(1);
		take_fork(num);
		put_fork(num);	
	}
}



int main()
{
	int i,j,k;
	
	sem_init(&mutex,0,1);
	for(i=0;i<N;i++)
		sem_init(&s[i],0,0);
		
	for(i=0;i<N;i++)
	{
		pthread_create(&pid[i],NULL,&philosopher,&i);
		printf("\nPhilosopher %d is thinking ",i+1);
	}
	for(i=0;i<N;i++)
		pthread_join(pid[i],NULL);

}

