#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
//#include <QDir>
//#include <QtSql/QSqlDatabase>
//#include <QSqlQuery>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void setValidator();

private slots:
    void on_loginButton_clicked();

    void on_signUpButton_clicked();

    void on_forgetPasswdBtn_clicked();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
