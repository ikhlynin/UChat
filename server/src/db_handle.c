#include "../inc/server.h"

void create_db(sqlite3 **db, char *db_name)
{
    char *err_msg = NULL;
    char *db_code = NULL;
    int rc = sqlite3_open(db_name, db);
    if (rc != SQLITE_OK)
    { // esli problema
        printf("error: %s", err_msg);
        return;
    }
    else
    {
        printf("Opened db successfully\n");
    }
    db_code = mx_file_to_str("server/DB.sql");
    rc = sqlite3_exec(*db, db_code, NULL, NULL, &err_msg);
    mx_strdel(&db_code);
    if (rc)
    {
        fprintf(stderr, "Can't create: %s\n", sqlite3_errmsg(*db));
        return;
    }
    else
    {
        fprintf(stderr, "Created database successfully\n");
    }

    char *insert = "INSERT INTO `message` (`text`, `Time`, `chat_idchar`, `Sender`) VALUES ('L', '12:00', 1, '@222');"
                   "INSERT INTO `chat` (`Name`) VALUES ('@111-@222');"
                   "INSERT INTO `user` (`Login`, `Password`) VALUES('@111', 'ddd');"
                   "INSERT INTO `user` (`Login`, `Password`) VALUES('@222', 'ddd');"
                   "INSERT INTO `message` (`text`, `Time`, `chat_idchar`, `Sender`) VALUES ('Igor bitch', '13:02', 1, '@111');"
                   "INSERT INTO `user_has_chat` (`user_iduser`, `chat_idchar`) VALUES(1, 1);"
                   "INSERT INTO `user_has_chat` (`user_iduser`, `chat_idchar`) VALUES(2, 1);";
    if (sqlite3_exec(*db, insert, user_callback, NULL, &err_msg) != SQLITE_OK)
    {
        fprintf(stderr, "VARLOK error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }
}

// void register_user(sqlite3 *db, char *login, char *passwd)
// {
// }

/*char *handle_request(char *request)
{

}*/

sqlite3 *db_init(char *db_name)
{
    sqlite3 *db = NULL;
    char *str_f = mx_file_to_str(db_name);
    if (!str_f)
    {
        printf("db creating\n");
        create_db(&db, db_name);
    }
    else
    {
        int rc = sqlite3_open(db_name, &db);
        if (rc != SQLITE_OK)
        {
            printf("Error occured when tryed to open db");
        }
        else
        {
            printf("Opened db successfully\n");
        }
        printf("db already exist\n");
    }
    mx_strdel(&str_f);
    return db;
}
