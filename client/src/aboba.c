#include "client.h"
// info.image = gtk_image_new_from_file("/Users/ikhlynin/Desktop/ikhlynin/client/img/zxchat.png");
// gtk_widget_set_name(info.image, "ChatName");

// //gtk_widget_set_size_request(GTK_WIDGET(info.image),50,100);// установка размера

// /// ***
// info.password_label = gtk_label_new("Password: ");
// //gtk_widget_set_margin_start ( info.password_label, 10 );
// gtk_widget_set_size_request(GTK_WIDGET(info.password_label), 50, 100);
// /// ***

// info.userName_label = gtk_label_new("Username: ");
// gtk_widget_set_margin_start(info.userName_label, 10);

// info.userName_entry = gtk_entry_new();
// gtk_widget_set_size_request(GTK_WIDGET(info.userName_entry), width / 100 * 10, height / 100 * 60);
// info.password_entry = gtk_entry_new();
// // Govno
// // /// *** 
// gtk_entry_set_max_length(GTK_ENTRY(info.password_entry), 20);
// gtk_entry_set_visibility(GTK_ENTRY(info.password_entry), FALSE);
// gtk_entry_set_invisible_char(GTK_ENTRY(info.password_entry), '*');
// // /// ***
// // g_signal_connect_swapped ( info.name_entry,     "activate", G_CALLBACK ( activate_callback ), info.name_entry );
// // g_signal_connect_swapped ( info.userName_entry, "activate", G_CALLBACK ( activate_callback ), info.userName_entry );
// // g_signal_connect_swapped ( info.password_entry, "activate", G_CALLBACK ( activate_callback ), info.password_entry );
// // g_signal_connect_swapped ( info.email_entry,    "activate", G_CALLBACK ( activate_callback ), info.email_entry );
// // g_signal_connect_swapped ( info.phone_entry,    "activate", G_CALLBACK ( activate_callback ), info.phone_entry );
// // g_signal_connect_swapped ( info.phone_entry,    "activate", G_CALLBACK ( zero_to_nine_keys_callback ), info.phone_entry );
// // /// ***
// // g_signal_connect_swapped ( info.phone_entry, "key_press_event", G_CALLBACK ( zero_to_nine_keys_callback ), info.phone_entry );
// // /// ***
// info.imgSingIn = gtk_image_new_from_file("/Users/ikhlynin/Desktop/ikhlynin/client/img/sign_in_button2.png");
// info.buttonSingIn = gtk_button_new();
// gtk_widget_set_name(info.buttonSingIn, "myButton1");



    

// gtk_widget_set_size_request(GTK_WIDGET(info.buttonSingIn), 10, 10);

// gtk_button_set_image(GTK_BUTTON(info.buttonSingIn), info.imgSingIn);
// //
// // gtk_container_add(GTK_CONTAINER(info.buttonSingIn), info.imgSingIn);

// info.submit_button1 = gtk_button_new_with_mnemonic("Sing in");
// gtk_widget_set_name(info.submit_button1, "myButton");
// /// ***
// g_signal_connect_swapped ( info.buttonSingIn, "clicked", G_CALLBACK ( submit_clicked ), info.name_entry );
// g_signal_connect_swapped ( info.buttonSingIn, "clicked", G_CALLBACK ( submit_clicked ), info.userName_entry );
// g_signal_connect_swapped ( info.buttonSingIn, "clicked", G_CALLBACK ( submit_clicked ), info.password_entry );
// g_signal_connect_swapped ( info.buttonSingIn, "clicked", G_CALLBACK ( submit_clicked ), info.email_entry );
// g_signal_connect_swapped ( info.buttonSingIn, "clicked", G_CALLBACK ( submit_clicked ), info.phone_entry );
/// ***

// gtk_grid_attach(GTK_GRID(info.grid), info.image, 5, 4, 6, 1);

// gtk_grid_attach ( GTK_GRID ( info.grid ), info.name_label,      0, 1, 1, 1 );
// gtk_grid_attach ( GTK_GRID ( info.grid ), info.userName_label,  0, 2, 1, 1 );
// gtk_grid_attach ( GTK_GRID ( info.grid ), info.password_label,  0, 3, 1, 1 );
// gtk_grid_attach ( GTK_GRID ( info.grid ), info.email_label,     0, 4, 1, 1 );
// x ( GTK_GRID ( info.grid ), info.phone_label,     0, 5, 1, 1 );
/// ***

