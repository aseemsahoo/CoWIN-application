#pragma once

#ifndef USER_H
#define USER_H
#include <iostream>
#include <QString>
using namespace std;

class User
{
private:
    QString username,password,aadhaar,firstName,lastName,age,vaccine,dose,date,time;

public:
    // constructor
    User();

    // ******* Mutators
    void setUsername(QString un);
    void setPassword(QString pw);
    void setAadhaar(QString aadhaar);
    void setFirstName(QString fn);
    void setLastName(QString ln);
    void setAge(QString age);
    void setVaccine(QString vacc);
    void setDose(QString dose);
    void setDate(QString date);
    void setTime(QString time);

    // ********* Accessors
    QString getUsername(){      return username;  };
    QString getPassword(){      return password;  };
    QString getAadhaar(){       return aadhaar;  };
    QString getFirstName(){     return firstName;  };
    QString getLastName(){      return lastName;  };
    QString getAge(){           return age;  };
    QString getVaccine(){       return vaccine;  };
    QString getdose(){          return dose;  };
    QString getDate(){          return date;  };
    QString getTime(){          return time;  };
};

#endif // USER_H
