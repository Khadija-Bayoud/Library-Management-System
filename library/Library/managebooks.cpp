#include "managebooks.h"
#include "ui_managebooks.h"
#include "digitallibrary.h"
#include "addbook.h"
#include "editbook.h"
#include <QMessageBox>
#include <QDebug>

manageBooks::manageBooks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manageBooks)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Genres");

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;
    model = new QSqlQueryModel;

    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM genres"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from genres";
    model->setQuery(select);
    ui->genreTableView->setModel(model);

    //Validator for ID
    QRegExp ID("[0-9]{1000}");
    QRegExpValidator *valID = new QRegExpValidator(ID, this);
    ui->ID->setValidator(valID);

    //Validator for name
    QRegExp Name("^[A-Za-z][A-Za-z_-]{7,29}$");
    QRegExpValidator *valName = new QRegExpValidator(Name, this);
    ui->Name->setValidator(valName);
}

manageBooks::~manageBooks()
{
    delete ui;
    delete model;
}

void manageBooks::on_add_clicked()
{
    //retrieve content
    QString ID = ui->ID->text();
    QString name = ui->Name->text();

    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //define query
    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM genres"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from genres";

    //insert the new genre in the db genres table, otherwise update it
    if(!ID.isEmpty() & !name.isEmpty())
    {
        auto search = QSqlQuery(db);
        QString searchIDName = {"SELECT * FROM genres WHERE ID = '"+ID+"'"};
        if(!search.exec(searchIDName))
            qDebug() << "Cannot select from genres";
        int count = 0;
        while(search.next())
            count++;
        if(count >= 1)
        {
            auto query = QSqlQuery(db);
            QString update = {"UPDATE genres SET  name = '"+name+"'"
                              "WHERE ID = '"+ID+"'"};
            if(!query.exec(update))
                qDebug() << "Cannot select from genres";

            //Afficher les genres dans QTableView
            model->setQuery(select);
            ui->genreTableView->setModel(model);
        }
        else{
            auto query = QSqlQuery(db);
            QString addGenre = {"INSERT INTO genres (ID, name) VALUES ('%1', '%2')"};

            if(!query.exec(addGenre.arg(ID.toInt()).arg(name)))
                qDebug() << "Cannot add genre";
            else
            {
                QMessageBox::information(this, "SUCCESS", "Genre added successfully");
            }

            //Afficher les genres dans QTableView
            model->setQuery(select);
            ui->genreTableView->setModel(model);
        }
    }
    else
       QMessageBox::warning(this, "Empty", "Fields are empty!");
}


void manageBooks::on_edit_clicked()
{
    QModelIndexList selectedRow = ui->genreTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);

        //get the content of each column
        QString ID = ui->genreTableView->model()->data(ui->genreTableView->model()->index(row.row(), 0)).toString();
        QString name = ui->genreTableView->model()->data(ui->genreTableView->model()->index(row.row(), 1)).toString();

        //set the ID and the name in te correspondant lienEdit
        ui->ID->setText(ID);
        ui->Name->setText(name);
    }
}


void manageBooks::on_deleteButton_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //to update the value of genres (QcomboBox)
    addBook book;
    editBook editBook;

    QModelIndexList selectedRow = ui->genreTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);
        QString name = ui->genreTableView->model()->data(ui->genreTableView->model()->index(row.row(), 1)).toString();

        auto select = QSqlQuery(db);
        QString selectAll = {"SELECT * FROM genres"};
        if(!select.exec(selectAll))
            qDebug() << "Cannot select from genres";

        auto deleteQuery = QSqlQuery(db);
        QString deleteGenre = {"DELETE FROM genres WHERE name= '"+name+"'"};
        if(!deleteQuery.exec(deleteGenre))
            qDebug() << "Cannot delete from genres";

        model->setQuery(select);
        ui->genreTableView->setModel(model);
    }
}

