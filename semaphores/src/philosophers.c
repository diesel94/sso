#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#define PHILOSOPHERS_NUM 5
#define PHILOSOPHERS_EATING_TIME 5
#define PHILOSOPHERS_THINKIG_TIME 2

pthread_t threads[PHILOSOPHERS_NUM];
sem_t forks_sem;
sem_t waiter_sem;
char* philosophers_status[PHILOSOPHERS_NUM];

void philosopher_func(void* arg)
{
	printf("func\n");
	int id = (int)arg;
	philosophers_status[id] = "START";

	while(1)
	{
		philosophers_status[id] = "TRY ENTER";
		sem_wait(&waiter_sem);

		philosophers_status[id] = "WAIT FIRST FORK";
		sem_wait(&forks_sem);

		philosophers_status[id] = "WAIT SECOND FORK";
		sem_wait(&forks_sem);

		philosophers_status[id] = "EAT";
		sleep(PHILOSOPHERS_EATING_TIME);

		sem_post(&forks_sem);
		sem_post(&forks_sem);

		philosophers_status[id] = "EXIT";
		sem_post(&waiter_sem);

		philosophers_status[id] = "THINK";
		sleep(PHILOSOPHERS_THINKIG_TIME);
	}
}

void update_table()
{
	for(int i=0; i<PHILOSOPHERS_NUM; i++)
	{
		printf("[%d]: %s\n", i, philosophers_status[i]);
	}
}

void clean()
{
	for(int i=0; i<PHILOSOPHERS_NUM; i++)
	{
		if(pthread_cancel(threads[i]) != 0)
		{
			perror("pthread_cancel");
			exit(1);
		}
	}

	sem_destroy(&forks_sem);
	sem_destroy(&waiter_sem);

	exit(0);
}

void sig_handler(int sig)
{
	if(sig == SIGABRT)
	{
		printf("[SIGABRT]\n");
		clean();
		
	}
	else if(sig == SIGUSR1)
	{
		printf("[SIGUSR1]\n");
		update_table();
	}
}

void assign_sig_handler(int sig)
{
	if(signal(sig, sig_handler) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}
}

void main()
{
	sem_init(&forks_sem, 0, PHILOSOPHERS_NUM);
	sem_init(&waiter_sem, 0, PHILOSOPHERS_NUM-1);

	assign_sig_handler(SIGABRT);
	assign_sig_handler(SIGUSR1);

	for(int i=0; i<PHILOSOPHERS_NUM; i++)
	{
		if(pthread_create(&threads[i],
		NULL,
		(void *)philosopher_func, 
		(void *)i) != 0)
		{
			perror("thread_create");
			exit(1);
		}
	}

	while(1)
	{
		sleep(1);
	}
}