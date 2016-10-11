#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int error(char* errmsg)
{
	printf("%s", errmsg);
	return 1;
}

int main()
{
	int fd[2], nbytes_read, nbytes_write, buff_size;
	int status;
	pid_t chpid;


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
	
	}
	else
	{
	}
}
