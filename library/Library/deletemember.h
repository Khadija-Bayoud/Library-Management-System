#ifndef DELETEMEMBER_H
#define DELETEMEMBER_H

#include <QDialog>

namespace Ui {
class deleteMember;
}

class deleteMember : public QDialog
{
    Q_OBJECT

public:
    explicit deleteMember(QWidget *parent = nullptr);
    ~deleteMember();


private slots:
    void on_deleteMemberBtn_clicked();

private:
    Ui::deleteMember *ui;
};

#endif // DELETEMEMBER_H
