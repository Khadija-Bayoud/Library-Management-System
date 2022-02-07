#include "digitallibrary.h"
#include "ui_digitallibrary.h"
#include "login.h"
#include <managebooks.h>
#include <manageauthors.h>
#include <addmember.h>
#include <editmember.h>
#include <deletemember.h>
#include <memberslist.h>
#include <addbook.h>
#include <editbook.h>
#include <deletebook.h>
#include <booklist.h>
#include <issuebook.h>
#include <returnbook.h>
#include <QMessageBox>
#include <QDebug>

digitalLibrary::digitalLibrary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::digitalLibrary)
{
    ui->setupUi(this);
    connectDB();

    setUsername(username);
    showBookNum();
    showMemberNum();
    showAuthorNum();
    showCover();
}

void digitalLibrary::connectDB()
{
    //Add the database with the SQLITE driver
    db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");

    //Set the database path
    db.setDatabaseName(this->filename);

    //check if the database is opened
    if(!db.open())
        QMessageBox::critical(this, "FAILED", "DB is not opened");

    //définir la requete sur la base de données
    auto query = QSqlQuery(db);

    //Create a table named accounts
    QString accountTable{"CREATE TABLE IF NOT EXISTS accounts"
                         "(username VARCHAR(20), name VARCHAR(20),"
                         "password VARCHAR(20))"};

    if(!query.exec(accountTable))
        QMessageBox::critical(this,"Info","Cannot create accounts");

    //Create a table named genres
    QString genreTable{"CREATE TABLE IF NOT EXISTS genres"
                            "(ID INTEGER, name VARCHAR(20))"};
    if(!query.exec(genreTable))
        QMessageBox::critical(this,"Info","Cannot create genre Table");

    //Create a table named authors
    QString authorTable{"CREATE TABLE IF NOT EXISTS authors"
                      "(ID INTEGER, firstName VARCHAR(20), lastName VARCHAR(20),"
                       "expertise VARCHAR(20), about VARCHAR(40))"};
    if(!query.exec(authorTable))
        QMessageBox::critical(this,"Info","Cannot create authors Table");

    //Create a table named members
    QString memberTable{"CREATE TABLE IF NOT EXISTS members"
                      "(ID INTEGER PRIMARY KEY, firstName VARCHAR(20), lastName VARCHAR(20),"
                       "phone VARCHAR(20), email VARCHAR(40), gender VARCHAR(10))"};
    if(!query.exec(memberTable))
        QMessageBox::critical(this,"Info","Cannot create members Table");

    //Create a table named books
    QString bookTable{"CREATE TABLE IF NOT EXISTS books"
                      "(ID INTEGER PRIMARY KEY, ISBN VARCHAR(20), name VARCHAR(20),"
                      "author VARCHAR(20), genre VARCHAR(20), quantity INT,"
                      "publisher VARCHAR(20), price REAL, date VARCHAR(10),"
                      "description VARCHAR(80), cover VARCHAR(50))"};
    if(!query.exec(bookTable))
        QMessageBox::critical(this,"Failed","Cannot create books Table");

    //Create a table named bookStatus
    QString Table{"CREATE TABLE IF NOT EXISTS bookStatus"
                      "(Book INTEGER, Member INTEGER, Status VARCHAR(10),"
                       "IssueDate date, ReturnDate date, Note VARCHAR(50))"};
    if(!query.exec(Table))
        QMessageBox::critical(this,"Info","Cannot create bookStatus Table");
}

digitalLibrary::~digitalLibrary()
{
    delete ui;
}

void digitalLibrary::on_manageGenre_clicked()
{
    manageBooks manage;
    manage.exec();
}

void digitalLibrary::on_manageAuthorButton_clicked()
{
    ManageAuthors manage;
    manage.exec();
}

void digitalLibrary::on_addMemberBtn_clicked()
{
    addMember member;
    member.exec();
}

void digitalLibrary::on_editMemberBtn_clicked()
{
    editMember editMember;
    editMember.exec();
}

void digitalLibrary::on_deleteMemberBtn_clicked()
{
    deleteMember delMember;
    delMember.exec();
}

void digitalLibrary::on_membersListBtn_clicked()
{
    membersList memberlist;
    memberlist.exec();
}

void digitalLibrary::on_addBookBtn_clicked()
{
    addBook addBook;
    addBook.exec();
}

void digitalLibrary::on_editBookBtn_clicked()
{
    editBook editBook;
    editBook.exec();
}

void digitalLibrary::on_deleteBookBtn_clicked()
{
    deleteBook delBook;
    delBook.exec();
}

void digitalLibrary::on_booksListBtn_clicked()
{
    bookList book;
    book.exec();
}

void digitalLibrary::on_issueBookBtn_clicked()
{
    IssueBook book;
    book.exec();
}

void digitalLibrary::on_returnBookBtn_clicked()
{
    ReturnBook book;
    book.exec();
}

void digitalLibrary::setUsername(QString username)
{
    ui->username->setText(username);
}

void digitalLibrary::showBookNum(){

    //define the query on the db and the model
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM books"};

    //execute the query
    if(!query.exec(select))
        qDebug() << "Cannot select from books";

    int count = 0;
    while(query.next())
        count++;

    ui->bookNum->setText(QString::number(count));
}

void digitalLibrary::showMemberNum(){

    //define the query on the db and the model
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM members"};

    //execute the query
    if(!query.exec(select))
        qDebug() << "Cannot select from members";

    int count = 0;
    while(query.next())
        count++;

    ui->memberNum->setText(QString::number(count));
}

void digitalLibrary::showAuthorNum(){

    //define the query
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM authors"};

    //execute the query
    if(!query.exec(select))
        qDebug() << "Cannot select from authors";

    int count = 0;
    while(query.next())
        count++;

    ui->authorNum->setText(QString::number(count));
}

void digitalLibrary::showCover(){

    //vector of coverLabels
   QVector<QLabel*> covers;
   covers.append(ui->cover_1);
   covers.append(ui->cover_2);
   covers.append(ui->cover_3);
   covers.append(ui->cover_4);

   //counter
   int i = 0;
   int count = 0;

   //select four cover
    QString cover;

    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM books"};
    //execute the query
    if(!query.exec(select))
        qDebug() << "Cannot select from books";
    while(query.next())
        count++;
    qDebug() <<count;

    if(count <= 4)
    {
        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from books";
        while (query.next()) {
            cover = query.value(10).toString();
            if(i>=count)
                 return;
            else if(!covers.isEmpty())
                 covers[i]->setPixmap(cover);
            i++;
        }
    }
    else
    {
        QString selectTop4{"SELECT * FROM books LIMIT 4"};
        //execute the query
        if(!query.exec(selectTop4))
            qDebug() << "Cannot select from books";
        while (query.next()) {

            if(query.first())
            {
                cover = query.value(10).toString();

                if(i>=4)
                    return;
                else if(!covers.isEmpty())
                    covers[i]->setPixmap(cover);
                i++;
            }
        }
    }
}





