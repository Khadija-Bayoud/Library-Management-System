<h1 align="center">Library Management System</h1> 

<p align="center">
  <img align="center" width="60%" height="50%" src="https://user-images.githubusercontent.com/72691265/152707716-39e6702d-b583-4b7b-8339-c2da22c654c8.png"/>
</p>

## Table of content 
  * [Introduction](#introduction)
  * [Tools](#tools)
  * [Features](#features)
     * [Authorization and Authentication](#authorization-and-authentication)
        * [Login](#login) 
        * [Sign Up](#sign-up)
        * [New Password](#new-password)
     * [Manage Genres](#manage-genres)
     * [Manage Authors](#manage-authors)
     * [Manage Members](#manage-members)
        * [Add Member](#add-member) 
        * [Edit Member](#edit-member)
        * [Delete Member](#delete-member)
        * [Members List](#members-list)
     * [Manage Books](#manage-books)
        * [Add Book](#add-book) 
        * [Edit Book](#edit-book)
        * [Delete Book](#delete-book)
        * [Books List](#books-list)
     * [Manage Books Transaction](#manage-books-transaction)
        * [Issue Book](#issue-book) 
        * [Return Member](#return-book)
  * [Video](#video)
  * [Conclusion](#conclusion)
    * [Future enhacements](#future-enhacement)


## Introduction
Library Management system is an application that refers to library systems which are generally small or medium in size. It is used by librarian to manage the library using a computerized system where he/she can record various transactions like issue of books, return of books, addition of new books, addition of new students etc.
Books and students maintenance modules are also included in this system which would keep track of the students using the library and also a detailed description about the books a library contains. With this computerized system there will be no loss of book record or member record which generally happens when a non-computerized system is used.
All these modules are able to help librarian to manage the library with more convenience and in a more efficient way as compared to library systems which are not computerized. </br>

## Tools
This project required the following tools:
* [Qt Creator](https://www.qt.io/download) version 5.12
  * Qt designer
* Qt ressource classes 
  * [QSqlDatabase](https://doc.qt.io/qt-5/qsqldatabase.html)
  * [QSqlQuery](https://doc.qt.io/qt-5/qsqlquery.html)
  * [QSqlQueryModel](https://doc.qt.io/qt-5/qsqlquerymodel.html#details)
  * [QTableView](https://doc.qt.io/qt-5/qtableview.html)
* CSS  for stylesheet 
* [DB browser (SQlite)](https://sqlitebrowser.org)

## Features
This project aims to implement the following features:
* Easily manage the complete management of the library through the graphical user interface.
* Removes manual process of issuing books and simplifies the way of issuing book to save time and effort.
* Can manage genres
* Manage authors
* Books Management
* Update the details when the student returns the book
* Search student by using their student ID
* View student details</br></br>
We are using a main database to store all the informations.</br>

```digitalLibrary.cpp```
```cpp
void digitalLibrary::connectDB()
{
    //Add the database with the SQLITE driver
    db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");

    //Set the database path
    db.setDatabaseName(this->filename);

    //check if the database is opened
    if(!db.open())
        QMessageBox::critical(this, "FAILED", "DB is not opened");

    //définir la requete sur la base de données
    auto query = QSqlQuery(db);

    //Create a table named accounts
    QString accountTable{"CREATE TABLE IF NOT EXISTS accounts"
                         "(username VARCHAR(20), name VARCHAR(20),"
                         "password VARCHAR(20))"};

    if(!query.exec(accountTable))
        QMessageBox::critical(this,"Info","Cannot create accounts");

    //Create a table named genres
    QString genreTable{"CREATE TABLE IF NOT EXISTS genres"
                            "(ID INTEGER, name VARCHAR(20))"};
    if(!query.exec(genreTable))
        QMessageBox::critical(this,"Info","Cannot create genre Table");

    //Create a table named authors
    QString authorTable{"CREATE TABLE IF NOT EXISTS authors"
                      "(ID INTEGER, firstName VARCHAR(20), lastName VARCHAR(20),"
                       "expertise VARCHAR(20), about VARCHAR(40))"};
    if(!query.exec(authorTable))
        QMessageBox::critical(this,"Info","Cannot create authors Table");

    //Create a table named members
    QString memberTable{"CREATE TABLE IF NOT EXISTS members"
                      "(ID INTEGER PRIMARY KEY, firstName VARCHAR(20), lastName VARCHAR(20),"
                       "phone VARCHAR(20), email VARCHAR(40), gender VARCHAR(10))"};
    if(!query.exec(memberTable))
        QMessageBox::critical(this,"Info","Cannot create members Table");

    //Create a table named books
    QString bookTable{"CREATE TABLE IF NOT EXISTS books"
                      "(ID INTEGER PRIMARY KEY, ISBN VARCHAR(20), name VARCHAR(20),"
                      "author VARCHAR(20), genre VARCHAR(20), quantity INT,"
                      "publisher VARCHAR(20), price REAL, date VARCHAR(10),"
                      "description VARCHAR(80), cover VARCHAR(50))"};
    if(!query.exec(bookTable))
        QMessageBox::critical(this,"Failed","Cannot create books Table");

    //Create a table named bookStatus
    QString Table{"CREATE TABLE IF NOT EXISTS bookStatus"
                      "(Book INTEGER, Member INTEGER, Status VARCHAR(10),"
                       "IssueDate date, ReturnDate date, Note VARCHAR(50))"};
    if(!query.exec(Table))
        QMessageBox::critical(this,"Info","Cannot create bookStatus Table");
}

```

## Authorization and Authentication
### Login 
<p align="center">
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152709497-b43079bc-6fb9-4eb9-affb-b64daaaa128c.png"/>
</p> </br>

This feature is used by the users to login into system. They are required to enter username and
password before they are allowed to enter the system .The username and password will be verified
and if invalid username or password is there user is not allowed to enter the system.</br>


```Login.cpp```
```cpp
void Login::on_loginButton_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //Get the username
    QString username = ui->username->text();

    //Get the password
    QString password = ui->password->text();
    
    //Check if the db is opened
    if(!db.isOpen())
    {
        qDebug() << "Failed to open the database";
    }

    //Define the query
    auto query = QSqlQuery(db);

    if(!username.isEmpty() & !password.isEmpty())
    {
        //Create the body of the query
        QString checkLogin = {"SELECT * FROM accounts WHERE username='"
                              +username+"' AND password='"+password+"'"};

        if(query.exec(checkLogin))
        {
            int count = 0;
            while(query.next())
            {
                count++;
            }
            if(count == 1)
            {
                lib.setUsername(username);

                //Hide the current window
                this->hide();

                //show the mainwindow
                lib.exec();
            }
            else if(count < 1)
                QMessageBox::warning(this, "Empty", "You are not registered!");
        }
        else
            qDebug() << "cannot select from accounts";
    }
    else
        QMessageBox::warning(this, "Empty", "Fields are empty!");
}

void Login::on_signUpButton_clicked()
{
    this->hide();
    signUp signUp;
    signUp.exec();
}

void Login::on_forgetPasswdBtn_clicked()
{
    this->hide();
    newPasswd newpass;
    newpass.exec();
}
```

## Sign Up
<p align="center">
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152710340-87180d46-a3b1-4de1-b330-40115a3c8acc.png"/>
</p></br>
This feature can be performed by all users to register new user to create account.</br>

```signup.cpp``` 
```cpp
void signUp::on_createButton_clicked()
{
    //Get the content
    QString username = ui->username->text();
    QString name = ui->name->text();
    QString password = ui->password->text();

    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //Add name password and username to the db
    if((!username.isEmpty() & !name.isEmpty()) & !password.isEmpty())
    {
        //cherche si le compte existe
        auto search = QSqlQuery(db);
        QString searchAcc = {"SELECT * FROM accounts WHERE username='"
                             +username+"' AND name='"+name+"' AND password='"
                             +password+"'"};
        if(!search.exec(searchAcc))
             qDebug() << "Cannot select";
        int count = 0;
        while(search.next())
        {
            count++;
        }

        if(count>=1)
            QMessageBox::warning(this, "Failed", "Account Already Exist!");
        else
        {
            QString addEntry = {"INSERT INTO accounts (username, name, password)"
                                "VALUES ('%1', '%2', '%3')"};
            auto query = QSqlQuery(db);

            if(!query.exec(addEntry.arg(username).arg(name).arg(password)))
                qDebug() << "Cannot add entry";
            else
                QMessageBox::information(this, "SUCCESS", "You registered succesfully!");
            }
     }
    else
     QMessageBox::warning(this, "Empty", "Fields are empty!");
}

void signUp::on_backButton_clicked()
{
    this->hide();
    Login login;
    login.exec();
}
```
## New Password
<p align="center">
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152710893-0bf76eea-1cc9-4133-a244-83435f458cc7.png"/>
</p></br>
This feature allows users to update their passwords.</br>

```newpasswd.cpp```
```cpp
void newPasswd::on_submitButton_clicked()
{
    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //Get the username
    QString username = ui->username->text();

    //Get the username
    QString name = ui->name->text();

    //Get the password
    QString newpass = ui->newpass->text();

    //Check if the db is opened
    if(!db.isOpen())
    {
        qDebug() << "Failed to open the database";
    }

    //Define the query
    auto query = QSqlQuery(db);

    //Define the body of the query
    QString updatePass = {"UPDATE accounts SET password= '"+newpass+"'"
                          "WHERE username='"+username+"'AND name='"+name+"'"};

    //Execute the query
    if(!query.exec(updatePass))
        qDebug() << "Cannot update passwd";

    int count = 0;
    while(query.next())
    {
        count++;
    }
    if(count == 1)
    {
        QMessageBox::information(this, "SUCCESS", "Password updated succesfully!");
    }
    else
        QMessageBox::warning(this, "Warning", "Name or Username is incorrect");
}
void newPasswd::on_backButton_clicked()
{
    this->hide();
    Login login;
    login.exec();
}
```

## Manage Genres
<p align="center">
  <img align="center" width="60%" height="60%" src="https://user-images.githubusercontent.com/72691265/152711598-e42f9220-ce50-46a9-a705-b72cd3b34cb4.png"/>
</p></br>
In order not to limit the genres books at the level of choosing the book's category, this feature allows librarians to manage available genres (adding, editing, deleting).</br>

```manageGenres.cpp```
```cpp
void manageBooks::on_add_clicked()
{
    //retrieve content
    QString ID = ui->ID->text();
    QString name = ui->Name->text();

    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;
    
    //define query
    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM genres"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from genres";
    
    //insert the new genre in the db genres table, otherwise update it
    if(!ID.isEmpty() & !name.isEmpty())
    {
        auto search = QSqlQuery(db);
        QString searchIDName = {"SELECT * FROM genres WHERE ID = '"+ID+"'"};
        if(!search.exec(searchIDName))
            qDebug() << "Cannot select from genres";
        int count = 0;
        while(search.next())
            count++;
        if(count >= 1)
        {
            auto query = QSqlQuery(db);
            QString update = {"UPDATE genres SET  name = '"+name+"'"
                              "WHERE ID = '"+ID+"'"};
            if(!query.exec(update))
                qDebug() << "Cannot select from genres";

            //Afficher les genres dans QTableView
            model->setQuery(select);
            ui->genreTableView->setModel(model);
        }
        else{
            auto query = QSqlQuery(db);
            QString addGenre = {"INSERT INTO genres (ID, name) VALUES ('%1', '%2')"};

            if(!query.exec(addGenre.arg(ID.toInt()).arg(name)))
                qDebug() << "Cannot add genre";
            else
            {
                QMessageBox::information(this, "SUCCESS", "Genre added successfully");
            }

            //Afficher les genres dans QTableView
            model->setQuery(select);
            ui->genreTableView->setModel(model);
        }
    }
    else
       QMessageBox::warning(this, "Empty", "Fields are empty!");
}
void manageBooks::on_edit_clicked()
{
    QModelIndexList selectedRow = ui->genreTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);

        //get the content of each column
        QString ID = ui->genreTableView->model()->data(ui->genreTableView->model()->index(row.row(), 0)).toString();
        QString name = ui->genreTableView->model()->data(ui->genreTableView->model()->index(row.row(), 1)).toString();

        //set the ID and the name in te correspondant lienEdit
        ui->ID->setText(ID);
        ui->Name->setText(name);
    }
}
void manageBooks::on_deleteButton_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;
    
    //to update the value of genres (QcomboBox)
    addBook book;
    editBook editBook;

    QModelIndexList selectedRow = ui->genreTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);
        QString name = ui->genreTableView->model()->data(ui->genreTableView->model()->index(row.row(), 1)).toString();

        auto select = QSqlQuery(db);
        QString selectAll = {"SELECT * FROM genres"};
        if(!select.exec(selectAll))
            qDebug() << "Cannot select from genres";

        auto deleteQuery = QSqlQuery(db);
        QString deleteGenre = {"DELETE FROM genres WHERE name= '"+name+"'"};
        if(!deleteQuery.exec(deleteGenre))
            qDebug() << "Cannot delete from genres";

        model->setQuery(select);
        ui->genreTableView->setModel(model);
    }
}
```

## Manage Authors
<p align="center">
  <img align="center" width="70%" height="70%" src="https://user-images.githubusercontent.com/72691265/152712241-b7996645-94a4-4f43-b838-13a5d4892e60.png"/>
</p></br>
This feature allows admin to add, edit and delete a authors.</br>

```manageAuthors.cpp```
```cpp
void ManageAuthors::on_addButtton_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;
    
    //retrieve content
    QString ID = ui->ID->text();
    QString firstName = ui->firstName->text();
    QString lastName = ui->lastName->text();
    QString expertise = ui->expertise->text();
    QString about = ui->about->toPlainText();

    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM authors"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from authors";

    if((!ID.isEmpty() & !firstName.isEmpty())&(!lastName.isEmpty() & !expertise.isEmpty()) & !about.isEmpty())
    {
        auto search = QSqlQuery(db);
        QString searchIDAuthor = {"SELECT * FROM authors WHERE ID = '"+ID+"'"};
        if(!search.exec(searchIDAuthor))
            qDebug() << "Cannot select from authors";

        int count = 0;
        while(search.next())
            count++;

        if(count >= 1)
        {
            auto query = QSqlQuery(db);
            QString update = {"UPDATE authors SET  firstName = '"+firstName+"', lastName="
                              "'"+lastName+"', expertise='"+expertise+"', about = '"+about+"'"
                              " WHERE ID = '"+ID+"'"};
            if(!query.exec(update))
                qDebug() << "Cannot update authors";

            //Afficher les auteurs dans QTableView
            model->setQuery(select);
            ui->authorTableView->setModel(model);
        }
        else{
            auto query = QSqlQuery(db);
            QString addAuthor = {"INSERT INTO authors (ID, firstName, lastName, expertise,"
                                "about) VALUES ('%1', '%2','%3', '%4', '%5')"};

            if(!query.exec(addAuthor.arg(ID.toInt()).arg(firstName).arg(lastName).arg(expertise).arg(about)))
                qDebug() << "Cannot add authors";

            //Afficher les genres dans QTableView
            model->setQuery(select);
            ui->authorTableView->setModel(model);
        }
    }
    else
       QMessageBox::warning(this, "Empty", "Fields are empty!");
}

void ManageAuthors::on_editButton_clicked()
{
    QModelIndexList selectedRow = ui->authorTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);

        //get the content of each column
        QString ID = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 0)).toString();
        QString firstName = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 1)).toString();
        QString lastName = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 2)).toString();
        QString expertise = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 3)).toString();
        QString about = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 4)).toString();

        //set the ID and the name in te correspondant lienEdit
        ui->ID->setText(ID);
        ui->firstName->setText(firstName);
        ui->lastName->setText(lastName);
        ui->expertise->setText(expertise);
        ui->about->setText(about);
    }
}
void ManageAuthors::on_deleteButton_clicked()
{
    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    QModelIndexList selectedRow = ui->authorTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);

        QString ID = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 0)).toString();

        auto select = QSqlQuery(db);
        QString selectAll = {"SELECT * FROM authors"};
        if(!select.exec(selectAll))
            qDebug() << "Cannot select from authors";

        auto deleteQuery = QSqlQuery(db);
        QString deleteGenre = {"DELETE FROM authors WHERE ID= '"+ID+"'"};
        if(!deleteQuery.exec(deleteGenre))
            qDebug() << "Cannot delete from authors";

        model->setQuery(select);
        ui->authorTableView->setModel(model);
    }
}
```

## Manage Members
### Add Member
<p align="center">
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152712674-292e868f-ba84-476b-93f5-ce1fccc81091.png"/>
</p></br>

```addMember.cpp```
```cpp
void addMember::on_addMemberButton_clicked()
{
    //get the content of the fields
    QString firstName =ui->firstName->text();
    QString lastName = ui->lastName->text();
    QString  phone = ui->phone->text();
    QString email = ui->email->text();
    QString gender = ui->gender->currentText();

    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //Make sure that the fields are not empty
    if((!firstName.isEmpty() & !lastName.isEmpty())&(!phone.isEmpty() & !email.isEmpty())& !gender.isEmpty())
    {
        //Create the query
        auto query = QSqlQuery(db);

        //Insert into db
        QString insert = {"INSERT INTO members (firstName, lastName, phone, email, gender)"
                          "VALUES ('%1', '%2', '%3', '%4', '%5')"};

        //Execute the query
        if(!query.exec(insert.arg(firstName).arg(lastName).arg(phone).arg(email).arg(gender)))
            qDebug() << "Cannot insert into members";
        else
            QMessageBox::information(this, "SUCCESS", "Member added succesfully!");
    }
    else
       QMessageBox::warning(this, "Empty", "Fields are empty!");
}

```

### Edit Member
<p align="center">
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152712854-2cc2ad04-73b1-4131-bfb8-01e98c898a89.png"/>
</p></br>

```editMember.cpp```
```cpp
void editMember::on_searchMemberBtn_clicked()
{
    //get the content of the Line edit
    QString ID = ui->ID->text();
    QString firstName;
    QString lastName;
    QString phone;
    QString mail;
    QString gender;

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //Define the query
    auto query = QSqlQuery(db);
    QString searchID = {"SELECT * FROM members WHERE ID = '%1'"};

    //execute the query
    if(!query.exec(searchID.arg(ID)))
        qDebug() << "Cannot select from members";

    //check if the member is found
    while(query.next())
        count++;

    if(count != 1)
    {
        QMessageBox::warning(this, "Not Found", "Member not Found");
        ui->ID->clear();
    }
    else
    {
        //Retrieve the fields identified by ID
        if(query.first())
        {
            firstName = query.value(1).toString();
            lastName = query.value(2).toString();
            phone = query.value(3).toString();
            mail = query.value(4).toString();
            gender = query.value(5).toString();
        }
    }

    //Show the fields in the corresponding line Edit
    ui->firstName->setText(firstName);
    ui->lastName->setText(lastName);
    ui->phone->setText(phone);
    ui->mail->setText(mail);
    ui->gender->setCurrentText(gender);

}
void editMember::on_editMemberBtn_clicked()
{
    //get the content of the line edits
    QString ID = ui->ID->text();
    QString firstName = ui->firstName->text();
    QString lastName = ui->lastName->text();
    QString phone = ui->phone->text();;
    QString mail = ui->mail->text();
    QString gender = ui->gender->currentText();

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //Define the query
    auto query = QSqlQuery(db);
    QString searchID = {"UPDATE members SET firstName = '"+firstName+"',"
                        "lastName = '"+lastName+"', phone = '"+phone+"',"
                        "email = '"+mail+"', gender = '"+gender+"'"
                        " WHERE ID = '"+ID+"'"};
    if(!ID.isEmpty())
    {
        if(count == 1)
        {
            //execute the query
            if(!query.exec(searchID))
                qDebug() << "Cannot update members";
            else
                QMessageBox::information(this, "SUCCESS", "Member updated successfully");
        }
        else
            QMessageBox::warning(this, "Warning", "Search member");
    }
    else
        QMessageBox::warning(this, "Warning", "Insert ID");
}
```
### Delete Member
<p align="center">
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152713041-ba11aca6-39d2-494e-87cf-d89f3ac41520.png"/>
</p></br>

```deleteMember.cpp```
```cpp
void deleteMember::on_deleteMemberBtn_clicked()
{
    //Get The ID
    QString ID = ui->ID->text();

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //check if the member exists
    auto searchQuery = QSqlQuery(db);
    QString search{"SELECT * FROM members WHERE ID = '%1'"};
    if(!searchQuery.exec(search.arg(ID)))
        qDebug() << "cannot search in members";
    int count = 0;
    while(searchQuery.next())
        count++;

    if(!ID.isEmpty())
    {
        if(count == 1)
        {
            //define the query on the db
            auto query = QSqlQuery(db);
            QString del{"DELETE FROM members WHERE ID= '%1'"};

            //execute the query
            if(!query.exec(del.arg(ID)))
                qDebug() << "Cannot delete member";
            else
                QMessageBox::information(this, "SUCCESS", "member deleted successfully");
        }
        else
        {
            QMessageBox::warning(this, "Failed", "Member not found");
            ui->ID->del();
        }
    }
    else
        QMessageBox::warning(this, "Failed", "Insert ID");
}
```

### Members List
<p align="center">
  <img align="center" width="70%" height="70%" src="https://user-images.githubusercontent.com/72691265/152713200-cb750d6c-0a6c-4ca2-8717-fa2ff5bb4e94.png"/>
</p></br>

```membersList.cpp```
```cpp
void membersList::on_value_textEdited(const QString &text)
{
    //get the content of the line edit
    QString value = ui->value->text() + "%";

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(!value.isEmpty())
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM members WHERE ID LIKE '"+value+"'"
                       "OR firstName LIKE '"+value+"' OR lastName LIKE"
                       "'"+value+"' OR phone LIKE '"+value+"' OR email LIKE '"+value+"'"
                       "OR gender LIKE '"+value+"'"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from members";
        else
        {
            //define the model
            QSqlQueryModel * model = new QSqlQueryModel;
            model->setQuery(query);
            ui->tableView->setModel(model);
        }
    }
    else
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM members"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from members";

        //define the model
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
}
````

## Manage Books
### Add Book
<p align="center">
  <img align="center" width="70%" height="70%" src="https://user-images.githubusercontent.com/72691265/152713397-751335f0-367e-448f-a4c8-d87480646540.png"/>
</p></br>

```addBook.cpp```
```cpp
void addBook::on_addBookBtn_clicked()
{
    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //get the content
    QString ISBN = ui->ISBN->text();
    QString name = ui->Name->text();
    QString author = ui->author->text();
    QString genre = ui->Genre->currentText();
    QString quantity = ui->quantity->text();
    QString publisher = ui->publisher->text();
    QString price = ui->price->text();
    QString date = ui->date->text();
    QString description = ui->description->toPlainText();
    QString coverPath = coverFilename;

    QStringList bookInfo {ISBN, name, author, genre, quantity, publisher, price, date};

    //test if the fields are not empty
    bool full = true;
    for(int i=0; i<bookInfo.length(); i++)
    {
        if(bookInfo[i].isEmpty())
        {
            full = false;
            break;
        }
    }

    //test if the book already exits
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM books WHERE ISBN = '%1'"};
    if(!query.exec(select.arg(ISBN)))
        qDebug() << "Cannot select from books table";


    int count = 0;
    while(query.next())
        count++;

    if(full)
    {
        if(count == 0)
        {
            //Define the query on the db
            auto query = QSqlQuery(db);
            QString insert{"INSERT INTO books (ISBN, name, author, genre, quantity, publisher, price, date, description, cover)"
                           "VALUES ('%1', '%2', '%3','%4','%5','%6','%7','%8','%9', '%10')"};

            //execute the query
                  if(!query.exec(insert.arg(ISBN).arg(name).arg(author).arg(genre).arg(quantity.toInt()).arg(publisher).arg(price.toDouble()).arg(date).arg(description).arg(coverPath)))
            {
                QMessageBox::critical(this,"Failed","Cannot fill books Table");
            }
            else
            {
                QMessageBox::information(this,"Info","Book is added sucessfully");
            }
        }
        else
            QMessageBox::warning(this, "Info", "Book already exists");
    }
    else
        QMessageBox::critical(this,"Failed","Fields are empty");
}

void addBook::on_selectImgBtn_clicked()
{
    //Open a file dialog to choose the image
    coverFilename = QFileDialog::getOpenFileName();
    ui->coverLabel->setPixmap(coverFilename);
}

void addBook::on_chooseAuthBtn_clicked()
{
    authorsList authors;
    authors.exec();
    ui->author->setText(authors.author);
}

void addBook::on_chooseGenreBtn_clicked()
{
    genreList genre;
    genre.exec();
    ui->Genre->addItem(genre.genre);
}
```
### Edit Book
<p align="center">
  <img align="center" width="70%" height="70%" src="https://user-images.githubusercontent.com/72691265/152713652-6496ec47-4602-43a8-ab39-4e41560bdd63.png"/>
</p></br>

```editBook.cpp```
```cpp
void editBook::on_cancelBtn_clicked()
{
    this->hide();
}

void editBook::on_selectImgBtn_clicked()
{
    coverFilename = QFileDialog::getOpenFileName();
    ui->coverLabel->setPixmap(coverFilename);
    clicked = true;
}

void editBook::on_editBookBtn_clicked()
{
    //get the content of the Line edit
    QString ISBN = ui->ISBN->text();
    QString name = ui->name->text();
    QString author = ui->author->text() ;
    QString genre = ui->genre->currentText();
    QString quantity = ui->quantity->text();
    QString publisher = ui->publisher->text();
    QString price = ui->price->text();
    QString date = ui->date->text();
    QString description = ui->description->toPlainText();

    //test if the fields are not empty
    QStringList bookInfo {ISBN, name, author, genre, quantity, publisher, price, date};
    bool full = true;
    for(int i=0; i<bookInfo.length(); i++)
    {
        if(bookInfo[i].isEmpty())
        {
            full = false;
            break;
        }
    }

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(full)
    {
        if(clicked)
        {
            QString coverPath = coverFilename;
            //Define the query
            auto query = QSqlQuery(db);
            QString searchISBN = {"UPDATE books SET name = '"+name+"',"
                                "author = '"+author+"', genre = '"+genre+"',"
                                "quantity = '"+quantity+"', publisher = '"+publisher+"',"
                                "price = '"+price+"', date = '"+date+"', description = '"+description+"',"
                                "cover = '"+coverPath+"' WHERE ISBN = '"+ISBN+"'"};
            if(!query.exec(searchISBN))
                qDebug() << "Cannot search ISBN";
            else
                QMessageBox::information(this,"SUCCESS", "Book updated successfully");
        }
        else
        {
            //Define the query
            auto query = QSqlQuery(db);
            QString searchISBN = {"UPDATE books SET name = '"+name+"',"
                                "author = '"+author+"', genre = '"+genre+"',"
                                "quantity = '"+quantity+"', publisher = '"+publisher+"',"
                                "price = '"+price+"', date = '"+date+"', description = '"+description+"'"
                                "WHERE ISBN = '"+ISBN+"'"};
            if(!query.exec(searchISBN))
                qDebug() << "Cannot search ISBN";
            else
                QMessageBox::information(this,"SUCCESS", "Book updated successfully");
        }
    }
    else
        QMessageBox::warning(this,"Failed", "Fields are empty");
}

void editBook::on_searchBtn_clicked()
{
    //get the content of the Line edit
    QString ISBN = ui->ISBN->text();
    QString name;
    QString author;
    QString genre;
    QString quantity;
    QString publisher;
    QString price;
    QString date;
    QString description;
    QString coverPath;

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(!ISBN.isEmpty())
    {
        //Define the query
        auto query = QSqlQuery(db);
        QString searchISBN = {"SELECT * FROM books WHERE ISBN = '%1'"};

        //execute the query
        if(!query.exec(searchISBN.arg(ISBN)))
            qDebug() << "Cannot select from books";

        //check if the book is found
        while(query.next())
            count++;

        if(count != 1)
        {
            QMessageBox::warning(this, "Not Found", "Book not Found");
            ui->ISBN->clear();
        }
        else
        {
            //Retrieve the fields identified by ID
            if(query.first())
            {
                name = query.value(2).toString();
                author = query.value(3).toString();
                genre = query.value(4).toString();
                quantity = query.value(5).toString();
                publisher = query.value(6).toString();
                price = query.value(7).toString();
                date = query.value(8).toString();
                description = query.value(9).toString();
                coverPath = query.value(10).toString();
            }
        }

        //Convert to QDate
        QStringList dateList = date.split("/");
        QDate Date;
        if(dateList.length() == 3)
            Date = QDate(dateList[2].toInt(), dateList[1].toInt(), dateList[0].toInt());

        //Show the fields in the corresponding line Edit
        ui->name->setText(name);
        ui->author->setText(author);
        ui->genre->setCurrentText(genre);
        ui->quantity->setValue(quantity.toInt());
        ui->publisher->setText(publisher);
        ui->price->setText(price);
        ui->date->setDate(Date);
        ui->description->setText(description);
        if(QFileInfo::exists(coverPath))
            ui->coverLabel->setPixmap(coverPath);
        else
            ui->coverLabel->setText("Book cover not found");
    }
    else
        QMessageBox::warning(this, "ISBN", "Insert ISBN");

}

void editBook::on_changeAuthorBtn_clicked()
{
    authorsList authors;
    authors.exec();
    ui->author->setText(authors.author);
}
```
### Delete Book
<p align="center">
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152714145-31f176f9-ba5c-4506-a709-c551992d16c2.png"/>
</p></br>

```deleteBook.cpp```
```cpp
void deleteBook::on_deleteBookBtn_clicked()
{
    //Get The ID
    QString ID = ui->ID->text();

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //check if the member exists
    auto searchQuery = QSqlQuery(db);
    QString search{"SELECT * FROM books WHERE ID = '%1'"};
    if(!searchQuery.exec(search.arg(ID)))
        qDebug() << "cannot search in members";
    int count = 0;
    while(searchQuery.next())
        count++;

    if(!ID.isEmpty())
    {
        if(count == 1)
        {
            //define the query on the db
            auto query = QSqlQuery(db);
            QString del{"DELETE FROM books WHERE ID= '%1'"};

            //execute the query
            if(!query.exec(del.arg(ID)))
                qDebug() << "Cannot delete book";
            else
            {
                QMessageBox::information(this, "SUCCESS", "Book deleted successfully");
            }
        }
        else
        {
            QMessageBox::warning(this, "Failed", "Book not found");
            ui->ID->clear();
        }
    }
    else
        QMessageBox::warning(this, "Failed", "Insert ID");
}
```
### Books List
<p align="center">
  <img align="center" width="70%" height="70%" src="https://user-images.githubusercontent.com/72691265/152714379-85165e82-9610-4ed9-a7f7-136321d4ae4b.png"/>
</p></br>

```booksList.cpp```
```cpp
void bookList::on_value_textEdited(const QString &arg1)
{
    //get the content of the line edit
    QString value = ui->value->text() + "%";

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(!value.isEmpty())
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM books WHERE ID LIKE '"+value+"'"
                       "OR ISBN LIKE '"+value+"' OR name LIKE '"+value+"' OR author LIKE '"+value+"'"
                       "OR genre LIKE '"+value+"' OR quantity LIKE '"+value+"'"
                       "OR publisher LIKE '"+value+"' OR price LIKE '"+value+"' OR date LIKE '"+value+"'"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from books";
        else
        {
            //define the model
            QSqlQueryModel * model = new QSqlQueryModel;
            model->setQuery(query);
            ui->tableView->setModel(model);
        }
    }
    else
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM books"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from books";

        //define the model
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
}

void bookList::showInfo()
{
    //get the clicked item
    auto row = ui->tableView->currentIndex().row();

    //show information in the left side
    QString ISBN = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(row,2)).toString();
    QString author = ui->tableView->model()->data(ui->tableView->model()->index(row,3)).toString();
    QString genre = ui->tableView->model()->data(ui->tableView->model()->index(row,4)).toString();
    QString quantity = ui->tableView->model()->data(ui->tableView->model()->index(row,5)).toString();
    QString publisher = ui->tableView->model()->data(ui->tableView->model()->index(row,6)).toString();
    QString price = ui->tableView->model()->data(ui->tableView->model()->index(row,7)).toString();
    QString date = ui->tableView->model()->data(ui->tableView->model()->index(row,8)).toString();
    QString desc = ui->tableView->model()->data(ui->tableView->model()->index(row,9)).toString();
    QString cover = ui->tableView->model()->data(ui->tableView->model()->index(row,10)).toString();

    ui->coverLabel->setPixmap(cover);
    ui->ISBN->setText(ISBN);
    ui->name->setText(name);
    ui->author->setText(author);
    ui->genre->setText(genre);
    ui->publisher->setText(publisher);
    ui->price->setText(price);
    ui->quantity->setText(quantity);
    ui->date->setText(date);
    ui->desc->setText(desc);
}

```

### SelectAuthor
<p align="center">
  <img align="center" width="60%" height="60%" src="https://user-images.githubusercontent.com/72691265/152714723-596b45ec-0aaa-4389-a3d1-a127d4255ec5.png"/>
</p></br>

```authorsList.cpp```
```cpp
    //At constructor
    connect(ui->authorTableView, &QTableView::doubleClicked, this, &authorsList::showInfo);
    
    void authorsList::showInfo()
{
    QModelIndexList selectedRow = ui->authorTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);
        auto firstName = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 1)).toString();
        auto lastName = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 2)).toString();
        author = firstName + " " + lastName;
    }
    this->hide();
}

void authorsList::on_value_textEdited(const QString &arg1)
{
    //get the content of the line edit
    QString value = ui->value->text() + "%";

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(!value.isEmpty())
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM authors WHERE ID LIKE '"+value+"'"
                       "OR firstName LIKE '"+value+"' OR lastName LIKE '"+value+"' OR expertise LIKE '"+value+"'"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from auhors";
        else
        {
            //define the model
            QSqlQueryModel * model = new QSqlQueryModel;
            model->setQuery(query);
            ui->authorTableView->setModel(model);
        }
    }
    else
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM authors"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from authors";

        //define the model
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->authorTableView->setModel(model);
    }
}
```
### SelectGenre
<p align="center">
  <img align="center" width="60%" height="60%" src="https://user-images.githubusercontent.com/72691265/152715491-5a1cf481-eb21-4e51-bb39-34bb42909bf6.png"/>
</p></br>

```genresList.cpp```
```cpp
    //At the constructor
    connect(ui->TableView, &QTableView::doubleClicked, this, &genreList::showInfo);
    
    void genreList::showInfo()
{
    QModelIndexList selectedRow = ui->TableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);
        genre = ui->TableView->model()->data(ui->TableView->model()->index(row.row(), 1)).toString();
    }
    this->hide();
}

void genreList::on_value_textEdited(const QString &arg1)
{
    //get the content of the line edit
    QString value = ui->value->text() + "%";

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(!value.isEmpty())
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM genres WHERE ID LIKE '"+value+"' OR name LIKE '"+value+"'"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from genres";
        else
        {
            //define the model
            QSqlQueryModel * model = new QSqlQueryModel;
            model->setQuery(query);
            ui->TableView->setModel(model);
        }
    }
    else
    {
        //define the query on the db and the model
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM genres"};

        //execute the query
        if(!query.exec(select))
            qDebug() << "Cannot select from genres";

        //define the model
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->TableView->setModel(model);
    }
}   
```
## Manage Books Transaction
Book transaction feature is a main feature in Library Management System. When members wants to borrow books, return book or they want to register lost book, it is all under Book Transaction Feature.

### Issue Book
<p align="center">
  <img align="center" width="60%" height="60%" src="https://user-images.githubusercontent.com/72691265/152715535-5b310ee5-26c4-4a85-af4f-91cd044f39f4.png"/>
</p></br>

```issueBook.cpp```
```cpp
void IssueBook::on_searchBook_clicked()
{
    //Get the ID
    QString bookID = ui->bookID->text();
    QString bookName;
    int quantity;

    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //search the book
    auto query = QSqlQuery(db);
    QString searchBook{"SELECT * FROM books WHERE ID = '%1'"};
    if(!query.exec(searchBook.arg(bookID)))
        qDebug() << "Cannot select from  books";

    int count = 0;
    while(query.next())
        count++;
    if(count > 0)
    {
        if(query.first())
        {
            bookName = query.value(2).toString();
            ui->bookName->setText(bookName);

            quantity = query.value(5).toInt();
            if(quantity > 0)
            {
                 ui->available->setText("Yes");
                 ui->available->setStyleSheet("QLabel {color : green; font: 10pt Comic Sans MS;}");
            }
            else
            {
                ui->available->setText("No");
                ui->available->setStyleSheet("QLabel {color : red; font: 10pt Comic Sans MS;}");
            }
        }
    }
    else
        QMessageBox::critical(this,"Failed", "Book Not found");
}
void IssueBook::on_searchMember_clicked()
{
    //Get the ID
    QString memberID = ui->memberID->text();
    QString memberName;

    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //search the member
    auto query = QSqlQuery(db);
    QString searchMember{"SELECT * FROM members WHERE ID = '%1'"};
    if(!query.exec(searchMember.arg(memberID)))
        qDebug() << "Cannot select from  members";

    int count = 0;
    while(query.next())
        count++;

    if(count > 0)
    {
        if(query.first())
        {
            memberName = query.value(1).toString();
            ui->memberName->setText(memberName);
        }
    }
    else
        QMessageBox::critical(this,"Failed", "Member Not found");
}

void IssueBook::on_issue_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //retrieve the IDs
    QString bookID = ui->bookID->text();
    QString memberID = ui->memberID->text();
    QString status{"Issued"};
    QString issueDate = ui->issueDate->text();
    QString returnDate = ui->returnDate->text();
    QString notes = ui->notes->toPlainText();

    //retrieve the issueDate
    QStringList dateList_1 = issueDate.split("/");
    QDate Date_1;
    if(dateList_1.length() == 3)
        Date_1 = QDate(dateList_1[2].toInt(), dateList_1[1].toInt(), dateList_1[0].toInt());

    //Retrieve the return Date
    QStringList dateList_2 = returnDate.split("/");
    QDate Date_2;
    if(dateList_2.length() == 3)
        Date_2 = QDate(dateList_2[2].toInt(), dateList_2[1].toInt(), dateList_2[0].toInt());

    //test
    if(Date_1 > Date_2)
        QMessageBox::critical(this, "Failed", "The return date must be after the issue Date");
    else{
        auto query = QSqlQuery(db);
        QString insert{"INSERT INTO bookStatus (Book, Member, Status, IssueDate, ReturnDate, Note) VALUES ('%1', '%2','%3', '%4', '%5','%6')"};
        if(!query.exec(insert.arg(bookID.toInt()).arg(memberID.toInt()).arg(status).arg(issueDate).arg(returnDate).arg(notes)))
        {
            qDebug() << "cannot fill bookStatus";
        }
        else
            QMessageBox::information(this, "SUCCESS", "Book issued successfully");
    }
}

void IssueBook::on_cancel_clicked()
{
    this->hide();
}
```

### Return Book
<p align="center">
  <img align="center" width="70%" height="70%" src="https://user-images.githubusercontent.com/72691265/152715812-eff16c0e-9391-48bc-af3a-25b9207e307c.png"/>
</p></br>

```issueBook.cpp```
```cpp
void ReturnBook::on_returnBtn_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //retrieve the IDs
    QString bookID = ui->bookID->text();
    QString memberID = ui->memberID->text();
    QString status{"Returned"};
    QString returnDate = ui->returnDate->text();
    QString note = ui->notes->toPlainText();

    //retrieve the issueDate
    QStringList dateList_1 = ui->issueDate->text().split("/");
    QDate Date_1;
    if(!dateList_1.isEmpty())
        Date_1 = QDate(dateList_1[2].toInt(), dateList_1[1].toInt(), dateList_1[0].toInt());

    //Retrieve the return Date
    QStringList dateList_2 = ui->returnDate->text().split("/");
    QDate Date_2;
    if(!dateList_2.isEmpty())
        Date_2 = QDate(dateList_2[2].toInt(), dateList_2[1].toInt(), dateList_2[0].toInt());

    //test
    if(Date_1 > Date_2)
        QMessageBox::critical(this, "Failed", "The return date must be after the issue Date");
    else{
        auto query = QSqlQuery(db);
        QString update{"UPDATE bookStatus SET Status = '%1', ReturnDate = '%2', Note = '%3' WHERE (Book = '%4' AND Member = '%5')"};
        if(!query.exec(update.arg(status).arg(returnDate).arg(note).arg(bookID.toInt()).arg(memberID.toInt())))
            qDebug() << "cannot update bookStatus";
        else
            QMessageBox::information(this, "SUCCESS", "Book returned successfully");
    }

    //updtae the table view
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM bookStatus"};
    if(!query.exec(select))
        qDebug() << "Cannot select from bookStatus";
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(query);
    ui->tableView->setModel(model);
}

void ReturnBook::showInfo()
{
    QModelIndexList selectedRow = ui->tableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);
        auto bookID = ui->tableView->model()->data(ui->tableView->model()->index(row.row(), 0)).toString();
        auto memberID = ui->tableView->model()->data(ui->tableView->model()->index(row.row(), 1)).toString();
        auto issueDate = ui->tableView->model()->data(ui->tableView->model()->index(row.row(), 3)).toString();
        auto returnDate = ui->tableView->model()->data(ui->tableView->model()->index(row.row(), 4)).toString();
        auto note = ui->tableView->model()->data(ui->tableView->model()->index(row.row(), 5)).toString();

        ui->bookID->setText(bookID);
        ui->memberID->setText(memberID);

        //retrieve the issueDate
        QStringList dateList = issueDate.split("/");
        QDate Date;
        if(!dateList.isEmpty())
            Date = QDate(dateList[2].toInt(), dateList[1].toInt(), dateList[0].toInt());
        ui->issueDate->setDate(Date);

        //retrieve the returnDate
        QStringList dateList_2 = returnDate.split("/");
        QDate Date_2;
        if(!dateList_2.isEmpty())
            Date_2 = QDate(dateList_2[2].toInt(), dateList_2[1].toInt(), dateList_2[0].toInt());
        ui->returnDate->setDate(Date_2);

        //retrieve the notes
        ui->notes->setText(note);

    }
}

void ReturnBook::on_lostBtn_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //retrieve the IDs
    QString bookID = ui->bookID->text();
    QString memberID = ui->memberID->text();
    QString status{"Lost"};
    QString returnDate = ui->returnDate->text();
    QString note = ui->notes->toPlainText();

    auto query = QSqlQuery(db);
    QString update{"UPDATE bookStatus SET Status = '%1', ReturnDate = '%2', Note = '%3' WHERE (Book = '%4' AND Member = '%5')"};
    if(!query.exec(update.arg(status).arg(returnDate).arg(note).arg(bookID.toInt()).arg(memberID.toInt())))
        qDebug() << "cannot update bookStatus";
    else
        QMessageBox::information(this, "SUCCESS", "Book status updated successfully");

    //updtae the table view
    QString select{"SELECT * FROM bookStatus"};
    if(!query.exec(select))
        qDebug() << "Cannot select from bookStatus";
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(query);
    ui->tableView->setModel(model);
}

void ReturnBook::on_deleteBtn_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    QString bookID = ui->bookID->text();
    QString memberID = ui->memberID->text();

    auto query = QSqlQuery(db);
    QString del{"DELETE FROM bookStatus WHERE (Book = '%1' AND Member = '%2')"};
    if(!query.exec(del.arg(bookID.toInt()).arg(memberID.toInt())))
        qDebug() << "cannot delete from bookStatus";
    else
        QMessageBox::information(this, "SUCCESS", "Book deleted successfully");

    //updtae the table view
    QString select{"SELECT * FROM bookStatus"};
    if(!query.exec(select))
        qDebug() << "Cannot select from bookStatus";
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(query);
    ui->tableView->setModel(model);

}

void ReturnBook::on_bookStatus_currentIndexChanged(int index)
{
    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(index == 0)
    {
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM bookStatus"};
        if(!query.exec(select))
            qDebug() << "Cannot select from bookStatus";
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
    else if(index == 1)
    {
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM bookStatus WHERE Status = '%1'"};
        if(!query.exec(select.arg("Issued")))
            qDebug() << "Cannot select from bookStatus";
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
    else if(index == 2)
    {
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM bookStatus WHERE Status = '%1'"};
        if(!query.exec(select.arg("Returned")))
            qDebug() << "Cannot select from bookStatus";
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
    else
    {
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM bookStatus WHERE Status = '%1'"};
        if(!query.exec(select.arg("Lost")))
            qDebug() << "Cannot select from bookStatus";
        QSqlQueryModel * model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
}
```

## Video
https://user-images.githubusercontent.com/74473164/152719709-86fcbc21-20e1-4d12-89df-90619ef137b9.mp4




## Conclusion
Here, we have come to the end of the project Library Management system. It was a great opportunity for us to develop our skills in designing GUI and developing its backends using variety of tools that are provided by Qt Library. We tried our best to include all the necessary points that are required related to the given project. We do hope that our project will be interesting and may be even knowledgeable.
For us  no single  project should be considered as a complete  project  forever because our mind is always thinking somthing new  and the requirement
of users, should be change over the time .We always want something more than what we have.

### Future Enhacements
* Allow management of multiple admin accounts on the same database using advanced database table with foreign Keys.
* Manage the number of issuance a member can make.
* Mutli-services platform
   * Allow members to access their accounts.
   * Allow authors to access their accounts.
* Combine editing books and editing members to provide more features.















