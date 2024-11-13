#include "client.h"

void mx_chat_grid(gpointer window)
{

    GtkWidget *grid;
    grid = gtk_container_get_children(GTK_CONTAINER(window))->data;

    t_list *iter = chats_list;
    while (iter != NULL)
    {
        if (mx_strcmp(((chat_t *)(iter->data))->name, opend_chat) == 0)
            break;
        iter = iter->next;
    }

    GtkWidget *chat;

    GtkWidget *scrolledwindow;
    // IMAGES
    GtkWidget *imgSend;
    GtkWidget *avatar;

    // BOXES
    GtkWidget *headerColor;
    GtkWidget *footerColor;
    GtkWidget *header;
    GtkWidget *space;
    GtkWidget *footer;

    // BUTTONS
    GtkWidget *sendBtn;
    GtkWidget *avatarBtn;
    GtkWidget *testSpace;

    // ENTRIES
    GtkWidget *textArea;

    // LABLES
    GtkWidget *name;
    headerColor = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(headerColor), 1200, 80);
    gtk_widget_set_name(headerColor, "chatHeaderColor");
    header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(header, "chatHeader");
    // gtk_widget_set_size_request(GTK_WIDGET(header), 380, 40);
    //------------------------------------------ПЕРЕПИСКА
    space = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(space, "MesBOX");
    gtk_widget_set_halign(space, GTK_ALIGN_END);
    // gtk_widget_set_name(space, "chatSpace");
    gtk_widget_set_size_request(GTK_WIDGET(space), 1160, 710);

    scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_show(scrolledwindow);
    // gtk_widget_set_name(scrolledwindow, "scrole");
    gtk_widget_set_size_request(GTK_WIDGET(scrolledwindow), 1170, 715);

    mx_slot_message(space); //FORK функция создания ячейки чата

    gtk_container_add(GTK_CONTAINER(scrolledwindow), space);

    footerColor = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(footerColor), 1200, 80);
    gtk_widget_set_name(footerColor, "chatFooterColor");
    footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(footer, "chatFooter");
    gtk_widget_set_size_request(GTK_WIDGET(footer), 1100, 40);

    GdkPixbuf *px1 = gdk_pixbuf_new_from_file_at_size("img/send.png", 50, 50, NULL);
    imgSend = gtk_image_new_from_pixbuf(px1);
    // imgSend = gtk_image_new_from_file("img/send.png");
    sendBtn = gtk_button_new();
    gtk_widget_set_name(sendBtn, "sendBtn");
    gtk_button_set_image(GTK_BUTTON(sendBtn), imgSend);

    textArea = gtk_entry_new();
    gtk_widget_set_name(textArea, "textArea");
    gtk_widget_set_size_request(GTK_WIDGET(textArea), 1000, 40);
    char *chatName = opend_chat;
    char **temp = mx_strsplit(chatName, '-');
    if (temp[1])
    {
        if (mx_strcmp(temp[0], user.login) == 0)
        {
            chatName = temp[1];
        }
        else
            chatName = temp[0];
    }

    name = gtk_label_new(chatName);
    gtk_widget_set_name(name, "name");

    char *ava = ((chat_t *)(iter->data))->img;
    GdkPixbuf *px = gdk_pixbuf_new_from_file_at_size(ava, 40, 40, NULL);
    avatar = gtk_image_new_from_pixbuf(px);
    avatarBtn = gtk_button_new();
    gtk_widget_set_name(avatarBtn, "avatarBtn");
    gtk_button_set_image(GTK_BUTTON(avatarBtn), avatar);

    gtk_container_add(GTK_CONTAINER(header), avatarBtn);
    gtk_container_add(GTK_CONTAINER(header), name);

    gtk_container_add(GTK_CONTAINER(space), testSpace);

    gtk_container_add(GTK_CONTAINER(footer), textArea);
    gtk_container_add(GTK_CONTAINER(footer), sendBtn);

    gtk_container_add(GTK_CONTAINER(headerColor), header);
    gtk_container_add(GTK_CONTAINER(footerColor), footer);

    chat = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(chat), 3);
    gtk_grid_set_row_spacing(GTK_GRID(chat), 3);

    gtk_grid_attach(GTK_GRID(chat), headerColor, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(chat), scrolledwindow, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(chat), footerColor, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), chat, 1, 1, 1, 1);

    g_signal_connect_swapped(G_OBJECT(sendBtn), "clicked", G_CALLBACK(mx_send_msg), G_OBJECT(textArea));
    gtk_widget_show_all(window);
}
