#include "client.h"

void mx_open_chat(gpointer chatName)
{

    char *name = (char *)gtk_label_get_text(GTK_LABEL(chatName));
    t_list *iter = chats_list;

    while (iter != NULL)
    {
        if (strstr(((chat_t *)(iter->data))->name, name))
            break;
        iter = iter->next;
    }
    opend_chat = ((chat_t *)(iter->data))->name;
    char *toSend = mx_strdup("/get-msg\1");
    mx_str_concat(&toSend, ((chat_t *)(iter->data))->name);
    send_msg_to_serv(toSend);
}
