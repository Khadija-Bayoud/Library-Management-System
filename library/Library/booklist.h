#ifndef BOOKLIST_H
#define BOOKLIST_H

#include <QDialog>

namespace Ui {
class bookList;
}

class bookList : public QDialog
{
    Q_OBJECT

public:
    explicit bookList(QWidget *parent = nullptr);
    ~bookList();

private slots:
    void on_value_textEdited(const QString &arg1);
    void showInfo();

private:
    Ui::bookList *ui;
};

#endif // BOOKLIST_H
