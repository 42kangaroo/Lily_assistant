#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSql>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include "Database_handler.hpp"

namespace Ui {
    class LilyAdd;
}
namespace Lily {
    class LilyAdd : public QMainWindow {
    Q_OBJECT

    public:
        explicit LilyAdd(QWidget *parent = nullptr);

    private:
        Ui::LilyAdd *ui;

        QString isValidQuerryText(QString);

        void init();

        void setDefault();

        bool selecting;

        void displayAll();

        bool isValid();

        Database_handler db;

    private slots:

        void load2Lines();

        void edit();

        void add();

        void deleteSelected();

        void filter_all();
    };
}
#endif // MAINWINDOW_H
