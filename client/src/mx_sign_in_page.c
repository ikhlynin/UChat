#include "client.h"

void mx_sign_In_page(GtkWidget *homePage, gpointer window)
{
    GList *childrenGrid, *iter, *childrenWin;
    childrenWin = gtk_container_get_children(GTK_CONTAINER(window));
    childrenGrid = gtk_container_get_children(GTK_CONTAINER(childrenWin->data));
    // childrenGrid = g_list_next(childrenGrid);
    for (iter = childrenGrid; iter != NULL; iter = g_list_next(iter))
        gtk_container_remove(GTK_CONTAINER(childrenWin->data), GTK_WIDGET(iter->data));
    //gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(childrenGrid);

    //creating new layout
    GtkWidget *logo;
    GtkWidget *loginEntry;
    GtkWidget *pswdEntry;
    GtkWidget *submitBtn;
    GtkWidget *imgSingin;
    // GtkWidget *repeatPswdEntry;

    //GtkWidget *submitBtn;

    logo = gtk_image_new_from_file("img/zxchat.png");
    gtk_widget_set_name(logo, "ChatName");
    gtk_widget_set_size_request(GTK_WIDGET(logo), 1000, 10);

    loginEntry = gtk_entry_new();
    gtk_widget_set_hexpand(loginEntry, FALSE);
    gtk_widget_set_vexpand(loginEntry, FALSE);
    gtk_widget_set_halign(loginEntry, GTK_ALIGN_CENTER);
    gtk_entry_set_placeholder_text(GTK_ENTRY(loginEntry), "username");
    gtk_widget_set_size_request(GTK_WIDGET(loginEntry), 260, 10);
    gtk_widget_set_name(loginEntry, "entry");

    pswdEntry = gtk_entry_new();
    gtk_widget_set_hexpand(pswdEntry, FALSE);
    gtk_widget_set_vexpand(pswdEntry, FALSE);
    gtk_widget_set_halign(pswdEntry, GTK_ALIGN_CENTER);
    gtk_entry_set_placeholder_text(GTK_ENTRY(pswdEntry), "password"); // добавление фонового текстаа
    gtk_widget_set_size_request(GTK_WIDGET(pswdEntry), 260, 10);
    gtk_widget_set_name(pswdEntry, "entry");
    gtk_entry_set_max_length(GTK_ENTRY(pswdEntry), 20);
    gtk_entry_set_visibility(GTK_ENTRY(pswdEntry), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(pswdEntry), '*');

    //repeatPswdEntry = gtk_entry_new();

    submitBtn = gtk_button_new();
    imgSingin = gtk_image_new_from_file("img/sign_in_button2.png");
    gtk_widget_set_hexpand(submitBtn, FALSE);
    gtk_widget_set_vexpand(submitBtn, FALSE);
    gtk_widget_set_halign(submitBtn, GTK_ALIGN_CENTER);
    gtk_button_set_image(GTK_BUTTON(submitBtn), imgSingin);
    gtk_widget_set_name(submitBtn, "buttonSingIn");
    gtk_button_set_relief(GTK_BUTTON(submitBtn), GTK_RELIEF_NONE); // отменяет стандартное декарирование
    gtk_widget_set_size_request(GTK_WIDGET(submitBtn), 98, 10);
    g_signal_connect_swapped(G_OBJECT(submitBtn), "clicked", G_CALLBACK(mx_proceed_login), window);

    //  submitBtn = gtk_button_new();
    gtk_grid_attach(GTK_GRID(childrenWin->data), logo, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(childrenWin->data), loginEntry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(childrenWin->data), pswdEntry, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(childrenWin->data), submitBtn, 1, 4, 1, 1);

    gtk_widget_show(loginEntry);
    gtk_widget_show(pswdEntry);
    gtk_widget_show(logo);
    gtk_widget_show(submitBtn);
}
