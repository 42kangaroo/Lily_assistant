//
// Created by 42kangaroo on 23.04.20.
//

#ifndef ADDGUI_DATABASE_HANDLER_HPP
#define ADDGUI_DATABASE_HANDLER_HPP

#include <QtSql/QSqlQuery>
#include <QtSql>

namespace Lily {
    class Database_handler {
    public:
        Database_handler(std::string str= "/home/pi/C-Programmes/database/questions.sqlite");

        ~Database_handler();

    protected:
        QSqlDatabase db;
    };
}

#endif //ADDGUI_DATABASE_HANDLER_HPP
