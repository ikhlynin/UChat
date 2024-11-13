
#include "client.h"

//void sort_by_time(){}

void mx_slot_chat(gpointer bbb, gpointer window)
{
    if (gtk_container_get_children(GTK_CONTAINER(bbb)))
        gtk_container_remove(GTK_CONTAINER(bbb), gtk_container_get_children(GTK_CONTAINER(bbb))->data);

    // GtkWidget *grid;
    // grid = gtk_container_get_children(GTK_CONTAINER(window))->data;
    mx_printstr("\ntest1\n");
    GtkWidget *chatField;
    GtkWidget *chatBox;
    GtkWidget *imgChat;
    GtkWidget *nameChat;
    GtkWidget *timeChat;
    GtkWidget *endMessage;
    GtkWidget *countMessage;
    // GtkWidget *id;

    int count = 0;
    for (t_list *iter = chats_list; iter != NULL; iter = iter->next)
    {
        chat_t *curr_chat = iter->data;
        message_t *curr_msg = curr_chat->lastMsg;

        chatField = gtk_button_new();
        gtk_widget_set_name(chatField, "chatField");
        gtk_widget_set_size_request(GTK_WIDGET(chatField), 280, 90);
        gtk_button_set_relief(GTK_BUTTON(chatField), GTK_RELIEF_NONE); // отменяет стандартное декарирование

        chatBox = gtk_grid_new();
        gtk_widget_set_name(chatBox, "1");
        gtk_grid_set_column_spacing(GTK_GRID(chatBox), 3);
        gtk_grid_set_row_spacing(GTK_GRID(chatBox), 2);
        GdkPixbuf *px = gdk_pixbuf_new_from_file_at_size(curr_chat->img, 90, 90, NULL);
        imgChat = gtk_image_new_from_pixbuf(px);
        gtk_image_set_pixel_size(GTK_IMAGE(imgChat), 50);
        gtk_widget_set_size_request(GTK_WIDGET(imgChat), 75, 70);
        gtk_widget_set_name(imgChat, "imgChatMenu");

        gchar *lastMess = g_str_to_ascii(curr_msg->masage, NULL);
        //gchar *showMess = malloc(sizeof(gchar) * 15);
        char *chatName = curr_chat->name;
        char **temp = mx_strsplit(chatName, '-');
        if (temp[1])
        {
            if (mx_strcmp(temp[0], user.login) == 0)
            {
                chatName = temp[1];
                login = temp[0];
            }
            else
            {
                chatName = temp[0];
                login = temp[1];
            }
        }

        gchar *nameChatText = g_str_to_ascii(chatName, NULL);
        gchar *gTime = g_str_to_ascii(curr_chat->lastMsg->time, NULL);
        // gchar *showChat = malloc(sizeof(gchar) * 11);

        // if (mx_strlen(nameChatText) > 8)
        // {
        //     for (int i = 0; i < 8; i++)
        //     {
        //         showChat[i] = nameChatText[i];
        //     }
        // }
        // else
        // {
        //     showChat = nameChatText;
        // }

        // if (mx_strlen(lastMess) > 12)
        // {
        //     for (int i = 0; i < 12; i++)
        //     {
        //         showMess[i] = lastMess[i];
        //     }
        // }
        // else
        // {
        //     showMess = lastMess;
        // }
        // showChat = g_str_to_ascii(showChat, NULL);
        // showMess = g_str_to_ascii(showMess, NULL);
        nameChat = gtk_label_new(nameChatText);
        gtk_widget_set_name(nameChat, "nameChatMenu");
        gtk_widget_set_size_request(GTK_WIDGET(nameChat), 180, 10);
        timeChat = gtk_label_new(gTime);
        gtk_widget_set_name(timeChat, "timeChatMenu");
        // timeChat = gtk_label_new("21:40");
        // gtk_widget_set_name(timeChat, "timeChatMenu");
        endMessage = gtk_label_new(lastMess);
        gtk_widget_set_name(endMessage, "lastMassageChatMenu");
        gtk_widget_set_size_request(GTK_WIDGET(endMessage), 150, 10);
        countMessage = gtk_label_new("1");
        gtk_widget_set_name(countMessage, "countMessageChatMenu");
        gtk_widget_set_size_request(GTK_WIDGET(countMessage), 5, 5);

        // gtk_label_set_max_width_chars(GTK_LABEL(endMessage), 10);
        // gtk_widget_set_name(endMessage, "ad");

        gtk_grid_attach(GTK_GRID(chatBox), imgChat, 1, 1, 1, 2);
        gtk_grid_attach(GTK_GRID(chatBox), nameChat, 2, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(chatBox), timeChat, 3, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(chatBox), endMessage, 2, 2, 1, 1);
        gtk_grid_attach(GTK_GRID(chatBox), countMessage, 3, 2, 1, 1);

        gtk_container_add(GTK_CONTAINER(chatField), chatBox);

        //g_signal_connect_swapped(G_OBJECT(chatField), "clicked", G_CALLBACK(mx_chat_grid), G_OBJECT(window));
        g_signal_connect_swapped(G_OBJECT(chatField), "clicked", G_CALLBACK(mx_open_chat), G_OBJECT(nameChat));

        gtk_container_add(GTK_CONTAINER(bbb), chatField);
        count++;
    }
}
