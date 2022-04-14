#include "expenses.h"

namespace Data {


Expenses::Expenses(QObject *parent) : QObject(parent)
{

}

Expenses::Expenses(QDate _Date, QString _Description, float _Amount, QString _UID, QString _Employee):
    _Date(_Date),_Description(_Description),_Amount(_Amount),_UID(_UID),_Employee(_Employee)
{

}

QDate Expenses::Date() const
{
    return _Date;
}

void Expenses::setDate(const QDate &Date)
{
    _Date = Date;
}

QString Expenses::Description() const
{
    return _Description;
}

void Expenses::setDescription(const QString &Description)
{
    _Description = Description;
}

float Expenses::Amount() const
{
    return _Amount;
}

void Expenses::setAmount(float Amount)
{
    _Amount = Amount;
}

QString Expenses::UID() const
{
    return _UID;
}

void Expenses::setUID(const QString &UID)
{
    _UID = UID;
}

QString Expenses::Employee() const
{
    return _Employee;
}

void Expenses::setEmployee(const QString &Employee)
{
    _Employee = Employee;
}
}
