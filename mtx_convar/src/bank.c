#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define ACCOUNTS_NUM 2
#define OPERATIONS_NUM 10

int accounts[ACCOUNTS_NUM];
pthread_cond_t conds[ACCOUNTS_NUM];
pthread_t threads[2];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void operation_func(void* arg)
{
    int value = (int)arg;
    int id = value > 0 ? 0 : 1;

    for(int i=0; i < OPERATIONS_NUM; i++)
    {
        pthread_mutex_lock(&mutex);
        while((accounts[0] - value) < 0)
        {
            pthread_cond_wait(&conds[0], &mutex);
        }

        while((accounts[1] - value) <  0)
        {
            pthread_cond_wait(&conds[1], &mutex);
        }

        accounts[0] -= value;
        accounts[1] += value;        
        pthread_mutex_unlock(&mutex);

        pthread_cond_broadcast(&mutex);

        printf("[%d] account1: %d, account2: %d\n", 
        id, accounts[0], accounts[1]);

        sleep(2);
    }

    exit(0);
}

void main()
{

    for(int i=0; i<ACCOUNTS_NUM; i++)
    {
        accounts[i] = 100 * (i+1);

        if(pthread_cond_init(&conds[i], NULL) != 0)
        {
            perror("pthread_cond_init");
            exit(1);
        }
    }

    if(pthread_create(&threads[0], NULL,
    (void *)operation_func, (void *)100) != 0)
    {
        perror("pthread_create");
        exit(1);
    }
    if(pthread_create(&threads[1], NULL,
    (void *)operation_func, (void *)-50) != 0)
    {
        perror("pthread_create");
        exit(1);
    }

    while(1)
	{
		sleep(1);
	}
}