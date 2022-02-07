#ifndef DIGITALLIBRARY_H
#define DIGITALLIBRARY_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>

namespace Ui {
class digitalLibrary;
}

class digitalLibrary : public QDialog
{
    Q_OBJECT

public:
    explicit digitalLibrary(QWidget *parent = nullptr);
    ~digitalLibrary();

    QSqlDatabase db;
    void connectDB();

    void setUsername(QString username);
    void showBookNum();
    void showMemberNum();
    void showAuthorNum();
    void showCover();


private slots:

    void on_manageGenre_clicked();

    void on_manageAuthorButton_clicked();

    void on_addMemberBtn_clicked();

    void on_editMemberBtn_clicked();

    void on_deleteMemberBtn_clicked();

    void on_membersListBtn_clicked();

    void on_addBookBtn_clicked();

    void on_editBookBtn_clicked();

    void on_deleteBookBtn_clicked();

    void on_booksListBtn_clicked();

    void on_issueBookBtn_clicked();

    void on_returnBookBtn_clicked();

private:
    Ui::digitalLibrary *ui;

    QString filename = QDir::homePath()+ "/libraryDB.sqlite";

    QString username;
};

#endif // DIGITALLIBRARY_H
