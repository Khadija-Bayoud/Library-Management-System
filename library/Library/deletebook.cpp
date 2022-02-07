#include "deletebook.h"
#include "ui_deletebook.h"
#include "digitallibrary.h"
#include "addbook.h"
#include <QtDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

deleteBook::deleteBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteBook)
{
    ui->setupUi(this);
    this->setWindowTitle("Delete Book");

    //Validator for ID
    QRegExp ID("[0-9]{1000}");
    QRegExpValidator *valID = new QRegExpValidator(ID, this);
    ui->ID->setValidator(valID);
}

deleteBook::~deleteBook()
{
    delete ui;
}

void deleteBook::on_deleteBookBtn_clicked()
{

    //Get The ID
    QString ID = ui->ID->text();

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //check if the member exists
    auto searchQuery = QSqlQuery(db);
    QString search{"SELECT * FROM books WHERE ID = '%1'"};
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
            QString del{"DELETE FROM books WHERE ID= '%1'"};

            //execute the query
            if(!query.exec(del.arg(ID)))
                qDebug() << "Cannot delete book";
            else
            {
                QMessageBox::information(this, "SUCCESS", "Book deleted successfully");
            }
        }
        else
        {
            QMessageBox::warning(this, "Failed", "Book not found");
            ui->ID->clear();
        }
    }
    else
        QMessageBox::warning(this, "Failed", "Insert ID");


}

