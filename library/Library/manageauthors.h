#ifndef MANAGEAUTHORS_H
#define MANAGEAUTHORS_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>

namespace Ui {
class ManageAuthors;
}

class ManageAuthors : public QDialog
{
    Q_OBJECT

public:
    explicit ManageAuthors(QWidget *parent = nullptr);
    ~ManageAuthors();

    void setValidator();


private slots:
    void on_addButtton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::ManageAuthors *ui;
    QSqlQueryModel *model;
};

#endif // MANAGEAUTHORS_H
