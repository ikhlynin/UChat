#include "client.h"

void mx_settings_user(gpointer window)
{

    //     // IMAGES
    GtkWidget *grid = gtk_container_get_children(GTK_CONTAINER(window))->data;
    GList *sideGridList = gtk_container_get_children(GTK_CONTAINER(grid));
    //sideGridList = g_list_next(sideGridList);
    GtkWidget *sideGrid = sideGridList->data;

    GtkWidget *imgBack;

    // BLOCKS
    GtkWidget *menu;
    GtkWidget *settings;
    GtkWidget *settingMenuBox;

    //     //BUTTONS
    GtkWidget *back;

    // ПРОФИЛЬ
    GtkWidget *userButtSet;
    GtkWidget *userBox;
    GtkWidget *imgUser;
    GtkWidget *nameUser;

    GtkWidget *loginUser;
    //new
    GtkWidget *name;
    GtkWidget *labelName;
    GtkWidget *bio;
    GtkWidget *labelBio;

    mx_printstr("               1111               ");
    GList *iter = gtk_container_get_children(GTK_CONTAINER(sideGrid));
    for (; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(iter->data);

    menu = gtk_label_new("ACCOUNT SETTINGS");
    gtk_widget_set_name(menu, "menu4");

    //--------------------------------------------------КНОПКА НАЗАД
    imgBack = gtk_image_new_from_file("img/arrow.png");
    back = gtk_button_new();
    gtk_widget_set_name(back, "backImgButtonMenu");
    gtk_button_set_relief(GTK_BUTTON(back), GTK_RELIEF_NONE);
    gtk_button_set_image(GTK_BUTTON(back), imgBack);
    gtk_widget_set_size_request(GTK_WIDGET(back), 380, 80);
    //--------------------------------------------------НАСТРОЙКИ ПРОФИЛЯ ФОТО

    /////////
    userButtSet = gtk_button_new();
    gtk_widget_set_name(userButtSet, "userButtSet");
    gtk_widget_set_size_request(GTK_WIDGET(userButtSet), 280, 90);
    gtk_button_set_relief(GTK_BUTTON(userButtSet), GTK_RELIEF_NONE); // отменяет стандартное декарирование

    userBox = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(userBox), 2);
    gtk_grid_set_row_spacing(GTK_GRID(userBox), 2);
    GdkPixbuf *px = gdk_pixbuf_new_from_file_at_size(user.img, 90, 90, NULL);
    imgUser = gtk_image_new_from_pixbuf(px);
    gtk_image_set_pixel_size(GTK_IMAGE(imgUser), 50);
    // gtk_widget_set_size_request(GTK_WIDGET(imgUser), 75, 70);
    gtk_widget_set_name(imgUser, "imgChatMenu");

    // gchar *login = g_str_to_ascii("@komushki", NULL);

    nameUser = gtk_label_new("change foto");
    gtk_widget_set_name(nameUser, "nameChatMenu");
    gtk_widget_set_size_request(GTK_WIDGET(nameUser), 180, 10);

    loginUser = gtk_label_new((gchar *)login);
    gtk_widget_set_name(loginUser, "lastMassageChatMenu");
    gtk_widget_set_size_request(GTK_WIDGET(loginUser), 150, 10);

    gtk_grid_attach(GTK_GRID(userBox), imgUser, 1, 1, 1, 2);
    gtk_grid_attach(GTK_GRID(userBox), nameUser, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(userBox), loginUser, 2, 2, 1, 1);

    gtk_container_add(GTK_CONTAINER(userButtSet), userBox);

    //--------------------------------------------------НАСТРОЙКИ ПРОФИЛЯ
    settings = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(settings, "settings1");

    labelName = gtk_label_new("Name");
    name = gtk_entry_new();
    gtk_widget_set_name(name, "entr");
    // char *nameText = "Komushki";
    GtkEntryBuffer *textName = gtk_entry_buffer_new((gchar *)nameUs, 8);
    gtk_entry_set_buffer(GTK_ENTRY(name), textName);

    labelBio = gtk_label_new("Bio");
    bio = gtk_entry_new();
    gtk_widget_set_name(bio, "entr");
    // char *bioText = "Komushki";
    GtkEntryBuffer *textBio = gtk_entry_buffer_new((gchar *)bio, 8);
    gtk_entry_set_buffer(GTK_ENTRY(bio), textBio);

    gtk_container_add(GTK_CONTAINER(settings), labelName);
    gtk_container_add(GTK_CONTAINER(settings), name);
    gtk_container_add(GTK_CONTAINER(settings), labelBio);
    gtk_container_add(GTK_CONTAINER(settings), bio);

    //--------------------------------------------------ОБЩИЙ КОНТЕЙНЕР
    settingMenuBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(settingMenuBox, "settings");
    gtk_widget_set_size_request(GTK_WIDGET(settingMenuBox), 380, 500);

    gtk_container_add(GTK_CONTAINER(settingMenuBox), menu);
    gtk_container_add(GTK_CONTAINER(settingMenuBox), userButtSet);
    gtk_container_add(GTK_CONTAINER(settingMenuBox), settings);

    gtk_grid_attach(GTK_GRID(sideGrid), back, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(sideGrid), settingMenuBox, 1, 2, 1, 1);

    //     g_signal_connect_swapped(G_OBJECT(accSet), "clicked", G_CALLBACK(mx_settings_user), G_OBJECT(window));

    g_signal_connect_swapped(G_OBJECT(back), "clicked", G_CALLBACK(mx_settings_page), G_OBJECT(window));

    gtk_widget_show_all(sideGrid);
}
