#ifndef SERVERH_H
#define SERVERH_H

#include "../../libs/libmx/inc/libmx.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sqlite3.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

#include <strings.h>

typedef struct
{
    char *name; ////

    struct sockaddr_in address;
    int sockfd;
    int uid;

} client_t;

sqlite3 *db_init(char *db_name);
void create_db(sqlite3 **db, char *db_name);

int user_callback(void *data, int argc, char **argv, char **azColName);

int register_client(sqlite3 *db, char *login, char *passwd);
int login_client(sqlite3 *db, char *login, char *passwd);
int call_for_text(void *data, int argc, char **argv, char **azColName);
char *insert_in_str(char **str, char *sub, char *repl);
void send_chats_of_user(sqlite3 *db, char *login, int sockfd);
void send_msg_to_cli(int sockfd, char *msg);
void print_to_send_str(char *to_send);
void msg_send(sqlite3 *db, char *sender, char *chat_name, char *text, int senderfd, int reciverfd, char *reciver);
void send_msgs(sqlite3 *db, char *chat_name, int sockfd, char *login);
void create_new_chat(sqlite3 *db, char *sender, char *reciver, int sockfd);
char *compress_arr_into_str(char **arr);
char *get_time(void);

#endif
