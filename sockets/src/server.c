#include "common.h"
#include <pthread.h>

int sockfd;

void conn_func(void* arg)
{
     int connsockfd = (int)arg;
     int n;
     char buffer[256];
     bzero(buffer,256);
    
     while(1)
     {
        n = read(connsockfd,buffer,255);
        if(n == 0)
        {
            printf("EOF closing connection\n");
        }
        if(n < 0)
        {
            printf("ERROR reading from socket");
        }

        printf("Here is the message: %s\n",buffer);

        n = write(connsockfd,"server got your message",25);
        if(n < 0)
        {
            printf("ERROR writing to socket, closing connection\n");
            break;
        }

        printf("\n");
     }
     close(connsockfd);
}

void sig_handler(int sig)
{
    if(sig == SIGINT)
    {
        close(sockfd);
        printf("server get SIGINT, closing socket\n");
        exit(0);
    }
}

void assign_sig_handler(int sig)
{
	if(signal(sig, sig_handler) == SIG_ERR)
	{
		error("signal");
	}
}

int main(int argc, char *argv[])
{
     int newsockfd, portno;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

     if(argc < 2)
     {
         error("usage: port\n");
     }

     assign_sig_handler(SIGINT);
     sigignore(SIGPIPE);

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     { 
        error("ERROR opening socket");
     }

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if(bind(sockfd,
     (struct sockaddr *) &serv_addr,
     sizeof(serv_addr)) < 0)
     {
             error("ERROR on binding");
     }
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     while(1)
     {
        if((newsockfd = accept(sockfd, 
        (struct sockaddr *) &cli_addr, &clilen)) < 0)
        { 
            error("ERROR on accept");
        }

        pthread_t client_thread;
        if(pthread_create(&client_thread,
		NULL,
		(void *)conn_func, 
		(void *)newsockfd) != 0)
		{
			error("thread_create");
            close(newsockfd);
		}
     }

     printf("server exit main loop\n");
     close(sockfd);

     return 0; 
}