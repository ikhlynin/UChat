#include "client.h"

void mx_proceed_registration(gpointer window)
{

    int entry = 0;
    int count_err = 0;

    GList *
        childrenGrid,
        *iter, *childrenWin;

    childrenWin = gtk_container_get_children(GTK_CONTAINER(window));
    GtkWidget *grid = childrenWin->data;

    childrenGrid = gtk_container_get_children(GTK_CONTAINER(grid));
    while (childrenGrid != NULL)
    {
        count_err++;
        childrenGrid = g_list_next(childrenGrid);
    }

    childrenGrid = gtk_container_get_children(GTK_CONTAINER(grid));
    if (count_err == 6)
    {
        gtk_widget_destroy(childrenGrid->data);
    }
    childrenGrid = gtk_container_get_children(GTK_CONTAINER(grid));
    int count = 0;
    childrenGrid = g_list_next(childrenGrid);

    for (iter = childrenGrid; iter != NULL && count < 3; iter = g_list_next(iter), count++)
    {
        gtk_widget_set_name(iter->data, "entry");
    }

    childrenGrid = gtk_container_get_children(GTK_CONTAINER(grid));
    childrenGrid = g_list_next(childrenGrid);
    char **regData = malloc(sizeof(char **) * 1024);
    for (iter = childrenGrid; iter != NULL && entry < 3; iter = g_list_next(iter), entry++)
    {
        regData[entry] = (char *)gtk_entry_get_text(GTK_ENTRY(iter->data));
    }
    if (mx_strlen(regData[2]) == 0 || mx_strlen(regData[1]) == 0 || mx_strlen(regData[0]) == 0)
    {

        if (mx_strlen(regData[2]) == 0 && mx_strlen(regData[1]) != 0 && mx_strlen(regData[0]) != 0)
        {

            childrenGrid = gtk_container_get_children(GTK_CONTAINER(childrenWin->data));
            childrenGrid = g_list_next(childrenGrid);
            childrenGrid = g_list_next(childrenGrid);
            childrenGrid = g_list_next(childrenGrid);
            gtk_widget_set_name(childrenGrid->data, "entryError");
            //g_list_free(childrenGrid);
            mx_sign_Up_page(NULL, window, "Enter username");
        }

        else if (mx_strlen(regData[1]) == 0 && mx_strlen(regData[2]) != 0 && mx_strlen(regData[0]) != 0)
        {

            childrenGrid = gtk_container_get_children(GTK_CONTAINER(childrenWin->data));
            childrenGrid = g_list_next(childrenGrid);
            childrenGrid = g_list_next(childrenGrid);
            gtk_widget_set_name(childrenGrid->data, "entryError");
            g_list_free(childrenGrid);
            mx_sign_Up_page(NULL, window, "Enter password");
        }

        else if (mx_strlen(regData[0]) == 0 && mx_strlen(regData[2]) != 0 && mx_strlen(regData[1]) != 0)
        {
            childrenGrid = gtk_container_get_children(GTK_CONTAINER(childrenWin->data));
            childrenGrid = g_list_next(childrenGrid);
            gtk_widget_set_name(childrenGrid->data, "entryError");
            mx_sign_Up_page(NULL, window, "Enter repeat password");
        }
        else
        {
            int count = 0;
            childrenGrid = gtk_container_get_children(GTK_CONTAINER(childrenWin->data));
            childrenGrid = g_list_next(childrenGrid);

            if (mx_strlen(regData[0]) != 0)
            {
                childrenGrid = g_list_next(childrenGrid);
                for (iter = childrenGrid; iter != NULL && count < 2; iter = g_list_next(iter), count++)
                    gtk_widget_set_name(iter->data, "entryError");
            }
            else if (mx_strlen(regData[1]) != 0)
            {
                gtk_widget_set_name(childrenGrid->data, "entryError");
                childrenGrid = g_list_next(childrenGrid);
                childrenGrid = g_list_next(childrenGrid);
                gtk_widget_set_name(childrenGrid->data, "entryError");
            }
            else if (mx_strlen(regData[2]) != 0)
            {
                for (iter = childrenGrid; iter != NULL && count < 2; iter = g_list_next(iter), count++)
                    gtk_widget_set_name(iter->data, "entryError");
            }
            else
            {
                for (iter = childrenGrid; iter != NULL && count < 3; iter = g_list_next(iter), count++)
                    gtk_widget_set_name(iter->data, "entryError");
            }
            mx_sign_Up_page(NULL, window, "Enter data in the fields");
        }
    }
    else if (mx_strcmp(regData[1], regData[0]) != 0)
    {
        childrenGrid = gtk_container_get_children(GTK_CONTAINER(childrenWin->data));
        childrenGrid = g_list_next(childrenGrid);
        gtk_widget_set_name(childrenGrid->data, "entryError");
        mx_sign_Up_page(NULL, window, "Password not match");
    }
    else //proceed
    {

        char *toSend = NULL;
        mx_str_concat(&toSend, "/reg");
        for (int i = 1; i < 3; i++)
        {
            mx_str_concat(&toSend, "\1");
            if (i == 2)
                mx_str_concat(&toSend, "@");
            mx_str_concat(&toSend, regData[i]);
        }
        send_msg_to_serv(toSend);

        if (!serv_resp())
            mx_sign_In_page(NULL, G_OBJECT(window));

        else
            mx_sign_Up_page(NULL, G_OBJECT(window), "User already exist");
    }
}
