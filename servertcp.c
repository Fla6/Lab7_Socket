#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/un.h>

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, servlen, n;
    socklen_t clilen;
    struct sockaddr_un cli_addr = {0};
    struct sockaddr_un serv_addr = {0};
    char buf[50] = {0};

    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, argv[1]);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        printf("Error creating socket\n");
        exit(EXIT_FAILURE);
    }
    
    if (bind(sockfd, (struct sockaddr *)&serv_addr, servlen) < 0)
    {
        printf("Error binding socket\n");
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        printf("Error accepting socket\n");
        exit(EXIT_FAILURE);
    }

    
    printf("Connection has been established\n");
    n = read(newsockfd, buf, 50);
    write(1, buf, n);
    write(newsockfd, "I got your message\n", 19);
    close(newsockfd);
    close(sockfd);
    return 0;
}