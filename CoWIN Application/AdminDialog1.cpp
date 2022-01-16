#include <QString>
#include <QMessageBox>
#include <QPixmap>
#include <QTableView>
#include <QListView>
#include <QLineEdit>
#include <QSqlTableModel>
#include <QComboBox>
#include "user.h"
#include "AdminDialog1.h"
#include "ui_AdminDialog1.h"
#include "Login.h"

AdminDialog1::AdminDialog1(QWidget *parent) : QDialog(parent), ui(new Ui::AdminDialog1){
    ui->setupUi(this);
}

AdminDialog1::~AdminDialog1(){
    delete ui;
}

// load user table from SQL database
void AdminDialog1::on_pushButton_loadInfo_clicked()
{
    Login conn;
    conn.connOpen();

    QSqlQueryModel * model = new QSqlQueryModel();      // create model, data source will be SQL database
    model->setQuery("SELECT * from userInfo");          // The QSqlQueryModel class provides a
                                                        // read-only data model for SQL result sets
    ui->listView->setModel(model);
    ui->comboBox->setModel(model);
    ui->tableView->setModel(model);

    conn.connClose();
}

// Link QComboBox with SQL Database values
void AdminDialog1::on_comboBox_activated(int index)
{
    (void) index;
    QString user_name = ui->comboBox->currentText();
    Login conn;
    if(!conn.connOpen())
    {
        qDebug() <<"Failed to open the database";
        return ;
    }
    QSqlQuery query;

    query.prepare("SELECT * from userInfo "
                  "WHERE username = ?");
    query.addBindValue(user_name);
    qDebug()<<query.executedQuery();

    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_username->setText(query.value(0).toString());
            ui->lineEdit_pw->setText(query.value(1).toString());
            ui->lineEdit_aadhaar->setText(query.value(2).toString());
            ui->lineEdit_fName->setText(query.value(3).toString());
            ui->lineEdit_lName->setText(query.value(4).toString());
            ui->lineEdit_age->setText(query.value(5).toString());
            ui->lineEdit_vaccine->setText(query.value(6).toString());
            ui->lineEdit_dose->setText(query.value(7).toString());
            ui->lineEdit_date->setText(query.value(8).toString());
            ui->lineEdit_time->setText(query.value(9).toString());
        }
    }
    else
        QMessageBox::critical(this,tr("Error"),query.lastError().text());
    conn.connClose();
}

// set text on all the line edits
void AdminDialog1::set_LineEdit_text(const QModelIndex &index)
{
    int row = index.row();              // get corresponding row of SQL database

    ui->lineEdit_username->setText(index.sibling(row, 0).data().toString());
    ui->lineEdit_pw->setText(index.sibling(row, 1).data().toString());
    ui->lineEdit_aadhaar->setText(index.sibling(row, 2).data().toString());
    ui->lineEdit_fName->setText(index.sibling(row, 3).data().toString());
    ui->lineEdit_lName->setText(index.sibling(row, 4).data().toString());
    ui->lineEdit_age->setText(index.sibling(row, 5).data().toString());
    ui->lineEdit_vaccine->setText(index.sibling(row, 6).data().toString());
    ui->lineEdit_dose->setText(index.sibling(row, 7).data().toString());
    ui->lineEdit_date->setText(index.sibling(row, 8).data().toString());
    ui->lineEdit_time->setText(index.sibling(row, 9).data().toString());

}
// Link QTableView with SQL Database values
void AdminDialog1::on_tableView_activated(const QModelIndex &index)
{
    set_LineEdit_text(index);
}

// Link QListView with SQL Database values
void AdminDialog1::on_listView_activated(const QModelIndex &index)
{
    set_LineEdit_text(index);
}

