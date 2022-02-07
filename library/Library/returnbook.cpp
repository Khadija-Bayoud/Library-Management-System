#include "returnbook.h"
#include "ui_returnbook.h"
#include "digitallibrary.h"
#include <QDebug>
#include <QMessageBox>

ReturnBook::ReturnBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReturnBook)
{
    ui->setupUi(this);
    this->setWindowTitle("Return Book");
    ui->issueDate->setDate(QDate::currentDate());
    ui->returnDate->setDate(QDate::currentDate());

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM bookStatus"};
    if(!query.exec(select))
        qDebug() << "Cannot select from bookStatus";
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(query);
    ui->tableView->setModel(model);

    //make connection
    connect(ui->tableView, &QTableView::doubleClicked, this, &ReturnBook::showInfo);
}

ReturnBook::~ReturnBook()
{
    delete ui;
}

void ReturnBook::on_returnBtn_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //retrieve the IDs
    QString bookID = ui->bookID->text();
    QString memberID = ui->memberID->text();
    QString status{"Returned"};
    QString returnDate = ui->returnDate->text();
    QString note = ui->notes->toPlainText();

    //retrieve the issueDate
    QStringList dateList_1 = ui->issueDate->text().split("/");
    QDate Date_1;
    if(!dateList_1.isEmpty())
        Date_1 = QDate(dateList_1[2].toInt(), dateList_1[1].toInt(), dateList_1[0].toInt());

    //Retrieve the return Date
    QStringList dateList_2 = ui->returnDate->text().split("/");
    QDate Date_2;
    if(!dateList_2.isEmpty())
        Date_2 = QDate(dateList_2[2].toInt(), dateList_2[1].toInt(), dateList_2[0].toInt());

    //test
    if(Date_1 > Date_2)
        QMessageBox::critical(this, "Failed", "The return date must be after the issue Date");
    else{
        auto query = QSqlQuery(db);
        QString update{"UPDATE bookStatus SET Status = '%1', ReturnDate = '%2', Note = '%3' WHERE (Book = '%4' AND Member = '%5')"};
        if(!query.exec(update.arg(status).arg(returnDate).arg(note).arg(bookID.toInt()).arg(memberID.toInt())))
            qDebug() << "cannot update bookStatus";
        else
            QMessageBox::information(this, "SUCCESS", "Book returned successfully");
    }

    //updtae the table view
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM bookStatus"};
    if(!query.exec(select))
        qDebug() << "Cannot select from bookStatus";
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(query);
    ui->tableView->setModel(model);
}

void ReturnBook::showInfo()
{
    QModelIndexList selectedRow = ui->tableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);
        auto bookID = ui->tableView->model()->data(ui->tableView->model()->index(row.row(), 0)).toString();
        auto memberID = ui->tableView->model()->data(ui->tableView->model()->index(row.row(), 1)).toString();
        auto issueDate = ui->tableView->model()->data(ui->tableView->model()->index(row.row(), 3)).toString();
        auto returnDate = ui->tableView->model()->data(ui->tableView->model()->index(row.row(), 4)).toString();
        auto note = ui->tableView->model()->data(ui->tableView->model()->index(row.row(), 5)).toString();

        ui->bookID->setText(bookID);
        ui->memberID->setText(memberID);

        //retrieve the issueDate
        QStringList dateList = issueDate.split("/");
        QDate Date;
        if(!dateList.isEmpty())
            Date = QDate(dateList[2].toInt(), dateList[1].toInt(), dateList[0].toInt());
        ui->issueDate->setDate(Date);

        //retrieve the returnDate
        QStringList dateList_2 = returnDate.split("/");
        QDate Date_2;
        if(!dateList_2.isEmpty())
            Date_2 = QDate(dateList_2[2].toInt(), dateList_2[1].toInt(), dateList_2[0].toInt());
        ui->returnDate->setDate(Date_2);

        //retrieve the notes
        ui->notes->setText(note);

    }
}

void ReturnBook::on_lostBtn_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //retrieve the IDs
    QString bookID = ui->bookID->text();
    QString memberID = ui->memberID->text();
    QString status{"Lost"};
    QString returnDate = ui->returnDate->text();
    QString note = ui->notes->toPlainText();

    auto query = QSqlQuery(db);
    QString update{"UPDATE bookStatus SET Status = '%1', ReturnDate = '%2', Note = '%3' WHERE (Book = '%4' AND Member = '%5')"};
    if(!query.exec(update.arg(status).arg(returnDate).arg(note).arg(bookID.toInt()).arg(memberID.toInt())))
        qDebug() << "cannot update bookStatus";
    else
        QMessageBox::information(this, "SUCCESS", "Book status updated successfully");

    //updtae the table view
    QString select{"SELECT * FROM bookStatus"};
    if(!query.exec(select))
        qDebug() << "Cannot select from bookStatus";
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(query);
    ui->tableView->setModel(model);
}

void ReturnBook::on_deleteBtn_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    QString bookID = ui->bookID->text();
    QString memberID = ui->memberID->text();

    auto query = QSqlQuery(db);
    QString del{"DELETE FROM bookStatus WHERE (Book = '%1' AND Member = '%2')"};
    if(!query.exec(del.arg(bookID.toInt()).arg(memberID.toInt())))
        qDebug() << "cannot delete from bookStatus";
    else
        QMessageBox::information(this, "SUCCESS", "Book deleted successfully");

    //updtae the table view
    QString select{"SELECT * FROM bookStatus"};
    if(!query.exec(select))
        qDebug() << "Cannot select from bookStatus";
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(query);
    ui->tableView->setModel(model);

}

void ReturnBook::on_bookStatus_currentIndexChanged(int index)
{
    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(index == 0)
    {
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM bookStatus"};
        if(!query.exec(select))
            qDebug() << "Cannot select from bookStatus";
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
    else if(index == 1)
    {
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM bookStatus WHERE Status = '%1'"};
        if(!query.exec(select.arg("Issued")))
            qDebug() << "Cannot select from bookStatus";
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
    else if(index == 2)
    {
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM bookStatus WHERE Status = '%1'"};
        if(!query.exec(select.arg("Returned")))
            qDebug() << "Cannot select from bookStatus";
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
    else
    {
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM bookStatus WHERE Status = '%1'"};
        if(!query.exec(select.arg("Lost")))
            qDebug() << "Cannot select from bookStatus";
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
}

