#include "addmember.h"
#include "ui_addmember.h"
#include "digitallibrary.h"
#include <QMessageBox>
#include <QDebug>

addMember::addMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addMember)
{
    ui->setupUi(this);
    this->resize(350, 400);
    this->setWindowTitle("Add Member");

    setValidator();
}

addMember::~addMember()
{
    delete ui;
}

void addMember::on_addMemberButton_clicked()
{
    //get the content of the fields
    QString firstName =ui->firstName->text();
    QString lastName = ui->lastName->text();
    QString  phone = ui->phone->text();
    QString email = ui->email->text();
    QString gender = ui->gender->currentText();

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //Make sure that the fields are not empty
    if((!firstName.isEmpty() & !lastName.isEmpty())&(!phone.isEmpty() & !email.isEmpty())& !gender.isEmpty())
    {
        //Create the query
        auto query = QSqlQuery(db);

        //Insert into db
        QString insert = {"INSERT INTO members (firstName, lastName, phone, email, gender)"
                          "VALUES ('%1', '%2', '%3', '%4', '%5')"};

        //Execute the query
        if(!query.exec(insert.arg(firstName).arg(lastName).arg(phone).arg(email).arg(gender)))
            qDebug() << "Cannot insert into members";
        else
            QMessageBox::information(this, "SUCCESS", "Member added succesfully!");
    }
    else
       QMessageBox::warning(this, "Empty", "Fields are empty!");

}

void addMember::setValidator(){
    //regx for name
    QRegExp Name("^[A-Za-z]{7,29}$");
    QRegExpValidator *valName = new QRegExpValidator(Name, this);
    ui->firstName->setValidator(valName);
    ui->lastName->setValidator(valName);

    //Validator for phone number
    QRegExp phone("[0-9]{10}");
    QRegExpValidator *valPhone = new QRegExpValidator(phone, this);
    ui->phone->setValidator(valPhone);

    //Validator for email
    QRegExp email("^[a-zA-Z0-9_.-]+@[a-zA-Z0-9.-]+$");
    QRegExpValidator *valMail = new QRegExpValidator(email, this);
    ui->email->setValidator(valMail);




}
