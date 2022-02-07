#include "issuebook.h"
#include "ui_issuebook.h"
#include "addbook.h"
#include "addmember.h"
#include "digitallibrary.h"
#include <QDebug>
#include <QMessageBox>

IssueBook::IssueBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IssueBook)
{
    ui->setupUi(this);
    this->setWindowTitle("Issue Book");

    ui->issueDate->setDate(QDate::currentDate());
    ui->returnDate->setDate(QDate::currentDate());

    //Validator for ID
    QRegExp ID("[0-9]{1}");
    QRegExpValidator *valID = new QRegExpValidator(ID, this);
    ui->bookID->setValidator(valID);
    ui->memberID->setValidator(valID);

}

IssueBook::~IssueBook()
{
    delete ui;
}


void IssueBook::on_searchBook_clicked()
{
    //Get the ID
    QString bookID = ui->bookID->text();
    QString bookName;
    int quantity;

    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //search the book
    auto query = QSqlQuery(db);
    QString searchBook{"SELECT * FROM books WHERE ID = '%1'"};
    if(!query.exec(searchBook.arg(bookID)))
        qDebug() << "Cannot select from  books";

    int count = 0;
    while(query.next())
        count++;
    if(count > 0)
    {
        if(query.first())
        {
            bookName = query.value(2).toString();
            ui->bookName->setText(bookName);

            quantity = query.value(5).toInt();
            if(quantity > 0)
            {
                 ui->available->setText("Yes");
                 ui->available->setStyleSheet("QLabel {color : green; font: 10pt Comic Sans MS;}");
            }
            else
            {
                ui->available->setText("No");
                ui->available->setStyleSheet("QLabel {color : red; font: 10pt Comic Sans MS;}");
            }

        }
    }
    else
        QMessageBox::critical(this,"Failed", "Book Not found");

}


void IssueBook::on_searchMember_clicked()
{
    //Get the ID
    QString memberID = ui->memberID->text();
    QString memberName;

    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //search the member
    auto query = QSqlQuery(db);
    QString searchMember{"SELECT * FROM members WHERE ID = '%1'"};
    if(!query.exec(searchMember.arg(memberID)))
        qDebug() << "Cannot select from  members";

    int count = 0;
    while(query.next())
        count++;

    if(count > 0)
    {
        if(query.first())
        {
            memberName = query.value(1).toString();
            ui->memberName->setText(memberName);
        }
    }
    else
        QMessageBox::critical(this,"Failed", "Member Not found");


}


void IssueBook::on_issue_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //retrieve the IDs
    QString bookID = ui->bookID->text();
    QString memberID = ui->memberID->text();
    QString status{"Issued"};
    QString issueDate = ui->issueDate->text();
    QString returnDate = ui->returnDate->text();
    QString notes = ui->notes->toPlainText();

    //retrieve the issueDate
    QStringList dateList_1 = issueDate.split("/");
    QDate Date_1;
    if(dateList_1.length() == 3)
        Date_1 = QDate(dateList_1[2].toInt(), dateList_1[1].toInt(), dateList_1[0].toInt());

    //Retrieve the return Date
    QStringList dateList_2 = returnDate.split("/");
    QDate Date_2;
    if(dateList_2.length() == 3)
        Date_2 = QDate(dateList_2[2].toInt(), dateList_2[1].toInt(), dateList_2[0].toInt());

    //test
    if(Date_1 > Date_2)
        QMessageBox::critical(this, "Failed", "The return date must be after the issue Date");
    else{
        auto query = QSqlQuery(db);
        QString insert{"INSERT INTO bookStatus (Book, Member, Status, IssueDate, ReturnDate, Note) VALUES ('%1', '%2','%3', '%4', '%5','%6')"};
        if(!query.exec(insert.arg(bookID.toInt()).arg(memberID.toInt()).arg(status).arg(issueDate).arg(returnDate).arg(notes)))
        {
            qDebug() << "cannot fill bookStatus";
        }
        else
            QMessageBox::information(this, "SUCCESS", "Book issued successfully");
    }
}


void IssueBook::on_cancel_clicked()
{
    this->hide();
}

