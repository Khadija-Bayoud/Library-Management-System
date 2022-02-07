#ifndef ADDMEMBER_H
#define ADDMEMBER_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>

namespace Ui {
class addMember;
}

class addMember : public QDialog
{
    Q_OBJECT

public:
    explicit addMember(QWidget *parent = nullptr);
    ~addMember();

    void setValidator();

private slots:

    void on_addMemberButton_clicked();

private:
    Ui::addMember *ui;

    QString filename = QDir::homePath()+ "/membersDB.sqlite";
};

#endif // ADDMEMBER_H
