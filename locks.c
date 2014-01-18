#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t lock;
int globe=2;

void *doThis(void *arg)
{
	int i,j;
	int n=*((int *)arg);
	printf("\nInside the function from %d ",n);
	for(i=0;i<0xffffff;i++);
	sem_wait(&lock);
	printf("\nThis is running in critical section ");
	printf("\nValue of globe is %d",globe);
	globe++;	
	printf("\nValue of globe is %d",globe);
	printf("\nExiting critical section");
	sem_post(&lock);

}

int main()
{
	int er,i,j;
	pthread_t pid[2];
	er=sem_init(&lock,0,1);
	if(er)
		printf("\nError while semaphore");
	
	int a[2];
	a[0]=0;
	a[1]=1;
	i=0;
	
	while(i<2){
		er=pthread_create(&pid[i],NULL,&doThis,&a[i]);
		if(er){
			printf("\nError crreating thread ");
			break;
		}
		i++;
	}
	
	pthread_join(pid[0],NULL);	
	pthread_join(pid[1],NULL);
	sem_destroy(&lock);
	return 0;
}


