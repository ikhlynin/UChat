#include "client.h"

void mx_connect(int argc, char **argv)
{
    if (!argv[1] || !argv[2])
    {
        mx_printstr("Too few arguments");
        return;
    }
    ip = argv[1];
    port = argv[2];

    //server params

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(mx_atoi(port));

    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        mx_printstr("connection with the server failed...\n");
        //exit(0);
    }
    else
    {
        mx_printstr("connected to the server..\n");
    }

}
