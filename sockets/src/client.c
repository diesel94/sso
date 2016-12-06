#include "common.h"

int sockfd;

void sig_handler(int sig)
{
    if(sig == SIGINT)
    {
        shutdown(sockfd, SHUT_RDWR);
        close(sockfd);
        printf("client get SIGINT, closing socket\n");
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
    int portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    
    assign_sig_handler(SIGINT);

    if(argc < 4)
    {
       error("usage: hostname port message\n");
    }

    portno = atoi(argv[2]);
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { 
        error("ERROR opening socket");
    }

    if((server = gethostbyname(argv[1])) == NULL)
    {
        error("given host not exist\n");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,
    sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
    }

    bzero(buffer,256);

    while(1)
    {
        strncpy(buffer, argv[3], 256);
        
        if((n = write(sockfd,buffer,strlen(buffer))) < 0)
        {
            error("ERROR writing to socket");
        }
        printf("snet to server: %s\n", buffer);

        bzero(buffer,256);

        if((n = read(sockfd,buffer,255)) < 0)
        {
            error("ERROR reading from socket");
        }
        printf("%s\n",buffer);

        sleep(2);
        printf("\n");
    }

    return 0;
}