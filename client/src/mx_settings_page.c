#include "client.h"

void mx_settings_page(gpointer window)
{
    // IMAGES
    GtkWidget *grid = gtk_container_get_children(GTK_CONTAINER(window))->data;
    GList *sideGridList = gtk_container_get_children(GTK_CONTAINER(grid));
    // sideGridList = g_list_next(sideGridList);
    GtkWidget *sideGrid = sideGridList->data;

    GtkWidget *imgBack;
    GtkWidget *imgContacts;
    GtkWidget *imgGroup;
    GtkWidget *imgAcc;
    GtkWidget *imgLang;

    // BLOCKS
    GtkWidget *menu;
    GtkWidget *settings;
    GtkWidget *settingMenuBox;
    GtkWidget *footer;

    //BUTTONS
    GtkWidget *back;
    GtkWidget *contacts;
    GtkWidget *newGroup;
    GtkWidget *accSet;
    GtkWidget *Language;
    GtkWidget *Logout;

    // ПРОФИЛЬ
    GtkWidget *userButtSet;
    GtkWidget *userBox;
    GtkWidget *imgUser;
    GtkWidget *nameUser;

    GtkWidget *loginUser;

    GList *iter = gtk_container_get_children(GTK_CONTAINER(sideGrid));
    for (; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(iter->data);

    menu = gtk_label_new("MENU");
    gtk_widget_set_name(menu, "menu");

    //--------------------------------------------------КНОПКА НАЗАД
    imgBack = gtk_image_new_from_file("img/arrow.png");
    back = gtk_button_new();
    gtk_widget_set_name(back, "backImgButtonMenu");
    gtk_button_set_relief(GTK_BUTTON(back), GTK_RELIEF_NONE);
    gtk_button_set_image(GTK_BUTTON(back), imgBack);
    gtk_widget_set_size_request(GTK_WIDGET(back), 380, 80);
    //--------------------------------------------------НАСТРОЙКИ ПРОФИЛЯ
    userButtSet = gtk_button_new();
    gtk_widget_set_name(userButtSet, "userButtSet");
    gtk_widget_set_size_request(GTK_WIDGET(userButtSet), 280, 90);
    gtk_button_set_relief(GTK_BUTTON(userButtSet), GTK_RELIEF_NONE); // отменяет стандартное декарирование

    userBox = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(userBox), 2);
    gtk_grid_set_row_spacing(GTK_GRID(userBox), 2);
    
    //mx_printstr(user.img);
    GdkPixbuf *px = gdk_pixbuf_new_from_file_at_size(user.img, 90, 90, NULL);
    imgUser = gtk_image_new_from_pixbuf(px);
    gtk_image_set_pixel_size(GTK_IMAGE(imgUser), 50);
    gtk_widget_set_size_request(GTK_WIDGET(imgUser), 75, 70);
    gtk_widget_set_name(imgUser, "imgChatMenu");

    nameUser = gtk_label_new(nameUs);
    gtk_widget_set_name(nameUser, "nameChatMenu");
    gtk_widget_set_size_request(GTK_WIDGET(nameUser), 180, 10);

    loginUser = gtk_label_new(login);
    gtk_widget_set_name(loginUser, "lastMassageChatMenu");
    gtk_widget_set_size_request(GTK_WIDGET(loginUser), 150, 10);

    gtk_grid_attach(GTK_GRID(userBox), imgUser, 1, 1, 1, 2);
    gtk_grid_attach(GTK_GRID(userBox), nameUser, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(userBox), loginUser, 2, 2, 1, 1);

    gtk_container_add(GTK_CONTAINER(userButtSet), userBox);

    //--------------------------------------------------НАСТРОЙКИ ОСНОВНЫЕ
    settings = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(settings, "settings1");

    GdkPixbuf *px2 = gdk_pixbuf_new_from_file_at_size("img/contacts.png", 220, 40, NULL);
    imgContacts = gtk_image_new_from_pixbuf(px2);
    contacts = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(contacts), GTK_RELIEF_NONE);
    gtk_button_set_image(GTK_BUTTON(contacts), imgContacts);
    gtk_widget_set_halign(contacts, GTK_ALIGN_START);

    GdkPixbuf *px3 = gdk_pixbuf_new_from_file_at_size("img/groups.png", 180, 40, NULL);
    imgGroup = gtk_image_new_from_pixbuf(px3);
    newGroup = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(newGroup), GTK_RELIEF_NONE);
    gtk_button_set_image(GTK_BUTTON(newGroup), imgGroup);
    gtk_widget_set_halign(newGroup, GTK_ALIGN_START);

    GdkPixbuf *px4 = gdk_pixbuf_new_from_file_at_size("img/account.png", 250, 40, NULL);
    imgAcc = gtk_image_new_from_pixbuf(px4);
    accSet = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(accSet), GTK_RELIEF_NONE);
    gtk_button_set_image(GTK_BUTTON(accSet), imgAcc);
    gtk_widget_set_halign(accSet, GTK_ALIGN_START);

    GdkPixbuf *px5 = gdk_pixbuf_new_from_file_at_size("img/language.png", 200, 40, NULL);
    imgLang = gtk_image_new_from_pixbuf(px5);
    Language = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(Language), GTK_RELIEF_NONE);
    gtk_button_set_image(GTK_BUTTON(Language), imgLang);
    gtk_widget_set_halign(Language, GTK_ALIGN_START);

    gtk_container_add(GTK_CONTAINER(settings), contacts);
    gtk_container_add(GTK_CONTAINER(settings), newGroup);
    gtk_container_add(GTK_CONTAINER(settings), accSet);
    gtk_container_add(GTK_CONTAINER(settings), Language);

    //--------------------------------------------------ВЫХОД
    footer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(footer, "footer");
    Logout = gtk_button_new_with_label("Logout");
    gtk_widget_set_name(Logout, "Logout");
    gtk_button_set_relief(GTK_BUTTON(Logout), GTK_RELIEF_NONE);

    gtk_container_add(GTK_CONTAINER(footer), Logout);
    //-----------------------------------------------Кнопка смены темы
    GdkPixbuf *px6 = gdk_pixbuf_new_from_file_at_size("img/image.png", 180, 40, NULL);
    GtkWidget *fonImg = gtk_image_new_from_pixbuf(px6);
    GtkWidget *imgFon = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(imgFon), GTK_RELIEF_NONE);
    gtk_widget_set_name(imgFon, "imgFon");
    gtk_button_set_image(GTK_BUTTON(imgFon), fonImg);

    //--------------------------------------------------ОБЩИЙ КОНТЕЙНЕР
    settingMenuBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(settingMenuBox, "settings");
    gtk_widget_set_size_request(GTK_WIDGET(settingMenuBox), 380, 500);

    gtk_container_add(GTK_CONTAINER(settingMenuBox), menu);
    gtk_container_add(GTK_CONTAINER(settingMenuBox), userButtSet);
    gtk_container_add(GTK_CONTAINER(settingMenuBox), settings);
    gtk_container_add(GTK_CONTAINER(settingMenuBox), imgFon);
    gtk_container_add(GTK_CONTAINER(settingMenuBox), footer);

    gtk_grid_attach(GTK_GRID(sideGrid), back, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(sideGrid), settingMenuBox, 1, 2, 1, 1);

    g_signal_connect_swapped(G_OBJECT(imgFon), "clicked", G_CALLBACK(mx_update_bg), G_OBJECT(window));
    g_signal_connect_swapped(G_OBJECT(accSet), "clicked", G_CALLBACK(mx_settings_user), G_OBJECT(window));

    g_signal_connect_swapped(G_OBJECT(back), "clicked", G_CALLBACK(mx_main_page), G_OBJECT(window));
    g_signal_connect_swapped(G_OBJECT(Logout), "clicked", G_CALLBACK(mx_logout), G_OBJECT(sideGrid));

    gtk_widget_show_all(sideGrid);
}
