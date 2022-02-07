#ifndef GENRELIST_H
#define GENRELIST_H

#include <QDialog>

namespace Ui {
class genreList;
}

class genreList : public QDialog
{
    Q_OBJECT

public:
    explicit genreList(QWidget *parent = nullptr);
    ~genreList();

    QString genre;

private slots:
    void showInfo();

    void on_value_textEdited(const QString &arg1);

private:
    Ui::genreList *ui;
};

#endif // GENRELIST_H
