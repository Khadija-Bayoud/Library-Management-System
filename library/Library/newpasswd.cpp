#include "newpasswd.h"
#include "ui_newpasswd.h"
#include <digitallibrary.h>
#include <login.h>
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

newPasswd::newPasswd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newPasswd)
{
    ui->setupUi(this);
    this->setWindowTitle("New Password");
    setValidator();

}

newPasswd::~newPasswd()
{
    delete ui;
}

void newPasswd::on_submitButton_clicked()
{
    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //Get the username
    QString username = ui->username->text();

    //Get the username
    QString name = ui->name->text();

    //Get the password
    QString newpass = ui->newpass->text();

    //Check if the db is opened
    if(!db.isOpen())
    {
        qDebug() << "Failed to open the database";
    }

    //Define the query
    auto query = QSqlQuery(db);

    //Define the body of the query
    QString updatePass = {"UPDATE accounts SET password= '"+newpass+"'"
                          "WHERE username='"+username+"'AND name='"+name+"'"};

    //Execute the query
    if(!query.exec(updatePass))
        qDebug() << "Cannot update passwd";

    int count = 0;
    while(query.next())
    {
        count++;
    }

    if(count == 1)
    {
        QMessageBox::information(this, "SUCCESS", "Password updated succesfully!");
    }
    else
        QMessageBox::warning(this, "Warning", "Name or Username is incorrect");
}


void newPasswd::on_backButton_clicked()
{
    this->hide();
    Login login;
    login.exec();
}

void newPasswd::setValidator()
{
    //regx for username
    QRegExp rxUsername("^[A-Za-z][A-Za-z0-9_]{7,29}$");
    QRegExpValidator *valUsername = new QRegExpValidator(rxUsername, this);
    ui->username->setValidator(valUsername);

    //regx for name
    QRegExp rxName("^[A-Za-z]{7,29}$");
    QRegExpValidator *valName = new QRegExpValidator(rxName, this);
    ui->name->setValidator(valName);
}
