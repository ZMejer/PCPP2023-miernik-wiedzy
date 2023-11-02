#include "DatabaseHandler.hpp"
#include <iostream>

DatabaseHandler::DatabaseHandler(const char *server, const char *user, const char *password, const char *database, int port) {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    if (mysql_real_connect(conn, server, user, password, database, port, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
    }
}

DatabaseHandler::~DatabaseHandler() {
    mysql_close(conn);
}

bool DatabaseHandler::executeQuery(const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return false;
    }
    return true;
}

MYSQL_RES *DatabaseHandler::storeResult() {
    return mysql_store_result(conn);
}

// Implementujemy nową metodę do pobierania wszystkich pytań
std::vector<std::string> DatabaseHandler::getAllQuestionContents() {
    std::vector<std::string> questionContents;

    if (!executeQuery("select * from pytania")) {
        questionContents.push_back("Błąd w zapytaniu do bazy danych");
        return questionContents;
    }

    MYSQL_RES *res = storeResult();
    if (res == NULL) {
        questionContents.push_back("Błąd podczas pobierania wyników z bazy danych");
        return questionContents;
    }

    int num_fields = mysql_num_fields(res);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        std::string content = row[3] ? row[3] : "Brak treści pytania";
        questionContents.push_back(content);
    }

    mysql_free_result(res);
    return questionContents;
}

