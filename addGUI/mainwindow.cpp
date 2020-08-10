


#include "mainwindow.hpp"
#include "ui_mainwindow.h"

namespace Lily {
    LilyAdd::LilyAdd(QWidget *parent) :
            QMainWindow(parent),
            ui(new Ui::LilyAdd) {
        ui->setupUi(this);
        this->setWindowTitle("LilyAdd GUI");
        init();
        displayAll();

    }

    void LilyAdd::filter_all() {

        QSqlQueryModel model;
        QString lang = (ui->cblang->currentText() == "<None>") ? "%" : ui->cblang->currentText();
        QString has_is = (ui->cbhas_is->currentText() == "<None>") ? "%" : ui->cbhas_is->currentText();

        QString query = QString(
                "select * from questions where question like '%%1%' and answer like '%%2%' and language like '%3' and questionType like '%4' and priority like '%5' order by priority;");
        query = query.arg(isValidQuerryText(ui->lequest->text()));
        query = query.arg(isValidQuerryText(ui->leanswer->text()));
        query = query.arg(lang);
        query = query.arg(has_is);
        if (ui->sbprio->value() == 0) {
            query = query.arg("%");
        } else {
            query = query.arg(ui->sbprio->value());
        }

        model.setQuery(query);
        ui->tableWidget->setRowCount(model.rowCount());
        for (int i = 0; i < model.rowCount(); ++i) {
            int priority = model.record(i).value("priority").toInt();
            QString answer = model.record(i).value("answer").toString();
            QString question = model.record(i).value("question").toString();
            QString questionType = model.record(i).value("questionType").toString();
            QString language = model.record(i).value("language").toString();
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(question));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(answer));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(language));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(priority)));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(questionType));

        }
    }

    void LilyAdd::init() {
        selecting = false;
        connect(ui->pbfilter, SIGNAL(clicked()), this, SLOT(filter_all()));
        connect(ui->pbdelete, SIGNAL(clicked()), this, SLOT(deleteSelected()));
        connect(ui->pbadd, SIGNAL(clicked()), this, SLOT(add()));
        connect(ui->pbsave, SIGNAL(clicked()), this, SLOT(edit()));
        connect(ui->tableWidget, SIGNAL(itemSelectionChanged()), this, SLOT(load2Lines()));
        ui->centralwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->cbhas_is->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->cblang->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->sbprio->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->leanswer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->lequest->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->pbadd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->pbdelete->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->pbfilter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->pbsave->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->gridLayout->setColumnMinimumWidth(0, 600);
        ui->gridLayout->setColumnMinimumWidth(1, 30);
        ui->gridLayout->setColumnStretch(0, 10);
        ui->gridLayout->setColumnStretch(1, 1);
        ui->gridLayout->setMargin(20);
        centralWidget()->setLayout(ui->gridLayout);
        ui->cblang->addItem("mb-en1");
        ui->cblang->addItem("mb-de6");
        ui->cblang->addItem("mb-fr1");
        ui->cblang->addItem("<None>");
        ui->cbhas_is->addItem("has");
        ui->cbhas_is->addItem("is");
        ui->cbhas_is->addItem("<None>");
        ui->sbprio->setMaximum(99);
        ui->sbprio->setMinimum(0);
        ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderLabels({"question", "answer", "language", "priority", "Type"});
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->leanswer->setPlaceholderText("answer");
        ui->lequest->setPlaceholderText("question");
        setDefault();
    }

    void LilyAdd::displayAll() {
        selecting = true;

        QSqlQueryModel model;
        model.setQuery("select * from questions order by priority, question;");
        ui->tableWidget->setRowCount(model.rowCount());
        for (int i = 0; i < model.rowCount(); ++i) {
            int priority = model.record(i).value("priority").toInt();
            QString answer = model.record(i).value("answer").toString();
            QString question = model.record(i).value("question").toString();
            QString questionType = model.record(i).value("questionType").toString();
            QString language = model.record(i).value("language").toString();
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(question));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(answer));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(language));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(priority)));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(questionType));

        }


        selecting = false;
    }

    void LilyAdd::add() {
        QSqlQuery qry;

        if (isValid()) {
            QString textAnswer = ui->leanswer->text().simplified();
            QString textQuestion = ui->lequest->text().simplified().toLower();
            qry.prepare("insert into questions values ( :language, :question, :answer, :priority, :questionType);");
            qry.bindValue(":language", ui->cblang->currentText());
            qry.bindValue(":question", textQuestion);
            qry.bindValue(":answer", textAnswer);
            qry.bindValue(":questionType", ui->cbhas_is->currentText());
            qry.bindValue(":priority", ui->sbprio->value());

            if (!qry.exec()) {
                qDebug() << "failed" << qry.lastError().text() << qry.lastQuery();
                if (qry.lastError().type() == QSqlError::ConnectionError) {
                    QMessageBox::critical(this, tr("same question"), tr("please change the question"));
                }
                return;
            }
            setDefault();

        }
        displayAll();

    }

    void LilyAdd::deleteSelected() {
        QModelIndexList selection = ui->tableWidget->selectionModel()->selectedRows();
        QSqlQuery qry;
        for (int i = 0; i < selection.count(); i++) {
            QModelIndex index = selection.at(i);
            QString question = ui->tableWidget->item(index.row(), 0)->text();

            QMessageBox questbox(QMessageBox::Question, "delete message",
                                 "do you wrily want to delete question with keywords:" + question,
                                 QMessageBox::Yes | QMessageBox::YesAll | QMessageBox::No, this);

            if (i == 0 && selection.count() > 1) {
                questbox.button(QMessageBox::YesAll)->setText("delete all");
            } else {
                questbox.button(QMessageBox::YesAll)->hide();
            }
            switch (questbox.exec()) {
                case QMessageBox::Yes:
                    qry.prepare("delete from questions where question=:question;");
                    qry.bindValue(":question", question);
                    if (!qry.exec()) {
                        qDebug() << "failed delete" << qry.lastError().text() << qry.lastQuery();
                    }
                    break;
                case QMessageBox::YesAll:
                    for (int j = 0; j < selection.count(); j++) {
                        index = selection.at(j);
                        question = ui->tableWidget->item(index.row(), 0)->text();
                        qry.prepare("delete from questions where question=:question;");
                        qry.bindValue(":question", question);
                        if (!qry.exec()) {
                            qDebug() << "failed delete" << qry.lastError().text() << qry.lastQuery();
                        }
                    }
                    displayAll();
                    return;
                default:
                    break;
            }
            continue;
        }

        displayAll();

    }


    void LilyAdd::load2Lines() {
        if (!selecting) {
            qDebug() << "selecting changed";
            QModelIndexList selection = ui->tableWidget->selectionModel()->selectedRows();
            if (selection.count() == 1) {
                QModelIndex index = selection.at(0);
                ui->lequest->setText(ui->tableWidget->item(index.row(), 0)->text());
                ui->leanswer->setText(ui->tableWidget->item(index.row(), 1)->text());
                ui->cblang->setCurrentText(ui->tableWidget->item(index.row(), 2)->text());
                ui->sbprio->setValue(ui->tableWidget->item(index.row(), 3)->text().toInt());
                ui->cbhas_is->setCurrentText((ui->tableWidget->item(index.row(), 4)->text()));
            }
        }
    }

    void LilyAdd::edit() {
        QModelIndexList selection = ui->tableWidget->selectionModel()->selectedRows();
        if (selection.count() == 1) {
            QSqlQuery qry;
            QModelIndex index = selection.at(0);
            if (isValid()) {
                QString textAnswer = ui->leanswer->text().simplified();
                QString textQuestion = ui->lequest->text().simplified().toLower();
                qry.prepare(
                        "update questions set language=:language, question=:question, answer=:answer, priority=:priority, questionType=:questionType where question = :lastQuest;");
                qry.bindValue(":language", ui->cblang->currentText());
                qry.bindValue(":question", textQuestion);
                qry.bindValue(":answer", textAnswer);
                qry.bindValue(":questionType", ui->cbhas_is->currentText());
                qry.bindValue(":priority", ui->sbprio->value());
                qry.bindValue(":lastQuest", ui->tableWidget->item(index.row(), 0)->text());

                if (!qry.exec()) {
                    qDebug() << "failed" << qry.lastError().text() << qry.lastQuery();
                    if (qry.lastError().type() == QSqlError::ConnectionError) {
                        QMessageBox::critical(this, tr("same question"), tr("please change the question"));
                    }
                    return;
                }
                setDefault();

            }
            displayAll();
        } else {
            QMessageBox::critical(this, tr("selection error"), tr("Please only select one to edit"));
        }
    }

    bool LilyAdd::isValid() {
        if (ui->cbhas_is->currentText() == "<None>" || ui->cblang->currentText() == "<None>") {
            QMessageBox::critical(this, tr("false values"), tr("please select valid values for choosing boxes"));
            return false;
        }
        QString textAnswer = ui->leanswer->text().simplified();
        QString textQuestion = ui->lequest->text().simplified().toLower();
        if (textAnswer == "" || textQuestion == "") {
            QMessageBox::critical(this, tr("false values"), tr("enter values for question and answer"));
            return false;
        }
        if (ui->sbprio->value() < 1) {
            QMessageBox::critical(this, tr("false values"), tr("enter a value between 1 and 99 for priority"));
            return false;
        }
        return true;
    }

    void LilyAdd::setDefault() {
        ui->lequest->clear();
        ui->leanswer->clear();
        ui->sbprio->setValue(3);
        ui->cbhas_is->setCurrentText("has");
        ui->cblang->setCurrentText("mb-en1");
    }

    QString LilyAdd::isValidQuerryText(QString str) {
        if (str.contains("'") || str.contains("--") || str.contains("\"")) {
            QMessageBox::critical(this, "Don't try to hack my you *****", "Don't try to hack my you *****");
            return "";
        }
        return str;

    }
}
