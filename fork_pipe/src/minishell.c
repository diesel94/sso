#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int error(char* errmsg)
{
	printf("%s", errmsg);
	return 1;
}

int main(int argc, char** argv)
{
	int fd[2];
	pid_t chpid;

	if(argc != 3)
	{
		return error("required 2 parameters\n");
	}

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
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execl("/bin/bash", "bash", "-c", argv[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execl("/bin/bash", "bash", "-c", argv[2]);
	}
	wait(NULL);
	return 0;
}
