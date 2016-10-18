#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void error(char* errmsg)
{
	printf("%s", errmsg);
	exit(1);
}

void main()
{
	const int msg_count = 100000;
	int fd[2], i;
	int nbytes_write, buff_size;
	pid_t chpid;
	char msg = 'H';
	char msgbuff[1];
	
	if(pipe(fd) == -1)
	{
		error("failed to pipe!\n");
	}

	if((chpid = fork()) == -1)
	{
		error("faild to fork!\n");
	}
	if(chpid == 0)
	{
		close(fd[1]);
		printf("[child] sleep 10 sec\n");
		sleep(10); 
		printf("[child start reading...\n");
		for(i = 0; i < msg_count; i++)
		{
			read(fd[0], &msgbuff, sizeof(msgbuff));
		}
		printf("[child] finish reading\n");

		close(fd[0]);
		exit(0);
	}
	else
	{
		close(fd[0]);
		printf("[parent] start sending msgs...\n");
		for(i = 0; i < msg_count; i++)
		{
			nbytes_write = write(fd[1], &msg, sizeof(msg));
			if(nbytes_write > -1)
			{
				buff_size += nbytes_write;
				printf("[parent] send bytes: %d\n", buff_size);
			}
			else
			{
				error("[parent] write failed\n");
			}
		}	
		printf("[parent] waitng for child process\n");
		chpid = wait(NULL);
		printf("[parent] process %d exit\n", chpid);

		close(fd[1]);
		exit(0);
	}
}
