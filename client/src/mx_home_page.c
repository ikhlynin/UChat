#include "client.h"

void mx_home_page()
{
  GtkWidget *grid;
  GtkWidget *logo;

  //--------------КНОПКИ
  GtkWidget *imgSingIn;
  GtkWidget *imgSingUp;
  GtkWidget *buttonSingIn;
  GtkWidget *buttonSingUp;
  // ---------------------------------------СОЗДАНИЕ ОКНА АВТОРИЗАЦИИ/РЕГИСТРАЦИИ
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "ZXChat");
  gtk_window_set_default_size(GTK_WINDOW(window), 1548, 680);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  //---------------------------------------------------РАМЕР ОСНОВНОГО ОКНА
  int width, height;
  gtk_window_get_size(GTK_WINDOW(window), &width, &height);

  //---------------------------------------------------
  //---------------------------------------------------НАЗВАНИЕ

  logo = gtk_image_new_from_file("img/zxchat.png");
  gtk_widget_set_name(logo, "ChatName");
  gtk_widget_set_size_request(GTK_WIDGET(logo), 1000, 10);

  //---------------------------------------------------СОЗДАНИ КНОПКИ АВТОРИЗАЦИИ

  imgSingIn = gtk_image_new_from_file("img/sign_in_button2.png");
  buttonSingIn = gtk_button_new();
  gtk_widget_set_hexpand(buttonSingIn, FALSE);
  gtk_widget_set_vexpand(buttonSingIn, FALSE);
  gtk_widget_set_halign(buttonSingIn, GTK_ALIGN_CENTER);
  gtk_button_set_image(GTK_BUTTON(buttonSingIn), imgSingIn);

  gtk_widget_set_name(buttonSingIn, "buttonSingIn");
  gtk_button_set_relief(GTK_BUTTON(buttonSingIn), GTK_RELIEF_NONE); // отменяет стандартное декарирование
  gtk_widget_set_size_request(GTK_WIDGET(buttonSingIn), 98, 10);

  //---------------------------------------------------СОЗДАНИ КНОПКИ РЕГИСТРАЦИИ

  imgSingUp = gtk_image_new_from_file("img/sign_up_button2.png");
  buttonSingUp = gtk_button_new();
  gtk_widget_set_hexpand(buttonSingUp, FALSE);
  gtk_widget_set_vexpand(buttonSingUp, FALSE);
  gtk_widget_set_halign(buttonSingUp, GTK_ALIGN_CENTER);
  gtk_button_set_image(GTK_BUTTON(buttonSingUp), imgSingUp);

  gtk_widget_set_name(buttonSingUp, "buttonSingUp");
  gtk_button_set_relief(GTK_BUTTON(buttonSingUp), GTK_RELIEF_NONE); // отменяет стандартное декарирование
  gtk_widget_set_size_request(GTK_WIDGET(buttonSingUp), 98, 10);

  //---------------------------------------------------ФОРМИРОВАНИЕ СЕТКИ

  grid = gtk_grid_new();
  gtk_widget_set_name(grid, "myGrid");
  gtk_widget_set_halign(logo, GTK_ALIGN_CENTER);

  gtk_grid_set_column_spacing(GTK_GRID(grid), 1);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 6);

  //---------------------------------------------------РАЗМЕЩЕНИЕ НА СЕТКЕ

  gtk_grid_attach(GTK_GRID(grid), buttonSingIn, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), buttonSingUp, 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), logo, 1, 0, 1, 1);

  //---------------------------------------------------ОТРАБОТКА СИГНАЛОВ КНОПОК

  g_signal_connect(G_OBJECT(buttonSingIn), "clicked", G_CALLBACK(mx_sign_In_page), G_OBJECT(window));
  g_signal_connect(G_OBJECT(buttonSingUp), "clicked", G_CALLBACK(mx_sign_Up_page), G_OBJECT(window));

  gtk_container_add(GTK_CONTAINER(window), grid);
  gtk_widget_show_all(window);
}
