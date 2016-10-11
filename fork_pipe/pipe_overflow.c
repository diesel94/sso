#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int error(char* errmsg)
{
	printf("%s", errmsg);
	return 1;
}

int main()
{
	int fd[2], i;
	size_t nbytes_read, nbytes_write, buff_size;
	int status;
	pid_t chpid;
	char msg[] = "H";
	char msgbuff[80];
	
	if(pipe(fd) == -1)
	{
		return error("failed to pipe!\n");
	}

	if((chpid = fork()) == -1)
	{
		return error("faild to fork!\n");
	}
	if(chpid == 0)
	{
		close(fd[1]);
		printf("[child] sleep 5 sec\n");
		sleep(5);
		printf("[child] reading msg from pipe\n");
		nbytes_read = read(fd[0], msgbuff, sizeof(msgbuff));
		if(nbytes_read > 0)
		{
			printf("[child] msg from parent: %s\n", msgbuff);
		}
		else
		{
			return error("read failed!\n");
		}
		
		return 0;
	}
	else
	{
		close(fd[0]);
		printf("[parent] start sending msgs...\n");
		for(i=0; i<10000; i++)
		{
			if(nbytes_write = write(fd[1], &msg, (strlen(msg) + 1) > 0))
			{	
				buff_size += nbytes_write;
				printf("bytes: %d\n", buff_size);
			}
			else
			{
				return error("[parent] write failed");
			}
		}
	}
	
	printf("[parent] waitng for child process\n");
	chpid = wait(&status);
	printf("[parent] process %d exit\n", chpid);
	
	return 0;
}
