#include "memberslist.h"
#include "ui_memberslist.h"
#include "addmember.h"
#include "digitallibrary.h"
#include <QMessageBox>
#include <QDebug>

membersList::membersList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::membersList)
{
    ui->setupUi(this);
    this->setWindowTitle("Members List");

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //define the query on the db and the model
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM members"};

    //execute the query
    if(!query.exec(select))
        qDebug() << "Cannot select from members";

    //define the model
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(query);
    ui->tableView->setModel(model);
}

membersList::~membersList()
{
    delete ui;
}

void membersList::on_value_textEdited(const QString &text)
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
        QString select{"SELECT * FROM members WHERE ID LIKE '"+value+"'"
                       "OR firstName LIKE '"+value+"' OR lastName LIKE"
                       "'"+value+"' OR phone LIKE '"+value+"' OR email LIKE '"+value+"'"
                       "OR gender LIKE '"+value+"'"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from members";
        else
        {
            //define the model
            QSqlQueryModel * model = new QSqlQueryModel;
            model->setQuery(query);
            ui->tableView->setModel(model);
        }
    }
    else
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM members"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from members";

        //define the model
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
}

