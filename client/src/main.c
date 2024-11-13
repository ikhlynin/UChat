#include "client.h"

int main(int argc, char *argv[])
{
    nameUs = "Komushki";
    bio = "Не выбил деда(";
    bgImg = "wrapper";
    gtk_init(&argc, &argv);
    mx_connect(argc, argv);
    load_css();

    // g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
    // g_signal_connect        ( window, "destroy", gtk_main_quit, window );

    mx_home_page();

    gtk_main();
}
