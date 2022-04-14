#include "employee.h"

namespace Data {
Employee_D::Employee_D(QObject *parent) : QObject(parent)
{

}
Employee_D::Employee_D(int id, QString _FName, QString _LName, QString _Email, QString _Phone, QString _Gender, QString _Username, QString _PAssword, QString _Role):
       id(id),_FName(_FName),_LName(_LName),_Email(_Email),_Phone(_Phone),_Gender(_Gender),_Username(_Username),_PAssword(_PAssword),_Role(_Role)
{

}

QString Employee_D::FName() const
{
    return _FName;
}

void Employee_D::setFName(const QString &FName)
{
    _FName = FName;
}

QString Employee_D::LName() const
{
    return _LName;
}

void Employee_D::setLName(const QString &LName)
{
    _LName = LName;
}

QString Employee_D::Email() const
{
    return _Email;
}

void Employee_D::setEmail(const QString &Email)
{
    _Email = Email;
}

QString Employee_D::Phone() const
{
    return _Phone;
}

void Employee_D::setPhone(const QString &Phone)
{
    _Phone = Phone;
}

QString Employee_D::Gender() const
{
    return _Gender;
}

void Employee_D::setGender(const QString &Gender)
{
    _Gender = Gender;
}

QString Employee_D::Username() const
{
    return _Username;
}

void Employee_D::setUsername(const QString &Username)
{
    _Username = Username;
}

QString Employee_D::PAssword() const
{
    return _PAssword;
}

void Employee_D::setPAssword(const QString &PAssword)
{
    _PAssword = PAssword;
}

QString Employee_D::Role() const
{
    return _Role;
}

void Employee_D::setRole(const QString &Role)
{
    _Role = Role;
}

int Employee_D::getId() const
{
    return id;
}

void Employee_D::setId(int value)
{
    id = value;
}
}
