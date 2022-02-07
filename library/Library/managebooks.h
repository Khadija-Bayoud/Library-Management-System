#ifndef MANAGEBOOKS_H
#define MANAGEBOOKS_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>

namespace Ui {
class manageBooks;
}

class manageBooks : public QDialog
{
    Q_OBJECT

public:
    explicit manageBooks(QWidget *parent = nullptr);
    ~manageBooks();

//    void connectDB();

private slots:

    void on_add_clicked();

    void on_edit_clicked();


    void on_deleteButton_clicked();

private:
    Ui::manageBooks *ui;

//    QSqlDatabase db;
    QSqlQueryModel *model;
//    QString filename = QDir::homePath()+ "/genresDB.sqlite";
};

#endif // MANAGEBOOKS_H
