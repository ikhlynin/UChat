#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "libmx.h"

#define LENGTH 2048

// Global variables
volatile sig_atomic_t flag = 0;
int sockfd = 0;
char name[45];

void str_overwrite_stdout()
{
	printf("%s", "> ");
	fflush(stdout);
}

void str_trim_lf(char *arr, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{ // trim \n
		if (arr[i] == '\n')
		{
			arr[i] = '\0';
			break;
		}
	}
}

void catch_ctrl_c_and_exit(int sig)
{
	flag = 1;
}

void send_msg_handler()
{
	char message[LENGTH] = {};
	char buffer[LENGTH + 45] = {};

	while (1)
	{
		str_overwrite_stdout();
		fgets(message, LENGTH, stdin);
		str_trim_lf(message, LENGTH);

		if (strcmp(message, "exit") == 0)
		{
			break;
		}
		else
		{
			sprintf(buffer, "%s: %s\n", name, message);
			send(sockfd, buffer, strlen(buffer), 0);
		}

		bzero(message, LENGTH);
		bzero(buffer, LENGTH + 45);
	}
	catch_ctrl_c_and_exit(2);
}

void recv_msg_handler()
{
	char message[LENGTH] = {};
	while (1)
	{
		int receive = recv(sockfd, message, LENGTH, 0);
		if (receive > 0)
		{
			printf("%s", message);
			str_overwrite_stdout();
		}
		else if (receive == 0)
		{
			break;
		}
		else
		{
			// -1
		}
		memset(message, 0, sizeof(message));
	}
}

void send_msg_to_serv(int sockfd, char *msg)
{
	int send_size = mx_strlen(msg);
	send(sockfd, &send_size, sizeof(int), 0);
	send(sockfd, msg, mx_strlen(msg), 0);
}
int accept_serv_resp(int sockfd)
{
	int res = -1;
	recv(sockfd, &res, sizeof(int), 0);
	return res;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: %s <port> <ip>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char passwd[45];

	char *ip = malloc(sizeof(char) * 15); //"10.11.2.8";
	strcpy(ip, argv[2]);
	int port = atoi(argv[1]);

	signal(SIGINT, catch_ctrl_c_and_exit);

	printf("Please enter your name: ");
	fgets(name, 45, stdin);
	str_trim_lf(name, strlen(name));

	printf("Please enter passwd: ");
	fgets(passwd, 45, stdin);
	str_trim_lf(passwd, strlen(passwd));

	if (strlen(name) > 45 || strlen(name) < 2)
	{
		printf("Name must be less than 30 and more than 2 characters.\n");
		return EXIT_FAILURE;
	}

	struct sockaddr_in server_addr;

	/* Socket settings */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(port);

	// Connect to Server
	int err = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (err == -1)
	{
		printf("ERROR: connect\n");
		return EXIT_FAILURE;
	}

	// Send name
	// send(sockfd, name, 45, 0);
	// send(sockfd, passwd, 45, 0);
	char *to_send = NULL;
	mx_str_concat(&to_send, "/log\1");
	mx_str_concat(&to_send, passwd);
	mx_str_concat(&to_send, "\1");
	mx_str_concat(&to_send, name);
	send_msg_to_serv(sockfd, to_send);
	mx_strdel(&to_send);
	printf("%d\n", accept_serv_resp(sockfd));

	printf("=== WELCOME TO THE CHATROOM ===\n");

	pthread_t send_msg_thread;
	if (pthread_create(&send_msg_thread, NULL, (void *)send_msg_handler, NULL) != 0)
	{
		printf("ERROR: pthread\n");
		return EXIT_FAILURE;
	}

	pthread_t recv_msg_thread;
	if (pthread_create(&recv_msg_thread, NULL, (void *)recv_msg_handler, NULL) != 0)
	{
		printf("ERROR: pthread\n");
		return EXIT_FAILURE;
	}

	while (1)
	{
		if (flag)
		{
			printf("\nBye\n");
			break;
		}
	}

	close(sockfd);

	return EXIT_SUCCESS;
}
