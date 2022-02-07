#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QDialog>

namespace Ui {
class ReturnBook;
}

class ReturnBook : public QDialog
{
    Q_OBJECT

public:
    explicit ReturnBook(QWidget *parent = nullptr);
    ~ReturnBook();

private slots:
    void on_returnBtn_clicked();
    void showInfo();

    void on_lostBtn_clicked();

    void on_deleteBtn_clicked();

    void on_bookStatus_currentIndexChanged(int index);

private:
    Ui::ReturnBook *ui;
};

#endif // RETURNBOOK_H
