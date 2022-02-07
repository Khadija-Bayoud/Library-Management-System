#include "genrelist.h"
#include "ui_genrelist.h"
#include "digitallibrary.h"
#include <QSqlQueryModel>
#include <QDebug>

genreList::genreList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::genreList)
{
    ui->setupUi(this);
    this->setWindowTitle("Select Genre");

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    QSqlQueryModel *model = new QSqlQueryModel;

    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM genres"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from genres";
    model->setQuery(select);
    ui->TableView->setModel(model);

    //make connection
    connect(ui->TableView, &QTableView::doubleClicked, this, &genreList::showInfo);
}

genreList::~genreList()
{
    delete ui;
}

void genreList::showInfo()
{
    QModelIndexList selectedRow = ui->TableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);
        genre = ui->TableView->model()->data(ui->TableView->model()->index(row.row(), 1)).toString();
    }
    this->hide();
}

void genreList::on_value_textEdited(const QString &arg1)
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
        QString select{"SELECT * FROM genres WHERE ID LIKE '"+value+"' OR name LIKE '"+value+"'"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from genres";
        else
        {
            //define the model
            QSqlQueryModel * model = new QSqlQueryModel;
            model->setQuery(query);
            ui->TableView->setModel(model);
        }
    }
    else
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM genres"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from genres";

        //define the model
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->TableView->setModel(model);
    }
}

