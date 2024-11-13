#include "client.h"

void mx_proceed_login(gpointer window)
{
    int entry = 0;
    //g_print("sasda");

    GList *childrenGrid, *iter, *childrenWin;

    childrenWin = gtk_container_get_children(GTK_CONTAINER(window));
    GtkWidget *grid = childrenWin->data;

    childrenGrid = gtk_container_get_children(GTK_CONTAINER(grid));
    childrenGrid = g_list_next(childrenGrid);

    char *toSend;
    toSend = mx_strjoin(toSend, "/log");
    int i = 0;
    for (iter = childrenGrid; iter != NULL && entry < 2; iter = g_list_next(iter), entry++, i++)
    {
        toSend = mx_strjoin(toSend, "\1");
        if (i == 1)
            toSend = mx_strjoin(toSend, "@");
        toSend = mx_strjoin(toSend, (char *)gtk_entry_get_text(GTK_ENTRY(iter->data)));
    }
    //char **regData = mx_strsplit(toSend, "\1");
    if (1 == 2)
    {
    }
    else
    {
        send_msg_to_serv(toSend);
        if (!serv_resp())
        {
            gtk_widget_destroy(window);
            GtkWidget *window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_window_set_title(GTK_WINDOW(window1), "ZXChat");
            gtk_window_set_default_size(GTK_WINDOW(window1), 1548, 892);
            gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

            loadMain = load_main();
            flag = 0;
            //if (!mx_strsplit((const char *)load_main, '\1')[1])
            parse_str(loadMain);
            //mx_strdel(&loadMain);
            mx_main_page(window1);
        }
    }
}