// gtk_grid_attach(GTK_GRID(info.grid), info.userName_entry, 1, 2, 1, 1);
// gtk_grid_attach(GTK_GRID(info.grid), info.password_entry, 1, 3, 1, 1);
// gtk_grid_attach(GTK_GRID(info.grid), info.submit_button1, 1, 2, 1, 1);
// gtk_grid_attach(GTK_GRID(info.grid), info.buttonSingIn, 5, 5, 1, 1);
// gtk_grid_attach ( GTK_GRID ( info.grid ), info.buttonSingIn,   1, 6, 1, 1 );
// /// ***
// gtk_widget_set_sensitive ( info.userName_entry,  FALSE );
// gtk_widget_set_sensitive ( info.password_entry,  FALSE );
// gtk_widget_set_sensitive ( info.phone_entry,     FALSE );
// gtk_widget_set_sensitive ( info.email_entry,     FALSE );
// gtk_widget_set_sensitive ( info.buttonSingIn,   FALSE );

// #include "client.h"

// // static guint flag = 0;

// // gboolean zero_to_nine_keys_callback ( GtkWidget *widget, GdkEventKey *event );
// // void submit_clicked ( GtkWidget *widget );
// // void load_css ( void );
// // GtkWidget *createWindow ( const gint width, const gint height );
// // void activate_callback ( GtkWidget *widget );

// int main(int argc, char *argv[])
// {
//     gtk_init(&argc, &argv);
//     load_css();

//     // g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
//     // g_signal_connect        ( window, "destroy", gtk_main_quit, window );

//     //gtk_container_set_border_width  ( GTK_CONTAINER ( window ), 150 );

//     mx_home_page();

//     gtk_main();
// }

// void activate_callback ( GtkWidget *widget )
// {
//     const gchar *text = gtk_entry_get_text ( GTK_ENTRY ( widget ) );

//     if ( strlen ( text ) > 0 )
//     {
//         switch ( flag )
//         {
//         case 0:
//             gtk_widget_set_sensitive ( info.userName_entry, TRUE );
//             gtk_entry_grab_focus_without_selecting ( GTK_ENTRY ( info.userName_entry ) );
//             gtk_widget_set_sensitive ( info.name_entry,  FALSE );
//             flag++;
//             break;

//         case 1:
//             gtk_widget_set_sensitive ( info.password_entry, TRUE );
//             gtk_entry_grab_focus_without_selecting ( GTK_ENTRY ( info.password_entry ) );
//             gtk_widget_set_sensitive ( info.userName_entry,  FALSE );
//             flag++;
//             break;

//         case 2:
//             gtk_widget_set_sensitive ( info.email_entry, TRUE );
//             gtk_entry_grab_focus_without_selecting ( GTK_ENTRY ( info.email_entry ) );
//             gtk_widget_set_sensitive ( info.password_entry,  FALSE );
//             flag++;
//             break;

//         case 3:
//             gtk_widget_set_sensitive ( info.phone_entry, TRUE );
//             gtk_entry_grab_focus_without_selecting ( GTK_ENTRY ( info.phone_entry ) );
//             gtk_widget_set_sensitive ( info.email_entry,  FALSE );
//             flag++;
//             break;

//         case 4:
//             gtk_widget_set_sensitive ( info.submit_button, TRUE );
//             gtk_window_set_focus ( GTK_WINDOW ( info.window ), info.submit_button );
//             gtk_widget_set_sensitive ( info.phone_entry,  FALSE );
//             flag++;
//             break;

//         default:
//             flag = 5;
//         }
//     }
// }

// void submit_clicked ( GtkWidget *widget )
// {
//     static guchar status = 0;

//     if ( status < 5  )
//     {
//         g_print ( "%s\n", gtk_entry_get_text ( GTK_ENTRY ( widget ) ) );
//         gtk_widget_set_sensitive ( info.phone_entry,  FALSE );
//         status++;
//     }
// }

// gboolean zero_to_nine_keys_callback ( GtkWidget *widget, GdkEventKey *event )
// {
//     ( void ) widget;
//     guint keys[11] =
//     {
//         GDK_KEY_0, GDK_KEY_1, GDK_KEY_2, GDK_KEY_3, GDK_KEY_4,
//         GDK_KEY_5, GDK_KEY_6, GDK_KEY_7, GDK_KEY_8, GDK_KEY_9,
//         GDK_KEY_BackSpace
//     };

//     for ( guint i = 0 ; i < 11 ; i++ )
//     {
//         if ( event->keyval == keys[i] )
//         {
//             if ( gtk_widget_get_sensitive ( info.submit_button ) == FALSE )
//             {
//                 gtk_widget_set_sensitive ( info.submit_button, TRUE );
//             }

//             return FALSE;
//         }
//     }

//     return TRUE;
// }
