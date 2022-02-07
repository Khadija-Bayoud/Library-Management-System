#include "authorslist.h"
#include "ui_authorslist.h"
#include <manageauthors.h>
#include "digitallibrary.h"
#include <QSqlQueryModel>
#include <QDebug>

authorsList::authorsList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorsList)
{
    ui->setupUi(this);
    this->setWindowTitle("Choose Author");

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    QSqlQueryModel *model = new QSqlQueryModel;

    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM authors"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from authors";
    model->setQuery(select);
    ui->authorTableView->setModel(model);

    //make connection
    connect(ui->authorTableView, &QTableView::doubleClicked, this, &authorsList::showInfo);

}

authorsList::~authorsList()
{
    delete ui;
}

void authorsList::showInfo()
{
    QModelIndexList selectedRow = ui->authorTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);
        auto firstName = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 1)).toString();
        auto lastName = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 2)).toString();
        author = firstName + " " + lastName;
    }
    this->hide();
}


void authorsList::on_value_textEdited(const QString &arg1)
{
    //get the content of the line edit
    QString value = ui->value->text() + "%";

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(!value.isEmpty())
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM authors WHERE ID LIKE '"+value+"'"
                       "OR firstName LIKE '"+value+"' OR lastName LIKE '"+value+"' OR expertise LIKE '"+value+"'"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from auhors";
        else
        {
            //define the model
            QSqlQueryModel * model = new QSqlQueryModel;
            model->setQuery(query);
            ui->authorTableView->setModel(model);
        }
    }
    else
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM authors"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from authors";

        //define the model
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->authorTableView->setModel(model);
    }
}

