#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "UserDialog1.h"
#include "AdminDialog1.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;      // create database object
    bool connOpen();
    void connClose();

    explicit Login(QWidget *parent = nullptr);  // explicit keyword is used to avoid implicit type conversion.
    ~Login();

private slots:
    void on_pushButton_userLogin_clicked();
    void on_pushButton_adminLogin_clicked();
    void on_pushButton_userRegister_clicked();
    void on_pushButton_adminRegister_clicked();
    void on_pushButton_loginQuit_clicked();

private:
    Ui::Login *ui;
    UserDialog1 *userP1;            // use pointers, so it will work in heap memory
    AdminDialog1 *adminP1;
};
#endif // LOGIN_H
