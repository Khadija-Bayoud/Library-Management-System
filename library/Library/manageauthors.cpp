#include "manageauthors.h"
#include "ui_manageauthors.h"
#include "digitallibrary.h"
#include <QDebug>
#include <QMessageBox>

ManageAuthors::ManageAuthors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageAuthors)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Authors");

    model = new QSqlQueryModel;

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM authors"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from authors";
    model->setQuery(select);
    ui->authorTableView->setModel(model);

    setValidator();
}

ManageAuthors::~ManageAuthors()
{
    delete ui;
    delete  model;
}

void ManageAuthors::on_addButtton_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //retrieve content
    QString ID = ui->ID->text();
    QString firstName = ui->firstName->text();
    QString lastName = ui->lastName->text();
    QString expertise = ui->expertise->text();
    QString about = ui->about->toPlainText();

    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM authors"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from authors";

    if((!ID.isEmpty() & !firstName.isEmpty())&(!lastName.isEmpty() & !expertise.isEmpty()) & !about.isEmpty())
    {
        auto search = QSqlQuery(db);
        QString searchIDAuthor = {"SELECT * FROM authors WHERE ID = '"+ID+"'"};
        if(!search.exec(searchIDAuthor))
            qDebug() << "Cannot select from authors";

        int count = 0;
        while(search.next())
            count++;

        if(count >= 1)
        {
            auto query = QSqlQuery(db);
            QString update = {"UPDATE authors SET  firstName = '"+firstName+"', lastName="
                              "'"+lastName+"', expertise='"+expertise+"', about = '"+about+"'"
                              " WHERE ID = '"+ID+"'"};
            if(!query.exec(update))
                qDebug() << "Cannot update authors";

            //Afficher les auteurs dans QTableView
            model->setQuery(select);
            ui->authorTableView->setModel(model);
        }
        else{
            auto query = QSqlQuery(db);
            QString addAuthor = {"INSERT INTO authors (ID, firstName, lastName, expertise,"
                                "about) VALUES ('%1', '%2','%3', '%4', '%5')"};

            if(!query.exec(addAuthor.arg(ID.toInt()).arg(firstName).arg(lastName).arg(expertise).arg(about)))
                qDebug() << "Cannot add authors";

            //Afficher les genres dans QTableView
            model->setQuery(select);
            ui->authorTableView->setModel(model);
        }
    }
    else
       QMessageBox::warning(this, "Empty", "Fields are empty!");
}


void ManageAuthors::on_editButton_clicked()
{
    QModelIndexList selectedRow = ui->authorTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);

        //get the content of each column
        QString ID = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 0)).toString();
        QString firstName = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 1)).toString();
        QString lastName = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 2)).toString();
        QString expertise = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 3)).toString();
        QString about = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 4)).toString();

        //set the ID and the name in te correspondant lienEdit
        ui->ID->setText(ID);
        ui->firstName->setText(firstName);
        ui->lastName->setText(lastName);
        ui->expertise->setText(expertise);
        ui->about->setText(about);
    }
}


void ManageAuthors::on_deleteButton_clicked()
{
    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    QModelIndexList selectedRow = ui->authorTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);

        QString ID = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 0)).toString();

        auto select = QSqlQuery(db);
        QString selectAll = {"SELECT * FROM authors"};
        if(!select.exec(selectAll))
            qDebug() << "Cannot select from authors";

        auto deleteQuery = QSqlQuery(db);
        QString deleteGenre = {"DELETE FROM authors WHERE ID= '"+ID+"'"};
        if(!deleteQuery.exec(deleteGenre))
            qDebug() << "Cannot delete from authors";

        model->setQuery(select);
        ui->authorTableView->setModel(model);
    }
}


void ManageAuthors::setValidator()
{
    //Validator for ID
    QRegExp ID("[0-9]{1000}");
    QRegExpValidator *valID = new QRegExpValidator(ID, this);
    ui->ID->setValidator(valID);

    //regx for name
    QRegExp Name("[a-zA-Z0-9_+-\\s]{1000}");
    QRegExpValidator *valName = new QRegExpValidator(Name, this);
    ui->firstName->setValidator(valName);
    ui->lastName->setValidator(valName);
    ui->expertise->setValidator(valName);
}
