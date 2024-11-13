
#include "client.h"

void mx_update_bg(gpointer window)
{
    GList *wd = gtk_container_get_children(GTK_CONTAINER(window));
    GtkWidget *grid = wd->data;
    if (mx_strcmp(bgImg, "wrapper") == 0)
    {
        bgImg = mx_strdup("wrapper1");
        gtk_widget_set_name(grid, bgImg);
    }
    else if (mx_strcmp(bgImg, "wrapper1") == 0)
    {
        bgImg = mx_strdup("wrapper2");
        gtk_widget_set_name(grid, bgImg);
        // gtk_widget_set_name(grid, "wrapper2");
    }
    else if (mx_strcmp(bgImg, "wrapper2") == 0)
    {
        bgImg = mx_strdup("wrapper");
        gtk_widget_set_name(grid, bgImg);
        // gtk_widget_set_name(grid, "wrapper");
    }
}
