#ifndef NEWPASSWD_H
#define NEWPASSWD_H

#include <QDialog>

namespace Ui {
class newPasswd;
}

class newPasswd : public QDialog
{
    Q_OBJECT

public:
    explicit newPasswd(QWidget *parent = nullptr);
    ~newPasswd();

    void setValidator();

private slots:
    void on_submitButton_clicked();

    void on_backButton_clicked();

private:
    Ui::newPasswd *ui;
};

#endif // NEWPASSWD_H
