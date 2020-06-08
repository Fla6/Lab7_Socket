#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

int main()
{
    char buff[50] = {0};
	struct sockaddr_in servaddr = {0};
    struct sockaddr_in cliaddr = {0};
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}
	
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(12344);
    cliaddr.sin_addr.s_addr = INADDR_ANY;

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(12345);
	servaddr.sin_addr.s_addr = INADDR_ANY;

    int rc = bind(sockfd, (const struct sockaddr *)&cliaddr, 
		sizeof(cliaddr));
		
	if(rc == -1)
	{
		perror("failed to bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
    socklen_t len = 0;
	while (1)
    {
        printf("Client: ");
        fgets(buff, 49, stdin);
        int n = sendto(sockfd, (const char *)buff, 50,
		0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        if(n ==-1)
        {
            perror("failed to send");
        }
        printf("Server: ");
        recvfrom(sockfd, (char *)buff, 50, MSG_WAITALL, 0, &len);
        //recvfrom(sockfd, (char *)buff, 50, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        buff[n] = '\n';
        printf("%s", buff);
    }
	close(sockfd);
    return 0;
}