#include "signup.h"
#include "ui_signup.h"
#include "digitallibrary.h"
#include <QMessageBox>
#include <login.h>
#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>

signUp::signUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signUp)
{
    ui->setupUi(this);
    this->setWindowTitle("New Account");
    setValidator();
}

signUp::~signUp()
{
    delete ui;
}

void signUp::on_createButton_clicked()
{
    //Get the content
    QString username = ui->username->text();
    QString name = ui->name->text();
    QString password = ui->password->text();

    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //Add name password and username to the db
    if((!username.isEmpty() & !name.isEmpty()) & !password.isEmpty())
    {
        //cherche si le compte existe
        auto search = QSqlQuery(db);
        QString searchAcc = {"SELECT * FROM accounts WHERE username='"
                             +username+"' AND name='"+name+"' AND password='"
                             +password+"'"};
        if(!search.exec(searchAcc))
             qDebug() << "Cannot select";
        int count = 0;
        while(search.next())
        {
            count++;
        }

        if(count>=1)
            QMessageBox::warning(this, "Failed", "Account Already Exist!");
        else
        {
            QString addEntry = {"INSERT INTO accounts (username, name, password)"
                                "VALUES ('%1', '%2', '%3')"};
            auto query = QSqlQuery(db);

            if(!query.exec(addEntry.arg(username).arg(name).arg(password)))
                qDebug() << "Cannot add entry";
            else
                QMessageBox::information(this, "SUCCESS", "You registered succesfully!");
            }
     }
    else
     QMessageBox::warning(this, "Empty", "Fields are empty!");
}

void signUp::on_backButton_clicked()
{
    this->hide();
    Login login;
    login.exec();
}
void signUp::setValidator()
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
