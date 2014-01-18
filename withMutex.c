//with synchronisation

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t pid[2];
int now;
pthread_mutex_t lock;

void *doThis(void *arg)
{
	pthread_mutex_lock(&lock);
	int i=0;
	now++;
	printf("\nThe job %d has started",now);
	
	for(i=0;i<0xfffff;i++);
	
	printf("\nThe job %d is over",now);
	pthread_mutex_unlock(&lock);
}

int main()
{
	int i,j,er;
	er=pthread_mutex_init(&lock,NULL);
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
	pthread_mutex_destroy(&lock);

	return 0;
}
