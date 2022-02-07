<h1 align="center">Library Management System</h1> 

<p align="center">
  <img align="center" width="60%" height="50%" src="https://user-images.githubusercontent.com/72691265/152707716-39e6702d-b583-4b7b-8339-c2da22c654c8.png"/>
</p>

## Table of content 
  * [Introduction](#introduction)
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
  * [Conclusion](#conclusion)


## Introduction
Library Management system is an application that refers to library systems which are generally small or medium in size. It is used by librarian to manage the library using a computerized system where he/she can record various transactions like issue of books, return of books, addition of new books, addition of new students etc.
Books and students maintenance modules are also included in this system which would keep track of the students using the library and also a detailed description about the books a library contains. With this computerized system there will be no loss of book record or member record which generally happens when a non-computerized system is used.
All these modules are able to help librarian to manage the library with more convenience and in a more efficient way as compared to library systems which are not computerized. </br>

## Features
This project aims to achieve the following features:
* Easily manage the complete management of the library through the graphical user interface.
* Removes manual process of issuing books and simplifies the way of issuing book to save time and effort.
* Can manage genres
* Manage authors
* Books Management
* Update the details when the student returns the book
* Search student by using their student ID
* View student details </br>
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
and if invalid username or password is there user is not allowed to enter the system. </br>


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
</p> </br>
This feature can be performed by all users to register new user to create account.

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
</p> </br>
This feature allows users to update their passwords. </br>
```newpasswd.cpp```
``` cpp
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
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152711598-e42f9220-ce50-46a9-a705-b72cd3b34cb4.png"/>
</p> </br>
In order not to limit the genres books at the level of choosing the book's category, this feature allows librarians to manage available genres (adding, editing, deleting)</br>
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
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152712241-b7996645-94a4-4f43-b838-13a5d4892e60.png"/>
</p> </br>
This  feature allows admin to add, edit and delete a authors. </br>

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
</p> </br>

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
</p> </br>

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
</p> </br>

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
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152713200-cb750d6c-0a6c-4ca2-8717-fa2ff5bb4e94.png"/>
</p> </br>

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
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152713397-751335f0-367e-448f-a4c8-d87480646540.png"/>
</p> </br>

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
  <img align="center" width="40%" height="40%" src="https://user-images.githubusercontent.com/72691265/152713652-6496ec47-4602-43a8-ab39-4e41560bdd63.png"/>
</p> </br>

```addBook.cpp```
```cpp

```













