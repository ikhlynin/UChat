#include "client.h"

void mx_send_msg(gpointer textArea)
{
    if(!gtk_entry_get_text(GTK_ENTRY(textArea)))
        return;

    char *toSend = mx_strdup("/send\1");
    mx_str_concat(&toSend, opend_chat);
    mx_str_concat(&toSend, "\1");
    char *msg = (char *)gtk_entry_get_text(GTK_ENTRY(textArea));
    mx_str_concat(&toSend, msg);
    send_msg_to_serv(toSend);
}
