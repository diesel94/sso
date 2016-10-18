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

int main()
{
	const char* node_path = "/tmp/node";
	const char msg[80];	
	int node_fh, i, read_bytes;	
	
	node_fh = open(node_path, O_RDWR);
	if(node_fh == -1)
	{
		return error("node file open failed");
	}
	
	for(i=0; i<10; i++)
	{
		read_bytes = read(node_fh, &msg, sizeof(msg));
		printf("[read %i bytes:%i] %s \n", i, read_bytes, msg);
		sleep(1);
	}
	
	close(node_fh);
	return 0;	
}

