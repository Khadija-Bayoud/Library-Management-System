#ifndef DELETEBOOK_H
#define DELETEBOOK_H

#include <QDialog>

namespace Ui {
class deleteBook;
}

class deleteBook : public QDialog
{
    Q_OBJECT

public:
    explicit deleteBook(QWidget *parent = nullptr);
    ~deleteBook();

private slots:
    void on_deleteBookBtn_clicked();

private:
    Ui::deleteBook *ui;
};

#endif // DELETEBOOK_H