// get texts from all the line edits for 'save' or 'update'
void AdminDialog1::get_LineEdit_text(User &user)
{
    user.setUsername(ui->lineEdit_username->text());
    user.setPassword(ui->lineEdit_pw->text());
    user.setAadhaar(ui->lineEdit_aadhaar->text());
    user.setFirstName(ui->lineEdit_fName->text());
    user.setLastName(ui->lineEdit_lName->text());
    user.setAge(ui->lineEdit_age->text());
    user.setVaccine(ui->lineEdit_vaccine->text());
    user.setDose(ui->lineEdit_dose->text());
    user.setDate(ui->lineEdit_date->text());
    user.setTime(ui->lineEdit_time->text());
}
void AdminDialog1::on_pushButton_save_clicked()     // insert
{
    Login conn;
    if(!conn.connOpen())
    {
        qDebug() <<"Failed to open the database";
        return;
    }
    User user;
    get_LineEdit_text(user);

    QSqlQuery query;

    query.prepare("INSERT into userInfo"
                  "(username,password,aadhaar,firstName,lastName,age,vaccine,dose,date,time)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(user.getUsername());
    query.addBindValue(user.getPassword());
    query.addBindValue(user.getAadhaar());
    query.addBindValue(user.getFirstName());
    query.addBindValue(user.getLastName());
    query.addBindValue(user.getAge());
    query.addBindValue(user.getVaccine());
    query.addBindValue(user.getdose());
    query.addBindValue(user.getDate());
    query.addBindValue(user.getTime());

    qDebug()<<query.executedQuery();

    if(query.exec())
        QMessageBox::information(this,tr("Save"),tr("Data Saved!"));
    else
        QMessageBox::critical(this,tr("Error"),query.lastError().text());
    conn.connClose();
    qDebug()<< user.getUsername() + " saved his/her infomation. ";
}

// update
void AdminDialog1::on_pushButton_update_clicked()
{
    Login conn;
    if(!conn.connOpen())
    {
        qDebug() <<"Failed to open the database";
        return;
    }

    User user;
    get_LineEdit_text(user);

    QSqlQuery query;

    query.prepare("UPDATE userInfo "
                  "SET username=?, password=?, aadhaar=?, firstName=?, lastName=?, age=?, vaccine=?, dose=?, date=?, time=? "
                  "WHERE username = ?" );
    query.addBindValue(user.getUsername());
    query.addBindValue(user.getPassword());
    query.addBindValue(user.getAadhaar());
    query.addBindValue(user.getFirstName());
    query.addBindValue(user.getLastName());
    query.addBindValue(user.getAge());
    query.addBindValue(user.getVaccine());
    query.addBindValue(user.getdose());
    query.addBindValue(user.getDate());
    query.addBindValue(user.getTime());
    query.addBindValue(user.getUsername());

    qDebug()<<query.executedQuery();

    if(query.exec())
        QMessageBox::information(this,tr("Edit"),tr("Data Updated!"));
    else
        QMessageBox::critical(this,tr("Error"),query.lastError().text());
    conn.connClose();
    qDebug()<< user.getUsername() + " Updated infomation.";
}

// delete
void AdminDialog1::on_pushButton_delete_clicked()
{
    Login conn;
    //only need a unique variable, find whole row and delete
    QString username = ui->lineEdit_username->text();

    if(!conn.connOpen())
    {
        qDebug() <<"Failed to open the database";
        return;
    }
    QSqlQuery query;

    query.prepare("DELETE from userInfo "
                  "WHERE username=?");
    query.addBindValue(username);

    qDebug()<<query.executedQuery();

    if(query.exec())
        QMessageBox::information(this,tr("Delete"),tr("Data Deleted!"));
    else
        QMessageBox::critical(this,tr("Error"),query.lastError().text());
    conn.connClose();
    qDebug()<< username + " deleted infomation.";
}

void AdminDialog1::on_pushButton_quit_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"My Title", "Do you want to quit the Admin page?", QMessageBox::Yes| QMessageBox::No);
    if(reply == QMessageBox::Yes)
        QApplication::quit();
}
