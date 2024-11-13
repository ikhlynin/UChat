#include "client.h"

void parse_str(char *str)
{
    chats_list = NULL;
    char **splited = mx_strsplit(str, '\1');
    //mx_print_strarr(splited, "    1     ");
    user.login = mx_strdup(splited[0]);
    user.img = mx_strdup(splited[1]);

    //fotoUs = mx_strdup(splited[1]);

    for (int i = 2; splited[i]; i++)
    {
        chat_t *chat = malloc(sizeof(chat_t));
        message_t *last_msg = malloc(sizeof(message_t));
        char **chat_params = mx_strsplit(splited[i], '\2');
        chat->name = chat_params[0];

        chat->img = chat_params[1];

        last_msg->masage = chat_params[2];
        last_msg->time = chat_params[3];
        chat->lastMsg = last_msg;
        // mx_printstr(user.login);
        // mx_printstr(user.img);
        // mx_printstr("\n");
        // mx_printstr(chat->name);
        // mx_printstr(chat->img);
        // mx_printstr(chat->lastMsg->masage);
        // mx_printstr(chat->lastMsg->time);
        // mx_printstr("asd");
        mx_push_back(&chats_list, chat);
        free(chat_params);
    }
    mx_del_strarr(&splited);
}
