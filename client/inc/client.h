#ifndef ZXChat
#define ZXChat

#include "../../libs/libmx/inc/libmx.h"
#include <gtk/gtk.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef struct user_s
{
    char *login;
    char *img;
} user_t;

typedef struct message_s
{

    char *masage;
    char *time;
    bool to;
} message_t;

typedef struct chat_s
{
    char *name;
    char *img;
    message_t *lastMsg;
    message_t **msg;
} chat_t;

t_list *chats_list;
user_t user;
char *opend_chat;

char *login;
char *nameUs;
char *bio;
bool flag;
char * fotoUs;
char *bgImg;
#define SA struct sockaddr
#define COUNTER_GOVNA 228
char *ip;
char *port;

char *loadMain;
int sockfd;
struct sockaddr_in servaddr;

void load_css(void);
void mx_home_page();
void mx_sign_In_page(GtkWidget *homePage, gpointer window);
void mx_sign_Up_page(GtkWidget *homePage, gpointer window, char *bar);
void mx_proceed_registration(gpointer window);
void mx_proceed_login(gpointer window);
void mx_create_button(GtkCssProvider *css_provider, GtkWidget *layout, char *text, const char *namebut);
void mx_connect(int argc, char **argv);
void mx_settings_page(gpointer sideGrid);
void mx_settings_user(gpointer window);
void mx_logout(gpointer window);
void mx_send_msg(gpointer textArea);
void mx_slot_chat(gpointer scrolledwindow, gpointer window);
void mx_slot_message(gpointer bbb);

void mx_chat_grid(gpointer widnow);
void send_msg_to_serv(char *msg);
void mx_open_chat(gpointer chatName);
int serv_resp();
void mx_main_page(gpointer window);
void parse_str(char *str);
char *load_main();
void *event_listner(gpointer window);
void mx_search_chat(gpointer window);

void mx_update_bg(gpointer window);
void mx_slot_message(gpointer bbb);

#endif /* ZXChat */
