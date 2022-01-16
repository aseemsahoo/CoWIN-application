#ifndef USERDIALOG1_H
#define USERDIALOG1_H

#include <QDialog>

namespace Ui {
class UserDialog1;
}

class UserDialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog1(QWidget *parent = nullptr);    // explicit keyword is used to avoid implicit type conversion
    ~UserDialog1();

    QString user_name, pw;               // make sure the logged in user edits their own information

    QString age, vaccine, dose, date;    // variables for saving the data input;


private slots:
    void on_pushButton_userLoadData_clicked();
    void on_pushButton_userSubmit_clicked();

    void on_radioButton_Covishield_clicked();
    void on_radioButton_Covaxin_clicked();
    void on_radioButton_SputnikV_clicked();

    void on_radioButton_under18_clicked();
    void on_radioButton_over18_clicked();
    void on_radioButton_over45_clicked();

    void on_radioButton_firstDose_clicked();
    void on_radioButton_secondDose_clicked();

private:
    Ui::UserDialog1 *ui;
};

#endif // USERDIALOG1_H
