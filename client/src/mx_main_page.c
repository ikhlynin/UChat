#include "client.h"

void mx_main_page(gpointer window)
{

    if (gtk_container_get_children(GTK_CONTAINER(window)))
        gtk_container_remove(GTK_CONTAINER(window), gtk_container_get_children(GTK_CONTAINER(window))->data);

    GtkWidget *sidePanel;

    GtkWidget *grid;
    // КНОПКИ

    // ---------------------------------------Side panel top menu
    GtkWidget *buttonMenu;
    GtkWidget *imgButtonMenu;
    GtkWidget *searchBox;
    GtkWidget *imgSearchButton;
    GtkWidget *searchEntry;
    GtkWidget *searchButton;

    GtkWidget *scrolledwindow;
    // ---------------------------------------СОЗДАНИЕ ОКНА ЧАТОВ

    // ---------------------------------------СОЗДАНИЕ СЕТКИ МЕНЮ
    sidePanel = gtk_grid_new();
    gtk_widget_set_name(sidePanel, "sidePanel");
    gtk_grid_set_column_spacing(GTK_GRID(sidePanel), 1);
    gtk_grid_set_row_spacing(GTK_GRID(sidePanel), 1);

    // ---------------------------------------Side panel top menu
    // кнопка открытия настроек
    imgButtonMenu = gtk_image_new_from_file("img/menu_icon.png");
    buttonMenu = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(buttonMenu), imgButtonMenu);
    gtk_widget_set_name(buttonMenu, "imgButtonMenu");
    gtk_button_set_relief(GTK_BUTTON(buttonMenu), GTK_RELIEF_NONE); // отменяет стандартное декарирование

    //КОНТЕЙНЕР ПОИСКА  ( нукинуть стили )

    imgSearchButton = gtk_image_new_from_file("img/search_icon.png");
    searchButton = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(searchButton), imgSearchButton);
    gtk_widget_set_name(searchButton, "searchButton");
    gtk_button_set_relief(GTK_BUTTON(searchButton), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(imgSearchButton), 10, 10);

    searchEntry = gtk_entry_new();
    gtk_widget_set_hexpand(searchEntry, FALSE);
    gtk_widget_set_vexpand(searchEntry, FALSE);
    gtk_widget_set_halign(searchEntry, GTK_ALIGN_CENTER);
    gtk_widget_set_name(searchEntry, "searchEntry");
    gtk_entry_set_placeholder_text(GTK_ENTRY(searchEntry), "Search...");
    gtk_widget_set_size_request(GTK_WIDGET(searchEntry), 100, 10);

    searchBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 40);
    gtk_widget_set_name(searchBox, "topBox");
    gtk_widget_set_halign(searchBox, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(searchBox), 180, 20);

    gtk_container_add(GTK_CONTAINER(searchBox), searchButton);
    gtk_container_add(GTK_CONTAINER(searchBox), searchEntry);

    g_signal_connect_swapped(G_OBJECT(searchButton), "clicked", G_CALLBACK(mx_search_chat), G_OBJECT(window));

    // добавление в сетку меню  компонент
    gtk_grid_attach(GTK_GRID(sidePanel), buttonMenu, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(sidePanel), searchBox, 1, 0, 1, 1);

    //-----------------------------------------------КОНТЕЙНЕР ЧАТОВ
    GtkWidget *bbb;
    bbb = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_show(scrolledwindow);
    gtk_widget_set_name(scrolledwindow, "scrole");
    gtk_widget_set_size_request(GTK_WIDGET(scrolledwindow), 380, 770);

    gtk_container_add(GTK_CONTAINER(scrolledwindow), bbb);

    gtk_grid_attach(GTK_GRID(sidePanel), scrolledwindow, 0, 1, 2, 1);
    ///////////////////////////////////////////////////////////////

    //---------------------------------------------------ФОРМИРОВАНИЕ ОСНОВНОЙ СЕТКИ**
    grid = gtk_grid_new();
    gtk_widget_set_name(grid, bgImg);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
    gtk_grid_attach(GTK_GRID(grid), sidePanel, 0, 1, 1, 1);

    g_signal_connect_swapped(G_OBJECT(buttonMenu), "clicked", G_CALLBACK(mx_settings_page), G_OBJECT(window));

    gtk_container_add(GTK_CONTAINER(window), grid);

    mx_slot_chat(bbb, window); //FORK функция создания ячейки чата
    //---------------------------------------------------ФОРМИРОВАНИЕ СЕТКИ ТЕКУЩЕГО ЧАТА

    gtk_widget_show_all(window);
    if (!flag)
    {
        pthread_t tid;
        pthread_attr_t attr;

        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, &event_listner, G_OBJECT(window));
    }
}
