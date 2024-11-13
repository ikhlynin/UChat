
#include "client.h"

//void sort_by_time(){}

void mx_slot_message(gpointer bbb)
{

    t_list *iter = chats_list;
    while (iter != NULL)
    {
        if (mx_strcmp(((chat_t *)(iter->data))->name, opend_chat) == 0)
            break;
    }

    // message_t *mmm = ((chat_t *)(iter->data))->;

    GtkWidget *messageBox;
    GtkWidget *messadeText;
    int count = 0;
    // GtkWidget *messageGrid = gtk_grid_new()
    // gtk_grid_set_column_spacing(GTK_GRID(messageGrid), 1);
    // gtk_grid_set_row_spacing(GTK_GRID(messageGrid), 2);
    message_t **cur_chat_mess = ((chat_t *)(iter->data))->msg;
    mx_printint(cur_chat_mess[0] == NULL);
    // gtk_grid_attach(GTK_GRID(grid), sidePanel, 0, 1, 1, 1);
    for (int i = 0; cur_chat_mess[i] != NULL; i++)
    {
        mx_printstr("asdasd");
        messageBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(messageBox, "mesfon");

        // char *text = "hfurhfurhfhr";

        char *chatName = cur_chat_mess[i]->masage;
        messadeText = gtk_label_new(chatName);
        char *timeMes = cur_chat_mess[i]->time;
        GtkWidget *time = gtk_label_new(timeMes);
        gtk_container_add(GTK_CONTAINER(messageBox), messadeText);
        gtk_container_add(GTK_CONTAINER(messageBox), time);
        gtk_widget_set_name(time, "time");
        if (cur_chat_mess[i]->to == 0)
        {
            gtk_widget_set_halign(messageBox, GTK_ALIGN_START);
        }
        else
            gtk_widget_set_halign(messageBox, GTK_ALIGN_END);
        gtk_container_add(GTK_CONTAINER(bbb), messageBox);

        count++;
    }

    // GtkWidget *imgChat;
    // GtkWidget *nameChat;
    // GtkWidget *timeChat;
    // GtkWidget *endMessage;
    // GtkWidget *countMessage;
    // // GtkWidget *id;

    // int count = 0;
    // while (count < 14)
    // {
    //     chatField = gtk_button_new();
    //     gtk_widget_set_name(chatField, "chatField");
    //     gtk_widget_set_size_request(GTK_WIDGET(chatField), 280, 90);
    //     gtk_button_set_relief(GTK_BUTTON(chatField), GTK_RELIEF_NONE); // отменяет стандартное декарирование

    //     chatBox = gtk_grid_new();
    //     gtk_widget_set_name(chatBox, "1");
    //     gtk_grid_set_column_spacing(GTK_GRID(chatBox), 3);
    //     gtk_grid_set_row_spacing(GTK_GRID(chatBox), 2);

    //     GdkPixbuf *px = gdk_pixbuf_new_from_file_at_size("img/wallpaperbetter.jpg", 40, 40, NULL);

    //     imgChat = gtk_image_new_from_pixbuf(px);
    //     gtk_image_set_pixel_size(GTK_IMAGE(imgChat), 50);
    //     gtk_widget_set_size_request(GTK_WIDGET(imgChat), 75, 70);
    //     gtk_widget_set_name(imgChat, "imgChatMenu");

    //     gchar *lastMess = g_str_to_ascii("ddwdwdwdwdwfefwefewfwfwfwfwfwfwfwfwfwfwfwfwfwfwfwfwffwwfwfwfwfwfwfwfwa", NULL);
    //     gchar *showMess = malloc(sizeof(char *) * 40);
    //     gchar *nameChatText = g_str_to_ascii("gavno", NULL);
    //     gchar *showChat = malloc(sizeof(char *) * 40);

    //     if (mx_strlen(nameChatText) > 8)
    //     {
    //         for (int i = 0; i < 8; i++)
    //         {
    //             showChat[i] = nameChatText[i];
    //         }
    //         mx_str_concat(&showChat, "...");
    //     }
    //     else
    //     {
    //         showChat = nameChatText;
    //     }

    //     if (mx_strlen(lastMess) > 12)
    //     {
    //         for (int i = 0; i < 12; i++)
    //         {
    //             showMess[i] = lastMess[i];
    //         }
    //         mx_str_concat(&showMess, "...");
    //     }
    //     else
    //     {
    //         showMess = lastMess;
    //     }
    //     showChat = g_str_to_ascii(showChat, NULL);
    //     showMess = g_str_to_ascii(showMess, NULL);
    //     nameChat = gtk_label_new(showChat);
    //     gtk_widget_set_name(nameChat, "nameChatMenu");
    //     gtk_widget_set_size_request(GTK_WIDGET(nameChat), 180, 10);
    //     timeChat = gtk_label_new("21:40");
    //     gtk_widget_set_name(timeChat, "timeChatMenu");
    //     // timeChat = gtk_label_new("21:40");
    //     // gtk_widget_set_name(timeChat, "timeChatMenu");
    //     endMessage = gtk_label_new(showMess);
    //     gtk_widget_set_name(endMessage, "lastMassageChatMenu");
    //     gtk_widget_set_size_request(GTK_WIDGET(endMessage), 150, 10);
    //     countMessage = gtk_label_new("1");
    //     gtk_widget_set_name(countMessage, "countMessageChatMenu");
    //     gtk_widget_set_size_request(GTK_WIDGET(countMessage), 5, 5);

    //     // gtk_label_set_max_width_chars(GTK_LABEL(endMessage), 10);
    //     // gtk_widget_set_name(endMessage, "ad");

    //     gtk_grid_attach(GTK_GRID(chatBox), imgChat, 1, 1, 1, 2);
    //     // gtk_grid_attach(GTK_GRID(chatBox), nameChat, 2, 1, 1, 1);
    //     // gtk_grid_attach(GTK_GRID(chatBox), timeChat, 3, 1, 1, 1);
    //     // gtk_grid_attach(GTK_GRID(chatBox), endMessage, 2, 2, 1, 1);
    //     // gtk_grid_attach(GTK_GRID(chatBox), countMessage, 3, 2, 1, 1);

    //     gtk_container_add(GTK_CONTAINER(chatField), chatBox);

    //     g_signal_connect_swapped(G_OBJECT(chatField), "clicked", G_CALLBACK(mx_open_chat), G_OBJECT(nameChat));
}
