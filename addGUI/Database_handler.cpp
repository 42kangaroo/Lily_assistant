//
// Created by 42kangaroo on 23.04.20.
//


#include "Database_handler.hpp"

namespace Lily {

    Database_handler::Database_handler(std::string str) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(str.c_str());
        if (!db.open()) {
            qDebug() << "open failed";
        }
        QSqlQuery qry;
        if (!qry.exec("CREATE TABLE IF NOT EXISTS questions("
                      "language VARCHAR(20),"
                      "question varchar(200),"
                      "answer varchar(200),"
                      "priority int,"
                      "questionType varchar(4),"
                      "PRIMARY KEY (question));")) {
            qDebug() << "no new table";
        }
    }

    Database_handler::~Database_handler() {
        db.close();
    }
}