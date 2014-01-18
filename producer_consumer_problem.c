#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXM 6

pthread_mutex_t lock;
pthread_mutex_t empty;
int first;
int last=-1;
int que[6];
int numQue;

void putOn(int num)
{
	pthread_mutex_lock(&lock);
/*	int num=*((int*)arg);*/
	last++;
	last%=MAXM;
	que[last]=num;
	numQue++;
	pthread_mutex_unlock(&lock);
	pthread_mutex_unlock(&empty);
	
}


int getOff()
{
	int num;
	while(numQue==0) pthread_mutex_lock(&empty);
	pthread_mutex_lock(&lock);
	num=que[first];
	first++;
	first%=MAXM;
	numQue--;
	pthread_mutex_unlock(&lock);
/*	pthread_mutex_lock(&empty);*/
	return num;
}


void *producer(void *arg)
{
	int i;
	int n=*((int *)arg);
	
	for(i=0;i<3;i++){
		printf("\nPutting on que %d",i+100*n);
		sleep(1);
		putOn(i+100*n);
		printf("\nPut %d on que",i+100*n);
	}

}

void *consumer(void *arg)
{
	int i,num;
	for(i=0;i<6;i++)
	{
		printf("\nTaking off que for next");
		num=getOff();
		printf("\nGetting %d",num);
	}

}





int main()
{
	pthread_t pid[3];
	int one=1;
	int two=2;
	pthread_mutex_init(&lock,NULL);
	pthread_mutex_init(&empty,NULL);
	pthread_create(&pid[0],NULL,&producer,&one);
	pthread_create(&pid[1],NULL,&producer,&two);
	pthread_create(&pid[2],NULL,&consumer,NULL);
	
	pthread_join(pid[0],NULL);
	pthread_join(pid[1],NULL);
	pthread_join(pid[2],NULL);
	pthread_mutex_destroy(&lock);		
	pthread_mutex_destroy(&empty);
}

