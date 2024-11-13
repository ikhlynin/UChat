#include "client.h"

void send_msg_to_serv(char *msg)
{
	mx_printstr("Sended msg: ");
	mx_printstr(msg);
	mx_printstr("\n");
	int send_size = mx_strlen(msg);
	send(sockfd, &send_size, sizeof(int), 0);
	send(sockfd, msg, mx_strlen(msg), 0);
}

