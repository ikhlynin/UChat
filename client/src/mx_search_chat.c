#include "client.h"

void mx_founded_chats()
{
}

void mx_search_chat(gpointer window)
{
    GtkWidget *grid = gtk_container_get_children(GTK_CONTAINER(window))->data;
    GtkWidget *sideGrid = gtk_container_get_children(GTK_CONTAINER(grid))->data; //segfault

    GList *sideGridChld = gtk_container_get_children(GTK_CONTAINER(sideGrid));
    sideGridChld = g_list_next(sideGridChld);
    //sideGridChld = g_list_next(sideGridChld);
    GtkWidget *searchBox = sideGridChld->data;

    GList *searchEntry = gtk_container_get_children(GTK_CONTAINER(searchBox));
    searchEntry = g_list_next(searchEntry);
    GtkWidget *text = searchEntry->data;

    //GtkWidget *searchEntry = gtk_container_get_children(GTK_CONTAINER(searchBox))->data;

    char *req = (char *)gtk_entry_get_text(GTK_ENTRY(text));
    char *toSend = mx_strdup("/new\1");

    // mx_str_concat(&toSend, user.login);
    // mx_str_concat(&toSend, "-");
    mx_str_concat(&toSend, req);

    // хз че делает и зачем
    // mx_str_concat(&toSend, "-");
    // mx_str_concat(&toSend, user.login);
    // mx_printstr(user.login);
    //-----------

    // chat_t *newChat = malloc(sizeof(chat_t));
    // newChat->name = mx_strdup(req);

    // newChat->img = mx_strdup("avatar.png");
    // newChat->lastMsg = malloc(sizeof(message_t));
    // newChat->lastMsg->masage = mx_strdup("993");
    // newChat->lastMsg->time = mx_strdup("00:00");

    // newChat->msg = malloc(sizeof(message_t) * 2);
    // newChat->msg[0] = malloc(sizeof(message_t));
    // newChat->msg[0]->masage = mx_strdup("1000-7");
    // newChat->msg[0]->time = mx_strdup("00:00");
    // newChat->msg[0]->to = 1;

    // newChat->msg[1] = malloc(sizeof(message_t));
    // newChat->msg[1]->masage = mx_strdup("993");
    // newChat->msg[1]->time = mx_strdup("00:00");
    // newChat->msg[1]->to = 0;

    // mx_push_back(&chats_list, newChat);

    //GtkWidget *scrolledWindow = gtk_container_get_children(GTK_CONTAINER(sideGrid))->data;
    //GtkWidget *bbb = gtk_container_get_children(GTK_CONTAINER(scrolledWindow))->data;
    //GtkWidget *target = gtk_container_get_children(GTK_CONTAINER(bbb))->data;

    //mx_schat_grid(window);
    send_msg_to_serv(toSend);
    parse_str(load_main());
    mx_main_page(window);
    // if (gtk_container_get_children(GTK_CONTAINER(sideGrid)))
    //     gtk_container_remove(GTK_CONTAINER(sideGrid), gtk_container_get_children(GTK_CONTAINER(sideGrid))->data);
}
