#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class signUp;
}

class signUp : public QDialog
{
    Q_OBJECT

public:
    explicit signUp(QWidget *parent = nullptr);
    ~signUp();
    void setValidator();

private slots:
    void on_createButton_clicked();

    void on_backButton_clicked();

private:
    Ui::signUp *ui;

};

#endif // SIGNUP_H
