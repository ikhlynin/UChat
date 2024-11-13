#include "client.h"

int serv_resp()
{
	int res = -1;
	recv(sockfd, &res, sizeof(int), 0);
	return res;
}

char *load_main()
{
	int respSize = 0;
	char *res = NULL;
	recv(sockfd, &respSize, sizeof(int), 0);
	res = mx_strnew(respSize);
	recv(sockfd, res, respSize, 0);
	mx_printstr("Recive msg: ");
	mx_printstr(res);
	mx_printstr("\n");
	return res;
}
