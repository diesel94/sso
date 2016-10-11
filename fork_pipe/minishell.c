#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

int error(char* errmsg)
{
	printf("%s", errmsg);
	return 1;
}

int main()
{
	int fd[2], stdin_sv, stdout_sv;
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
		close(fd[1]);
		stdin_sv = dup(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		system("sort");	
		dup2(stdin_sv, STDIN_FILENO);
	}
	else
	{
		close(fd[0]);
		stdout_sv = dup(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		system("ls");
		dup2(stdout_sv, STDOUT_FILENO);
	}

	return 0;
}
