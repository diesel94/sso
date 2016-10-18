#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int error(char* errmsg)
{
	perror(errmsg);
	return 1;
}

char* get_command(int key)
{
	switch(key)
	{
		case 44:
		return "seek -5\n";

		case 46:
		return "seek 5\n";

		case 112:
		return "pause\n";

		case 114:
		return "resume\n";

		default:
		return "";
	}
}

int main()
{
	const char* node_path = "/tmp/node";
	char* command;
	char key = 0;
	int node_fh;

	node_fh = open(node_path, O_RDWR);
	if(node_fh == -1)
	{
		return error("node file open failed");
	}

	system("stty raw");

	do
	{
		key = getchar();
		command = get_command(key);
		write(node_fh, command, (sizeof(command)));
		printf("[%s] ", command);
	}
	while(key != 113);

	system("stty cooked");

	close(node_fh);
	return 0;
}

