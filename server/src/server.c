#include "../inc/server.h"

#define MAX_CLIENTS 100
#define BUFFER_SZ 2048

sqlite3 *db = NULL;
static _Atomic unsigned int cli_count = 0;
static int uid = 10;

/* Client structure */

client_t *clients[MAX_CLIENTS];

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void send_msg_to_cli(int sockfd, char *msg)
{
	mx_printstr("sending -> ");
	print_to_send_str(msg);
	int send_size = mx_strlen(msg);
	send(sockfd, &send_size, sizeof(int), 0);
	send(sockfd, msg, mx_strlen(msg), 0);
}

void str_overwrite_stdout()
{
	printf("\r%s", "> ");
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

void print_client_addr(struct sockaddr_in addr)
{
	printf("%d.%d.%d.%d",
		   addr.sin_addr.s_addr & 0xff,
		   (addr.sin_addr.s_addr & 0xff00) >> 8,
		   (addr.sin_addr.s_addr & 0xff0000) >> 16,
		   (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

/* Add clients to queue */
void queue_add(client_t *cl)
{
	pthread_mutex_lock(&clients_mutex);

	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (!clients[i])
		{
			clients[i] = cl;
			break;
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

/* Remove clients to queue */
void queue_remove(int uid)
{
	pthread_mutex_lock(&clients_mutex);

	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (clients[i])
		{
			if (clients[i]->uid == uid)
			{
				clients[i] = NULL;
				break;
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

/* Send message to all clients except sender */
void send_message(char *s, int uid)
{
	pthread_mutex_lock(&clients_mutex);

	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (clients[i])
		{
			if (clients[i]->uid != uid)
			{
				if (write(clients[i]->sockfd, s, strlen(s)) < 0)
				{
					perror("ERROR: write to descriptor failed");
					break;
				}
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

void send_message2(char *s, client_t *dstcli, int uid)
{
	pthread_mutex_lock(&clients_mutex);
	if (write(dstcli->sockfd, s, strlen(s)) < 0) // send maessage
	{
		perror("ERROR: write to descriptor failed");
		return;
	}

	pthread_mutex_unlock(&clients_mutex);
}

void send_message_group(char *s, client_t **arr_cli, int ct_cl)
{ /////////////////////
	pthread_mutex_lock(&clients_mutex);

	for (int i = 0; i < ct_cl; i++)
	{
		if (write(arr_cli[i]->sockfd, s, strlen(s) + 1) < 0)
		{
			perror("ERROR: write to descriptor failed");
			return;
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

char **unfold_msg_from_cli(client_t *cli)
{
	int msg_len = 0;
	int response = -2;
	char *buf;
	char **result = NULL;
	if (recv(cli->sockfd, &msg_len, sizeof(int), 0) > 0 && msg_len > 0)
	{
		buf = mx_strnew(msg_len);
		if (recv(cli->sockfd, buf, msg_len, 0))
		{
			result = mx_strsplit(buf, '\1');
			response = 0;
		}
		else
		{
			response = -3;
		}
		mx_strdel(&buf);
	}
	return result;
}
// /user_get ..., /user_set ...

client_t *find_reciver(char *chat_name, int sockfd)
{
	client_t *res = NULL;
	for (int i = 0; i < cli_count; i++)
	{
		if (clients[i]->sockfd == sockfd)
			continue;
		if (clients[i]->name && mx_strstr(chat_name, clients[i]->name))
		{
			res = clients[i];
			break;
		}
	}
	return res;
}

/* Handle all communication with the client */
void *handle_client(void *arg)
{
	char **from_cli = NULL;
	char buff_out[BUFFER_SZ];
	char name[45];
	char passwd[45];
	int leave_flag = 0;
	int server_resp = -1;

	char group[45][45]; //////arr users of group

	cli_count++;
	client_t *cli = (client_t *)arg;
	client_t *reciver = NULL;

	// Name
	// if (recv(cli->sockfd, name, 45, 0) <= 0 || strlen(name) < 2 || strlen(name) >= 45 - 1)
	// {
	// 	printf("Didn't enter the name.\n");
	// 	leave_flag = 1;
	// }
	// else
	// {
	// 	// strcpy(cli->name, name);
	// 	sprintf(buff_out, "\n%s\n", name);

	// 	printf("%s", buff_out);
	// 	// send_message(buff_out, cli->uid);
	// }
	// // passwd
	// bzero(buff_out, BUFFER_SZ);
	// if (recv(cli->sockfd, passwd, 45, 0) <= 0 || strlen(passwd) < 2 || strlen(passwd) >= 45 - 1)
	// {
	// 	// printf("Didn't enter the name.\n");
	// 	leave_flag = 1;
	// }
	// else
	// {
	// 	sprintf(buff_out, "\n%s", passwd);
	// 	printf("\n%s\n", buff_out);
	// }

	// handle_user_enter(db, name, passwd);
	// printf("Test1\n");
	cli->name = NULL;
	while (1)
	{
		// printf("Test2\n");
		from_cli = unfold_msg_from_cli(cli);
		if (!from_cli)
		{
			// printf("Test5\n");
			printf("server -> %s leaved us\n", cli->name);
			mx_strdel(&(cli->name));
			break;
		}
		else
		{
			// printf("Test4\n");
			mx_printstr("client -> ");
			mx_print_strarr(from_cli, ", ");
			if (!from_cli[0])
			{
				// mx_printstr("Test7\n");
				mx_del_strarr(&from_cli);
				continue;
			}
			if (!mx_strcmp(from_cli[0], "/reg") || mx_strstr(from_cli[0], "/reg"))
			{
				server_resp = register_client(db, from_cli[2], from_cli[1]);
				send(cli->sockfd, &server_resp, sizeof(int), 0);
				cli->name = mx_strdup(from_cli[2]);
			}
			else if (!mx_strcmp(from_cli[0], "/log") || mx_strstr(from_cli[0], "/log"))
			{
				server_resp = login_client(db, from_cli[2], from_cli[1]);
				send(cli->sockfd, &server_resp, sizeof(int), 0);
				if (!server_resp)
				{
					send_chats_of_user(db, from_cli[2], cli->sockfd);
				}
				cli->name = mx_strdup(from_cli[2]);
			}
			else if (!mx_strcmp(from_cli[0], "/get-msg"))
			{
				send_msgs(db, from_cli[1], cli->sockfd, cli->name);
			}
			else if (!mx_strcmp(from_cli[0], "/new"))
			{
				create_new_chat(db, cli->name, from_cli[1], cli->sockfd);
			}
			else if (!mx_strcmp(from_cli[0], "/send"))
			{
				reciver = find_reciver(from_cli[1], cli->sockfd);
				if (reciver)
				{
					msg_send(db, cli->name, from_cli[1], from_cli[2], cli->sockfd, reciver->sockfd, reciver->name);
				}
				else
				{
					msg_send(db, cli->name, from_cli[1], from_cli[2], cli->sockfd, -1, NULL);
				}
			}
		}
		// printf("Test3\n");
		mx_del_strarr(&from_cli);

		// if (leave_flag)
		// {
		// 	break;
		// }
		// char **split_str;
		// int ct_group = 0;
		// client_t *dstcli;

		// int receive = recv(cli->sockfd, buff_out, BUFFER_SZ, 0);
		// str_trim_lf(buff_out, strlen(buff_out));
		// printf("%s -> %s\n", buff_out, cli->name);
		// split_str = mx_strsplit(buff_out, ' ');

		// if (receive > 0)
		// {

		// 	if (strcmp(split_str[1], "/register"))
		// 	{
		// 	}
		// 	if (strcmp(split_str[1], "/group") == 0)
		// 	{
		// 		for (int i = 2; split_str[i]; i++)
		// 		{
		// 			for (int j = 0; clients[j]; j++)
		// 			{
		// 				if (strcmp(split_str[i], clients[j]->name) == 0)
		// 				{
		// 					strcpy(group[ct_group], clients[j]->name);
		// 					ct_group++;
		// 				}
		// 			}
		// 		}
		// 		int ct_cl = 0;

		// 		client_t *tmp_cli[ct_group];

		// 		for (int i = 0; clients[i]; i++)
		// 		{
		// 			for (int j = 0; j < ct_group; j++)
		// 			{
		// 				if (strcmp(clients[i]->name, group[j]) == 0)
		// 				{
		// 					tmp_cli[ct_cl] = clients[i];
		// 					ct_cl++;
		// 				}
		// 			}
		// 		}

		// 		while (1)
		// 		{
		// 			bzero(buff_out, BUFFER_SZ);
		// 			int receive = recv(cli->sockfd, buff_out, BUFFER_SZ, 0);
		// 			if (receive > 0)
		// 			{
		// 				if (strchr(buff_out, '/') && strcmp(strchr(buff_out, '/'), "/exit\n") == 0)
		// 				{
		// 					break;
		// 				}
		// 				send_message_group(buff_out, tmp_cli, ct_cl);
		// 				str_trim_lf(buff_out, strlen(buff_out));
		// 				printf("%s -> %s\n", buff_out, cli->name);
		// 			}
		// 			else if (receive == 0 || strcmp(buff_out, "exit") == 0)
		// 			{
		// 				sprintf(buff_out, "%s has left\n", cli->name);
		// 				printf("%s", buff_out);
		// 				send_message(buff_out, cli->uid);
		// 				break;
		// 			}
		// 			else
		// 			{
		// 				printf("ERROR: -1\n");
		// 				break;
		// 			}
		// 		}
		// 	}
		// 	else if (strcmp(split_str[1], "/to") == 0)
		// 	{
		// 		for (int i = 0; clients[i]; i++)
		// 		{
		// 			if (strcmp(split_str[2], clients[i]->name) == 0)
		// 			{
		// 				dstcli = clients[i];
		// 				break;
		// 			}
		// 		}
		// 		while (1)
		// 		{
		// 			bzero(buff_out, BUFFER_SZ);
		// 			int receive = recv(cli->sockfd, buff_out, BUFFER_SZ, 0);

		// 			if (receive > 0)
		// 			{
		// 				printf("Buffout: %s\n", buff_out);
		// 				if (strchr(buff_out, '/') && strcmp(strchr(buff_out, '/'), "/exit\n") == 0)
		// 				{
		// 					break;
		// 				}

		// 				send_message2(buff_out, dstcli, cli->uid);
		// 				str_trim_lf(buff_out, strlen(buff_out));
		// 				printf("%s -> %s\n", buff_out, cli->name);
		// 			}
		// 			else if (receive == 0 || strcmp(buff_out, "exit") == 0)
		// 			{
		// 				sprintf(buff_out, "%s has left\n", cli->name);
		// 				printf("%s", buff_out);
		// 				send_message(buff_out, cli->uid);
		// 				break;
		// 			}
		// 			else
		// 			{
		// 				printf("ERROR: -1\n");
		// 				break;
		// 			}
		// 		}
		// 	}
		// }
		// else if (receive == 0 || strcmp(buff_out, "exit") == 0)
		// {
		// 	sprintf(buff_out, "%s has left\n", cli->name);
		// 	printf("%s", buff_out);
		// 	send_message(buff_out, cli->uid);
		// 	leave_flag = 1;
		// }
		// else
		// {
		// 	printf("ERROR: -1\n");
		// 	leave_flag = 1;
		// }

		// bzero(buff_out, BUFFER_SZ);
	}
	// printf("Test7\n");
	/* Delete client from queue and yield thread */
	close(cli->sockfd);
	queue_remove(cli->uid);
	// printf("Test8\n");
	free(cli);
	// printf("Test9\n");
	cli_count--;
	pthread_detach(pthread_self());
	// printf("Test10\n");

	return NULL;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: %s <port> <ip>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char *ip = malloc(sizeof(char) * 12); //"10.11.2.8";
	strcpy(ip, argv[2]);
	int port = atoi(argv[1]);
	int option = 1;
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	pthread_t tid;

	/* Socket settings */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(port);

	/* Ignore pipe signals */
	signal(SIGPIPE, SIG_IGN);

	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0)
	{
		perror("ERROR: setsockopt failed");
		return EXIT_FAILURE;
	}

	/* Bind */
	if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("ERROR: Socket binding failed");
		return EXIT_FAILURE;
	}

	/* Listen */
	if (listen(listenfd, 10) < 0)
	{
		perror("ERROR: Socket listening failed");
		return EXIT_FAILURE;
	}
	/*char *data_arr[] = {"Pidor", "img/send.png", "chat s pidorom", "img/send.png", "last msg pos", "12:00", "chat s igorem", "img/send.png", "last msg to igor", "13:00"};
	char *str = compress_arr_into_str(data_arr);
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '\1')
		{
			printf("1");
		}
		if (str[i] == '\2')
		{
			printf("2");
		}
		printf("%c", str[i]);
	}*/

	db = db_init("main.db");

	printf("=== WELCOME TO THE CHATROOM ===\n");
	while (1)
	{
		socklen_t clilen = sizeof(cli_addr);
		// mx_printstr("Test0\n");
		connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &clilen);
		// mx_printstr("Test-1\n");
		if (cli_count > 0 && clients[cli_count - 1]->sockfd == connfd)
		{
			sleep(1);
			continue;
		}
		mx_printstr("server -> Client connected\n");
		/* Check if max clients is reached */
		if ((cli_count + 1) == MAX_CLIENTS)
		{
			printf("Max clients reached. Rejected: ");
			print_client_addr(cli_addr);
			printf(":%d\n", cli_addr.sin_port);
			close(connfd);
			continue;
		}

		/* Client settings */
		client_t *cli = (client_t *)malloc(sizeof(client_t));
		cli->address = cli_addr;
		cli->sockfd = connfd;
		cli->uid = uid++;

		/* Add client to the queue and fork thread */
		queue_add(cli);
		pthread_create(&tid, NULL, &handle_client, (void *)cli);

		/* Reduce CPU usage */
	}
	return EXIT_SUCCESS;
}
