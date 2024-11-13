#include "client.h"

void parse_msg(char *str)
{
}

void *event_listner(gpointer window)
{
    flag = 1;

    // gpointer *ochko = (gpointer)window;
    // ochko = NULL;
    int ccc = 0;
    while (COUNTER_GOVNA)
    {

        parse_str(load_main());

        mx_printstr("\n");
        mx_printint(ccc);
        char *req = load_main();
        // mx_printstr(req);
        char **param = mx_strsplit(req, '\1');
        int count = 0;
        if (mx_strcmp(param[0], "/msgs") == 0)
        {
            chat_t *curr_chat = NULL;
            t_list *user_iter = chats_list;
            for (; user_iter != NULL; user_iter = user_iter->next)
            {
                curr_chat = user_iter->data;
                // char **param_param = mx_strsplit(param[1], '-');
                if (mx_strcmp(curr_chat->name, param[1]) == 0)
                    break;
            }
            for (int i = 2; param[i]; i++, count++)
                ;

            curr_chat->msg = malloc(sizeof(message_t *) * (count + 1));
            for (int i = 2, j = 0; param[i]; i++, j++)
            {
                char **buf = mx_strsplit(param[i], '\2');
                curr_chat->msg[j] = malloc(sizeof(message_t));
                curr_chat->msg[j]->masage = mx_strdup(buf[0]);
                curr_chat->msg[j]->time = mx_strdup(buf[1]);
                curr_chat->msg[j]->to = mx_atoi(buf[2]);
                mx_del_strarr(&buf);
            }
            curr_chat->msg[count] = NULL;

            
            /*-------------------TEST-------------------*/
            //     while (chats_list)
            //     {
            // for (int i = 0; ((chat_t *)(chats_list->data))->msg[i]; i++)
            // {
            //     mx_printstr(((chat_t *)(chats_list->data))->msg[i]->masage);
            //     mx_printstr(((chat_t *)(chats_list->data))->msg[i]->time);
            // }
            //chats_list = chats_list->next;
            //     }
            /*-------------------END OF TEST-------------------*/
        }
        if (mx_strcmp(param[0], "/log") == 0)
        {
            parse_str(load_main());
        }
        if (mx_strcmp(param[0], "/new") == 0)
        {
        }
        ccc++;

        mx_main_page(window);
        mx_chat_grid(window);
    }

    return NULL;
}
