#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define PHILOSOPHERS_NUM 3
#define PHILOSOPHERS_EATING_TIME 5
#define PHILOSOPHERS_THINKIG_TIME 2

sem_t forks_sem;
sem_t waiter_sem;

void philosopher_func(void* arg)
{
	int id = (int)arg;
	printf("philosopher[%d]: start\n", id);

	while(1)
	{
		printf("philosopher[%d]: try enter\n", id);
		sem_wait(&waiter_sem);

		//philosopher in room
		printf("philosopher[%d]: waiting for FIRST fork\n", id);
		sem_wait(&forks_sem);
		printf("philosopher[%d]: waiting for SECOND fork\n", id);
		sem_wait(&forks_sem);

		printf("philosopher[%d]: eating\n", id);
		sleep(PHILOSOPHERS_EATING_TIME);

		sem_post(&forks_sem);
		sem_post(&forks_sem);
		//philosopher in room

		printf("philosopher[%d]: exit\n", id);
		sem_post(&waiter_sem);

		printf("philosopher[%d]: thinking\n", id);
		sleep(PHILOSOPHERS_THINKIG_TIME);
	}
}

int main()
{
	pthread_t threads[PHILOSOPHERS_NUM];

	sem_init(&forks_sem, 0, PHILOSOPHERS_NUM);
	sem_init(&waiter_sem, 0, PHILOSOPHERS_NUM-1);

	for(int i=0; i<PHILOSOPHERS_NUM; i++)
	{
		if(pthread_create(&threads[i],
		NULL,
		(void *)philosopher_func, 
		(void *)i) != 0)
		{
			perror("thread_create");
			return 1;
		}
	}

	while(1)
	{
		if(getchar() == 113) //113 is 'q' ASCII value
		{
			break;
		}
	}

	return 0;
}