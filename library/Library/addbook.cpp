#include "addbook.h"
#include "ui_addbook.h"
#include "genrelist.h"
#include <digitallibrary.h>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <authorslist.h>
#include <QRegExp>
#include <QRegExpValidator>

addBook::addBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Book");
    ui->date->setDate(QDate::currentDate());
    setValidator();
}

addBook::~addBook()
{
    delete ui;
}

void addBook::on_cancelBtn_clicked()
{
    this->hide();
}

void addBook::on_addBookBtn_clicked()
{
    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //get the content
    QString ISBN = ui->ISBN->text();
    QString name = ui->Name->text();
    QString author = ui->author->text();
    QString genre = ui->Genre->currentText();
    QString quantity = ui->quantity->text();
    QString publisher = ui->publisher->text();
    QString price = ui->price->text();
    QString date = ui->date->text();
    QString description = ui->description->toPlainText();
    QString coverPath = coverFilename;

    QStringList bookInfo {ISBN, name, author, genre, quantity, publisher, price, date};

    //test if the fields are not empty
    bool full = true;
    for(int i=0; i<bookInfo.length(); i++)
    {
        if(bookInfo[i].isEmpty())
        {
            full = false;
            break;
        }
    }

    //test if the book already exits
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM books WHERE ISBN = '%1'"};
    if(!query.exec(select.arg(ISBN)))
        qDebug() << "Cannot select from books table";


    int count = 0;
    while(query.next())
        count++;

    if(full)
    {
        if(count == 0)
        {
            //Define the query on the db
            auto query = QSqlQuery(db);
            QString insert{"INSERT INTO books (ISBN, name, author, genre, quantity, publisher, price, date, description, cover)"
                           "VALUES ('%1', '%2', '%3','%4','%5','%6','%7','%8','%9', '%10')"};

            //execute the query
            if(!query.exec(insert.arg(ISBN).arg(name).arg(author).arg(genre).arg(quantity.toInt()).arg(publisher).arg(price.toDouble()).arg(date).arg(description).arg(coverPath)))
            {
                QMessageBox::critical(this,"Failed","Cannot fill books Table");
            }
            else
            {
                QMessageBox::information(this,"Info","Book is added sucessfully");
            }
        }
        else
            QMessageBox::warning(this, "Info", "Book already exists");
    }
    else
        QMessageBox::critical(this,"Failed","Fields are empty");
}

void addBook::on_selectImgBtn_clicked()
{
    //Open a file dialog to choose the image
    coverFilename = QFileDialog::getOpenFileName();
    ui->coverLabel->setPixmap(coverFilename);

}


void addBook::on_chooseAuthBtn_clicked()
{
    authorsList authors;
    authors.exec();
    ui->author->setText(authors.author);
}

void addBook::setValidator(){

    //ISBN Validator
    QRegExp ISBN ("[0-9]*[-| ][0-9]*[-| ][0-9]*[-| ][0-9]*[-| ][0-9]*");
    QRegExpValidator *ISBNVal = new QRegExpValidator(ISBN, this);
    ui->ISBN->setValidator(ISBNVal);

    //regx for name
    QRegExp Name("[a-zA-Z0-9_+-\\s]{1000}");
    QRegExpValidator *valName = new QRegExpValidator(Name, this);
    ui->Name->setValidator(valName);
    ui->publisher->setValidator(valName);

    //setValidator for price
    QRegExp price("^\\d{0,8}(\\.\\d{1,4})?$");
    QRegExpValidator *valPrice = new QRegExpValidator(price, this);
    ui->price->setValidator(valPrice);
}


void addBook::on_chooseGenreBtn_clicked()
{
    genreList genre;
    genre.exec();
    ui->Genre->addItem(genre.genre);
}

