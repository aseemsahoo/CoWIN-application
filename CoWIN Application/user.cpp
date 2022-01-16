#include <iostream>
#include <QString>
#include "user.h"
#include "Login.h"
using namespace std;

// Default constructor
User::User()
{
    QString username = NULL,
            password = NULL,
            aadhaar = NULL,
            firstName = NULL,
            lastName = NULL,
            age = NULL,
            vaccine = NULL,
            dose = NULL,
            date = NULL,
            time = NULL;
}

// ******* Mutators
void User::setUsername(QString un){
    username = un;
}
void User::setPassword(QString pw){
    password = pw;
}
void User::setAadhaar(QString adhr){
    aadhaar = adhr;
}
void User::setFirstName(QString fn){
    firstName = fn;
}
void User::setLastName(QString ln){
    lastName = ln;
}
void User::setAge(QString a){
    age = a;
}
void User::setVaccine(QString vacc){
    vaccine = vacc;
}
void User::setDose(QString ds){
    dose = ds;
}
void User::setDate(QString dt){
    date = dt;
}
void User::setTime(QString t){
    time = t;
}
