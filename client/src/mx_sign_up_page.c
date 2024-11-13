#include "client.h"

void mx_sign_Up_page(GtkWidget *homePage, gpointer window, char *bar)
{
    int count_err = 0;
    GList *childrenGrid, *iter, *childrenWin;
    childrenWin = gtk_container_get_children(GTK_CONTAINER(window));
    childrenGrid = gtk_container_get_children(GTK_CONTAINER(childrenWin->data));
    iter = childrenGrid;

    if (mx_strcmp(bar, "\0") != 0)
    {

        // while (childrenGrid != NULL)
        // {
        //     count_err++;
        //     childrenGrid = g_list_next(childrenGrid);
        // }
        // childrenGrid = gtk_container_get_children(GTK_CONTAINER(childrenWin->data));
        // if (count_err == 6)
        // {
        //     childrenGrid = g_list_next(childrenGrid);
        //     gtk_widget_destroy(childrenGrid->data);
        // }

        //--------------------------------------------ВЫВОД ОШИБКИ
        GtkWidget *error;
        error = gtk_label_new(bar);
        gtk_widget_set_hexpand(error, FALSE);
        gtk_widget_set_vexpand(error, FALSE);
        gtk_widget_set_halign(error, GTK_ALIGN_CENTER);
        gtk_widget_set_name(error, "aaaaa");
        gtk_widget_set_size_request(GTK_WIDGET(error), 98, 10);
        gtk_grid_attach(GTK_GRID(childrenWin->data), error, 1, 4, 1, 1);
        gtk_widget_show(error);
    }
    else
    {
        GtkWidget *logo;
        GtkWidget *loginEntry;
        GtkWidget *pswdEntry;
        GtkWidget *repeatPswdEntry;
        GtkWidget *imgSingUp;

        GtkWidget *submitBtn;
        while (iter != NULL)
        {
            count_err++;
            iter = g_list_next(iter);
        }
        if (count_err == 6)
        {
            iter = childrenGrid;
            iter = g_list_next(iter);
            gtk_container_remove(GTK_CONTAINER(childrenWin->data), GTK_WIDGET(iter->data));
        }
        iter = childrenGrid;

        // childrenGrid = g_list_next(childrenGrid);
        for (iter = childrenGrid; iter != NULL; iter = g_list_next(iter))
            gtk_container_remove(GTK_CONTAINER(childrenWin->data), GTK_WIDGET(iter->data));

        // ...

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
        gtk_entry_set_max_length(GTK_ENTRY(loginEntry), 15);

        pswdEntry = gtk_entry_new();
        gtk_widget_set_hexpand(pswdEntry, FALSE);
        gtk_widget_set_vexpand(pswdEntry, FALSE);
        gtk_widget_set_halign(pswdEntry, GTK_ALIGN_CENTER);
        gtk_entry_set_placeholder_text(GTK_ENTRY(pswdEntry), "password"); // добавление фонового текстаа
        gtk_widget_set_size_request(GTK_WIDGET(pswdEntry), 260, 10);
        gtk_widget_set_name(pswdEntry, "entry");
        gtk_entry_set_max_length(GTK_ENTRY(pswdEntry), 10);
        gtk_entry_set_visibility(GTK_ENTRY(pswdEntry), FALSE);
        gtk_entry_set_invisible_char(GTK_ENTRY(pswdEntry), '*');

        repeatPswdEntry = gtk_entry_new();
        gtk_widget_set_hexpand(repeatPswdEntry, FALSE);
        gtk_widget_set_vexpand(repeatPswdEntry, FALSE);
        gtk_widget_set_halign(repeatPswdEntry, GTK_ALIGN_CENTER);
        gtk_entry_set_placeholder_text(GTK_ENTRY(repeatPswdEntry), "repeat password"); // добавление фонового текстаа
        gtk_widget_set_size_request(GTK_WIDGET(repeatPswdEntry), 260, 10);
        gtk_widget_set_name(repeatPswdEntry, "entry");
        gtk_entry_set_max_length(GTK_ENTRY(repeatPswdEntry), 10);
        gtk_entry_set_visibility(GTK_ENTRY(repeatPswdEntry), FALSE);
        gtk_entry_set_invisible_char(GTK_ENTRY(repeatPswdEntry), '*');

        submitBtn = gtk_button_new();
        imgSingUp = gtk_image_new_from_file("img/sign_up_button2.png");
        gtk_widget_set_hexpand(submitBtn, FALSE);
        gtk_widget_set_vexpand(submitBtn, FALSE);
        gtk_widget_set_halign(submitBtn, GTK_ALIGN_CENTER);
        gtk_button_set_image(GTK_BUTTON(submitBtn), imgSingUp);
        gtk_widget_set_name(submitBtn, "buttonSingUp2");
        gtk_button_set_relief(GTK_BUTTON(submitBtn), GTK_RELIEF_NONE); // отменяет стандартное декарирование
        gtk_widget_set_size_request(GTK_WIDGET(submitBtn), 98, 10);

        gtk_grid_attach(GTK_GRID(childrenWin->data), logo, 1, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(childrenWin->data), loginEntry, 1, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(childrenWin->data), pswdEntry, 1, 2, 1, 1);
        gtk_grid_attach(GTK_GRID(childrenWin->data), repeatPswdEntry, 1, 3, 1, 1);
        gtk_grid_attach(GTK_GRID(childrenWin->data), submitBtn, 1, 5, 1, 1);

        gtk_widget_show(logo);
        gtk_widget_show(loginEntry);
        gtk_widget_show(pswdEntry);
        gtk_widget_show(repeatPswdEntry);
        gtk_widget_show(submitBtn);

        /* ERROR MESSAGES */

        /* END OF ERROR MESSAGES */

        g_signal_connect_swapped(G_OBJECT(submitBtn), "clicked", G_CALLBACK(mx_proceed_registration), window);
    }
}
