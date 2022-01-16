#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QException>
#include "user.h"
#include "user.cpp"
#include "Login.h"
#include "ui_Login.h"
#include "UserDialog1.h"

Login::Login(QWidget *parent): QMainWindow(parent), ui(new Ui::Login)
{
    QSqlDatabase mydb;                                  // create database object
    ui->setupUi(this);
    if(!connOpen())
    {
        ui->label->setStyleSheet("color: red");
        ui->label->setText("Status: Failed to open the database!");
        qDebug()<<"The database Not connected ";
    }
    else
    {
        ui->label->setStyleSheet("color: green");
        ui->label->setText("Status: Connected database........");
        qDebug()<<"The database connected ";
    }
}

Login::~Login(){
    delete ui;
}

// close down connection to database
void Login::connClose()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

// check connection to database
bool Login::connOpen()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Database/mydb.db");        // provide the path to database
    if(!mydb.open())
    {
        qDebug()<<("Failed to open the database!");
        return false;
    }
    else
    {
        qDebug()<<("Connected database........");
        return true;
    }
}

// for action "admin register" .... (admin_username, admin_password, admin_work_ID)
void Login::on_pushButton_adminRegister_clicked()
{
    Login conn;
    QString adminUsername, adminPassword, adminWorkID;

    adminUsername = ui->lineEdit_adminUsername->text();
    adminPassword = ui->lineEdit_adminPW->text();
    adminWorkID = ui->lineEdit_adminWorkID->text();

    if(!connOpen())
    {
        qDebug() <<"Failed to open the database";
        return;
    }

    QSqlQuery query;

    query.prepare("INSERT into admin (admin_username,admin_password,admin_work_ID)"
                  "VALUES (?, ?, ?)");
    query.addBindValue(adminUsername);
    query.addBindValue(adminPassword);
    query.addBindValue(adminWorkID);
    qDebug()<<query.executedQuery();

    if(query.exec())
        QMessageBox::information(this,tr("Save"),tr("Admin Data Saved!"));
    else
        QMessageBox::critical(this,tr("Error"),query.lastError().text());
    conn.connClose();
}

// for action "admin login", where we select the 3 columns from database
void Login::on_pushButton_adminLogin_clicked()
{
    //.........................................................Exception.....................................//
    try
    {
        // login and get the username and password from user input.
        QString adminUsername = ui ->lineEdit_adminUsername->text();
        QString adminPassword = ui->lineEdit_adminPW->text();
        QString adminWorkID = ui->lineEdit_adminWorkID->text();
        connOpen();
        QSqlQuery query;

        query.prepare("SELECT * from admin "
                      "WHERE admin_username=? AND admin_password = ? AND admin_work_ID = ?");
        query.addBindValue(adminUsername);
        query.addBindValue(adminPassword);
        query.addBindValue(adminWorkID);

        if(query.exec())
        {
            int count = 0;
            while(query.next())
                count++;
            if(count==1)
            {
                this->hide();       // hide this login window, to prevent memory leak
                adminP1 = new AdminDialog1(this);
                adminP1->show();
            }
            else
                throw("Error");
            connClose();
        }
    }
    catch (...)
    {
        ui->label->setStyleSheet("color: red");
        ui->label ->setText("Oops, Username, password or Work ID is NOT correct.");
        qDebug() << "Catch Error： Username, password or Work ID is NOT correct. ";
    }
}

// for action  user register select 2 columns
void Login::on_pushButton_userRegister_clicked()
{
    Login conn;
    User currUser;
    currUser.setUsername(ui->lineEdit_userUsername->text());
    currUser.setPassword(ui->lineEdit_userPW->text());

    if(!connOpen())
    {
        qDebug() <<"Failed to open the database";
        return;
    }
    QSqlQuery query;

    query.prepare("INSERT into userInfo (username,password) "
                  "VALUES (?, ?)" );
    query.addBindValue(currUser.getUsername());
    query.addBindValue(currUser.getPassword());

    if(query.exec())
    {
        ui->label->setStyleSheet("color: green");
        ui->label ->setText("User registered.");
        QMessageBox::information(this,tr("Save"),tr("User Data Saved!"));
    }
    else
    {
        ui->label->setStyleSheet("color: red");
        ui->label ->setText("Error:" + query.lastError().text());
        QMessageBox::critical(this,tr("Error"),query.lastError().text());
    }
    conn.connClose();
}

// for action "user login", we select 2 columns
void Login::on_pushButton_userLogin_clicked()
{
    //.........................................................Exception.....................................//
    try
    {
        QString userUsername = ui ->lineEdit_userUsername->text();     // login and get the text of username and password form user input.
        QString userPassword = ui->lineEdit_userPW->text();
        connOpen();                                                    // open the database function, there are debugs in the function.
        QSqlQuery query;

        query.prepare("SELECT * from userInfo "
                      "WHERE username=? AND password = ?" );
        query.addBindValue(userUsername);
        query.addBindValue(userPassword);

        if(query.exec())
        {
            int count = 0;
            while(query.next())
                count++;
            if(count == 1)
            {
                ui->label->setStyleSheet("color: green");
                ui->label ->setText("Username and password is correct.");

                this->hide();                           // hide this login window,
                userP1 = new UserDialog1(this);         // to prevent memory leak
                userP1->user_name = userUsername;       // get username and password
                userP1->pw = userPassword;              // so we can load user information

                qDebug() << userP1->user_name + " has logged in";
                userP1->show();
            }
            else
                throw("Error");
            connClose();
        }
    }
    catch (...)
    {
        ui->label->setStyleSheet("color: red");
        ui->label ->setText("Oops, Username or password is NOT correct.");
        qDebug() << "Catch Error： Username or password is NOT correct. ";
    }
}

// for quit button
void Login::on_pushButton_loginQuit_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"My Title","Are you sure to quit the login page? ", QMessageBox::Yes| QMessageBox::No);
    if(reply == QMessageBox::Yes)
        QApplication::quit();
}
