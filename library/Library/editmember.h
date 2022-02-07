#ifndef EDITMEMBER_H
#define EDITMEMBER_H

#include <QDialog>
#include <addmember.h>

namespace Ui {
class editMember;
}

class editMember : public QDialog
{
    Q_OBJECT

public:
    explicit editMember(QWidget *parent = nullptr);
    ~editMember();

    void setValidator();

private slots:

    void on_searchMemberBtn_clicked();

    void on_editMemberBtn_clicked();

private:
    Ui::editMember *ui;
    int count = 0;
};

#endif // EDITMEMBER_H
