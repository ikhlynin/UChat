#include "../inc/server.h"

void print_to_send_str(char *to_send)
{
    for (int i = 0; to_send[i] != 0; i++)
    {
        if (to_send[i] == '\1')
            mx_printstr("\\");
        else if (to_send[i] == '\2')
            mx_printstr("|");
        else
            mx_printchar(to_send[i]);
    }
    mx_printchar('\n');
}

char *insert_in_str(char **str, char *sub, char *repl)
{
    char *buf = NULL;
    buf = mx_replace_substr(*str, sub, repl);
    mx_strdel(str);
    *str = buf;
    return *str;
}

void sql_execute(sqlite3 *db, char *sql, char ***out_arr)
{
    char *err_msg = NULL;
    int rc = 0;
    rc = sqlite3_exec(db, sql, call_for_text, out_arr, &err_msg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

char *concat_arr_to_str(char **str, char **arr)
{
    if (!arr)
    {
        return *str;
    }
    else
    {
        for (int i = 0; arr[i]; i++)
        {
            mx_str_concat(str, arr[i]);
            if (arr[i + 1])
                mx_str_concat(str, "\1");
        }
    }
    return *str;
}

char *replace_sub(char **str, char *sub, char *replace)
{
    char *buf = mx_replace_substr(*str, sub, replace);
    mx_strdel(str);
    *str = buf;
    return buf;
}

char *get_time(void)
{
    time_t curr_time = time(NULL);
    char **cur_text_time = mx_strsplit(ctime(&curr_time), ' ');
    char **buf = mx_strsplit(cur_text_time[3], ':');
    char *res_time = NULL;
    mx_str_concat(&res_time, buf[0]);
    mx_str_concat(&res_time, ":");
    mx_str_concat(&res_time, buf[1]);
    mx_del_strarr(&buf);
    mx_del_strarr(&cur_text_time);
    return res_time;
}

void msg_send(sqlite3 *db, char *sender, char *chat_name, char *text, int senderfd, int reciverfd, char *reciver)
{
    char *insert = mx_strdup("INSERT INTO `message` (`chat_idchar`, `text`, `Time`, `Sender`) VALUES (\1, '\2', '\3', '\4');");
    char *sql = mx_strdup("SELECT `idchar` FROM `chat` WHERE `Name` = '\1'");
    char **msg_arr = NULL;
    char *to_send_sender = NULL;
    char *to_send_reciver = NULL;
    replace_sub(&sql, "\1", chat_name);
    sql_execute(db, sql, &msg_arr);
    if (!msg_arr)
    {
        printf("No %s chat found\n", chat_name);
        mx_strdel(&insert);
        mx_strdel(&sql);
        return;
    }
    char *curr_time = get_time();
    replace_sub(&insert, "\1", msg_arr[0]);
    replace_sub(&insert, "\2", text);
    replace_sub(&insert, "\3", curr_time);
    replace_sub(&insert, "\4", sender);

    sql_execute(db, insert, NULL);

    to_send_sender = mx_strdup("/msgs\1");
    mx_str_concat(&to_send_sender, chat_name);
    mx_str_concat(&to_send_sender, "\1");
    mx_str_concat(&to_send_sender, text);
    mx_str_concat(&to_send_sender, "\2");
    mx_str_concat(&to_send_sender, curr_time);
    mx_str_concat(&to_send_sender, "\2");
    to_send_reciver = mx_strjoin(to_send_sender, "0\1");
    mx_str_concat(&to_send_sender, "1\1");
    send_msgs(db, chat_name, senderfd, sender);
    // send_msg_to_cli(senderfd, to_send_sender);
    // printf("Sock1 %d, Sock2 %d\n", senderfd, reciverfd);
    if (reciverfd != -1 && reciver)
    {
        send_msgs(db, chat_name, reciverfd, reciver);
    }

    // send_msg_to_cli(reciverfd, to_send_reciver);
    mx_strdel(&curr_time);
    mx_strdel(&to_send_sender);
    mx_strdel(&to_send_reciver);
    mx_strdel(&insert);
    mx_strdel(&sql);
}

void create_new_chat(sqlite3 *db, char *sender, char *reciver, int sockfd)
{
    char **usr_arr = NULL;
    char **chat_arr = NULL;
    char *insert = mx_strdup("INSERT INTO `chat` (`Name`) VALUES ('\1-\2');");
    replace_sub(&insert, "\1", sender);
    replace_sub(&insert, "\2", reciver);
    sql_execute(db, insert, NULL);
    mx_strdel(&insert);
    char *sql = mx_strdup("SELECT `iduser` FROM `user` WHERE `Login` = '\1' OR `Login` = '\2'");
    replace_sub(&sql, "\1", sender);
    replace_sub(&sql, "\2", reciver);
    sql_execute(db, sql, &usr_arr);
    mx_strdel(&sql);
    sql = mx_strdup("SELECT `idchar` FROM `chat` WHERE `Name` = '\1-\2'");
    replace_sub(&sql, "\1", sender);
    replace_sub(&sql, "\2", reciver);
    sql_execute(db, sql, &chat_arr);
    mx_strdel(&sql);
    insert = mx_strdup("INSERT INTO `user_has_chat` (`user_iduser`, `chat_idchar`) VALUES (\3, \4);"
                       "INSERT INTO `user_has_chat` (`user_iduser`, `chat_idchar`) VALUES (\6, \4);"
                       "INSERT INTO `message` (`text`, `Time`, `chat_idchar`, `Sender`) VALUES ('1000-7?', '\5', \4, '\1');"
                       "INSERT INTO `message` (`text`, `Time`, `chat_idchar`, `Sender`) VALUES ('993', '\5', \4, '\2');");
    replace_sub(&insert, "\1", sender);
    replace_sub(&insert, "\2", reciver);
    replace_sub(&insert, "\3", usr_arr[0]);
    replace_sub(&insert, "\6", usr_arr[1]);
    replace_sub(&insert, "\4", chat_arr[0]);
    char *cur_time = get_time();
    replace_sub(&insert, "\5", cur_time);
    mx_strdel(&cur_time);
    sql_execute(db, insert, NULL);
    char *chat_name = NULL;
    mx_str_concat(&chat_name, sender);
    mx_str_concat(&chat_name, "-");
    mx_str_concat(&chat_name, reciver);
    send_chats_of_user(db, sender, sockfd);
    mx_strdel(&chat_name);
    mx_strdel(&cur_time);
    mx_del_strarr(&usr_arr);
    mx_del_strarr(&chat_arr);
}

void send_msgs(sqlite3 *db, char *chat_name, int sockfd, char *login)
{
    char *sql = "SELECT `text`, `Time`, `Sender` FROM `message` WHERE `chat_idchar` IN (SELECT `idchar` FROM `chat` WHERE `Name` = '\1') ORDER BY `idmessage`";
    char **msg_arr = NULL;
    char *buf = NULL;
    char **buf_arr = NULL;
    char *to_send = NULL;
    sql = mx_replace_substr(sql, "\1", chat_name);
    sql_execute(db, sql, &msg_arr);
    for (int i = 0; msg_arr && msg_arr[i]; i++)
    {
        if (mx_strstr(msg_arr[i], login))
        {
            buf = mx_replace_substr(msg_arr[i], login, "1");
        }
        else
        {
            buf_arr = mx_strsplit(msg_arr[i], '\2');
            buf = mx_replace_substr(msg_arr[i], buf_arr[2], "0");
            mx_del_strarr(&buf_arr);
        }
        mx_strdel(&msg_arr[i]);
        msg_arr[i] = buf;
    }
    mx_str_concat(&to_send, "/msgs\1");
    mx_str_concat(&to_send, chat_name);
    mx_str_concat(&to_send, "\1");
    concat_arr_to_str(&to_send, msg_arr);
    // print_to_send_str(to_send);
    send_chats_of_user(db, login, sockfd);
    send_msg_to_cli(sockfd, to_send);
    mx_del_strarr(&msg_arr);
    mx_strdel(&to_send);
}

void send_chats_of_user(sqlite3 *db, char *login, int sockfd)
{
    char *sql_user = "SELECT `Foto` FROM `user` WHERE `Login` = '\1'";
    char *sql_msg = "SELECT `Name`, `Path`, `text`, `Time` FROM `chat` LEFT JOIN `message` ON `chat`.`idchar` = `message`.`chat_idchar` WHERE `idmessage` IS NULL OR `idmessage` IN (SELECT MAX(`idmessage`) FROM `message` GROUP BY `chat_idchar`) AND `idchar` IN (SELECT `chat_idchar` FROM `user_has_chat` WHERE `user_iduser` IN (SELECT `iduser` FROM `user` WHERE `Login` = '\1'))";
    sql_user = mx_replace_substr(sql_user, "\1", login);
    sql_msg = mx_replace_substr(sql_msg, "\1", login);
    char **user_arr = NULL;
    char **msg_arr = NULL;
    char *to_send = NULL;
    sql_execute(db, sql_user, &user_arr);
    sql_execute(db, sql_msg, &msg_arr);
    mx_str_concat(&to_send, login);
    mx_str_concat(&to_send, "\1");

    concat_arr_to_str(&to_send, user_arr);

    mx_str_concat(&to_send, "\1");

    concat_arr_to_str(&to_send, msg_arr);
    send_msg_to_cli(sockfd, to_send);

    // print_to_send_str(to_send);
    mx_strdel(&to_send);
    mx_del_strarr(&msg_arr);
    mx_del_strarr(&user_arr);
}

char *compress_arr_into_str(char **arr)
{
    char *res = NULL;
    int ct = 0;
    for (; arr[ct]; ct++)
        ;

    mx_str_concat(&res, arr[0]);
    mx_str_concat(&res, "\1");
    mx_str_concat(&res, arr[1]);
    mx_str_concat(&res, "\1");

    int j = 2;
    while (j < ct)
    {
        int i = 2;
        for (; i < 6; i++)
        {
            mx_str_concat(&res, arr[j]);
            if (i < 5)
            {
                mx_str_concat(&res, "\2");
            }

            j++;
        }
        if (j < ct - 1)
        {
            mx_str_concat(&res, "\1");
        }
    }

    return res;
}

char **add_new_in_arr(char ***arr, char *new)
{
    if (!(*arr))
    {
        *arr = (char **)malloc(sizeof(char *) * 2);
        (*arr)[0] = NULL;
        (*arr)[1] = NULL;
    }
    int size = 0;
    for (int i = 0; (*arr)[i]; i++)
        size++;
    *arr = mx_realloc(*arr, sizeof(char *) * (size + 2));
    (*arr)[size] = new;
    (*arr)[size + 1] = NULL;
    return *arr;
}

int call_for_text(void *data, int argc, char **argv, char **azColName)
{
    if (data == NULL)
        return 0;
    char ***out_arr = (char ***)data;
    char *str_to_return = NULL;
    printf("SQL -> { ");
    for (int i = 0; i < argc; i++)
    {
        printf("'%s' : '%s'", azColName[i], argv[i] ? argv[i] : "NULL");
        if (i + 1 < argc)
            printf(" , ");
    }
    printf(" }\n");
    for (int i = 0; i < argc; i++)
    {
        if (!argv[i])
            continue;
        mx_str_concat(&str_to_return, argv[i]);
        if (i + 1 < argc)
            mx_str_concat(&str_to_return, "\2");
    }
    add_new_in_arr(out_arr, str_to_return);
    return 0;
}
//
int login_client(sqlite3 *db, char *login, char *passwd)
{
    char *err_msg = NULL;
    int res = -1;
    int rc = 0;
    bool is_exisst = false;
    char **passwd_in_db = NULL;
    char *sql = "SELECT EXISTS(SELECT `Password` FROM `user` WHERE `Login` = '\1');";
    sql = mx_replace_substr(sql, "\1", login);
    rc = sqlite3_exec(db, sql, call_for_text, &passwd_in_db, &err_msg);
    if (!mx_strcmp(passwd_in_db[0], "1"))
    {
        mx_strdel(&sql);
        sql = "SELECT `Password` FROM `user` WHERE `Login` = '\1'";
        sql = mx_replace_substr(sql, "\1", login);
        mx_del_strarr(&passwd_in_db);
        rc = sqlite3_exec(db, sql, call_for_text, &passwd_in_db, &err_msg);
        if (!mx_strcmp(passwd_in_db[0], passwd))
        {
            printf("server -> %s logged in\n", login);
            res = 0;
        }
        else
        {
            printf("server -> Password didn't match\n");
        }
    }
    else
    {
        printf("server -> User %s not found\n", login);
        res = 1;
    }
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Login SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return res;
    }
    return res;
}

int register_client(sqlite3 *db, char *login, char *passwd)
{
    char *err_msg = NULL;
    int rc = 0;
    char *sql = "SELECT EXISTS(SELECT `Login` FROM `user` WHERE `Login` = '/1');";
    bool is_registered = true;
    sql = mx_replace_substr(sql, "/1", login);
    rc = sqlite3_exec(db, sql, user_callback, &is_registered, &err_msg);
    mx_strdel(&sql);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "register SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    mx_printstr(is_registered ? "Login already in use\n" : "Registered new user\n");
    if (!is_registered)
    {
        sql = "INSERT INTO `user` (`Login`, `Password`) VALUES ('/1', '/2');";
        err_msg = mx_replace_substr(sql, "/1", login);
        sql = mx_replace_substr(err_msg, "/2", passwd);
        mx_strdel(&err_msg);
        sqlite3_exec(db, sql, user_callback, &is_registered, NULL);
        mx_strdel(&sql);
        return 0;
    }
    return 1;
}

int user_callback(void *data, int argc, char **argv, char **azColName)
{
    bool *data_b = (bool *)data;
    if (!mx_strcmp(argv[0], "0"))
    {
        *data_b = false;
    }
    printf("\n");
    return 0;
}
