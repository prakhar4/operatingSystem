//with synchronisation using semaphore

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t pid[2];
int now;
sem_t lockz;

void *doThis(void *arg)
{
	int i=0;
	printf("\nWaiting to get into the critical section of %d ",now);
/*	for(i=0;i<0xfffff;i++);*/
	sem_wait(&lockz);
	now++;
	printf("\nThe job %d has started in critical section",now);
	for(i=0;i<0xfffff;i++);
	printf("\nThe job %d is over from critical section",now);
	sem_post(&lockz);
}

int main()
{
	int i,j,er;
	sem_init(&lockz,0,1);

	if(er)
		printf("\nFailed to get the lock initialisation ");

	while(i<2){
		er=pthread_create(&pid[i],NULL,&doThis,NULL);
		if(er){
			printf("\nThere is error in creating process");
			break;
		}
		
		i++;
	}
	pthread_join(pid[0],NULL);
	pthread_join(pid[1],NULL);
	sem_destroy(&lockz);
	
	return 0;
}












