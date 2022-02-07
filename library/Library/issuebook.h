#ifndef ISSUEBOOK_H
#define ISSUEBOOK_H

#include <QDialog>

namespace Ui {
class IssueBook;
}

class IssueBook : public QDialog
{
    Q_OBJECT

public:
    explicit IssueBook(QWidget *parent = nullptr);
    ~IssueBook();

private slots:
    void on_searchBook_clicked();

    void on_searchMember_clicked();

    void on_issue_clicked();

    void on_cancel_clicked();

private:
    Ui::IssueBook *ui;
};

#endif // ISSUEBOOK_H
