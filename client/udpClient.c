// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main(int argc, char * ( argv[] ))
{
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from client";
    char path[1035];
    FILE *fp;

    struct hostent *h;


    struct sockaddr_in servaddr;

    if (argc < 2)
    {
        printf("Debe ejecutar %s (nombre de host)\n", argv[0]);
        exit(-1);
    }

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    if (h = gethostbyname(argv[1]))
    {
        memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);
    }
    else
    {
        herror("DNS error");
        exit(-1);
    }

    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    sendto(sockfd, (const char *)argv[2], strlen(hello),
           MSG_CONFIRM, (const struct sockaddr *)&servaddr,
           sizeof(servaddr));

    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                 MSG_WAITALL, (struct sockaddr *)&servaddr,
                 &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    close(sockfd);
    return 0;
}
