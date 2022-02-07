#include "editbook.h"
#include "ui_editbook.h"
#include "genrelist.h"
#include "addbook.h"
#include "authorslist.h"
#include "digitallibrary.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include <QFileInfo>

editBook::editBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editBook)
{
    ui->setupUi(this);
    this->setWindowTitle("Edit Book");
    ui->date->setDate(QDate::currentDate());

    setValidator();
}

editBook::~editBook()
{
    delete ui;
}

void editBook::on_cancelBtn_clicked()
{
    this->hide();
}

void editBook::on_selectImgBtn_clicked()
{
    coverFilename = QFileDialog::getOpenFileName();
    ui->coverLabel->setPixmap(coverFilename);
    clicked = true;
}

void editBook::on_editBookBtn_clicked()
{
    //get the content of the Line edit
    QString ISBN = ui->ISBN->text();
    QString name = ui->name->text();
    QString author = ui->author->text() ;
    QString genre = ui->genre->currentText();
    QString quantity = ui->quantity->text();
    QString publisher = ui->publisher->text();
    QString price = ui->price->text();
    QString date = ui->date->text();
    QString description = ui->description->toPlainText();

    //test if the fields are not empty
    QStringList bookInfo {ISBN, name, author, genre, quantity, publisher, price, date};
    bool full = true;
    for(int i=0; i<bookInfo.length(); i++)
    {
        if(bookInfo[i].isEmpty())
        {
            full = false;
            break;
        }
    }

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(full)
    {
        if(clicked)
        {
            QString coverPath = coverFilename;
            //Define the query
            auto query = QSqlQuery(db);
            QString searchISBN = {"UPDATE books SET name = '"+name+"',"
                                "author = '"+author+"', genre = '"+genre+"',"
                                "quantity = '"+quantity+"', publisher = '"+publisher+"',"
                                "price = '"+price+"', date = '"+date+"', description = '"+description+"',"
                                "cover = '"+coverPath+"' WHERE ISBN = '"+ISBN+"'"};
            if(!query.exec(searchISBN))
                qDebug() << "Cannot search ISBN";
            else
                QMessageBox::information(this,"SUCCESS", "Book updated successfully");
        }
        else
        {
            //Define the query
            auto query = QSqlQuery(db);
            QString searchISBN = {"UPDATE books SET name = '"+name+"',"
                                "author = '"+author+"', genre = '"+genre+"',"
                                "quantity = '"+quantity+"', publisher = '"+publisher+"',"
                                "price = '"+price+"', date = '"+date+"', description = '"+description+"'"
                                "WHERE ISBN = '"+ISBN+"'"};
            if(!query.exec(searchISBN))
                qDebug() << "Cannot search ISBN";
            else
                QMessageBox::information(this,"SUCCESS", "Book updated successfully");
        }
    }
    else
        QMessageBox::warning(this,"Failed", "Fields are empty");
}

void editBook::on_searchBtn_clicked()
{
    //get the content of the Line edit
    QString ISBN = ui->ISBN->text();
    QString name;
    QString author;
    QString genre;
    QString quantity;
    QString publisher;
    QString price;
    QString date;
    QString description;
    QString coverPath;

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(!ISBN.isEmpty())
    {
        //Define the query
        auto query = QSqlQuery(db);
        QString searchISBN = {"SELECT * FROM books WHERE ISBN = '%1'"};

        //execute the query
        if(!query.exec(searchISBN.arg(ISBN)))
            qDebug() << "Cannot select from books";

        //check if the book is found
        while(query.next())
            count++;

        if(count != 1)
        {
            QMessageBox::warning(this, "Not Found", "Book not Found");
            ui->ISBN->clear();
        }
        else
        {
            //Retrieve the fields identified by ID
            if(query.first())
            {
                name = query.value(2).toString();
                author = query.value(3).toString();
                genre = query.value(4).toString();
                quantity = query.value(5).toString();
                publisher = query.value(6).toString();
                price = query.value(7).toString();
                date = query.value(8).toString();
                description = query.value(9).toString();
                coverPath = query.value(10).toString();
            }
        }

        //Convert to QDate
        QStringList dateList = date.split("/");
        QDate Date;
        if(dateList.length() == 3)
            Date = QDate(dateList[2].toInt(), dateList[1].toInt(), dateList[0].toInt());

        //Show the fields in the corresponding line Edit
        ui->name->setText(name);
        ui->author->setText(author);
        ui->genre->setCurrentText(genre);
        ui->quantity->setValue(quantity.toInt());
        ui->publisher->setText(publisher);
        ui->price->setText(price);
        ui->date->setDate(Date);
        ui->description->setText(description);
        if(QFileInfo::exists(coverPath))
            ui->coverLabel->setPixmap(coverPath);
        else
            ui->coverLabel->setText("Book cover not found");
    }
    else
        QMessageBox::warning(this, "ISBN", "Insert ISBN");

}

void editBook::on_changeAuthorBtn_clicked()
{
    authorsList authors;
    authors.exec();
    ui->author->setText(authors.author);
}

void editBook::setValidator(){


    //ISBN Validator
    QRegExp ISBN ("[0-9]*[-| ][0-9]*[-| ][0-9]*[-| ][0-9]*[-| ][0-9]*");
    QRegExpValidator *ISBNVal = new QRegExpValidator(ISBN, this);
    ui->ISBN->setValidator(ISBNVal);

    //regx for name
    QRegExp Name("^[A-Za-z]{7,29}$");
    QRegExpValidator *valName = new QRegExpValidator(Name, this);
    ui->name->setValidator(valName);
    ui->publisher->setValidator(valName);

    //setValidator for price
    //regx for name
    QRegExp price("^\\d{0,8}(\\.\\d{1,4})?$");
    QRegExpValidator *valPrice = new QRegExpValidator(price, this);
    ui->price->setValidator(valPrice);
}

void editBook::on_changeGenreBtn_clicked()
{
    genreList genre;
    genre.exec();
    ui->genre->addItem(genre.genre);
}

