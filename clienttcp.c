#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/un.h>

int main(int argc, char *argv[])
{
    int sockfd, servlen, n;
    struct sockaddr_un serv_addr = {0};
    char buffer[50] = {0};

    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, argv[1]);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        printf("Error creating socket\n");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, servlen) < 0)
    {
        printf("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Enter your message: ");
    fgets(buffer, 49, stdin);
    write(sockfd, buffer, strlen(buffer));
    n = read(sockfd, buffer, 50);
    printf("Return message:\n");
    write(1, buffer, n);
    close(sockfd);
    return 0;
}