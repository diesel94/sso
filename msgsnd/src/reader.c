#include <stdlib.h>
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>

struct message
{
	long type;
	char text[8];
} msg;

int result, msqid;
long msg_typ;

int main(int argc, char* argv[])
{	
	if(argc < 3)
	{
		perror("msq and msgtypy required");
	}

	msqid = atoi(argv[1]);
	msg_typ = atoi(argv[2]);

	result = msgrcv(msqid, (void *) &msg, sizeof(msg.text), msg_typ, IPC_NOWAIT);
	if(result == -1)
	{
		perror("msgrcv error");
		return 1;
	}
	printf("msg: %s\n", msg.text);
	
	return 0;
}
