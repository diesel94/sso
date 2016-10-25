#include <stdlib.h>
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>

struct message
{
	long type;
	char text[8];
} msg;

int result, msqid, i;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		perror("msg type required");
	}
	msqid = msgget(IPC_PRIVATE, 0600|IPC_CREAT);
	printf("msqid: %d\n", msqid);
	msg.type = atoi(argv[1]);

	strcpy(msg.text, "Hello");
	for(i=0; i < 10000; i++)
	{
		result = msgsnd(msqid, (void *) &msg, sizeof(msg.text), IPC_NOWAIT);
	
		if(result == -1)
		{
			perror("msgsnd error");
			printf("sneds count: %d\n", i);
			return 1;
		}
	}
	return 0;
	
}
