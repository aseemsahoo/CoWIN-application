#include <QDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include "ui_UserDialog1.h"
#include "UserDialog1.h"
#include "user.h"
#include "Login.h"

UserDialog1::UserDialog1(QWidget *parent) : QDialog(parent),ui(new Ui::UserDialog1)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());        // set current date

    QPixmap pic1(":/img/header.jpg");                   // set the path of image
    ui->label_chooseVaccine->setPixmap(pic1);
    ui->label_chooseVaccine->setScaledContents( true );
    ui->label_chooseVaccine->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    Login conn;
    if(!conn.connOpen())
    {
        ui->label_userP1->setStyleSheet("color: red");
        ui->label_userP1->setText("Status: Failed to open the database!");
        qDebug()<<"The database NOT connected with UserDialog1 page.";
    }
    else
    {
        ui->label_userP1->setStyleSheet("color: green");
        ui->label_userP1->setText("Status: Connected database........");
        qDebug()<<"The database connected with UserDialog1 page.";
    }
}

UserDialog1::~UserDialog1(){
    delete ui;
}

// load information of logged in user (if any)
void UserDialog1::on_pushButton_userLoadData_clicked()
{
    Login conn;
    if(!conn.connOpen())
    {
        qDebug() <<"Failed to open the database";
        return;
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
            ui->lineEdit_aadhaar->setText(query.value(2).toString());
            ui->lineEdit_fName->setText(query.value(3).toString());
            ui->lineEdit_lName->setText(query.value(4).toString());
            QString age_info = query.value(5).toString();
            QString vaccine_info = query.value(6).toString();
            QString dose_info = query.value(7).toString();
            QString date_info = query.value(8).toString();
            QString time_info = query.value(9).toString();

            if(age_info != "NULL")
            {
                if(age_info == "Under 18")
                    ui->radioButton_under18->setChecked(true);
                if(age_info == "Between 18~45")
                    ui->radioButton_over18->setChecked(true);
                if(age_info == "Over 45")
                    ui->radioButton_over45->setChecked(true);
                age = age_info;
            }
            if(vaccine_info != "NULL")
            {
                if(vaccine_info == "Covishield")
                    ui->radioButton_Covishield->setChecked(true);
                if(vaccine_info == "Covaxin")
                    ui->radioButton_Covaxin->setChecked(true);
                if(vaccine_info == "Sputnik-V")
                    ui->radioButton_SputnikV->setChecked(true);
                vaccine = vaccine_info;
            }
            if(dose_info != "NULL")
            {
                if(dose_info == "First dose")
                    ui->radioButton_firstDose->setChecked(true);
                if(dose_info == "Second dose")
                    ui->radioButton_secondDose->setChecked(true);
                dose = dose_info;
            }
            if(date_info != "")
                ui->dateEdit->setDate(QDate::fromString(date_info,"dd-MMM-yyyy"));        // set user date (if any)
            if(time_info != "")
                ui->comboBox_hours->setCurrentText(time_info);

            ui->label_userP1->setStyleSheet("color: green");
            ui->label_userP1->setText("Status: Data uploaded.");
        }
    }
    else
    {
        ui->label_userP1->setStyleSheet("color: red");
        ui->label_userP1->setText("Status: Data could not be uploaded.");
        QMessageBox::critical(this,tr("Error"),query.lastError().text());
    }
    conn.connClose();
}

void UserDialog1::on_pushButton_userSubmit_clicked()
{
    User user;

    user.setUsername(user_name);
    user.setPassword(pw);
    user.setAadhaar(ui->lineEdit_aadhaar->text());
    user.setFirstName(ui->lineEdit_fName->text());
    user.setLastName(ui->lineEdit_lName->text());
    user.setAge(age);
    user.setVaccine(vaccine);
    user.setDose(dose);
    user.setDate(ui->dateEdit->text());
    user.setTime(ui->comboBox_hours->currentText());

    if(user.getAadhaar().length() != 12)
    {
        QMessageBox::warning(this,tr("Error"),tr("Aadhaar number must be of 12 digits."));
        return ;
    }
    Login conn;
    if(!conn.connOpen())
    {
        qDebug() <<"Failed to open the database";
        return ;
    }
    QSqlQuery query;

    query.prepare("UPDATE userInfo "
                  "SET username=?,password=?,aadhaar=?,firstName=?,lastName=?,age=?,vaccine=?,dose=?,date=?,time=? "
                  "WHERE username = ?");
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

    if(query.exec())
        QMessageBox::information(this,tr("Save"),tr("Your data has been saved. Thank you."));
    else
        QMessageBox::critical(this,tr("Error"),query.lastError().text());

    window()->hide();  // close this window after successful submission

    qDebug()<< user.getUsername() + " saved infomation. ";
    conn.connClose();
}

// for Radio Button, choose one of the vaccines;
void UserDialog1::on_radioButton_Covishield_clicked(){
    vaccine = "Covishield";
}
void UserDialog1::on_radioButton_Covaxin_clicked(){
    vaccine = "Covaxin";
}
void UserDialog1::on_radioButton_SputnikV_clicked(){
    vaccine = "Sputnik-V";
}

// for Radio Button, choose the age range
void UserDialog1::on_radioButton_under18_clicked(){
    age = "Under 18";
}
void UserDialog1::on_radioButton_over18_clicked(){
    age = "Between 18~45";
}
void UserDialog1::on_radioButton_over45_clicked(){
    age = "Over 45";
}

// for Radio Button, choose dose, first or second dose
void UserDialog1::on_radioButton_firstDose_clicked(){
    dose = "First dose";
}
void UserDialog1::on_radioButton_secondDose_clicked(){
    dose = "Second dose";
}
