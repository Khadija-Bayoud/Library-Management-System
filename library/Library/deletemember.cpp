#include "deletemember.h"
#include "ui_deletemember.h"
#include "addmember.h"
#include "digitallibrary.h"
#include <QMessageBox>
#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>

deleteMember::deleteMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteMember)
{
    ui->setupUi(this);
    this->setWindowTitle("Delete Member");

    //Validator for ID
    QRegExp ID("[0-9]{1000}");
    QRegExpValidator *valID = new QRegExpValidator(ID, this);
    ui->ID->setValidator(valID);
}

deleteMember::~deleteMember()
{
    delete ui;
}

void deleteMember::on_deleteMemberBtn_clicked()
{
    //Get The ID
    QString ID = ui->ID->text();

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //check if the member exists
    auto searchQuery = QSqlQuery(db);
    QString search{"SELECT * FROM members WHERE ID = '%1'"};
    if(!searchQuery.exec(search.arg(ID)))
        qDebug() << "cannot search in members";
    int count = 0;
    while(searchQuery.next())
        count++;

    if(!ID.isEmpty())
    {
        if(count == 1)
        {
            //define the query on the db
            auto query = QSqlQuery(db);
            QString del{"DELETE FROM members WHERE ID= '%1'"};

            //execute the query
            if(!query.exec(del.arg(ID)))
                qDebug() << "Cannot delete member";
            else
                QMessageBox::information(this, "SUCCESS", "member deleted successfully");
        }
        else
        {
            QMessageBox::warning(this, "Failed", "Member not found");
            ui->ID->del();
        }
    }
    else
        QMessageBox::warning(this, "Failed", "Insert ID");
}

